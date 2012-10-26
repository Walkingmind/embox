/**
 * @file
 * @brief SNTPv4 implementation over IPv4
 *
 * @date 13.07.2012
 * @author Alexander Kalmuk
 */

#include <net/skbuff.h>
#include <net/inet_sock.h>
#include <net/udp.h>
#include <net/ip.h>
#include <net/ntp.h>
#include <kernel/time/time.h>
#include <kernel/time/timer.h>
#include <errno.h>
#include <string.h>
#include <prom/prom_printf.h>
#include <unistd.h>
#include <math.h>

#define MIN_POLL 3 /* By RFC 4330 minimum poll interval is about 15 seconds */
#define MAX_POLL 16

static char kod[3][4] = {"DENY", "RSTR", "RATE"};

/* Config witch we use as server */
static struct ntphdr server_config;
/* Config witch we use as client */
static struct ntphdr client_config = {
		.status = NTP_LI_NO_WARNING | NTP_V_4 | NTP_CLIENT
};
/* Socket binded to port 123 */
static int ntp_sock;
/* Current server address for unicast interaction */
static struct sockaddr_in available_server;
/* Periodical timer for sending new request each tick */
static sys_timer_t *ntp_poll_timer;
/* Check for availability(reply) of server */
static bool is_server_reply = false;
static bool ntp_in_use = false;

static inline void ntp_data_ntohs(struct s_ntpdata *data) {
	data->sec = ntohs(data->sec);
	data->fraction = ntohs(data->fraction);
}

static inline void ntp_data_ntohl(struct l_ntpdata *data) {
	data->sec = ntohl(data->sec);
	data->fraction = ntohl(data->fraction);
}

static void ntp_ntoh(struct ntphdr *ntp) {
	ntp->refid = ntohl(ntp->refid);
	ntp_data_ntohs(&ntp->rootdelay);
	ntp_data_ntohs(&ntp->rootdisp);
	ntp_data_ntohl(&ntp->org_ts);
	ntp_data_ntohl(&ntp->rec_ts);
	ntp_data_ntohl(&ntp->ref_ts);
	ntp_data_ntohl(&ntp->xmt_ts);
}

static inline bool is_ntp_sock(struct sock *sk) {
	return (inet_sk(sk)->sport == htons(NTP_SERVER_PORT) ? true : false);
}

void ntp_server_set(uint32_t s_addr) {
	available_server.sin_addr.s_addr = s_addr;
}

int ntp_client_xmit(int sock, struct sockaddr_in *dst) {
	struct timespec ts;
	struct ntphdr x;

	x.status = client_config.status;
	x.poll = client_config.poll;

	gettimeofday(&ts, NULL);
	x.xmt_ts = timespec_to_ntp(ts);

	ntp_ntoh(&x);

	return sendto(sock, (void*) &x, sizeof(x), 0, (struct sockaddr *)dst, sizeof(*dst));
}

/* Reply to client with ntp_config last configuration */
static int ntp_server_reply(struct ntphdr *r, struct timespec rec, struct sockaddr_in *dst) {
	struct ntphdr x;
	struct timespec ts;

	x.status = get_leap(&server_config);
	x.status |= get_version(r);
	x.status |= NTP_SERVER; /* get_mode(&ntp_config); */

	if (server_config.stratum > NTP_SERVER_UNSYNC)
		x.stratum = 0;
	else
		x.stratum = server_config.stratum;

	x.poll = max(r->poll, MIN_POLL);
	/* TODO take into account our system clock source precision. */
	x.precision = server_config.precision;
	x.refid = server_config.refid;
	x.ref_ts = server_config.ref_ts;
	x.org_ts = r->xmt_ts;
	x.rec_ts = timespec_to_ntp(rec);
	gettimeofday(&ts, NULL);
	x.xmt_ts = timespec_to_ntp(ts);

	ntp_ntoh(&x);

	return sendto(ntp_sock, (void*) &x, sizeof(x), 0, (struct sockaddr *)dst, sizeof(*dst));
}

int ntp_receive(struct sock *sk, struct sk_buff *skb) {
	struct ntphdr *r;
	int mode, res = NET_RX_DROP;
	struct timespec ts;
	iphdr_t *iph = ip_hdr(skb);
	udphdr_t *udph = udp_hdr(skb);
	struct inet_sock *inet = inet_sk(sk);

	gettimeofday(&ts, NULL);

	/* check for NTP packet */
	if (ntohs(inet->sport) != NTP_SERVER_PORT &&
			ntohs(udph->source) != NTP_SERVER_PORT)
		goto free_and_drop;

	r = (struct ntphdr*)(skb->h.raw + UDP_HEADER_SIZE);

	ntp_ntoh(r);

	/* check if it is client packet */
	if ((mode = get_mode(r)) == NTP_CLIENT || mode == NTP_BROADCAST_CLIENT) {
		struct sockaddr_in dst;
		dst.sin_port = udph->source;
		dst.sin_addr.s_addr = iph->saddr;
		ntp_server_reply(r, ts, &dst);
		return ENOERR;
	}

	/* no, it is server reply. Process it below */

	if (r->stratum >= NTP_SERVER_UNSYNC ||
			(mode != NTP_SERVER && mode != NTP_BROADCAST))
		goto free_and_drop;

	/* check for server KoD */
	if (r->stratum == 0) {
		if (strcmp((char *)&r->refid, kod[2])) {
			if (client_config.poll > MIN_POLL)
				client_config.poll--;
			else
				available_server.sin_addr.s_addr = 0;
		} else if (strcmp((char *)&r->refid, kod[0]) ||
				strcmp((char *)&r->refid, kod[1])) {
			available_server.sin_addr.s_addr = 0;
		}

		res = NET_RX_DROP;
		goto free_and_drop;
	}

	if (is_ntp_sock(sk)) {
		/* set system time */
		ts = ntp_to_timespec(r->xmt_ts);
		ts = timespec_add(ts, ntp_delay(r));
		settimeofday(&ts, NULL);

		/* set server and ntp_config if now no server specified */
		if (available_server.sin_addr.s_addr == 0) {
			available_server.sin_addr.s_addr = iph->saddr;
			/* XXX ntp_config.stratum++ */
			memcpy(&server_config, r, sizeof(struct ntphdr));
		}

		/* update reply statstic */
		if (available_server.sin_addr.s_addr == iph->saddr)
			is_server_reply = true;

		/* update Reference Timestamp */
		server_config.ref_ts = timespec_to_ntp(ts);
		/* update poll interval. It is different from our request if server reply is broadcast. */
		client_config.poll = r->poll;
	}

	return ENOERR;
	/* TODO check Key Identifier (optional) */
free_and_drop:
	skb_free(skb);
	return -res;
}

struct timespec ntp_delay(struct ntphdr *ntp) {
	struct timespec client_r, server_x, server_r, client_x, res;

	gettimeofday(&client_r, NULL);
	client_x = ntp_to_timespec(ntp->org_ts);
	server_x = ntp_to_timespec(ntp->xmt_ts);
	server_r = ntp_to_timespec(ntp->rec_ts);

	res = timespec_sub(client_r, client_x);
	res = timespec_sub(res, timespec_sub(server_x, server_r));

	res.tv_sec /= 2;
	res.tv_nsec /= 2;
	return res;
}

struct timespec ntp_offset(struct ntphdr *ntp) {
	struct timespec client_r, server_x, server_r, client_x, res;

	gettimeofday(&client_r, NULL);
	client_x = ntp_to_timespec(ntp->org_ts);
	server_x = ntp_to_timespec(ntp->xmt_ts);
	server_r = ntp_to_timespec(ntp->rec_ts);

	res = timespec_sub(server_r, client_x);
	res = timespec_add(res, timespec_sub(server_x, client_r));

	res.tv_sec /= 2;
	res.tv_nsec /= 2;
	return res;
}

/* Send request to avaliable_server on each ntp_poll_timer reload */
static void send_request(struct sys_timer *timer, void *param) {
	if (available_server.sin_addr.s_addr) {
		/* if no reply from server, then increase polling interval */
		if (!is_server_reply && client_config.poll < MAX_POLL) {
			client_config.poll++;
			timer_close(ntp_poll_timer);
			timer_set(&ntp_poll_timer, TIMER_PERIODIC, (1 << client_config.poll) * MSEC_PER_SEC,
						send_request, NULL);
		}

		is_server_reply = false;
		ntp_client_xmit(ntp_sock, &available_server);
	}
}

int ntp_start(void) {
	struct sockaddr_in our;

	if (ntp_in_use)
		return -EBUSY;

	available_server.sin_port = htons((__u16)NTP_SERVER_PORT);
	/* set minimum polling interval */
	client_config.poll = MIN_POLL;
	/* our server is unsync now*/
	server_config.stratum = 0;

	if (0 > (ntp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))) {
		prom_printf("Can't to allocate NTP socket");
		return -ENOMEM;
	}

	socket_set_encap_recv(ntp_sock, ntp_receive);

	our.sin_family = AF_INET;
	our.sin_port = htons((__u16)NTP_SERVER_PORT);
	our.sin_addr.s_addr = htonl(INADDR_ANY);

	if (0 > bind(ntp_sock, (struct sockaddr *)&our, sizeof(our))) {
		prom_printf("error at bind()\n");
		return -EBUSY;
	}

	if (0 > timer_set(&ntp_poll_timer, TIMER_PERIODIC, (1 << MIN_POLL) * MSEC_PER_SEC,
			send_request, NULL)) {
		prom_printf("Can't to initialize NTP timer");
		return -ENOENT;
	}

	ntp_in_use = true;

	return ENOERR;
}

int ntp_stop(void) {
	close(ntp_sock);
	timer_close(ntp_poll_timer);
	ntp_in_use = false;

	return ENOERR;
}

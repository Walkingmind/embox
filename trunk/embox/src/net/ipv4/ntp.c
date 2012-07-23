/**
 * @file
 * @brief SNTP implementation over IPv4
 *
 * @date 13.07.2012
 * @author Alexander Kalmuk
 */

#include <net/skbuff.h>
#include <net/inet_sock.h>
#include <net/udp.h>
#include <net/ip.h>
#include <net/ntp.h>
#include <errno.h>
#include <kernel/time/time.h>

static inline void s_data_ntohs(struct s_ntpdata *data) {
	data->sec = ntohs(data->sec);
	data->fraction = ntohs(data->fraction);
}

static inline void l_data_ntohs(struct l_ntpdata *data) {
	data->sec = ntohl(data->sec);
	data->fraction = ntohl(data->fraction);
}

static void ntp_ntoh(struct ntphdr *ntp) {
	ntp->refid = ntohs(ntp->refid);
	s_data_ntohs(&ntp->rootdelay);
	s_data_ntohs(&ntp->rootdisp);
	l_data_ntohs(&ntp->org_ts);
	l_data_ntohs(&ntp->rec_ts);
	l_data_ntohs(&ntp->ref_ts);
	l_data_ntohs(&ntp->xmt_ts);
}

int ntp_client_xmit(int sock, struct sockaddr_in *dst) {
	struct ntphdr x;
	struct timespec ts;

	x.status = NTP_LI_NO_WARNING | NTP_V_4 | NTP_CLIENT;
	gettimeofday(&ts, NULL);
	x.xmt_ts.sec = htonl((ts.tv_sec / 232) * 1000);

	return sendto(sock, (void*) &x, sizeof(x), 0, (struct sockaddr *)dst, sizeof(*dst));
}

int ntp_client_receive(struct sock *sk, struct sk_buff *skb) {
	struct ntphdr *r;
	udphdr_t *udph = udp_hdr(skb);
	iphdr_t *iph = ip_hdr(skb);
	struct inet_sock *inet = inet_sk(sk);

	if (inet->daddr != INADDR_BROADCAST && inet->daddr != iph->saddr)
		goto free_and_drop;

	if (inet->dport != udph->source)
		goto free_and_drop;

	r = (struct ntphdr*)(skb->h.raw + UDP_HEADER_SIZE);

	ntp_ntoh(r);

	if ((r->xmt_ts.sec == 0 && r->xmt_ts.fraction == 0) ||
			r->stratum >= NTP_SERVER_UNSYNC ||
			(get_mode(r) != NTP_BROADCAST && get_mode(r) != NTP_SERVER))
		goto free_and_drop;

	return ENOERR;
	/* TODO check Key Identifier (optional) */
free_and_drop:
	skb_free(skb);
	return -NET_RX_DROP;
}

void ntp_format_to_timespec(struct timespec *ts, struct l_ntpdata ld) {
	ts->tv_sec = ld.sec;
	ts->tv_nsec = (ld.fraction / 1000) * 232;
}

struct timespec ntp_delay(struct ntphdr *ntp) {
	struct timespec client_r, server_x, server_r, client_x, res;

	gettimeofday(&client_r, NULL);
	ntp_format_to_timespec(&client_x, ntp->org_ts);
	ntp_format_to_timespec(&server_x, ntp->xmt_ts);
	ntp_format_to_timespec(&server_r, ntp->rec_ts);

	res = timespec_sub(client_r, client_x);
	res = timespec_sub(res, timespec_sub(server_x, server_r));

	return res;
}

int ntp_offset(struct ntphdr *ntp) {
	return 0;
}

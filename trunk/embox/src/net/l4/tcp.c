/**
 * @file
 * @brief Implementation of the Transmission Control Protocol (TCP).
 * @details RFC 768
 *
 * @date 04.04.10
 * @author Nikolay Korotky
 * @author Anton Kozlov
 * @author Ilia Vaprol
 */

#include <net/l4/tcp.h>
#include <string.h>
#include <mem/objalloc.h>
#include <util/array.h>
#include <net/inetdevice.h>
#include <sys/socket.h>
#include <net/util/checksum.h>
#include <net/l3/route.h>
#include <net/skbuff.h>
#include <errno.h>
#include <assert.h>
#include <net/sock.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <kernel/printk.h>
#include <sys/time.h>
#include <net/if_ether.h>
#include <util/sys_log.h>

#include <kernel/panic.h>
#include <kernel/event.h>
#include <kernel/time/timer.h>
#include <embox/net/proto.h>
#include <kernel/softirq_lock.h>
#include <kernel/time/time.h>
#include <kernel/time/ktime.h>
#include <util/indexator.h>

#include <kernel/task/io_sync.h>
#include <prom/prom_printf.h>

EMBOX_NET_PROTO_INIT(IPPROTO_TCP, tcp_v4_rcv, NULL, tcp_v4_init);

/** TODO
 * +1. Create default socket for resetting
 * +2. PSH flag
 * +3. RST flag
 * ?4. Changes state's logic (i.e. TCP_CLOSED for all socket which doesn't exists etc.)
 * +5. Rewrite send_from_sock (don't send new skb if queue is not empty)
 * +6. tcp_sock_free in tcp_st_finwait_2
 * +7. Remove seq_next (use rem.seq instead, build packet, and then rebuild only)
 * +8. Add lock/unlock
 * +9. Add rexmit
 * +-10. Add window
 * 11. Add options
 * +-12. Add timeout (i.e. sockopts) to tcp_sock.c
 */


/* Error code of TCP handlers */
enum tcp_ret_code {
	TCP_RET_OK,     /* all ok, don't free packet */
	TCP_RET_DROP,   /* drop packet */
	TCP_RET_SEND,   /* send packet */
	TCP_RET_FLUSH,  /* send acknowledgment or other packet without outgoing queue */
	TCP_RET_RST,    /* reset (Only for pre_process) */
	TCP_RET_FREE    /* drop packet and free socket */
};

/* Type of TCP state handlers */
typedef enum tcp_ret_code (*tcp_handler_t)(union sock_pointer sock, struct sk_buff **skb,
		struct tcphdr *tcph, struct tcphdr *out_tcph);

static union sock_pointer tcp_sock_default; /* Default socket for TCP protocol. */
static struct sys_timer tcp_tmr_default; /* Timer structure for rexmitting or TIME-WAIT satate */

/* Prototypes */
static int tcp_handle(union sock_pointer sock, struct sk_buff *skb, tcp_handler_t hnd);
static const tcp_handler_t tcp_st_handler[];
static void tcp_get_now(struct timeval *out_now);
static size_t tcp_seq_len(struct sk_buff *skb);

/************************ Debug functions ******************************/
#if 1
void debug_print(__u8 code, const char *msg, ...) { }
static inline void packet_print(union sock_pointer sock, struct sk_buff *skb, char *msg,
		in_addr_t ip, in_port_t port) { }

#else 

void debug_print(__u8 code, const char *msg, ...) {
	va_list args;

	va_start(args, msg);
	switch (code) {
//default:
//	case 0:  /* default */
	case 1:  /* in/out package print */
	case 2:  /* socket state */
//	case 3:  /* global functions */
//	case 4:  /* hash/unhash */
//	case 5:  /* lock/unlock */
//	case 6:	 /* sock_alloc/sock_free */
//	case 7:  /* tcp_default_timer action */
	case 8:  /* state's handler */
	case 9:  /* sending package */
//	case 10: /* pre_process */
//	case 11: /* tcp_handle */
		softirq_lock();
		prom_vprintf(msg, args);
		softirq_unlock();
		break;
	}
	va_end(args);
}

static inline void packet_print(union sock_pointer sock, struct sk_buff *skb, char *msg,
		in_addr_t ip, in_port_t port) {
	struct timeval now;
	tcp_get_now(&now);
	debug_print(1, "%ld.%ld %s:%d %s sk %p skb %p seq %u ack %u seq_len %u flags %s %s %s %s %s %s %s %s\n",
			// info
			now.tv_sec, now.tv_usec, inet_ntoa(*(struct in_addr*)&ip), ntohs(port), msg, sock.tcp_sk, skb,
			// seq, ack, seq_len
			ntohl(skb->h.th->seq), ntohl(skb->h.th->ack_seq), tcp_seq_len(skb),
			// flags
			(skb->h.th->ack ? "ACK" : ""), (skb->h.th->syn ? "SYN" : ""),
			(skb->h.th->fin ? "FIN" : ""), (skb->h.th->rst ? "RST" : ""),
			(skb->h.th->psh ? "PSH" : ""), (skb->h.th->urg ? "URG" : ""),
			(skb->h.th->ece ? "ECE" : ""), (skb->h.th->cwr ? "CWR" : ""));
}

#endif

/************************ Auxiliary functions **************************/
void build_tcp_packet(size_t opt_len, size_t data_len, union sock_pointer sock,
		struct sk_buff *skb) {
	size_t tcp_hdr_sz;

	opt_len = (opt_len + 3) & ~(size_t)3; /* round */

	tcp_hdr_sz = TCP_MIN_HEADER_SIZE + opt_len;

	skb->len = ETH_HEADER_SIZE + IP_MIN_HEADER_SIZE + tcp_hdr_sz + data_len;

	skb->nh.raw = skb->mac.raw + ETH_HEADER_SIZE;
	skb->nh.iph->ihl = IP_MIN_HEADER_SIZE / 4;
	skb->nh.iph->tot_len = htons(IP_MIN_HEADER_SIZE + tcp_hdr_sz + data_len);

	skb->h.raw = skb->nh.raw + IP_MIN_HEADER_SIZE;
	memset(skb->h.th, 0, tcp_hdr_sz);
	skb->h.th->source = sock.inet_sk->src_in.sin_port;
	skb->h.th->dest = sock.inet_sk->dst_in.sin_port;
	skb->h.th->seq = 0; /* use set_tcp_set_field */
	skb->h.th->doff = tcp_hdr_sz / 4;
}

static void set_tcp_seq_field(union sock_pointer sock,
		struct sk_buff *skb) {
	skb->h.th->seq = htonl(sock.tcp_sk->self.seq);
}

struct sk_buff * alloc_prep_skb(size_t opt_len, size_t data_len) {
	opt_len = (opt_len + 3) & ~(size_t)3; /* round */
	return skb_alloc(ETH_HEADER_SIZE + IP_MIN_HEADER_SIZE + TCP_MIN_HEADER_SIZE
			+ opt_len + data_len);
}

void tcp_obj_lock(union sock_pointer sock, unsigned int obj) {
	if (sock.tcp_sk->lock++ == 0) {
		softirq_lock();
	}
}

void tcp_obj_unlock(union sock_pointer sock, unsigned int obj) {
	assert(sock.tcp_sk->lock != 0);
	if (--sock.tcp_sk->lock == 0) {
		softirq_unlock();
	}
}

static size_t tcp_data_len(struct sk_buff *skb) {
	size_t ip_len, ip_tcp_hdr_sz;

	ip_len = ntohs(skb->nh.iph->tot_len);
	ip_tcp_hdr_sz = IP_HEADER_SIZE(skb->nh.iph) + TCP_HEADER_SIZE(skb->h.th);
	return ip_len > ip_tcp_hdr_sz ? ip_len - ip_tcp_hdr_sz : 0;
}

static void tcp_sock_save_skb(union sock_pointer sock, struct sk_buff *skb) {
	__u32 seq;

	seq = ntohl(skb->h.th->seq);

	/* move skb to socket received queue */
	assert(sock.tcp_sk->rem.seq >= seq); /* FIXME */
	sock_rcv(sock.sk, skb, skb->h.raw + TCP_HEADER_SIZE(skb->h.th)
			+ (sock.tcp_sk->rem.seq - seq), tcp_data_len(skb));
}

static size_t tcp_data_left(struct sk_buff *skb) {
	size_t ip_len, recv_sz;

	ip_len = ntohs(skb->nh.iph->tot_len);
	recv_sz = skb->p_data - skb->nh.raw;
	return ip_len > recv_sz ? ip_len - recv_sz : 0;
}

static int tcp_seq_flags(struct tcphdr *tcph) {
	return tcph->fin || tcph->syn;
}

static size_t tcp_seq_len(struct sk_buff *skb) {
	return tcp_data_len(skb) + tcp_seq_flags(skb->h.th);
}

static size_t tcp_seq_left(struct sk_buff *skb) {
	return tcp_data_left(skb) + tcp_seq_flags(skb->h.th);
}

void tcp_set_st(union sock_pointer sock,
		enum tcp_sock_state new_state) {
	const char *str_state[TCP_MAX_STATE] = {"TCP_CLOSED", "TCP_LISTEN",
			"TCP_SYN_SENT", "TCP_SYN_RECV_PRE", "TCP_SYN_RECV", "TCP_ESTABIL",
			"TCP_FINWAIT_1", "TCP_FINWAIT_2", "TCP_CLOSEWAIT", "TCP_CLOSING",
			"TCP_LASTACK", "TCP_TIMEWAIT"};

	switch (new_state) {
	default:
		break;
	case TCP_SYN_SENT:
	case TCP_SYN_RECV:
		tcp_get_now(&sock.tcp_sk->syn_time); /* set when SYN sent */
		/* fallthrough */
	case TCP_FINWAIT_1:
	case TCP_LASTACK:
		sock.tcp_sk->ack_flag = sock.tcp_sk->self.seq + 1;
		debug_print(2, "sk %p set ack_flag %u for state %d-%s\n",
				sock.tcp_sk, sock.tcp_sk->ack_flag, new_state, str_state[new_state]);
		break;
	}

	sock.tcp_sk->state = new_state;
	debug_print(2, "sk %p set state %d-%s\n", sock.tcp_sk, new_state, str_state[new_state]);

	/* io_sync manipulation */
	switch (new_state) {
	default:
		break;
	case TCP_ESTABIL: /* new connection */
		/* enable writing when connection is established */
		io_sync_enable(&sock.sk->ios, IO_SYNC_WRITING);
		/* enable reading for listening (parent) socket */
		if (sock.tcp_sk->parent != NULL) {
			tcp_obj_lock((union sock_pointer)sock.tcp_sk->parent,
					TCP_SYNC_CONN_QUEUE);
			{
				list_move(&sock.tcp_sk->conn_wait,
						&sock.tcp_sk->parent->conn_wait);
			}
			tcp_obj_unlock((union sock_pointer)sock.tcp_sk->parent,
					TCP_SYNC_CONN_QUEUE);
			io_sync_enable(&sock.tcp_sk->parent->inet.sk.ios,
					IO_SYNC_READING);
		}
		break;
	case TCP_CLOSEWAIT: /* throw error: can't read */
		io_sync_error_on(&sock.sk->ios, IO_SYNC_READING);
		break;
	case TCP_TIMEWAIT: /* throw error: can't read and write */
	case TCP_CLOSING:
	case TCP_CLOSED:
		io_sync_error(&sock.sk->ios);
		break;
	}
}

int tcp_st_status(union sock_pointer sock) {
	switch (sock.tcp_sk->state) {
	default:
	case TCP_CLOSED:
	case TCP_LISTEN:
		return TCP_ST_NOTEXIST;
	case TCP_SYN_SENT:
	case TCP_SYN_RECV_PRE:
	case TCP_SYN_RECV:
		return TCP_ST_NONSYNC;
	case TCP_ESTABIL:
	case TCP_FINWAIT_1:
	case TCP_FINWAIT_2:
	case TCP_CLOSEWAIT:
	case TCP_CLOSING:
	case TCP_LASTACK:
	case TCP_TIMEWAIT:
		return TCP_ST_SYNC;
	}
}

static void tcp_get_now(struct timeval *out_now) {
	ktime_get_timeval(out_now);
}

static int tcp_is_expired(struct timeval *since,
		useconds_t limit_msec) {
	struct timeval now, delta, limit;
	ktime_get_timeval(&now);
	timersub(&now, since, &delta);
	limit.tv_sec = limit_msec / MSEC_PER_SEC;
	limit.tv_usec = (limit_msec % MSEC_PER_SEC) * USEC_PER_MSEC;
	return timercmp(&delta, &limit, >=);
}

static __u16 tcp_checksum(__be32 saddr, __be32 daddr, __u8 proto,
		struct tcphdr *tcph, __u16 size) {
	struct tcp_pseudohdr ptcph;

	ptcph.saddr = saddr;
	ptcph.daddr = daddr;
	ptcph.zero = 0;
	ptcph.protocol = proto;
	ptcph.tcp_len = htons(size);
	return (~fold_short(partial_sum(&ptcph, sizeof ptcph) +
			partial_sum(tcph, size)) & 0xffff);
}

static void rebuild_tcp_packet(__be32 ip_src, __be32 ip_dest,
		__u32 ack_seq, __u16 window, struct sk_buff *skb) {
	struct tcphdr *tcph;

	tcph = tcp_hdr(skb);
	tcph->ack_seq = htonl(ack_seq);
	tcph->window = htons(window);
	tcph->check = 0;
	tcph->check = tcp_checksum(ip_src, ip_dest, IPPROTO_TCP,
		       tcph, TCP_HEADER_SIZE(tcph) + tcp_data_len(skb));
}

static void tcp_xmit(union sock_pointer sock, struct sk_buff *skb) {
//	int ret;
	rebuild_tcp_packet(sock.inet_sk->src_in.sin_addr.s_addr,
			sock.inet_sk->dst_in.sin_addr.s_addr,
			sock.tcp_sk->rem.seq, sock.tcp_sk->self.wind, skb);
	packet_print(sock, skb, "<=", sock.inet_sk->dst_in.sin_addr.s_addr,
			sock.inet_sk->dst_in.sin_port);
	/*ret =*/ ip_send_packet(sock.inet_sk, skb, NULL);
//	if (ret != 0) {
//		printk("tcp_xmit: erorr: ip_send_packet returned %d\n", ret);
//	}
}

static void tcp_rexmit(union sock_pointer sock) {
	struct sk_buff *skb, *skb_send;

	tcp_obj_lock(sock, TCP_SYNC_WRITE_QUEUE);
	{
		skb = skb_queue_front(&sock.sk->tx_queue);
		if (skb == NULL) {
			/**
			 * TODO
			 * self.seq is set in the function up the stack,
			 * so assert may trigger falsely. Need add lock
			 * and after that it will be correct.
			 */
			/* assert(sock.tcp_sk->last_ack == sock.tcp_sk->self.seq); */
			tcp_obj_unlock(sock, TCP_SYNC_WRITE_QUEUE);
			return;
		}
		skb_send = skb_clone(skb);
		if (skb_send == NULL) {
			tcp_obj_unlock(sock, TCP_SYNC_WRITE_QUEUE);
			return;
		}
		debug_print(9, "tcp_rexmit: send skb %p, postponed %p\n", skb_send, skb);
	}
	tcp_obj_unlock(sock, TCP_SYNC_WRITE_QUEUE);

	tcp_xmit(sock, skb_send);
}

/**
 * Send any packet without sequence (i.e. seq_len is 0)
 */
static void send_from_sock_now(union sock_pointer sock, struct sk_buff *skb) {
	debug_print(9, "send_from_sock_now: send %p\n", skb);
	set_tcp_seq_field(sock, skb);
	tcp_xmit(sock, skb);
}

/**
 * Send a data, only
 */
void send_data_from_sock(union sock_pointer sock, struct sk_buff *skb) {
	struct sk_buff *skb_send;
	debug_print(9, "send_data_from_sock: send %p\n", skb);

	skb->p_data = skb->h.raw + TCP_HEADER_SIZE(skb->h.th);

	skb_send = skb_clone(skb);

	tcp_obj_lock(sock, TCP_SYNC_WRITE_QUEUE);
	{
		set_tcp_seq_field(sock, skb);
		if (skb_send != NULL) {
			set_tcp_seq_field(sock, skb_send); /* set to cloned pkg */
		}
		skb_queue_push(&sock.sk->tx_queue, skb);
		sock.tcp_sk->self.seq += tcp_seq_len(skb);
	}
	tcp_obj_unlock(sock, TCP_SYNC_WRITE_QUEUE);

	if (skb_send != NULL) {
		tcp_xmit(sock, skb_send);
	}
}

static void free_rexmitting_queue(union sock_pointer sock, __u32 ack, __u32 last_ack) {
	struct sk_buff *sent_skb;
	size_t ack_len, seq_left;

	ack_len = ack - last_ack;
	assert(ack_len > 0);

	debug_print(9, "free_rexmitting_queue: sk %p ack %u last_ack %u\n",
			sock.tcp_sk, ack, last_ack);
	tcp_obj_lock(sock, TCP_SYNC_WRITE_QUEUE);
	{
		do {
			sent_skb = skb_queue_front(&sock.sk->tx_queue);
			assert(sent_skb != NULL);

			seq_left = tcp_seq_left(sent_skb);
			if (seq_left <= ack_len) {
				ack_len -= seq_left;
				debug_print(9, "free_rexmitting_queue: remove skb %p\n", sent_skb);
				skb_free(sent_skb); /* list_del_init will done at skb_free */
			} else {
				sent_skb->p_data += ack_len;
				break;
			}
		} while (ack_len > 0);
	}
	tcp_obj_unlock(sock, TCP_SYNC_WRITE_QUEUE);
}

void tcp_free_sock(union sock_pointer sock) {
	union sock_pointer anticipant;

	if (sock.tcp_sk->parent == NULL) {
		tcp_obj_lock(sock, TCP_SYNC_CONN_QUEUE);
		{
			list_for_each_entry(anticipant.tcp_sk,
					&sock.tcp_sk->conn_wait, conn_wait) {
				sock_release(anticipant.sk);
			}
		}
		tcp_obj_unlock(sock, TCP_SYNC_CONN_QUEUE);
	}
	else {
		tcp_obj_lock((union sock_pointer)sock.tcp_sk->parent,
				TCP_SYNC_CONN_QUEUE);
		{
			if (!list_empty(&sock.tcp_sk->conn_wait)) {
				assert(sock.tcp_sk->parent->conn_wait_len != 0);
				--sock.tcp_sk->parent->conn_wait_len;
				list_del(&sock.tcp_sk->conn_wait);
			}
		}
		tcp_obj_unlock((union sock_pointer)sock.tcp_sk->parent,
				TCP_SYNC_CONN_QUEUE);
	}

	if (sock.inet_sk->src_port_alloced) {
		assert(sock.sk->p_ops != NULL);
		index_unlock(sock.sk->p_ops->sock_port,
				ntohs(sock.inet_sk->src_in.sin_port));
	}
	sock_release(sock.sk);
}


/************************ Handlers of TCP states ***********************/
static enum tcp_ret_code tcp_st_closed(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	debug_print(8, "call tcp_st_closed\n");
	assert(sock.tcp_sk->state == TCP_CLOSED);

	out_tcph->rst = 1;
	/* Set seq and ack */
	if (tcph->ack) {
		sock.tcp_sk->last_ack = ntohl(tcph->ack_seq);
		sock.tcp_sk->rem.seq = 0;
	} else {
		out_tcph->ack = 1;
		sock.tcp_sk->last_ack = 0;
		sock.tcp_sk->rem.seq = ntohl(tcph->seq) + tcp_seq_len(*pskb);
	}

	/* Set up a socket */
	sock.inet_sk->src_in.sin_addr.s_addr = (*pskb)->nh.iph->daddr;
	sock.inet_sk->src_in.sin_port = tcph->dest;
	sock.inet_sk->dst_in.sin_addr.s_addr = (*pskb)->nh.iph->saddr;
	sock.inet_sk->dst_in.sin_port = tcph->source;

	return TCP_RET_FLUSH;
}

static enum tcp_ret_code tcp_st_listen(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	int ret;
	union sock_pointer newsock;

	debug_print(8, "call tcp_st_listen\n");
	assert(sock.tcp_sk->state == TCP_LISTEN);

	if (tcph->syn) {
		/* Check max length of accept queue and reserve 1 place */
		tcp_obj_lock(sock, TCP_SYNC_CONN_QUEUE);
		{
			if (sock.tcp_sk->conn_wait_len >= sock.tcp_sk->conn_wait_max) {
				LOG_DEBUG("tcp_st_listen", "conn_wait is too big");
				tcp_obj_unlock(sock, TCP_SYNC_CONN_QUEUE);
				return TCP_RET_DROP;
			}
			++sock.tcp_sk->conn_wait_len; /* reserve */
		}
		tcp_obj_unlock(sock, TCP_SYNC_CONN_QUEUE);

		/* Allocate new socket for this connection */
		ret = sock_create(sock.sk->opt.so_domain,
				SOCK_STREAM, IPPROTO_TCP, &newsock.sk);
		if (ret != 0) {
			printk("%s: can't alloc socket\n", __func__);
			tcp_obj_lock(sock, TCP_SYNC_CONN_QUEUE);
			{
				assert(sock.tcp_sk->conn_wait_len != 0);
				--sock.tcp_sk->conn_wait_len;
			}
			tcp_obj_unlock(sock, TCP_SYNC_CONN_QUEUE);
			return TCP_RET_DROP; /* error: see ret */
		}
		debug_print(8, "\t append sk %p for skb %p to sk %p queue\n", newsock.tcp_sk, *pskb, sock.tcp_sk);
		/* Set up new socket */
		newsock.inet_sk->src_in.sin_family = AF_INET;
		newsock.inet_sk->src_in.sin_port = (*pskb)->h.th->dest;
		newsock.inet_sk->src_in.sin_addr.s_addr = (*pskb)->nh.iph->daddr;
		newsock.inet_sk->dst_in.sin_family = AF_INET;
		newsock.inet_sk->dst_in.sin_port = (*pskb)->h.th->source;
		newsock.inet_sk->dst_in.sin_addr.s_addr = (*pskb)->nh.iph->saddr;
		/* Handling skb */
		tcp_obj_lock(sock, TCP_SYNC_STATE);
		{
			tcp_set_st(newsock, TCP_SYN_RECV_PRE); /* TODO remove this */
			tcp_handle(newsock, *pskb, tcp_st_handler[TCP_SYN_RECV_PRE]);
		}
		tcp_obj_unlock(sock, TCP_SYNC_STATE);
		/* Save new socket to accept queue */
		tcp_obj_lock(sock, TCP_SYNC_CONN_QUEUE);
		{
			newsock.tcp_sk->parent = sock.tcp_sk;
			list_add_tail(&newsock.tcp_sk->conn_wait, &sock.tcp_sk->conn_wait);
		}
		tcp_obj_unlock(sock, TCP_SYNC_CONN_QUEUE);

		return TCP_RET_OK;
	}

	return TCP_RET_DROP;
}

static enum tcp_ret_code tcp_st_syn_sent(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	debug_print(8, "call tcp_st_syn_sent\n");
	assert(sock.tcp_sk->state == TCP_SYN_SENT);

	if (tcph->syn) {
		sock.tcp_sk->rem.seq = ntohl(tcph->seq) + 1;
		sock.tcp_sk->rem.wind = ntohs(tcph->window);
		out_tcph->ack = 1;
		if (tcph->ack) {
			tcp_set_st(sock, TCP_ESTABIL);
		} else {
			tcp_set_st(sock, TCP_SYN_RECV);
		}
		return TCP_RET_FLUSH;
	}

	return TCP_RET_DROP;
}

static enum tcp_ret_code tcp_st_syn_recv_pre(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	debug_print(8, "call tcp_st_syn_recv_pre\n");
	assert(sock.tcp_sk->state == TCP_SYN_RECV_PRE);

	if (tcph->syn) {
		sock.tcp_sk->rem.seq = ntohl(tcph->seq) + 1;
		sock.tcp_sk->rem.wind = ntohs(tcph->window);
		out_tcph->ack = 1;
		out_tcph->syn = 1;
		tcp_set_st(sock, TCP_SYN_RECV);
		return TCP_RET_SEND;
	}
	return TCP_RET_DROP;
}

static enum tcp_ret_code tcp_st_syn_recv(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	debug_print(8, "call tcp_st_syn_recv\n");
	assert(sock.tcp_sk->state == TCP_SYN_RECV);

	if (tcph->ack) {
		tcp_set_st(sock, TCP_ESTABIL);
	}

	return TCP_RET_DROP;
}

static enum tcp_ret_code tcp_st_estabil(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	size_t data_len;
	struct sk_buff *answer;

	debug_print(8, "call tcp_st_estabil\n");
	assert(sock.tcp_sk->state == TCP_ESTABIL);

	data_len = tcp_data_len(*pskb);
	if (data_len > 0) {
		/* Allocate new sk_buff_t for sending ack flag */
		answer = alloc_prep_skb(0, 0);
		if (answer == NULL) {
			return TCP_RET_DROP; /* error: no memory */
		}
		/* Save current sk_buff_t with data */
		debug_print(8, "\t received %d\n", data_len);
		tcp_sock_save_skb(sock, *pskb);
		sock.tcp_sk->rem.seq += data_len;
		out_tcph->ack = 1;
		if (tcph->fin) {
			sock.tcp_sk->rem.seq += 1;
			tcp_set_st(sock, TCP_CLOSEWAIT);
		}
		*pskb = answer;
		return TCP_RET_FLUSH;
	} else if (tcph->fin) {
		sock.tcp_sk->rem.seq += 1;
		out_tcph->ack = 1;
		tcp_set_st(sock, TCP_CLOSEWAIT);
		return TCP_RET_FLUSH;
	}

	return TCP_RET_DROP;
}

static enum tcp_ret_code tcp_st_finwait_1(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	size_t data_len;
	struct sk_buff *answer;

	debug_print(8, "call tcp_st_finwait_1\n");
	assert(sock.tcp_sk->state == TCP_FINWAIT_1);

	data_len = tcp_data_len(*pskb);
	if (data_len > 0) {
		/* Allocate new sk_buff_t for sending ack's flag */
		answer = alloc_prep_skb(0, 0);
		if (answer == NULL) {
			return TCP_RET_DROP; /* error: no memory */
		}
		/* Save current sk_buff_t with data */
		debug_print(8, "\t received %d\n", data_len);
		tcp_sock_save_skb(sock, *pskb);
		sock.tcp_sk->rem.seq += data_len;
		out_tcph->ack = 1;
		if (tcph->fin) {
			sock.tcp_sk->rem.seq += 1;
			if (tcph->ack) {
				tcp_set_st(sock, TCP_TIMEWAIT);
			} else {
				tcp_set_st(sock, TCP_CLOSING);
			}
		} else if (tcph->ack) {
			tcp_set_st(sock, TCP_FINWAIT_2);
		}
		*pskb = answer;
		return TCP_RET_FLUSH;
	} else if (tcph->fin) {
		sock.tcp_sk->rem.seq += 1;
		out_tcph->ack = 1;
		if (tcph->ack) {
			tcp_set_st(sock, TCP_TIMEWAIT);
		} else {
			tcp_set_st(sock, TCP_CLOSING);
		}
		return TCP_RET_FLUSH;
	} else if (tcph->ack) {
		tcp_set_st(sock, TCP_FINWAIT_2);
	}

	return TCP_RET_DROP;
}

static enum tcp_ret_code tcp_st_finwait_2(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	size_t data_len;
	struct sk_buff *answer;

	debug_print(8, "call tcp_st_finwait_2\n");
	assert(sock.tcp_sk->state == TCP_FINWAIT_2);

	data_len = tcp_data_len(*pskb);
	if (data_len > 0) {
		/* Allocate new sk_buff_t for sending ack's flag */
		answer = alloc_prep_skb(0, 0);
		if (answer == NULL) {
			return TCP_RET_DROP; /* error: no memory */
		}
		/* Save current sk_buff_t with data */
		debug_print(8, "\t received %d\n", data_len);
		tcp_sock_save_skb(sock, *pskb);
		sock.tcp_sk->rem.seq += data_len;
		out_tcph->ack = 1;
		if (tcph->fin) {
			sock.tcp_sk->rem.seq += 1;
			tcp_set_st(sock, TCP_TIMEWAIT);
		}
		*pskb = answer;
		return TCP_RET_FLUSH;
	} else if (tcph->fin) {
		sock.tcp_sk->rem.seq += 1;
		out_tcph->ack = 1;
		tcp_set_st(sock, TCP_TIMEWAIT);
		return TCP_RET_FLUSH;
	}

	return TCP_RET_DROP;
}

static enum tcp_ret_code tcp_st_closewait(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	debug_print(8, "call tcp_st_closewait\n");
	assert(sock.tcp_sk->state == TCP_CLOSEWAIT);

	return TCP_RET_DROP;
}

static enum tcp_ret_code tcp_st_closing(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	debug_print(8, "call tcp_st_closing\n");
	assert(sock.tcp_sk->state == TCP_CLOSING);

	if (tcph->ack) {
		tcp_set_st(sock, TCP_TIMEWAIT);
	}

	return TCP_RET_DROP;
}

static enum tcp_ret_code tcp_st_lastack(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	debug_print(8, "call tcp_st_lastack\n");
	assert(sock.tcp_sk->state == TCP_LASTACK);

	if (tcph->ack) {
		tcp_set_st(sock, TCP_CLOSED);
		return TCP_RET_FREE;
	}

	return TCP_RET_DROP;
}

static enum tcp_ret_code tcp_st_timewait(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	debug_print(8, "call tcp_st_timewait\n");
	assert(sock.tcp_sk->state == TCP_TIMEWAIT);

	/* timeout 2msl and set TCP_CLOSED state */

	return TCP_RET_DROP;
}


/************************ Process functions ****************************/
static enum tcp_ret_code process_rst(union sock_pointer sock, struct tcphdr *tcph,
		struct tcphdr *out_tcph) {
	switch (sock.tcp_sk->state) {
	case TCP_LASTACK:
	case TCP_FINWAIT_1:
	case TCP_FINWAIT_2:
	case TCP_TIMEWAIT: /* don't wait for tcp_timer to collect the socket */
		/* socket have a state only after close call. It could be freed only here */
		return TCP_RET_FREE;
	case TCP_CLOSED: /* TODO */
	case TCP_LISTEN: /* TODO */
	case TCP_SYN_RECV_PRE: /* TODO */
		return TCP_RET_DROP;

	case TCP_SYN_SENT:
		if (sock.tcp_sk->self.seq != ntohl(tcph->ack_seq)) {
			/* invalid reset */
			return TCP_RET_DROP;
		}
		/* PASSTHROUGH */
	case TCP_SYN_RECV:
	case TCP_ESTABIL:
	case TCP_CLOSEWAIT:
	case TCP_CLOSING:
		tcp_set_st(sock, TCP_CLOSED);
		if (!list_empty(&sock.tcp_sk->conn_wait)) {
			assert(sock.tcp_sk->parent != NULL);
			return TCP_RET_FREE;
		}
		return TCP_RET_DROP;
	case TCP_MAX_STATE:
	default:
		panic("%s: unreachable state", __func__);
	}

	return TCP_RET_DROP;
}

static enum tcp_ret_code process_ack(union sock_pointer sock, struct tcphdr *tcph,
		struct tcphdr *out_tcph) {
	__u32 ack, self_seq, last_ack;

	/* Resetting if recv ack in this state */
	switch (sock.tcp_sk->state) {
	default:
		break;
	case TCP_CLOSED:
	case TCP_LISTEN:
		return TCP_RET_RST;
	}

	ack = ntohl(tcph->ack_seq);
	self_seq = sock.tcp_sk->self.seq;
	last_ack = sock.tcp_sk->last_ack;
	if ((last_ack < ack) && (ack <= self_seq)) {
		free_rexmitting_queue(sock, ack, last_ack);
		sock.tcp_sk->last_ack = ack;
		tcp_get_now(&sock.tcp_sk->ack_time);
	}
	else if (ack == last_ack) { /* no new acknowledgments */ }
	else if (ack < last_ack) { /* package with non-last acknowledgment */ }
	else {
		assert(ack > self_seq);
		debug_print(10, "process_ack: invalid acknowledgments: last_ack=%u ack=%u self_seq=%u\n", last_ack, ack, self_seq);
		switch (sock.tcp_sk->state) {
		default:
			break;
		case TCP_SYN_SENT:
		case TCP_SYN_RECV_PRE:
		case TCP_SYN_RECV:
			return TCP_RET_RST;
		}
		return TCP_RET_DROP;
	}

	/* Check ack flag for our state */
	switch (sock.tcp_sk->state) {
	default:
		break;
	case TCP_SYN_SENT:
	case TCP_SYN_RECV:
	case TCP_FINWAIT_1:
	case TCP_CLOSING:
	case TCP_LASTACK:
		if (ack >= sock.tcp_sk->ack_flag) { }/* All ok, our flag was confirmed */
		else { /* Else unmark ack flag */
			debug_print(10, "process_ack: sk %p unmark ack\n", sock.tcp_sk);
			tcph->ack = 0;
		}
		break;
	}
	return TCP_RET_OK;
}

static enum tcp_ret_code pre_process(union sock_pointer sock, struct sk_buff **pskb,
		struct tcphdr *tcph, struct tcphdr *out_tcph) {
	int ret;
	__u16 check;
	__u32 seq, seq_last, rem_seq, rem_last;

	/* Check CRC */
	check = tcph->check;
	tcph->check = 0;
	if (check != tcp_checksum((*pskb)->nh.iph->saddr,
				(*pskb)->nh.iph->daddr, IPPROTO_TCP, tcph,
				TCP_HEADER_SIZE(tcph) + tcp_data_len(*pskb))) {
		printk("pre_process: error: invalid ckecksum %hx sk %p skb %p\n",
				ntohs(check), sock.tcp_sk, *pskb);
		return TCP_RET_DROP;
	}

	/* Analyze sequence */
	switch (sock.tcp_sk->state) {
	default:
		break;
	case TCP_SYN_RECV:
	case TCP_ESTABIL:
	case TCP_FINWAIT_1:
	case TCP_FINWAIT_2:
	case TCP_CLOSEWAIT:
	case TCP_CLOSING:
	case TCP_LASTACK:
	case TCP_TIMEWAIT:
		seq = ntohl(tcph->seq);
		seq_last = seq + tcp_seq_len(*pskb) - 1;
		rem_seq = sock.tcp_sk->rem.seq;
		rem_last = rem_seq + sock.tcp_sk->self.wind;
		if ((rem_seq <= seq) && (seq < rem_last)) {
			if (rem_seq != seq) {
				/* TODO There is correct packet (with correct sequence
				 * number, but some packages was lost. We should save
				 * this skb, and wait previous packages.
				 */
				return TCP_RET_DROP;
			}
		}
		else if ((rem_seq <= seq_last) && (seq_last < rem_last)) { }
		else {
			debug_print(10, "pre_process: received old package: rem_seq=%u seq=%u seq_last=%u rem_last=%u\n", rem_seq, seq, seq_last, rem_last);
			if ((seq < rem_seq) && (seq_last < rem_seq)) {
				/* Send segment with ack flag if this packet is duplicated */
				out_tcph->ack = 1;
				return TCP_RET_FLUSH;
			}
			return TCP_RET_DROP;
		}
		break;
	}

	/* Processing RST */
	if (tcph->rst) {
		ret = process_rst(sock, tcph, out_tcph);
		if (ret != TCP_RET_OK) {
			return ret;
		}
	}

	/* Porcessing ACK */
	if (tcph->ack) {
		ret = process_ack(sock, tcph, out_tcph);
		if (ret != TCP_RET_OK) {
			return ret;
		}
	}

	return TCP_RET_OK;
}

#if 0
static inline int tcp_opt_process(struct tcphdr *tcph, struct tcphdr *otcph, struct tcp_sock *tcp_sk) {
	char *ptr = (char *) &tcph->options;
	for(;;) {
		switch(*ptr) {
		case TCP_OPT_KIND_EOL:
			return (int) ptr - (int) &tcph->options;
		case TCP_OPT_KIND_NOP:
			ptr++;
			break;
		case TCP_OPT_KIND_MSS:
			ptr+=2;
			tcp_sk->mss = ntohs((__be16) *ptr);
		}
	}
	return 0;
}
#endif


/************************ Handlers table *******************************/
static const tcp_handler_t tcp_st_handler[TCP_MAX_STATE] = {
		[ TCP_CLOSED ] = tcp_st_closed,
		[ TCP_LISTEN ] = tcp_st_listen,
		[ TCP_SYN_SENT ] = tcp_st_syn_sent,
		[ TCP_SYN_RECV_PRE ] = tcp_st_syn_recv_pre,
		[ TCP_SYN_RECV ] = tcp_st_syn_recv,
		[ TCP_ESTABIL ] = tcp_st_estabil,
		[ TCP_FINWAIT_1 ] = tcp_st_finwait_1,
		[ TCP_FINWAIT_2 ] = tcp_st_finwait_2,
		[ TCP_CLOSEWAIT ] = tcp_st_closewait,
		[ TCP_CLOSING ] = tcp_st_closing,
		[ TCP_LASTACK ] = tcp_st_lastack,
		[ TCP_TIMEWAIT ] = tcp_st_timewait
};

static int tcp_handle(union sock_pointer sock, struct sk_buff *skb, tcp_handler_t hnd) {
	/* If result is not TCP_RET_OK then further processing can't be made */
	enum tcp_ret_code ret;
	struct tcphdr out_tcph;

	memset(&out_tcph, 0, sizeof out_tcph);

	/**
	 * If we want to use the current package (to save for example),
	 * we must create a new package to send a response (if we need
	 * to send a response). After this the handler may do anything
	 * with current sk_buff_t.
	 * If hnd is NULL we use synchronization tools.
	 */
	assert(sock.tcp_sk->state < TCP_MAX_STATE);
	assert(tcp_st_handler[sock.tcp_sk->state] != NULL);
	hnd = hnd != NULL ? hnd : tcp_st_handler[sock.tcp_sk->state];

	tcp_obj_lock(sock, TCP_SYNC_STATE);
	{
		ret = hnd(sock, &skb, skb->h.th, &out_tcph);
	}
	tcp_obj_unlock(sock, TCP_SYNC_STATE);

	assert(skb != NULL);
	debug_print(11, "tcp_handle: ret %d skb %p sk %p\n", ret, skb, sock.tcp_sk);

	switch (ret) {
	case TCP_RET_FREE:
		/* skb may be listed in sock, so they must be free exactly
 		 * in this order */
		skb_free(skb);
		tcp_free_sock(sock);
		break;
	case TCP_RET_DROP:
		skb_free(skb);
		break;
	case TCP_RET_SEND:
		build_tcp_packet(0, 0, sock, skb);

		/* copy flags */
		skb->h.th->ack = out_tcph.ack;
		skb->h.th->syn = out_tcph.syn;

		send_data_from_sock(sock, skb);
		break;
	case TCP_RET_FLUSH:
		build_tcp_packet(0, 0, sock, skb);

		/* copy flags */
		skb->h.th->ack = out_tcph.ack;
		skb->h.th->rst = out_tcph.rst;

		send_from_sock_now(sock, skb);
		break;
	case TCP_RET_RST: /* this processing in tcp_process */
	case TCP_RET_OK:
		break;
	}

	return ret;
}

static int tcp_rcv_tester_strict(const struct sock *sk,
		const struct sk_buff *skb) {
	const struct inet_sock *in_sk;

	in_sk = (const struct inet_sock *)sk;
	assert(in_sk != NULL);

	assert(skb != NULL);
	assert(skb->nh.iph != NULL);
	assert(skb->h.th != NULL);
	return (in_sk->src_in.sin_addr.s_addr == skb->nh.iph->daddr)
			&& (in_sk->src_in.sin_port == skb->h.th->dest)
			&& (in_sk->dst_in.sin_addr.s_addr == skb->nh.iph->saddr)
			&& (in_sk->dst_in.sin_port == skb->h.th->source);
};

static int tcp_rcv_tester_soft(const struct sock *sk,
		const struct sk_buff *skb) {
	const struct inet_sock *in_sk;

	in_sk = (const struct inet_sock *)sk;
	assert(in_sk != NULL);

	assert(skb != NULL);
	assert(skb->nh.iph != NULL);
	assert(skb->h.th != NULL);
	return ((in_sk->src_in.sin_addr.s_addr == skb->nh.iph->daddr)
				|| (in_sk->src_in.sin_addr.s_addr == INADDR_ANY))
			&& (in_sk->src_in.sin_port == skb->h.th->dest);
}

/**
 * Main function of TCP protocol
 */
static void tcp_process(union sock_pointer sock, struct sk_buff *skb) {
	enum tcp_ret_code ret;

	tcp_get_now(&sock.tcp_sk->rcv_time);

	ret = tcp_handle(sock, skb, pre_process);

	if (ret == TCP_RET_OK) {
		ret = tcp_handle(sock, skb, NULL);
	}

	if (ret == TCP_RET_RST) {
		tcp_handle(tcp_sock_default, skb, tcp_st_handler[TCP_CLOSED]);
	}

}

static int tcp_v4_rcv(struct sk_buff *skb) {
	union sock_pointer sock;

	assert(skb != NULL);

	sock.sk = sock_lookup(NULL, tcp_sock_ops,
			tcp_rcv_tester_strict, skb);
	if (sock.sk == NULL) {
		sock.sk = sock_lookup(NULL, tcp_sock_ops,
				tcp_rcv_tester_soft, skb);
	}

	packet_print(sock, skb, "=>", skb->nh.iph->saddr, skb->h.th->source);
	if (sock.tcp_sk == NULL) {
		sock.tcp_sk = tcp_sock_default.tcp_sk;
	}
	tcp_process(sock, skb);

	return 0;
}

static void tcp_timer_handler(struct sys_timer *timer, void *param) {
	union sock_pointer sock;

	debug_print(7, "TIMER: call tcp_timer_handler\n");

	sock_foreach(sock.sk, tcp_sock_ops) {
		if ((sock.tcp_sk->state == TCP_TIMEWAIT)
				&& tcp_is_expired(&sock.tcp_sk->rcv_time,
					TCP_TIMEWAIT_DELAY)) {
			debug_print(7, "tcp_timer_handler: release timewait sk %p\n",
					sock.tcp_sk);
			tcp_free_sock(sock);
		}
		else if ((tcp_st_status(sock) == TCP_ST_NONSYNC)
				&& !list_empty(&sock.tcp_sk->conn_wait)
				&& tcp_is_expired(&sock.tcp_sk->syn_time,
					TCP_SYNC_TIMEOUT)) {
			assert(sock.tcp_sk->parent != NULL);
			debug_print(7, "tcp_timer_handler: release nonsync sk %p\n",
					sock.tcp_sk);
			tcp_free_sock(sock);
		}
		else if ((tcp_st_status(sock) != TCP_ST_NOTEXIST)
				&& tcp_is_expired(&sock.tcp_sk->ack_time,
					TCP_REXMIT_DELAY)) {
			debug_print(7, "tcp_timer_handler: rexmit sk %p\n",
					sock.tcp_sk);
			tcp_rexmit(sock);
		}
	}
}

static int tcp_v4_init(void) {
	int ret;

	/* Create default timer */
	ret = timer_init(&tcp_tmr_default, TIMER_PERIODIC, TCP_TIMER_FREQUENCY, tcp_timer_handler, NULL);
	if (ret < 0) {
		return ret;
	}

	/* Create default socket */
	ret = sock_create_ext(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0,
			&tcp_sock_default.sk);
	if (ret != 0) {
		return ret;
	}

	return 0;
}

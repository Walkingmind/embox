/**
 * @file
 * @brief Implementation of the Transmission Control Protocol(TCP).
 * @details RFC 768
 *
 * @date 04.04.10
 * @author Nikolay Korotky
 * @author Anton Kozlov 
 */

#include <net/tcp.h>

#include <string.h>
#include <mem/objalloc.h>
#include <net/inetdevice.h>
#include <net/ip.h>
#include <net/icmp.h>
#include <net/socket.h>
#include <net/checksum.h>
#include <net/protocol.h>
#include <net/inet_common.h>
#include <embox/net/proto.h>
#include <net/skbuff.h>
#include <errno.h>

EMBOX_NET_PROTO(IPPROTO_TCP, tcp_v4_rcv, NULL);

static tcp_sock_t *tcp_hash[CONFIG_MAX_KERNEL_SOCKETS];

OBJALLOC_DEF(tcp_socks, struct tcp_sock, CONFIG_MAX_KERNEL_SOCKETS);

static sock_t *tcp_v4_sock_alloc(void) {
	return (sock_t *) objalloc(&tcp_socks);
}

static void tcp_v4_sock_free(sock_t *sock) {
	objfree(&tcp_socks, sock);
}

int tcp_v4_init_sock(sock_t *sk) {
	sk->sk_state = TCP_CLOSE;

	return 0;
}

static inline unsigned short tcp_checksum (__be32 saddr, __be32 daddr, __u8 proto, 
		struct tcphdr *tcph, unsigned short size) {
	struct tcp_pseudohdr ptcph = {
		.saddr = saddr, 
		.daddr = daddr,
		.zero  = 0, 
		.protocol = proto, 
		.tcp_len = htons(size)
	};
	return (~fold_short(partial_sum(&ptcph, sizeof(struct tcp_pseudohdr)) + 
			partial_sum(tcph, size)) & 0xffff);
}

static inline void rebuild_tcp_header(__be32 ip_src, __be32 ip_dest,
		__be16 source, __be16 dest, __be32 seq, __be32 ack_seq,
		__be16 window,
	       	struct tcphdr *tcph) {
	tcph->dest = source;
	tcph->source = dest;
	tcph->seq = seq;
	tcph->ack_seq = ack_seq;

	tcph->doff = TCP_V4_HEADER_MIN_SIZE >> 2;
	tcph->window = htons(window);
	
	tcph->check = tcp_checksum(ip_dest, ip_src, IPPROTO_TCP,
		       tcph, TCP_V4_HEADER_SIZE(tcph));	

}

int tcp_v4_sendmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg,
			size_t len) {
	struct inet_sock *inet = inet_sk(sk);
	struct tcp_sock *tcpsk = (struct tcp_sock *) sk;

	sk_buff_t *skb;
	if (sk->sk_state != TCP_ESTABIL) {
		return -EINVAL;
	}
	skb = alloc_skb(ETH_HEADER_SIZE + IP_MIN_HEADER_SIZE +
				    /*inet->opt->optlen +*/ TCP_V4_HEADER_MIN_SIZE +
				    msg->msg_iov->iov_len, 0);
	skb->nh.raw = (unsigned char *) skb->data + ETH_HEADER_SIZE;
	skb->h.raw = (unsigned char *) skb->nh.raw + IP_MIN_HEADER_SIZE;// + inet->opt->optlen;
	memcpy((void*)((unsigned int)(skb->h.raw + TCP_V4_HEADER_MIN_SIZE)),
				(void *) msg->msg_iov->iov_base, msg->msg_iov->iov_len);
	/* Fill TCP header */
	//rebuild_tcp_header(skb, inet->sport, inet->dport, len);
	rebuild_tcp_header(0, 0, inet->sport, inet->dport, tcpsk->seq, tcpsk->ack_seq, 
		       14200, tcp_hdr(skb));
	return ip_send_packet(inet, skb);
}

int tcp_v4_recvmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg,
			size_t len, int noblock, int flags, int *addr_len) {
	struct sk_buff *skb;

	if (sk->sk_state != TCP_ESTABIL) {
		return -EINVAL;
	}

	skb = skb_recv_datagram(sk, flags, 0, 0);
	if (skb && skb->len > 0) {
		struct tcphdr *tcph = tcp_hdr(skb);
		if (len > (skb->nh.iph->tot_len - TCP_V4_HEADER_SIZE(tcph))) {
			len = skb->nh.iph->tot_len - TCP_V4_HEADER_SIZE(tcph);
		}
		memcpy((void *) msg->msg_iov->iov_base,
				(void *) (skb->h.raw + TCP_V4_HEADER_SIZE(tcph)), len);
		kfree_skb(skb);
	} else {
		len = 0;
	}
	msg->msg_iov->iov_len = len;
	return len;
}
//TODO move to hash table routines
static void tcp_v4_hash(struct sock *sk) {
	size_t i;
	for (i = 0; i< CONFIG_MAX_KERNEL_SOCKETS; i++) {
		if (tcp_hash[i] == NULL) {
			tcp_hash[i] = (tcp_sock_t *) sk;
			break;
		}
	}
}

static void tcp_v4_unhash(struct sock *sk) {
	size_t i;
	for (i = 0; i< CONFIG_MAX_KERNEL_SOCKETS; i++) {
		if (tcp_hash[i] == (tcp_sock_t *) sk) {
			tcp_hash[i] = NULL;
			break;
		}
	}
}
static struct tcp_sock *tcp_lookup(in_addr_t daddr, __be16 dport) {
	struct inet_sock *inet;
	size_t i;
	for (i = 0; i< CONFIG_MAX_KERNEL_SOCKETS; i++) {
		inet = inet_sk((struct sock*) tcp_hash[i]);
		if (inet) {
			if ((inet->rcv_saddr == INADDR_ANY || inet->rcv_saddr == daddr) &&
					inet->sport == dport) {
				return (struct tcp_sock*) inet;
			}
		}
	}
	return NULL;
}
//TODO end of hash table routines

#define TCP_ST_SEND 1
#define TCP_ST_NO_SEND 1

static void tcp_set_st(struct tcp_sock *tcpsk, char state) {
	TCP_SOCK(tcpsk)->sk_state = state;
}
#if 0
static inline int tcp_opt_process(struct tcphdr *tcph, struct tcphdr *otcph, struct tcp_sock *tcpsk) {
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
			tcpsk->mss = ntohs((__be16) *ptr); 
		}
	}
	return 0;
}
#endif
static int tcp_st_listen(struct tcp_sock *tcpsk, struct sk_buff *skb, 
		tcphdr_t *tcph, tcphdr_t *out_tcph) {
	if (TCP_SOCK(tcpsk)->sk_state != TCP_LISTEN) {
		return TCP_ST_NO_SEND;
	}
	if (tcph->ack) {
		// segment RST
		out_tcph->seq = tcph->ack_seq;
		out_tcph->rst |= 1;
		return TCP_ST_SEND;
	}
	if (tcph->syn) {
		tcpsk->seq_unack = 100;
		tcpsk->seq = tcpsk->seq_unack + 1;
		tcpsk->ack_seq = ntohl(tcph->seq) + 1;

		out_tcph->syn |= 1;
		out_tcph->ack |= 1;

		tcp_set_st(tcpsk, TCP_SYN_RECV);

		return TCP_ST_SEND;
	}
	return TCP_ST_NO_SEND;
}

static int tcp_v4_listen(struct sock *sk, int backlog) {
	sk->sk_state = TCP_LISTEN;
	return 0;
}

static int (*tcp_st_handler[TCP_MAX_STATE])(struct tcp_sock *tcpsk, 
		struct sk_buff *skb, tcphdr_t *tcph, tcphdr_t *out_tcph) = {
	[TCP_LISTEN] = tcp_st_listen
};

static int tcp_v4_rcv(sk_buff_t *skb) {
	iphdr_t *iph = ip_hdr(skb);
	tcphdr_t *tcph = tcp_hdr(skb);
	struct tcp_sock *sock = tcp_lookup(iph->daddr, tcph->dest);

	char out_tcph_raw[TCP_V4_HEADER_MIN_SIZE];
	tcphdr_t *out_tcph = (tcphdr_t *) out_tcph_raw;

	if (sock == NULL) {
		return -1;
	}
	memset(out_tcph, 0, TCP_V4_HEADER_SIZE(out_tcph));	
	if (tcp_st_handler[TCP_SOCK(sock)->sk_state](sock, skb, tcph, out_tcph) 
			== TCP_ST_SEND) {
		uint32_t ip_dest = skb->nh.iph->daddr;
		uint32_t ip_src  = skb->nh.iph->saddr;

		rebuild_tcp_header(ip_dest, ip_src, tcph->source, tcph->dest,
			       	htonl(sock->seq_unack), htonl(sock->ack_seq),
				14200, out_tcph);

		memcpy(tcp_hdr(skb), out_tcph, TCP_V4_HEADER_MIN_SIZE);
		skb->len = ETH_HEADER_SIZE + 
				IP_HEADER_SIZE(iph) + TCP_V4_HEADER_MIN_SIZE;
		ip_send_reply(NULL, ip_dest, ip_src, skb, ETH_HEADER_SIZE + 
				IP_HEADER_SIZE(iph) + TCP_V4_HEADER_MIN_SIZE);
	}
	return 0;
}

struct proto tcp_prot = {
	.name                   = "TCP",
	.init                   = tcp_v4_init_sock,
	.hash                   = tcp_v4_hash,
	.unhash                 = tcp_v4_unhash,
	.listen			= tcp_v4_listen,
	.sendmsg		= tcp_v4_sendmsg,
	.recvmsg		= tcp_v4_recvmsg,
	.sock_alloc		= tcp_v4_sock_alloc,
	.sock_free		= tcp_v4_sock_free
#if 0
	.owner                  = THIS_MODULE,
	.close                  = tcp_close,
	.connect                = tcp_v4_connect,
	.disconnect             = tcp_disconnect,
	.accept                 = inet_csk_accept,
	.ioctl                  = tcp_ioctl,
	.destroy                = tcp_v4_destroy_sock,
	.shutdown               = tcp_shutdown,
	.setsockopt             = tcp_setsockopt,
	.getsockopt             = tcp_getsockopt,
	.recvmsg                = tcp_recvmsg,
	.backlog_rcv            = tcp_v4_do_rcv,
	.get_port               = inet_csk_get_port,
	.enter_memory_pressure  = tcp_enter_memory_pressure,
	.sockets_allocated      = &tcp_sockets_allocated,
	.orphan_count           = &tcp_orphan_count,
	.memory_allocated       = &tcp_memory_allocated,
	.memory_pressure        = &tcp_memory_pressure,
	.sysctl_mem             = sysctl_tcp_mem,
	.sysctl_wmem            = sysctl_tcp_wmem,
	.sysctl_rmem            = sysctl_tcp_rmem,
	.max_header             = MAX_TCP_HEADER,
	.obj_size               = sizeof(struct tcp_sock),
	.slab_flags             = SLAB_DESTROY_BY_RCU,
	.twsk_prot              = &tcp_timewait_sock_ops,
	.rsk_prot               = &tcp_request_sock_ops,
	.h.hashinfo             = &tcp_hashinfo,
#endif
};


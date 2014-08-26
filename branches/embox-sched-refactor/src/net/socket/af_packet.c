/**
 * @file
 * @brief PF_PACKET protocol family socket handler
 *
 * @date 30.01.12
 * @author Anton Bondarev
 */

#include <errno.h>
#include <stdlib.h>
#include <mem/misc/pool.h>
#include <kernel/softirq_lock.h>
#include <framework/mod/options.h>
#include <framework/net/sock/self.h>
#include <embox/net/family.h>
#include <net/sock.h>
#include <sys/socket.h>
#include <net/l3/ipv4/ip.h>
#include <net/l2/ethernet.h>
#include <net/if.h>
#include <netpacket/packet.h>
#include <net/sock_wait.h>
#include <net/socket/packet.h>
#include <sys/uio.h>

#define MODOPS_AMOUNT_SOCKETS OPTION_GET(NUMBER, amount_sockets)

static const struct sock_family_ops packet_raw_ops;
static const struct net_family_type packet_types[] = {
	{ SOCK_STREAM, NULL },
	{ SOCK_DGRAM, NULL},
	{ SOCK_RAW, &packet_raw_ops }
};
static const struct net_pack_out_ops packet_out_ops_struct;
static const struct net_pack_out_ops *const packet_out_ops = &packet_out_ops_struct;
EMBOX_NET_FAMILY(AF_PACKET, packet_types, packet_out_ops);

static const struct sock_proto_ops packet_sock_ops_struct;
EMBOX_NET_SOCK(AF_PACKET, SOCK_RAW, 0x300 /*htons(ETH_P_ALL)*/, 0, packet_sock_ops_struct);

struct packet_sock {
	struct sock sk;
	struct dlist_head lnk;
	struct sockaddr_ll sll;
	struct sk_buff_head rx_q;
};

POOL_DEF(packet_sock_pool, struct packet_sock, 2);

static DLIST_DEFINE(packet_g_sock_list);

static inline struct packet_sock *sk2packet(struct sock *sk) {
	return member_cast_out(sk, struct packet_sock, sk);
}

static inline void af_packet_rcv_lock(void) {
	softirq_lock();
}

static inline void af_packet_rcv_unlock(void) {
	softirq_unlock();
}

static int packet_sock_init(struct sock *sk) {
	struct packet_sock *psk = sk2packet(sk);

	dlist_head_init(&psk->lnk);
	memset(&psk->sll, 0, sizeof(psk->sll));
	skb_queue_init(&psk->rx_q);

	af_packet_rcv_lock();
	{
		dlist_add_prev(&psk->lnk, &packet_g_sock_list);
	}
	af_packet_rcv_unlock();
	
	return 0;
}

static int packet_sock_close(struct sock *sk) {
	struct packet_sock *psk = sk2packet(sk);

	af_packet_rcv_lock();
	{
		dlist_del(&psk->lnk);
	}
	af_packet_rcv_unlock();

	skb_queue_purge(&psk->rx_q);
	sock_release(sk);
	return 0;
}

static int packet_sock_bind(struct sock *sk, const struct sockaddr *addr,
		socklen_t addrlen) {
	struct packet_sock *psk = sk2packet(sk);
	struct sockaddr_ll *newsll = (struct sockaddr_ll *) addr;

	assert(sk);
	assert(addr);

	if (addrlen != sizeof(struct sockaddr_ll)) {
		return -EINVAL;
	}

	if (newsll->sll_family != AF_PACKET) {
		return -EINVAL;
	}

	af_packet_rcv_lock();
	{
		memcpy(&psk->sll, addr, sizeof(psk->sll));
		skb_queue_purge(&psk->rx_q);
	}
	af_packet_rcv_unlock();

	return 0;
}

static void packet_sll_fill(struct sockaddr_ll *sll, struct sk_buff *skb) {
	sll->sll_family = AF_PACKET;
	sll->sll_protocol = htons(ETH_P_ALL); /* XXX */
	sll->sll_ifindex = skb->dev->index;
	sll->sll_hatype = 0;
	sll->sll_pkttype = pkt_type(skb);
	sll->sll_halen = 0;
	memset(&sll->sll_addr, 0, sizeof(sll->sll_addr));
}

static int packet_recvmsg(struct sock *sk, struct msghdr *msg,
		int flags) {
	struct packet_sock *psk = sk2packet(sk);
	struct sk_buff *skb;
	int n_byte, skb_err;

	af_packet_rcv_lock();
	{

		do {
			skb = skb_queue_pop(&psk->rx_q);
			if (skb) {
				break;
			}
			skb_err = sock_wait(sk, POLLIN | POLLERR, 0);
		} while (0 == skb_err);
	}
	af_packet_rcv_unlock();

	if (!skb) {
		return skb_err;
	}

	if (msg->msg_namelen >= sizeof(struct sockaddr_ll)) {
		packet_sll_fill(msg->msg_name, skb);
	}

	sock_update_tstamp(sk, skb);

	/* XXX now called only on tun, copy from nh.
 	 * Whole packet should be stored in future, and for tun it will be
	 * starting from ip header
	 */
	n_byte = skb_write_iovec(skb->nh.raw, skb->len - (skb->nh.raw - skb->mac.raw), 
			msg->msg_iov, msg->msg_iovlen); 

	skb_free(skb);
	msg->msg_iov->iov_len = n_byte; /* XXX */
	return 0;
}

static int packet_sendmsg(struct sock *sk, struct msghdr *msg, int flags) {
	return 0;
}
 
static int packet_sock_setsockopt(struct sock *sk, int level,
		int optname, const void *optval, socklen_t optlen) {

	if (optname == SO_ATTACH_FILTER) {
		return 0;
	}

	return -ENOTSUP;
}

static const struct sock_family_ops packet_raw_ops = {
	.init        = packet_sock_init,
	.close       = packet_sock_close,
	.bind        = packet_sock_bind,
	.sendmsg     = packet_sendmsg,
	.recvmsg     = packet_recvmsg,
	.setsockopt  = packet_sock_setsockopt,
	.sock_pool   = &packet_sock_pool
};

void sock_packet_add(struct sk_buff *skb) {
	struct packet_sock *psk;

	dlist_foreach_entry(psk, &packet_g_sock_list, lnk) {
		if (psk->sll.sll_ifindex == 0 
				|| psk->sll.sll_ifindex == skb->dev->index) {
			skb_queue_push(&psk->rx_q, skb_clone(skb));
			sock_notify(&psk->sk, POLLIN | POLLERR);
		}
	}
}

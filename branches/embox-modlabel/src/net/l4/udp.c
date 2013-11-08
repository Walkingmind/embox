/**
 * @file
 * @brief The User Datagram Protocol (UDP).
 * @details RFC 768
 *
 * @date 26.03.09
 * @author Nikolay Korotky
 */

#include <stdlib.h>
#include <embox/net/proto.h>
#include <net/l3/ipv4/ip.h>
#include <net/l4/udp.h>
#include <net/lib/udp.h>
#include <net/l3/icmpv4.h>
#include <assert.h>
#include <errno.h>
#include <net/socket/inet_sock.h>
#include <arpa/inet.h>
#include <net/netdevice.h>
#include <framework/net/sock/api.h>

static void udp_err(const struct sk_buff *skb, int error_info);

EMBOX_NET_PROTO(ETH_P_IP, IPPROTO_UDP, udp_rcv, udp_err);

static int udp_rcv_tester(const struct sock *sk,
		const struct sk_buff *skb) {
	const struct inet_sock *in_sk;

	in_sk = (const struct inet_sock *)sk;
	assert(in_sk != NULL);
	assert(in_sk->src_in.sin_family == AF_INET);

	assert(skb != NULL);
	assert(skb->nh.iph != NULL);
	assert(skb->h.uh != NULL);

	return ((in_sk->src_in.sin_addr.s_addr == skb->nh.iph->daddr)
				|| (in_sk->src_in.sin_addr.s_addr == INADDR_ANY))
			&& (in_sk->src_in.sin_port == skb->h.uh->dest);
}

static int udp_accept_dst(const struct inet_sock *in_sk,
		const struct sk_buff *skb) {
	assert(in_sk != NULL);
	assert(in_sk->dst_in.sin_family == AF_INET);

	assert(skb != NULL);
	assert(skb->nh.iph != NULL);
	assert(skb->h.uh != NULL);

	return ((in_sk->dst_in.sin_addr.s_addr == skb->nh.iph->daddr)
				|| (in_sk->dst_in.sin_addr.s_addr == INADDR_ANY))
			&& ((in_sk->dst_in.sin_port == skb->h.uh->source)
				|| (in_sk->dst_in.sin_port == 0))
			&& ((in_sk->sk.opt.so_bindtodevice == skb->dev)
				|| (in_sk->sk.opt.so_bindtodevice == NULL));
}

static int udp_rcv(struct sk_buff *skb) {
	struct sock *sk;
	uint16_t old_check;

	assert(skb != NULL);

	/* Check CRC */
	old_check = skb->h.uh->check;
	udp4_set_check_field(skb->h.uh, skb->nh.iph);
	if (old_check != skb->h.uh->check) {
		return 0; /* error: bad checksum */
	}

	sk = sock_lookup(NULL, udp_sock_ops, udp_rcv_tester, skb);
	if (sk != NULL) {
		if (udp_accept_dst(to_inet_sock(sk), skb)) {
			sock_rcv(sk, skb, skb->h.raw + UDP_HEADER_SIZE,
					ntohs(skb->h.uh->len) - UDP_HEADER_SIZE);
		}
		else {
			skb_free(skb);
		}
	}
	else {
		icmp_send(skb, ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, 0);
	}

	return 0;
}

static int udp_err_tester(const struct sock *sk,
		const struct sk_buff *skb) {
	const struct inet_sock *in_sk;
	const struct iphdr *emb_pack_iphdr;
	const struct udphdr *emb_pack_udphdr;

	in_sk = (const struct inet_sock *)sk;
	assert(in_sk != NULL);
	assert(in_sk->src_in.sin_family == AF_INET);
	assert(in_sk->dst_in.sin_family == AF_INET);

	assert(skb != NULL);
	assert(skb->h.raw != NULL);
	emb_pack_iphdr = (const struct iphdr *)(skb->h.raw
			+ IP_HEADER_SIZE(skb->nh.iph) + ICMP_HEADER_SIZE);

	assert(skb->nh.raw != NULL);
	emb_pack_udphdr = (const struct udphdr *)(skb->h.raw
			+ IP_HEADER_SIZE(skb->nh.iph) + ICMP_HEADER_SIZE
			+ IP_HEADER_SIZE(emb_pack_iphdr));

	return (((in_sk->src_in.sin_addr.s_addr == skb->nh.iph->daddr)
					&& (in_sk->src_in.sin_addr.s_addr == emb_pack_iphdr->saddr))
				|| (in_sk->src_in.sin_addr.s_addr == INADDR_ANY))
			&& (in_sk->src_in.sin_port == emb_pack_udphdr->source)
			&& (((in_sk->dst_in.sin_addr.s_addr == skb->nh.iph->saddr)
					&& (in_sk->dst_in.sin_addr.s_addr == emb_pack_iphdr->daddr))
				|| (in_sk->dst_in.sin_addr.s_addr == INADDR_ANY))
			&& ((in_sk->dst_in.sin_port == emb_pack_udphdr->dest)
				|| (in_sk->dst_in.sin_port == 0))
			&& (in_sk->sk.opt.so_protocol == emb_pack_iphdr->proto)
			&& ((in_sk->sk.opt.so_bindtodevice == skb->dev)
				|| (in_sk->sk.opt.so_bindtodevice == NULL));
}

static void udp_err(const struct sk_buff *skb, int error_info) {
	struct sock *sk;

	sk = NULL;

	while (1) {
		sk = sock_lookup(sk, udp_sock_ops, udp_err_tester, skb);
		if (sk == NULL) {
			break;
		}

		sock_set_so_error(sk, error_info);
	}
}

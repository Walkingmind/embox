/**
 * @file
 * @brief The Internet Protocol (IP) output module.
 *
 * @date 03.12.09
 * @author Nikolay Korotky
 */

#include <err.h>
#include <net/ip.h>
#include <net/udp.h>
#include <net/inet_sock.h>
#include <net/inetdevice.h>
#include <net/route.h>
#include <net/checksum.h>
#include <linux/init.h>
#include <net/ip_fragment.h>
#include <net/skbuff.h>

/* Generate a checksum for an outgoing IP datagram. */
static inline void ip_send_check(iphdr_t *iph) {
	iph->check = 0;
	iph->check = ptclbsum((void *) iph, IP_HEADER_SIZE(iph));
}

int rebuild_ip_header(sk_buff_t *skb, unsigned char ttl, unsigned char proto,
		unsigned short id, unsigned short len, in_addr_t saddr,
		in_addr_t daddr/*, ip_options_t *opt*/) {
	iphdr_t *hdr = skb->nh.iph;
	hdr->version = 4;
	hdr->ihl = IP_MIN_HEADER_SIZE >> 2 /* + opt->optlen */;
	hdr->saddr = saddr; // Changed as in_addr_t is in network-ordered
	hdr->daddr = daddr;
	hdr->tot_len = htons(len - ETH_HEADER_SIZE);
	hdr->ttl = htons(ttl);
	hdr->id = htons(id);
	hdr->tos = 0;
	hdr->frag_off = skb->offset;
	hdr->frag_off |= IP_DF;
	hdr->frag_off = htons(hdr->frag_off);
	hdr->proto = proto;
	ip_send_check(hdr);
	return 0;
}

static int build_ip_packet(struct inet_sock *sk, sk_buff_t *skb) {
	skb->nh.raw = skb->data + ETH_HEADER_SIZE;
	rebuild_ip_header(skb, sk->uc_ttl, sk->sk.sk_protocol, sk->id, skb->len,
			sk->saddr, sk->daddr/*, sk->opt*/);
	return 0;
}

#define LB_ADDRESS 0x0100007F 	/* loopback = 127.0.0.1 */

int ip_queue_xmit(sk_buff_t *skb, int ipfragok) {
	skb->protocol = ETH_P_IP;
	/* check if we are sending ip packet to our machine */
	if(skb->nh.iph->daddr == skb->nh.iph->saddr &&
		 skb->nh.iph->daddr != LB_ADDRESS){ /* loopback has it's own interface */
		netif_rx(skb);
		return 0;
	}
	return dev_queue_xmit(skb);
}

int ip_send_packet(struct inet_sock *sk, sk_buff_t *skb) {
	struct sk_buff_head *tx_buf;
	struct sk_buff *tmp;
	int res;

	res = 0;

	skb->nh.raw = (unsigned char *) skb->data + ETH_HEADER_SIZE;

	if (skb->len > MTU && !(skb->offset & IP_DF)) {
		tx_buf = ip_frag(skb);
		while ((tmp = skb_dequeue(tx_buf)) != NULL) {
			res += ip_send_packet(sk, tmp);
		}
		skb_queue_purge(tx_buf);
		return res;
	}

	if (sk->sk.sk_type != SOCK_RAW) {
		build_ip_packet(sk, skb);
	}
	if (ip_route(skb)) {
		kfree_skb(skb);
		return -1;
	}
	ip_send_check(skb->nh.iph);
	return ip_queue_xmit(skb, 0);
}

void ip_send_reply(struct sock *sk, in_addr_t saddr, in_addr_t daddr,
		sk_buff_t *skb, unsigned int len) {
	skb->nh.iph->saddr = saddr;
	skb->nh.iph->daddr = daddr;
	skb->nh.iph->id = htons(ntohs(skb->nh.iph->id) + 1);
	skb->nh.iph->frag_off = htons(IP_DF);
	ip_send_check(skb->nh.iph);
	ip_queue_xmit(skb, 0);
}

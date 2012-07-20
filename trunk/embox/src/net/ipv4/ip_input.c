/**
 * @file
 * @brief The Internet Protocol (IP) module.
 *
 * @date 17.03.09
 * @author Alexandr Batyukov
 * @author Nikolay Korotky
 * @author Vladimir Sokolov
 */

#include <err.h>
#include <string.h>
#include <net/ip.h>
#include <net/icmp.h>
#include <net/udp.h>
#include <net/raw.h>
#include <net/inet_sock.h>
#include <net/inetdevice.h>
#include <net/route.h>
#include <net/checksum.h>
#include <net/protocol.h>
#include <framework/net/proto/api.h>
#include <net/ip_fragment.h>
#include <net/neighbour.h>

int ip_rcv(sk_buff_t *skb, net_device_t *dev,
			packet_type_t *pt, net_device_t *orig_dev) {
	net_device_stats_t *stats = dev->netdev_ops->ndo_get_stats(skb->dev);
	const struct net_proto *net_proto_ptr = NULL;
	net_protocol_t *p_netproto;
	iphdr_t *iph = ip_hdr(skb);
	unsigned short tmp;
	unsigned int len;
	int optlen;
	sk_buff_t *complete_skb;

	/**
	 *   RFC1122: 3.1.2.2 MUST silently discard any IP frame that fails the checksum.
	 *   Is the datagram acceptable?
	 *   1.  Length at least the size of an ip header
	 *   2.  Version of 4
	 *   3.  Checksums correctly. [Speed optimisation for later, skip loopback checksums]
	 *   4.  Doesn't have a bogus length
	 */
	if (iph->ihl < 5 || iph->version != 4) {
		LOG_ERROR("invalid IPv4 header\n");
		stats->rx_err++;
		skb_free(skb);
		return NET_RX_DROP;
	}

	len = ntohs(iph->tot_len);
	if (skb->len < len || len < IP_HEADER_SIZE(iph)) {
		LOG_ERROR("invalid IPv4 header length\n");
		stats->rx_length_errors++;
		skb_free(skb);
		return NET_RX_DROP;
	}

	tmp = iph->check;
	iph->check = 0;
	if (tmp != ptclbsum(iph, IP_HEADER_SIZE(iph))) {
		LOG_ERROR("bad ip checksum\n");
		stats->rx_crc_errors++;
		skb_free(skb);
		return NET_RX_DROP;
	}

	optlen = IP_HEADER_SIZE(iph) - IP_MIN_HEADER_SIZE;
	if (optlen > 0) {
		/* NOTE : maybe it'd be better to copy skb here,
		 * 'cause options may cause modifications
		 * but smart people who wrote linux kernel
		 * say that this is extremely rarely needed
		 */
		ip_options_t *opts = (ip_options_t*)(skb->cb);

		memset(skb->cb, 0, sizeof(skb->cb));
		opts->optlen = optlen;
		if (ip_options_compile(skb, opts)) {
			stats->rx_err++;
			skb_free(skb);
			return NET_RX_DROP;
		}
		if (ip_options_handle_srr(skb)) {
			stats->tx_err++;
			skb_free(skb);
			return NET_RX_DROP;
		}
	}

	/* It's very useful for us to have complete packet even for forwarding
	 * (we may apply any filter, we may perform NAT etc),
	 * but it'll break routing if different parts of a fragmented
	 * packet will use different routes. So they can't be assembled.
	 * See RFC 1812 for details
	 */
	if ((complete_skb = ip_defrag(skb)) == NULL) {
		if (skb == NULL) {
			return NET_RX_DROP;
		}
		return NET_RX_SUCCESS;
	} else {
		skb = complete_skb;
		iph = ip_hdr(complete_skb);
	}
	skb->h.raw = skb->nh.raw + IP_HEADER_SIZE(iph);

	/* Have we it in the neighbors table? */
	if (neighbour_lookup(in_dev_get(dev), iph->saddr) == NULL) {
		neighbour_add(in_dev_get(dev), iph->saddr, skb->mac.ethh->h_source, ATF_COM);
	}

	/* When a packet is received, it is passed to any raw sockets
	 * which have been bound to its protocol or to socket with concrete protocol */
	raw_rcv(skb);

#if 0	/* Forwarding */
	/**
	 * Check the destination address, and if it doesn't match
	 * any of own addresses, retransmit packet according to the routing table.
	 */
	if (!ip_is_local(iph->daddr, true, false)) {
		if (ip_forward_packet(skb) <= 0) {
			return NET_RX_DROP;
		}
		return NET_RX_SUCCESS;
	}
#endif

	net_proto_foreach(net_proto_ptr) {
		p_netproto = net_proto_ptr->netproto;
		if (p_netproto->type == iph->proto) {
			/* if we are here then socket is registered in one of hash tables */
			return p_netproto->handler(skb); // handler must free skb
		}
	}

	skb_free(skb);
	return NET_RX_DROP; /* Nobody wants this packet */
}

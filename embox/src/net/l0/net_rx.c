/**
 * @file
 * @brief
 *
 * @date 19.06.11
 * @author Anton Bondarev
 * @author Ilia Vaprol
 */

#include <assert.h>
#include <embox/net/pack.h>
#include <net/if_packet.h>
#include <net/netdevice.h>
#include <net/skbuff.h>

int net_rx(struct sk_buff *skb) {
	struct net_header_info hdr_info;
	const struct net_pack *npack;

	/* check L2 header size */
	assert(skb != NULL);
	assert(skb->dev != NULL);
	if (skb->len < skb->dev->hdr_len) {
		return 0; /* error: invalid size */
	}

	/* parse L2 header */
	assert(skb->dev->ops != NULL);
	assert(skb->dev->ops->parse_hdr != NULL);
	if (0 != skb->dev->ops->parse_hdr(skb, &hdr_info)) {
		skb_free(skb);
		return 0; /* error: can't parse L2 header */
	}

	/* check recipient on L2 layer */
	switch (pkt_type(skb)) {
	default:
		skb_free(skb);
		return 0; /* not for us */
	case PACKET_HOST:
	case PACKET_LOOPBACK:
	case PACKET_BROADCAST:
	case PACKET_MULTICAST:
		break;
	}

	/* lookup handler for L3 layer */
	npack = net_pack_lookup(hdr_info.type);
	if (npack == NULL) {
		skb_free(skb);
		return 0; /* not supported */
	}

	/* setup L3 header */
	assert(skb->mac.raw != NULL);
	skb->nh.raw = skb->mac.raw + skb->dev->hdr_len;

	/* handling on L3 layer */
	return npack->rcv_pack(skb, skb->dev);
}

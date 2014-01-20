/**
 * @file
 * @brief A Reverse Address Resolution Protocol
 * @details RFC 903
 *
 * @date 29.09.12
 * @author Ilia Vaprol
 */

#include <arpa/inet.h>
#include <assert.h>
#include <embox/net/pack.h>
#include <errno.h>
#include <net/if.h>
#include <net/inetdevice.h>
#include <net/l0/net_tx.h>
#include <net/l2/ethernet.h>
#include <net/l3/arp.h>
#include <net/l3/rarp.h>
#include <net/lib/arp.h>
#include <net/neighbour.h>
#include <net/netdevice.h>
#include <net/skbuff.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <util/math.h>

EMBOX_NET_PACK(ETH_P_RARP, rarp_rcv);

static int rarp_xmit(struct sk_buff *skb) {
	assert(skb != NULL);
	assert(skb->dev != NULL);
	if (skb->dev->flags & IFF_NOARP) {
		skb_free(skb);
		return 0; /* error: rarp doesn't supported by device */
	}

	/* fall through to dev layer */
	return net_tx(skb, NULL);
}

static int rarp_send(struct sk_buff *skb, struct net_device *dev,
		uint16_t pro, uint8_t pln, uint16_t op, const void *sha,
		const void *spa, const void *tha, const void *tpa,
		const void *tar) {
	int ret;
	size_t size;
	struct net_header_info hdr_info;

	assert(skb != NULL);
	assert(dev != NULL);
	assert(pln != 0);
	assert(sha != NULL);
	assert(spa != NULL);
	assert(tha != NULL);
	assert(tpa != NULL);
	assert(tar != NULL);

	size = dev->hdr_len + ARP_CALC_HEADER_SIZE(dev->addr_len, pln);
	if (size > min(dev->mtu, skb_max_size())) {
		if (skb) skb_free(skb); /* TODO */
		return -EMSGSIZE; /* error: hdr size is too big */
	}

	skb = skb_realloc(size, skb);
	if (skb == NULL) {
		return -ENOMEM; /* error: no memory */
	}

	skb->dev = dev;
	skb->nh.raw = skb->mac.raw + dev->hdr_len;

	/* build device specific header */
	/* TODO move to l0 level */
	hdr_info.type = ETH_P_RARP;
	hdr_info.src_hw = sha;
	hdr_info.dst_hw = tar;
	assert(dev->ops != NULL);
	assert(dev->ops->build_hdr != NULL);
	ret = dev->ops->build_hdr(skb, &hdr_info);
	if (ret != 0) {
		skb_free(skb);
		return ret;
	}

	/* build RARP header */
	arp_build(arp_hdr(skb), dev->type, pro, dev->addr_len, pln,
			op, sha, spa, tha, tpa);

	/* and send */
	return rarp_xmit(skb);
}

static int rarp_hnd_request(const struct arphdr *rarph,
		const struct arpbody *rarpb, struct sk_buff *skb,
		struct net_device *dev) {
	int ret;
	uint8_t src_paddr[MAX_ADDR_LEN];
	uint8_t dst_haddr[MAX_ADDR_LEN], dst_paddr[MAX_ADDR_LEN];
	uint8_t tar_haddr[MAX_ADDR_LEN];
	struct in_device *in_dev;

	in_dev = inetdev_get_by_dev(dev);
	assert(in_dev != NULL);

	/* check protocol capabilities */
	if ((rarph->ar_pro != htons(ETH_P_IP))
			|| (rarph->ar_pln != sizeof in_dev->ifa_address)) {
		skb_free(skb);
		return 0; /* FIXME error: only IPv4 is supported */
	}

	/* get source protocol address */
	memcpy(&src_paddr[0], &in_dev->ifa_address, rarph->ar_pln);

	/* get dest addresses */
	memcpy(&dst_haddr[0], rarpb->ar_tha, rarph->ar_hln);
	ret = neighbour_get_paddr(ntohs(rarph->ar_hrd), &dst_haddr[0],
			dev, ntohs(rarph->ar_pro), rarph->ar_pln,
			&dst_paddr[0]);
	if (ret != 0) {
		skb_free(skb);
		return ret != -ENOENT ? ret : 0;
	}

	/* get target hardware address */
	memcpy(&tar_haddr[0], rarpb->ar_sha, rarph->ar_hln);

	/* declone sk_buff */
	if (NULL == skb_declone(skb)) {
		skb_free(skb);
		return -ENOMEM;
	}

	/* send reply */
	return rarp_send(skb, dev, ntohs(rarph->ar_pro),
			rarph->ar_pln, RARP_OP_REPLY, &dev->dev_addr[0],
			&src_paddr[0], &dst_haddr[0], &dst_paddr[0],
			&tar_haddr[0]);
}

static int rarp_hnd_reply(const struct arphdr *rarph,
		const struct arpbody *rarpb, struct sk_buff *skb,
		struct net_device *dev) {
	int ret;

	assert(rarph != NULL);
	assert(rarpb != NULL);

	/* save destination hardware and protocol addresses */
	ret = neighbour_add(ntohs(rarph->ar_pro), rarpb->ar_tpa,
			rarph->ar_pln, dev, ntohs(rarph->ar_hrd),
			rarpb->ar_tha, rarph->ar_hln, 0);

	/* free sk_buff */
	skb_free(skb);

	return ret;
}

static int rarp_rcv(struct sk_buff *skb, struct net_device *dev) {
	struct arphdr *rarph;
	struct arpbody rarpb;

	assert(skb != NULL);
	assert(dev != NULL);

	/* check device flags */
	if (dev->flags & IFF_NOARP) {
		return 0; /* error: rarp doesn't supported by device */
	}

	rarph = arp_hdr(skb);

	/* check hardware and protocol address lengths */
	if (dev->hdr_len + ARP_HEADER_SIZE(rarph) > skb->len) {
		skb_free(skb);
		return 0; /* error: bad packet */
	}

	/* check device capabilities */
	if ((rarph->ar_hrd != htons(dev->type))
			|| (rarph->ar_hln != dev->addr_len)) {
		skb_free(skb);
		return 0; /* error: invalid hardware address info */
	}

	/* build rarp body */
	arp_make_body(rarph, &rarpb);

	/* process the packet by the operation code */
	switch (rarph->ar_op) {
	default:
		skb_free(skb);
		return 0; /* error: bad operation type */
	case htons(RARP_OP_REQUEST):
		/* handling request */
		return rarp_hnd_request(rarph, &rarpb, skb, dev);
	case htons(RARP_OP_REPLY):
		/* handling reply */
		return rarp_hnd_reply(rarph, &rarpb, skb, dev);
	}
}

/**
 * @file
 * @brief Ethernet-type device handling.
 *
 * @date 4.03.09
 * @author Anton Bondarev
 * @author Ilia Vaprol
 */

#include <err.h>
#include <errno.h>
#include <net/arp.h>
#include <net/etherdevice.h>
#include <net/if.h>
#include <net/if_ether.h>
#include <net/netdevice.h>
#include <string.h>

static struct net_device *registered_etherdev[CONFIG_NET_DEVICES_QUANTITY]; // TODO before using must be cleared

int eth_header(sk_buff_t *pack, struct net_device *dev, unsigned short type,
			void *daddr, void *saddr, unsigned len) {
	struct ethhdr *eth;

	assert(pack != NULL);
	assert(dev != NULL);
	assert(saddr != NULL);

	eth = eth_hdr(pack);
	eth->h_proto = htons(type);

	/*  Set the source hardware address. */
	if (saddr == NULL) {
		saddr = dev->dev_addr;
	}
	memcpy(eth->h_source, saddr, ETH_ALEN);

	if (dev->flags & (IFF_LOOPBACK | IFF_NOARP)) {
		/* Anyway, the loopback-device should never use this function... */
		memset(eth->h_dest, 0, ETH_ALEN);
	} else {
		assert(daddr != NULL);

		memcpy(eth->h_dest, daddr, ETH_ALEN);
	}

	return ENOERR;
}

int eth_rebuild_header(sk_buff_t *pack) {
	struct ethhdr *eth;
	struct net_device *dev;

	assert(pack != NULL);

	dev = pack->dev;
	assert(dev != NULL);

	eth = eth_hdr(pack);
	eth->h_proto = htons(pack->protocol);

	if (pack->protocol == ETH_P_IP) {
		/* fill out eth packet source and destination */
		memcpy(eth->h_source, dev->dev_addr, ETH_ALEN);
		return arp_resolve(pack);
	} else if (pack->protocol == ETH_P_ARP) {
		return ENOERR;
	} else {
		LOG_ERROR("%s: unable to resolve type %X addresses.\n",
					dev->name, (int)eth->h_proto);
		return -EINVAL;
	}
}

int eth_header_parse(const sk_buff_t *pack, unsigned char *haddr) {
	assert(pack != NULL);
	assert(haddr != NULL);

	memcpy(haddr, pack->mac.raw, ETH_ALEN);

	return ENOERR;
}

int eth_mac_addr(struct net_device *dev, struct sockaddr *addr) {
	assert(dev != NULL);
	assert(addr != NULL);

	if (!is_valid_ether_addr((const uint8_t *) addr->sa_data)) {
		return -EADDRNOTAVAIL;
	}

	memcpy(dev->dev_addr, addr->sa_data, ETH_ALEN);

	return ENOERR;
}

int eth_change_mtu(struct net_device *dev, int new_mtu) {
	assert(dev != NULL);

	if ((new_mtu < 68) || (new_mtu > ETH_FRAME_LEN)) {
		return -EINVAL;
	}

	dev->mtu = new_mtu;

	return ENOERR;
}

int eth_flag_up(struct net_device *dev, int flag_type) {
	assert(dev != NULL);
	dev->flags |= flag_type;
	return ENOERR;
}

int eth_flag_down(struct net_device *dev, int flag_type) {
	assert(dev != NULL);
	dev->flags &= ~flag_type;
	return ENOERR;
}

int eth_set_irq(struct net_device *dev, int irq_num) {
	assert(dev != NULL);
	dev->irq = irq_num;
	return ENOERR;
}

int eth_set_baseaddr(struct net_device *dev, unsigned long base_addr) {
	assert(dev != NULL);
	dev->base_addr = base_addr;
	return ENOERR;
}

int eth_set_txqueuelen(struct net_device *dev, unsigned long new_len) {
	assert(dev != NULL);
	dev->tx_queue_len = new_len;
	return ENOERR;
}

int eth_set_broadcast_addr(struct net_device *dev, unsigned char *broadcast_addr) {
	assert(dev != NULL);
	assert(broadcast_addr != NULL);

	memcpy((void *)dev->broadcast, (void *)broadcast_addr, ETH_ALEN);
	LOG_ERROR("not realized\n");

	return 0;
}

const struct header_ops eth_header_ops = {
	.create        = eth_header,
	.parse         = eth_header_parse,
	.rebuild       = eth_rebuild_header,
};

const header_ops_t * get_eth_header_ops() {
	return &eth_header_ops;
}

void ether_setup(struct net_device *dev) {
	assert(dev != NULL);
	dev->header_ops    = &eth_header_ops;
	dev->type          = ARPHRD_ETHER;
	dev->mtu           = ETH_FRAME_LEN;
	dev->addr_len      = ETH_ALEN;
	dev->flags         = IFF_BROADCAST | IFF_MULTICAST;
	dev->tx_queue_len  = 1000;
	memset(dev->broadcast, 0xFF, ETH_ALEN);
}

struct net_device * alloc_etherdev(int sizeof_priv) {
	size_t i;
	char buff[IFNAMSIZ];
	struct net_device *ethrdev;

	for (i = 0; i < sizeof registered_etherdev / sizeof registered_etherdev[0]; ++i) {
		if (registered_etherdev[i] == NULL) {
			sprintf(buff, "eth%u", i);
			ethrdev = alloc_netdev(sizeof_priv, buff, ether_setup);
			if (ethrdev == NULL) {
				return NULL;
			}
			registered_etherdev[i] = ethrdev;
			return ethrdev;
		}
	}

	return NULL; /* Memory could not be allocated */
}

void free_etherdev(struct net_device *dev) {
	int idx, res;
	char *name;

	assert(dev != NULL);

	name = dev->name;

	if (strncmp(name, "eth", 3) != 0) {
		return; /* It's not an Ethernet device */
	}

	res = sscanf(name + 3, "%d", &idx);
	assert(res == 1);
	assert((0 <= idx) && (idx < sizeof registered_etherdev / sizeof registered_etherdev[0]));

	registered_etherdev[idx] = NULL;

	free_netdev(dev);
}

__be16 eth_type_trans(struct sk_buff *skb, struct net_device *dev) {
	assert(skb != NULL);
	return skb->mac.ethh->h_proto;
}

uint8_t eth_packet_type(struct sk_buff *skb) {
	struct ethhdr *eth;
	struct net_device *dev;

	assert(skb != NULL);

	dev = skb->dev;
	assert(dev != NULL);

	eth = eth_hdr(skb);

	if (dev == inet_get_loopback_dev()) {
		return PACKET_LOOPBACK;
	}
	
	if (is_multicast_ether_addr(eth->h_dest)) {
		if (!compare_ether_addr(eth->h_dest, dev->broadcast))
			return PACKET_BROADCAST;
		else
			return PACKET_MULTICAST;
	} else {
		if (unlikely(compare_ether_addr(eth->h_dest, dev->dev_addr))) {
			return PACKET_OTHERHOST;
		} else {
			return PACKET_HOST;
		}
	}
}

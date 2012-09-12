/**
 * @file
 * @brief Pseudo-driver for the loopback interface.
 *
 * @date 29.12.09
 * @author Nikolay Korotky
 * @author Dmitry Zubarevich
 */

#include <embox/unit.h>
#include <err.h>
#include <errno.h>
#include <net/etherdevice.h>
#include <net/if_arp.h>
#include <net/if_ether.h>
#include <net/netdevice.h>
#include <net/skbuff.h>
#include <stdlib.h>

EMBOX_UNIT_INIT(unit_init);

static int loopback_xmit(sk_buff_t *skb, struct net_device *dev) {
	net_device_stats_t *lb_stats;

	if ((skb == NULL) || (dev == NULL)) {
		return -EINVAL;
	}

	lb_stats = &(dev->stats);
	if (netif_rx(skb) == NET_RX_SUCCESS) {
		lb_stats->tx_packets++;
		lb_stats->rx_packets++;
		lb_stats->tx_bytes += skb->len;
		lb_stats->rx_bytes += skb->len;
	} else {
		lb_stats->rx_err++;
		lb_stats->tx_err++;
	}
	return ENOERR;
}

static net_device_stats_t * loopback_get_stats(struct net_device *dev) {
	if (dev == NULL) {
		return NULL;
	}

	return &(dev->stats);
}

static const struct net_device_ops loopback_ops = {
	.ndo_start_xmit      = loopback_xmit,
	.ndo_get_stats       = loopback_get_stats,
};

/**
 * The loopback device is special. There is only one instance
 * per network namespace.
 */
static void loopback_setup(struct net_device *dev) {
	dev->mtu                = (16 * 1024) + 20 + 20 + 12;
	dev->addr_len           = ETH_ALEN;
	dev->tx_queue_len       = 0;
	dev->type               = ARPHRD_LOOPBACK;
	dev->flags              = IFF_LOOPBACK;
	dev->netdev_ops         = &loopback_ops;
	dev->header_ops         = eth_get_header_ops();
}

struct net_device *loopback_dev;
/**
 * The initialization of loopback device
 */
static int unit_init(void) {

	loopback_dev = netdev_alloc("lo", &loopback_setup);
	if (loopback_dev == NULL) {
		LOG_ERROR("Can't allocate net device\n");
		return -ENOMEM;
	}

	return netdev_register(loopback_dev);
}


/**
 * @file
 * @brief Protocol independent device support routines.
 *
 * @date 04.03.09
 * @author Anton Bondarev
 * @author Ilia Vaprol
 */

#include <assert.h>
#include <errno.h>
#include <mem/misc/pool.h>
#include <net/if.h>
#include <net/netdevice.h>
#include <net/skbuff.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hal/ipl.h>

/*--------------------------------------------
 * network device registry and name calculator
 * -------------------------------------------
 */
//TODO use hash table instead this
struct net_device *opened_netdevs[CONFIG_NET_DEVICES_QUANTITY]; // FIXME clear before using

int register_netdev(struct net_device *dev) {
	size_t i;

	assert(dev != NULL);

	for (i = 0; i < CONFIG_NET_DEVICES_QUANTITY; ++i) {
		if (opened_netdevs[i] == NULL) {
			opened_netdevs[i] = dev;
			return ENOERR;
		}
	}

	return -ENOMEM;
}

void unregister_netdev(struct net_device *dev) {
	size_t i;

	assert(dev != NULL);

	for (i = 0; i < CONFIG_NET_DEVICES_QUANTITY; ++i) {
		if (opened_netdevs[i] == dev) {
			opened_netdevs[i] = NULL;
			return;
		}
	}
}

struct net_device * netdev_get_by_name(const char *name) {
	size_t i;

	assert(name != NULL);

	for (i = 0; i < CONFIG_NET_DEVICES_QUANTITY; ++i) {
		if (strncmp(name, opened_netdevs[i]->name, IFNAMSIZ) == 0) {
			return opened_netdevs[i];
		}
	}

	return NULL;
}

#if 0
struct net_device * get_dev_by_idx(int idx) {
	if ((idx < 0) || (idx >= CONFIG_NET_DEVICES_QUANTITY)) {
		return NULL;
	}

	return opened_netdevs[idx];
}

struct net_device * dev_getbyhwaddr(unsigned short type, char *hw_addr) {
	size_t i;
	struct net_device *dev;

	for (i = 1; i < CONFIG_NET_DEVICES_QUANTITY; ++i) {
		dev = opened_netdevs[i];
		if ((dev != NULL) && (memcmp(hw_addr, dev->dev_addr, dev->addr_len) == 0)) {
			return dev;
		}
	}

	return NULL;
}
#endif

/*-------------------------------------------
 * network device pool
 * ------------------------------------------
 */
static int process_backlog(struct net_device *dev);
POOL_DEF(netdev_pool, struct net_device, CONFIG_NET_DEVICES_QUANTITY);

struct net_device * alloc_netdev(int sizeof_priv, const char *name,
		void (*setup)(struct net_device *)) {
	struct net_device *dev;

	assert((name != NULL) && (setup != NULL));

	dev = (struct net_device *)pool_alloc(&netdev_pool);
	if (dev == NULL) {
		return NULL;
	}

	setup(dev);

	dev->dev_queue.next = (struct sk_buff *)(&(dev->dev_queue));
	dev->dev_queue.prev = (struct sk_buff *)(&(dev->dev_queue));
	dev->poll = process_backlog;

	strncpy(dev->name, name, IFNAMSIZ);

	return dev;
}

void free_netdev(struct net_device *dev) {
	assert(dev != NULL);
	pool_free(&netdev_pool, dev);
}

/*--------------------------------
 * network device interface
 * -------------------------------
 */
int dev_open(struct net_device *dev) {
	int res;
	const struct net_device_ops *ops;

	/* Is it already up? */
	if (dev->flags & IFF_UP) {
		return ENOERR;
	}

	res = ENOERR;
	ops = dev->netdev_ops;
	dev->state |= __LINK_STATE_START;

	if (ops->ndo_open) {
		res = ops->ndo_open(dev);
	}
	if (res != ENOERR) {
		dev->state &= ~__LINK_STATE_START;
	} else {
		/* Set the flags. */
		/*TODO: IFF_RUNNING sets not here*/
		dev->flags |= (IFF_UP | IFF_RUNNING);
	}

	return res;
}

int dev_close(struct net_device *dev) {
	int res;
	const struct net_device_ops *ops;

	if (!(dev->flags & IFF_UP)) {
		return ENOERR;
	}

	res = ENOERR;
	ops = dev->netdev_ops;
	dev->state &= ~__LINK_STATE_START;

	if (ops->ndo_stop) {
		res = ops->ndo_stop(dev);
	}
	if (res != ENOERR) {
		dev->state |= __LINK_STATE_START;
	} else {
		/* Device is now down. */
		/*TODO: IFF_RUNNING sets not here*/
		dev->flags &= ~(IFF_UP | IFF_RUNNING);
	}

	return res;
}

unsigned int dev_get_flags(const struct net_device *dev) {
	return dev->flags;
}

int dev_set_flags(struct net_device *dev, unsigned int flags) {
	int res, old_flags;
	int (*func)(struct net_device *);

	res = ENOERR;
	old_flags = dev->flags;
	if ((old_flags ^ flags) & IFF_UP) { /* i.e. IFF_UP bit was inverted */
		func = (flags & IFF_UP) ? &dev_open : &dev_close;
		res = func(dev);
	}

	dev->flags = flags;

	return res;
}


/*------------------------------------------------
 *  data processing
 *  --------------------------------------------- */
static int process_backlog(struct net_device *dev) {
	struct sk_buff *skb;

	while ((skb = skb_queue_pop(&(dev->dev_queue))) != NULL) {
		netif_receive_skb(skb);
	}

	return ENOERR;
}

static LIST_HEAD(rx_dev_queue);

int dev_rx_queued(struct net_device *dev) {
	ipl_t sp;

	sp = ipl_save();
	if((NULL == dev->rx_dev_link.next) && (NULL == dev->rx_dev_link.prev)) {
		list_add_tail(&dev->rx_dev_link, &rx_dev_queue);
	}
	ipl_restore(sp);
	return 0;
}

int dev_rx_dequeued(struct net_device *dev) {
	ipl_t sp;

	sp = ipl_save();

	list_del(&dev->rx_dev_link);

	ipl_restore(sp);

	return 0;
}

void dev_rx_processing(void) {
	struct net_device *dev, *save;

	list_for_each_entry_safe(dev, save, &rx_dev_queue, rx_dev_link) {
		dev->poll(dev);
		dev_rx_dequeued(dev);
	}
}

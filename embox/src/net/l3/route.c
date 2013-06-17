/**
 * @file
 * @brief implementation of the IP router.
 *
 * @date 16.11.09
 * @author Nikolay Korotky
 * @author Ilia Vaprol
 * @author Vladimir Sokolov
 */

#include <errno.h>
#include <assert.h>
#include <net/route.h>
#include <net/socket_registry.h>
#include <linux/in.h>
#include <mem/misc/pool.h>
#include <net/inetdevice.h>
#include <util/bit.h>
#include <util/list.h>
#include <util/member.h>

#include <framework/mod/options.h>

/**
 * NOTE: Linux route uses 3 structures for routing:
 *    + Forwarding Information Base (FIB)
 *    - routing cache (256 chains)
 *    + neighbour table (ARP cache)
 */

struct rt_entry_info {
	struct list_link lnk;
	struct rt_entry entry;
};

POOL_DEF(rt_entry_info_pool, struct rt_entry_info, OPTION_GET(NUMBER,route_table_size));
static LIST_DEF(rt_entry_info_list);

int rt_add_route(struct net_device *dev, in_addr_t dst,
		in_addr_t mask, in_addr_t gw, int flags) {
	struct rt_entry_info *rt_info;

	if (dev == NULL) {
		return -EINVAL;
	}

	rt_info = (struct rt_entry_info *)pool_alloc(&rt_entry_info_pool);
	if (rt_info == NULL) {
		return -ENOMEM;
	}
	rt_info->entry.dev = dev;
	rt_info->entry.rt_dst = dst; /* We assume that host bits are zeroes here */
	rt_info->entry.rt_mask = mask;
	rt_info->entry.rt_gateway = gw;
	rt_info->entry.rt_flags = RTF_UP | flags;

	list_add_last_element(rt_info, &rt_entry_info_list, lnk);

	return 0;
}

int rt_del_route(struct net_device *dev, in_addr_t dst,
		in_addr_t mask, in_addr_t gw) {
	struct rt_entry_info *rt_info;

	list_foreach(rt_info, &rt_entry_info_list, lnk) {
		if ((rt_info->entry.rt_dst == dst) &&
                ((rt_info->entry.rt_mask == mask) || (INADDR_ANY == mask)) &&
    			((rt_info->entry.rt_gateway == gw) || (INADDR_ANY == gw)) &&
    			((rt_info->entry.dev == dev) || (INADDR_ANY == dev))) {
			list_unlink_element(rt_info, lnk);
			pool_free(&rt_entry_info_pool, rt_info);
			return 0;
		}
	}

	return -ENOENT;
}

/* svv: ToDo:
 *      1) this function returns -ENOENT/0, but arp_resolve -1/0
 *         style must be the same
 *      2) Carrier without ARP can't be supported
 */
int ip_route(struct sk_buff *skb, struct rt_entry *suggested_route) {
	in_addr_t daddr;
	struct rt_entry *rte;
	struct net_device *wanna_dev;

	assert(skb != NULL);
	assert(skb->nh.iph != NULL);
	daddr = skb->nh.iph->daddr;

	assert(skb->sk != NULL);
	wanna_dev = skb->sk->opt.so_bindtodevice;

	/* SO_BROADCAST assert. */
	if (daddr == INADDR_BROADCAST) {
		if (wanna_dev == NULL) {
			return -ENODEV;
		}
		skb->dev = wanna_dev;
		return 0;
	}

	/* if loopback set lo device */
	if (ip_is_local(daddr, false, false)) {
		assert(inetdev_get_loopback_dev() != NULL);
		skb->dev = inetdev_get_loopback_dev()->dev;
		return 0;
	}

	/* route destanation address */
	rte = ((wanna_dev == NULL)
		? (suggested_route == NULL) ? rt_fib_get_best(daddr, NULL) : suggested_route
		: rt_fib_get_best(daddr, wanna_dev));
	if (rte == NULL) {
		return -ENETUNREACH;
	}

	/* set the device for current destination address */
	assert(rte->dev != NULL);
	assert((wanna_dev == NULL) || (wanna_dev == rte->dev));
	skb->dev = rte->dev;

	/* if the packet should be sent using gateway
	 * nothing todo there. all will be done in arp_resolve */
	return 0;
}

int rt_fib_route_ip(in_addr_t source_addr, in_addr_t *new_addr) {
	struct rt_entry *rte;

	if (source_addr == INADDR_BROADCAST) {
		*new_addr = source_addr;
		return 0;
	}

	rte = rt_fib_get_best(source_addr, NULL);
	if (rte == NULL) {
		return -ENETUNREACH;
	}

	*new_addr = (rte->rt_gateway == INADDR_ANY ? source_addr : rte->rt_gateway);

	return 0;
}

struct rt_entry * rt_fib_get_first(void) {
	if (list_is_empty(&rt_entry_info_list)) {
		return NULL;
	}

	return &list_first_element(&rt_entry_info_list,
			struct rt_entry_info, lnk)->entry;
}

struct rt_entry * rt_fib_get_next(struct rt_entry *entry) {
	struct rt_entry_info *rt_info;

	assert(entry != NULL);

	rt_info = member_cast_out(entry, struct rt_entry_info, entry);
	if (rt_info == list_last_element(&rt_entry_info_list,
			struct rt_entry_info, lnk)) {
		return NULL;
	}

	return &list_element(rt_info->lnk.next,
			struct rt_entry_info, lnk)->entry;
}

/* ToDo: It's too ugly to perform sorting for every packet.
 * Routes must be added into list with mask_len decrease.
 * In this case we'll simply take the first match
 */
struct rt_entry * rt_fib_get_best(in_addr_t dst, struct net_device *out_dev) {
	struct rt_entry_info *rt_info;
	int mask_len, best_mask_len;
	struct rt_entry *best_rte;

	best_rte = NULL;
	best_mask_len = -1;
	list_foreach(rt_info, &rt_entry_info_list, lnk) {
		mask_len = ~rt_info->entry.rt_mask
			? bit_clz(ntohl(~rt_info->entry.rt_mask)) + 1 : 32;
		if (((dst & rt_info->entry.rt_mask) == rt_info->entry.rt_dst)
				&& (out_dev == NULL || out_dev == rt_info->entry.dev)
				&& (mask_len > best_mask_len)) {
			best_rte = &rt_info->entry;
			best_mask_len = mask_len;
		}
	}

	return best_rte;
}

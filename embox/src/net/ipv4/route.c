/**
 * @file
 * @brief implementation of the IP router.
 *
 * @date 16.11.09
 * @author Nikolay Korotky
 * @author Ilia Vaprol
 * @author Vladimir Sokolov
 */

#include <net/route.h>
#include <errno.h>
#include <util/member.h>
#include <mem/misc/pool.h>
#include <assert.h>
#include <net/inetdevice.h>

#include <lib/list.h>

#include <framework/mod/options.h>


/**
 * NOTE: Linux route uses 3 structures for routing:
 *    + Forwarding Information Base (FIB)
 *    - routing cache (256 chains)
 *    + neighbour table (ARP cache)
 */

struct rt_entry_info {
	struct list_head lnk;
	struct rt_entry entry;
};

POOL_DEF(rt_entry_info_pool, struct rt_entry_info, OPTION_GET(NUMBER,route_table_size));
static LIST_HEAD(rt_entry_info_list);

int rt_add_route(net_device_t *dev, in_addr_t dst,
		in_addr_t mask, in_addr_t gw, int flags) {
	struct rt_entry_info *rt_info;

	assert(dev != NULL);

	rt_info = (struct rt_entry_info *)pool_alloc(&rt_entry_info_pool);
	if (rt_info == NULL) {
		return -ENOMEM;
	}
	rt_info->entry.dev = dev;
	rt_info->entry.rt_dst = dst; /* We assume that host bits are zeroes here */
	rt_info->entry.rt_mask = mask;
	rt_info->entry.rt_gateway = gw;
	rt_info->entry.rt_flags = RTF_UP | flags;

	list_add_tail(&rt_info->lnk, &rt_entry_info_list);

	return ENOERR;
}

int rt_del_route(net_device_t *dev, in_addr_t dst,
		in_addr_t mask, in_addr_t gw) {
	struct rt_entry_info *rt_info;

	assert(dev != NULL);

	list_for_each_entry(rt_info, &rt_entry_info_list, lnk) {
		if (((rt_info->entry.rt_dst == dst) || (INADDR_ANY == dst)) &&
                ((rt_info->entry.rt_mask == mask) || (INADDR_ANY == mask)) &&
    			((rt_info->entry.rt_gateway == gw) || (INADDR_ANY == gw))) {
    		list_del(&rt_info->lnk);
			pool_free(&rt_entry_info_pool, rt_info);
			return ENOERR;
		}
	}

	return -ENOENT;
}

/* svv: ToDo:
 *      1) this function returns -ENOENT/ENOERR, but arp_resolve -1/0
 *         style must be the same
 *      2) Carrier without ARP can't be supported
 */
int ip_route(struct sk_buff *skb, struct rt_entry *suggested_route) {
	in_addr_t daddr = skb->nh.iph->daddr;
	struct rt_entry *rte = (suggested_route ? suggested_route : rt_fib_get_best(daddr));

	assert(skb != NULL);

	if (!rte) {
		return -ENETUNREACH;
	}

	/* set the device for current destination address */
	assert(rte->dev != NULL);
	skb->dev = rte->dev;

	/* if source and destination addresses are equal send via LB interface
	 * svv: suspicious. There is no check (src == dst) in ip_input
	 */
	if (ipv4_is_loopback(daddr)
			|| (daddr == skb->nh.iph->saddr)) {
		skb->dev = inet_get_loopback_dev();
	}

	/* if the packet should be sent using gateway
	 * nothing todo there. all will be done in arp_resolve */
#if 0
	if (rte->rt_gateway != INADDR_ANY) {
		/* the next line coerses arp_resolve to set HW destination address
		 * to gateway's HW address.
		 * Suspicious:
		 *	probably	dev_queue_xmit()->
		 *				dev->header_ops->rebuild()->
		 *				eth_rebuild_header()
		 *	will do the same again and overwrite the result
		 */
		int arp_resolve_result;
		skb->nh.iph->daddr = rte->rt_gateway;
		arp_resolve_result = arp_resolve(skb);
		/* so here we need to return the original destination address */
		skb->nh.iph->daddr = daddr;
		return arp_resolve_result;
	}
#endif

	return ENOERR;
}

int rt_fib_route_ip(in_addr_t source_addr, in_addr_t *new_addr) {
	struct rt_entry *rte;

	if (source_addr == INADDR_BROADCAST) {
		*new_addr = source_addr;
		return ENOERR;
	}

	rte = rt_fib_get_best(source_addr);
	if (rte == NULL) {
		return -ENETUNREACH;
	}

	*new_addr = (rte->rt_gateway == INADDR_ANY ? source_addr : rte->rt_gateway);

	return ENOERR;
}

struct rt_entry * rt_fib_get_first(void) {
	struct rt_entry_info *rt_info;

	if (list_empty(&rt_entry_info_list)) {
		return NULL;
	}

	rt_info = member_cast_out(rt_entry_info_list.next, struct rt_entry_info, lnk);

	return &rt_info->entry;
}

struct rt_entry * rt_fib_get_next(struct rt_entry *entry) {
	struct rt_entry_info *rt_info;

	rt_info = member_cast_out(entry, struct rt_entry_info, entry);

	rt_info = member_cast_out(rt_info->lnk.next, struct rt_entry_info, lnk);

	return (&rt_info->lnk == &rt_entry_info_list) ? NULL : &rt_info->entry;
}

/* ToDo: It's too ugly to perform sorting for every packet.
 * Routes must be added into list with mask_len decrease.
 * In this case we'll simply take the first match
 */
struct rt_entry * rt_fib_get_best(in_addr_t dst) {
	struct rt_entry_info *rt_info;
	int mask_len, best_mask_len;
	struct rt_entry *best_rte;

	best_rte = NULL;
	best_mask_len = -1;
	list_for_each_entry(rt_info, &rt_entry_info_list, lnk) {
		mask_len = ipv4_mask_len(rt_info->entry.rt_mask);
		if (((dst & rt_info->entry.rt_mask) == rt_info->entry.rt_dst)
				&& (mask_len > best_mask_len)) {
			best_rte = &rt_info->entry;
			best_mask_len = mask_len;
		}
	}

	return best_rte;
}

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

#include <util/member.h>
#include <mem/misc/pool.h>

#include <linux/list.h>

#include <net/inetdevice.h>
#include <types.h>


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
	in_addr_t saddr, daddr;
	struct rt_entry *rte;
	struct net_device *wanna_dev;
	struct socket_opt_state *ops;

	assert(skb != NULL);

	assert(skb->nh.iph != NULL);
	daddr = skb->nh.iph->daddr;

	wanna_dev = NULL;

	if ((skb->sk != NULL) && (skb->sk->sk_socket != NULL)) {
		assert(skb->sk->sk_socket->socket_node != NULL);

		ops = &skb->sk->sk_socket->socket_node->options;
		assert(ops != NULL);

		/* kernel_socket_getsockopt(sk->sk.sk_socket, SOL_IP, SO_BINDTODEVICE,
				(char*)dev, NULL); */
		wanna_dev = ops->so_bindtodev;
	}

	/* SO_BROADCAST assert. */
	if (daddr == INADDR_BROADCAST) {
		skb->dev = wanna_dev;
		return ENOERR;
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
	saddr = in_dev_get(skb->dev)->ifa_address;

	/* if source and destination addresses are equal send via LB interface
	 * svv: suspicious. There is no check (src == dst) in ip_input
	 */
	if (ipv4_is_loopback(daddr)
			|| (daddr == saddr)) {
		/* FIXME it's the wrong check. need to check all interfaces
		 * XXX even if saddr and skb->nh.iph->saddr are different? */
		skb->dev = inet_get_loopback_dev();
	}

	/* if the packet should be sent using gateway
	 * nothing todo there. all will be done in arp_resolve */

	return ENOERR;
}

int rt_fib_route_ip(in_addr_t source_addr, in_addr_t *new_addr) {
	struct rt_entry *rte;

	if (source_addr == INADDR_BROADCAST) {
		*new_addr = source_addr;
		return ENOERR;
	}

	rte = rt_fib_get_best(source_addr, NULL);
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

static uint8_t ipv4_mask_len(in_addr_t mask) {
	/* ToDo: reimplement as xor/not, +1 and array map */
	uint8_t m_len = 0;
	while (mask > 0) {
		mask <<= 1;
		m_len++;
	}
	return m_len;
}

/* ToDo: It's too ugly to perform sorting for every packet.
 * Routes must be added into list with mask_len decrease.
 * In this case we'll simply take the first match
 */
struct rt_entry * rt_fib_get_best(in_addr_t dst, net_device_t *out_dev) {
	struct rt_entry_info *rt_info;
	int mask_len, best_mask_len;
	struct rt_entry *best_rte;

	best_rte = NULL;
	best_mask_len = -1;
	list_for_each_entry(rt_info, &rt_entry_info_list, lnk) {
		mask_len = ipv4_mask_len(rt_info->entry.rt_mask);
		if (((dst & rt_info->entry.rt_mask) == rt_info->entry.rt_dst)
				&& (out_dev == NULL || out_dev == rt_info->entry.dev)
				&& (mask_len > best_mask_len)) {
			best_rte = &rt_info->entry;
			best_mask_len = mask_len;
		}
	}

	return best_rte;
}

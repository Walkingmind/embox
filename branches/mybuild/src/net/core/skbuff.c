/**
 * @file
 * @details sk_buff management API implementation.
 *
 * @date 20.10.09
 * @author Anton Bondarev
 * @author Ilia Vaprol
 */

#include <stdio.h>
#include <hal/ipl.h>
#include <linux/init.h>
#include <linux/list.h>
#include <mem/misc/pool.h>
#include <net/ip.h>
#include <net/skbuff.h>
#include <string.h>
#include <assert.h>


POOL_DEF(skb_pool, struct sk_buff, CONFIG_QUANTITY_SKB);
POOL_DEF(skb_queue_pool, struct sk_buff_head, CONFIG_QUANTITY_SKB_QUEUE);
POOL_DEF(net_buff_pool, unsigned char[SK_BUF_EXTRA_HEADROOM + CONFIG_ETHERNET_V2_FRAME_SIZE], CONFIG_PACK_POOL_SIZE);

/**
 * Allocate net_packet_buff for one ethernet packet on the cache.
 * @return net_packet
 */
static unsigned char * net_buff_alloc(void) {
	ipl_t sp;
	unsigned char *buff;

	sp = ipl_save();
	buff = pool_alloc(&net_buff_pool);
	ipl_restore(sp);

	return buff;
}

/**
 * Free buff of net packet.
 * @param buff
 */
static void net_buff_free(unsigned char *buff) {
	ipl_t sp;

	/* printk("deallocating 0x%X\n", (unsigned int)buff); */

	sp = ipl_save();
	pool_free(&net_buff_pool, buff);
	ipl_restore(sp);
}

struct sk_buff_head * alloc_skb_queue(void) {
	ipl_t sp;
	struct sk_buff_head *queue;

	sp = ipl_save();
	queue = (struct sk_buff_head *)pool_alloc(&skb_queue_pool);
	ipl_restore(sp);
	if (queue == NULL) {
		return NULL;
	}
	/* in free queue we held structure sk_buff_head but this pointer has sk_buff * type
	 * we must assignment it
	 */
	INIT_LIST_HEAD((struct list_head *)queue);

	return queue;
}

void kfree_skb(struct sk_buff *skb) {
	ipl_t sp;

	if (skb == NULL) {
		return;
	}

	net_buff_free(skb->head);

	sp = ipl_save();

	if ((skb->prev != NULL) && (skb->next != NULL)) {
		list_del((struct list_head *)skb);
	}
	pool_free(&skb_pool, skb);

	ipl_restore(sp);
}

struct sk_buff * alloc_skb(unsigned int size, gfp_t priority) {
	ipl_t sp;
	struct sk_buff *skb;

	if (size == 0) {
		return NULL;
	}

	sp = ipl_save();
	skb = (struct sk_buff *)pool_alloc(&skb_pool);
	ipl_restore(sp);

	if (skb == NULL) {
		return NULL;
	}

	memset(skb, 0, sizeof(struct sk_buff));

	INIT_LIST_HEAD((struct list_head *) skb);

	skb->head = net_buff_alloc();
	if (skb->head == NULL) {
		kfree_skb(skb);
		return NULL;
	}
	skb->data = skb->head + SK_BUF_EXTRA_HEADROOM;

	skb->len = size;
	skb->mac.raw = skb->data;
	return skb;
}

void skb_queue_tail(struct sk_buff_head *list, struct sk_buff *newsk) {
	ipl_t sp;

	if ((newsk == NULL) || (list == NULL)) {
		return;
	}

	sp = ipl_save();
	list_move_tail((struct list_head *)newsk, (struct list_head *)list);
	ipl_restore(sp);
}

struct sk_buff * skb_peek(struct sk_buff_head *list) {
	struct sk_buff *next;

	if (list == NULL) {
		return NULL;
	}

	next = ((struct sk_buff *)list)->next;
	if (next == (struct sk_buff *)list) {
		return NULL;
	}

	return next;
}

static void skb_unlink(struct sk_buff *skb, struct sk_buff_head *list) {
	struct sk_buff *next, *prev;

	if ((skb == NULL) || (list == NULL)) {
		return;
	}

	next = skb->next;
	prev = skb->prev;
	skb->next = skb->prev = skb;
	next->prev = prev;
	prev->next = next;
}

struct sk_buff * skb_dequeue(struct sk_buff_head *list) {
	ipl_t sp;
	struct sk_buff *skb;

	if (list == NULL) {
		return NULL;
	}

	sp = ipl_save();

	skb = skb_peek(list);
	if (skb != NULL) {

		skb_unlink(skb, list);
	}

	ipl_restore(sp);

	return skb;
}

void skb_queue_purge(struct sk_buff_head *queue) {
	ipl_t sp;
	struct sk_buff *skb;

	if (queue == NULL) {
		return;
	}

	while ((skb = skb_dequeue(queue)) != NULL) {
		kfree_skb(skb);
	}

	sp = ipl_save();
	pool_free(&skb_queue_pool, queue);
	ipl_restore(sp);
}

/**
 * Split buffer to skb queue
 */
/* FIXME size must be less then CONFIG_ETHERNET_V2_FRAME_SIZE */
struct sk_buff * buff_to_skb(unsigned char *buff, unsigned int size) {
	struct sk_buff *skb;

	if ((buff == NULL) || (size == 0)) {
		return NULL;
	}

	skb = alloc_skb(size, 0);
	if (skb == NULL) {
		return NULL;
	}

	memcpy(skb->data, buff, size * sizeof(char));
	skb->protocol = ntohs(skb->mac.ethh->h_proto);
	skb->nh.raw = skb->mac.raw + ETH_HEADER_SIZE;
	if (skb->protocol == ETH_P_IP) {
		skb->h.raw = skb->nh.raw + IP_HEADER_SIZE(skb->nh.iph);
	}

	return skb;
}

static inline struct sk_buff *skb_copydata(const struct sk_buff *skb, gfp_t priority) {
	struct sk_buff *new_pack;

	if (skb == NULL) {
		return NULL;
	}

	new_pack = alloc_skb(skb->len, priority);
	if (new_pack == NULL) {
		return NULL;
	}

	memcpy(new_pack->data, skb->data, skb->len);
	new_pack->len = skb->len;

	/*fix references during copy net_pack*/
	if (skb->h.raw != NULL) {
		new_pack->h.raw = new_pack->data + (skb->h.raw - skb->data);
	}
	if (skb->nh.raw != NULL) {
		new_pack->nh.raw = new_pack->data + (skb->nh.raw - skb->data);
	}
	if (skb->mac.raw != NULL) {
		new_pack->mac.raw = new_pack->data + (skb->mac.raw - skb->data);
	}

	return new_pack;
}

struct sk_buff * skb_clone(struct sk_buff *skb, gfp_t priority) {
	struct sk_buff *clone = skb_copydata(skb, 0);

	if (clone == NULL) {
		return NULL;
	}

	clone->dev = skb->dev;
	clone->pkt_type = skb->pkt_type;
	clone->protocol = skb->protocol;
	clone->sk = skb->sk;

	clone->p_data = clone->data + (skb->p_data - skb->data);
	clone->prot_info = skb->prot_info;

	return clone;
}

struct sk_buff * skb_peek_datagram(struct sock *sk, unsigned flags, int noblock,
		int *err) {
	
	if ((sk == NULL) || (sk->sk_receive_queue == NULL)) {
		return NULL;
	}

	return skb_peek(sk->sk_receive_queue);
}

struct sk_buff *skb_copy_expand(struct sk_buff *skb, int newheadroom, int newtailroom, gfp_t priority) {
	/* ToDo: At least check that we have enough room to keep all as is 
	 *	In current implementation we might just reserve some reasonable amount at head/tail room
	 * ToDo: Should we transparently relink this skb into sk_buff_head chain?
	 */
	return skb;
}

struct sk_buff *skb_checkcopy_expand(struct sk_buff *skb, int headroom, int tailroom, gfp_t priority) {
	/* ToDo: At least check that we have enough room to keep all as is 
	 *	In current implementation we might just reserve some reasonable amount at head/tail room
	 * See also: skb_copy_expand()
	 */
	return skb;
}

void skb_shifthead(struct sk_buff *skb, int headshift) {
	assert(skb->data);
	skb->data -= headshift;
	if(likely(skb->h.raw))
		skb->h.raw -= headshift;
	if(likely(skb->nh.raw))
		skb->nh.raw -= headshift;
	if(likely(skb->mac.raw))
		skb->mac.raw -= headshift;
	assert(skb->head <= skb->data);
	/* ToDo: check end here */
}

struct sk_buff * skb_recv_datagram(struct sock *sk, unsigned flags, int noblock,
		int *err) {
	ipl_t sp;
	
	struct sk_buff *skb = skb_peek_datagram(sk, flags, noblock, err);

	if (skb != NULL) {
		sp = ipl_save();

		skb_unlink(skb, sk->sk_receive_queue);
		
		ipl_restore(sp);
	}

	return skb;
}

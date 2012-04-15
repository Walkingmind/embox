/**
 * @file
 * @brief IP Fragmentation
 *
 * @date 25.11.2011
 * @author Alexander Kalmuk
 */

#include <net/ip_fragment.h>
#include <net/skbuff.h>
#include <mem/objalloc.h>
#include <errno.h>
#include <string.h>
#include <kernel/timer.h>
#include <util/math.h>
#include <net/icmp.h>
#include <net/ip.h>
#include <errno.h>

/**
 * Datagram receive buffer
 */
struct dgram_buf {
	struct sk_buff   *next_skbuff;
	struct sk_buff   *prev_skbuff;
	struct list_head  next_buf; /* linked list pointers */
	in_addr_t         saddr;
	in_addr_t         daddr;
	uint16_t          id;
	uint8_t           protocol;
	int               uncomplete;
	int               meat;
	int               len; /* total length of original datagram */
	struct sys_timer *timer;
	int               proto;
	int               buf_ttl;
};

static LIST_HEAD(__dgram_buf_list);
OBJALLOC_DEF(__dgram_bufs, struct dgram_buf, MAX_BUFS_CNT);

#define dgram_buf_foreach(dgram_buf) \
	list_for_each_entry(dgram_buf, &__dgram_buf_list, next_buf)

#define skbuff_for_each(skb, buf) \
	for(skb = buf->next_skbuff;   \
	   ((struct list_head*)skb)!=(struct list_head*)buf; \
	   skb = skb->next)

#define df_flag(skb) (ntohs(skb->nh.iph->frag_off) & IP_DF)

#define TIMER_TICK 1000

static struct dgram_buf *buf_create(struct iphdr *iph);
static void buf_delete(struct dgram_buf *buf);
static void ip_frag_dgram_buf(struct dgram_buf *buf, struct sk_buff *skb);
static struct sk_buff *build_packet(struct dgram_buf *buf);
static void ttl_handler(struct sys_timer *timer, void *param);;

static void ttl_handler(struct sys_timer *timer, void *param) {
	struct dgram_buf *buf;

	buf = (struct dgram_buf *)param;

	if (buf->buf_ttl == 0) {
		/*icmp_send(buf->next_skbuff, ICMP_TIME_EXCEEDED, ICMP_EXC_FRAGTIME, 0);*/
		buf_delete(buf);
		timer_close(timer);
	} else {
		*(volatile int *)buf->buf_ttl -= 1;
	}
}

static inline struct dgram_buf *ip_find(struct iphdr *iph) {
	struct dgram_buf *buf;

	dgram_buf_foreach(buf) {
		if (buf->daddr == iph->daddr
			&& buf->saddr == iph->saddr
			&& buf->protocol == iph->proto
			&& buf->id == iph->id) {
			return buf;
		}
	}

	return NULL;
}

static void ip_frag_dgram_buf(struct dgram_buf *buf, struct sk_buff *skb) {
	struct sk_buff *tmp;
	int was_added = 0;
	int offset, tmp_offset;
	int data_len, end;

	buf->buf_ttl = max(buf->buf_ttl, ntohs(skb->nh.iph->ttl));

	offset = ntohs(skb->nh.iph->frag_off);
	offset &= IP_OFFSET;
	offset <<= 3;

	data_len = skb->len - (skb->h.raw - skb->mac.raw);
	end = offset + data_len;

	skbuff_for_each(tmp, buf) {
		tmp_offset = ntohs(tmp->nh.iph->frag_off);
		tmp_offset &= IP_OFFSET;
		tmp_offset <<= 3;
		if (offset < tmp_offset) {
			list_add((struct list_head *) skb, (struct list_head *) tmp->prev);
			was_added = 1;
			break;
		}
	}

	if (!was_added) {
		list_add_tail((struct list_head *) skb, (struct list_head *) buf);
	}

	buf->meat += data_len;
	if (end > buf->len) {
		buf->len = end;
	}
}

static struct sk_buff *build_packet(struct dgram_buf *buf) {
	struct sk_buff *skb;
	struct sk_buff *tmp;
	int offset = 0;
	int ihlen;

	tmp = buf->next_skbuff;

	ihlen = (tmp->h.raw - tmp->mac.raw);
	skb = alloc_skb(buf->len + ihlen, 0);
		/* Strange:
		 *	- it might return NULL, because length is too big now.
		 *	- ihlen has upper limit. So it's more wise to has such
		 *	amount of extra space in the pool (NOT shared with ICMP)
		 */
	assert(skb);
	memcpy(skb->mac.raw, tmp->mac.raw, tmp->len);

		/* Terrible. Some pointers might be NULL here. sk pointer is omitted */
	skb->h.raw = skb->mac.raw + (tmp->h.raw - tmp->mac.raw);
	skb->nh.raw = skb->mac.raw + (tmp->nh.raw - tmp->mac.raw);
	skb->protocol = tmp->protocol;
	skb->dev = tmp->dev;

	/* copy and concatenate data */
	while(!list_empty((struct list_head *)buf)) {
		memcpy(skb->mac.raw + ihlen + offset, tmp->mac.raw + ihlen, tmp->len - ihlen);
		offset += tmp->len - ihlen;
		list_del((struct list_head *)tmp);
		kfree_skb(tmp);
		tmp = buf->next_skbuff;
	}

	/* recalculate length */
	skb->len = buf->len + ihlen;
	buf_delete(buf);

	return skb;
}

static struct dgram_buf *buf_create(struct iphdr *iph) {
	struct dgram_buf *buf;
	sys_timer_t *timer;

	buf = (struct dgram_buf*) objalloc(&__dgram_bufs);
	if (!buf)
		return NULL;

	timer_set(&timer, TIMER_ONESHOT, TIMER_TICK, ttl_handler, (void *)buf);

	INIT_LIST_HEAD((struct list_head *)buf);
	INIT_LIST_HEAD(&buf->next_buf);
	list_add_tail(&buf->next_buf, &__dgram_buf_list);

	buf->protocol = iph->proto;
	buf->id = iph->id;
	buf->saddr = iph->saddr;
	buf->daddr = iph->daddr;
	buf->len = 0;
	buf->uncomplete = 1;
	buf->meat = 0;
	buf->timer = timer;
	buf->buf_ttl = MSL;

	return buf;
}

static void buf_delete(struct dgram_buf *buf) {
	struct sk_buff *tmp;

	while(!list_empty((struct list_head *)buf)) {
		tmp = buf->next_skbuff;
		list_del((struct list_head*)tmp);
		kfree_skb(tmp);
	}

	list_del(&buf->next_buf);
	pool_free(&__dgram_bufs, (void*)buf);
}

struct sk_buff *ip_defrag(struct sk_buff *skb) {
	struct dgram_buf *buf;
	int mf_flag;
	int offset;

	mf_flag = ntohs(skb->nh.iph->frag_off);
	mf_flag &= IP_MF;

	offset = ntohs(skb->nh.iph->frag_off);
	offset &= IP_OFFSET;
	offset <<= 3;
	/* if it is not complete packet */
	if(offset || mf_flag) {
		if (df_flag(skb)) {
				/* For some reason we don't like situation when someone used forced fragmentation */
			kfree_skb(skb);
			skb = (sk_buff_t *)NULL;
			return skb;
		}
		if (NULL == (buf = ip_find(skb->nh.iph))) {
			buf = buf_create(skb->nh.iph);
		}

		ip_frag_dgram_buf(buf, skb);

		if(buf->uncomplete)
			buf->uncomplete = mf_flag;

		if (!buf->uncomplete && buf->meat == buf->len) {
			return build_packet(buf);
		}
	} else {
		return skb;
	}

	return NULL;
}

struct sk_buff_head *ip_frag(const struct sk_buff *skb, uint32_t mtu) {
	struct sk_buff_head *tx_buf = alloc_skb_queue();
	struct sk_buff *fragment;
	int len = ETH_HEADER_SIZE + IP_HEADER_SIZE(skb->nh.iph);
	int offset = len;		/* offset from skb start (== mac.raw) */
	
		/* Note: correct MTU, because fragment offset must divide on 8*/
	int align_MTU = mtu - (mtu - len) % 8;

	if(unlikely(!tx_buf)) {
		return NULL;
	}

		/* copy sk_buff without last fragment. All this fragments have size MTU */
	while(offset < skb->len - align_MTU) {
		if(unlikely(!(fragment = alloc_skb(align_MTU, 0)))) {
			skb_queue_purge(tx_buf);
			return NULL;
		}
		
			/* Copy IP and MAC headers */
		memcpy(fragment->mac.raw, skb->mac.raw, len);
			/* Copy IP content */
		memcpy(fragment->mac.raw + len, skb->mac.raw + offset, align_MTU);
		fragment->nh.raw = fragment->mac.raw + ETH_HEADER_SIZE;
		fragment->nh.iph->frag_off = htons(
					(((offset - len) >> 3) /* data offset / 8 */) | IP_MF);
		ip_send_check(fragment->nh.iph);
		skb_queue_tail(tx_buf, fragment);
		offset += (align_MTU - len);
	}

	/* copy last fragment */
	if(offset < skb->len) {
		if(unlikely(!(fragment = alloc_skb(skb->len - offset + len, 0)))) {
			skb_queue_purge(tx_buf);
			return NULL;
		}

			/* Copy IP and MAC headers */
		memcpy(fragment->mac.raw, skb->mac.raw, len);
			/* Copy IP content */
		memcpy(fragment->mac.raw + len, skb->mac.raw + offset, skb->len - offset);
		fragment->nh.raw = fragment->mac.raw + ETH_HEADER_SIZE;
		fragment->nh.iph->frag_off = htons(((offset - len) >> 3));
		ip_send_check(fragment->nh.iph);
		skb_queue_tail(tx_buf, fragment);
	}

	return tx_buf;
}

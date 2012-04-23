/**
 * @file
 * @brief Definitions for the 'struct sk_buff' memory handlers.
 *
 * @date 20.10.09
 * @author Anton Bondarev
 * @author Ilia Vaprol
 * @author Vladimir Sokolov
 */

#ifndef NET_SKBUFF_H_
#define NET_SKBUFF_H_

/* FIXME include this */
//#include <net/if_arp.h>
//#include <net/if_ether.h>
//#include <net/netdevice.h>
//#include <net/ip.h>
//#include <net/icmp.h>
//#include <net/sock.h>
//#include <net/udp.h>
#include <types.h>
#include <assert.h>

struct skb_timeval {
	uint32_t off_sec;
	uint32_t off_usec;
};

#define SK_BUF_EXTRA_HEADROOM	50	/* Requires if someone wants to enlarge packet from head */

typedef struct sk_buff {        /* Socket buffer */
	/* These two members must be first. */
	struct sk_buff *next;       /* Next buffer in list */
	struct sk_buff *prev;       /* Previous buffer in list */

	struct sock *sk;            /* Socket we are owned by */
	struct net_device *dev;     /* Device we arrived on/are leaving by */

		/* Packet protocol from driver or protocol to put into Eth header during assembling.
		 * We should get rid of it. It's almost useless during packet
		 * receiving and there is a special field in LL header
		 * for packet assembling.
		 */
	uint16_t protocol;
	
		/* Control buffer (used to store layer-specific info e.g. ip options) 
		 * Nowdays it's used only in ip options, so it's a good idea to 
		 * remove this field
		 */
	char cb[52];
	
		/* Length of actual data, from LL header till the end */
	unsigned int len;
	
	union {                     /* Transport layer header */
		struct tcphdr *th;
		struct udphdr *uh;
		struct icmphdr *icmph;
		unsigned char *raw;
	} h;
	
		/* Network layer header.
		 * Usually iph contains IP_MIN_HEADER_SIZE except some cases:
		 *	when we process incoming IP packet with options
		 *	when we use RAW sockets for sending (still not fixed in design)
		 */
	union {
		struct iphdr *iph;
		struct arphdr *arph;
		unsigned char *raw;
	} nh;
	
		/* In current implementation our stack allocates
		 * ETH_HEADER_SIZE + IP_MIN_HEADER_SIZE + ...
		 * for outgoing packets.
		 * So it's assumed to have eth header at the start
		 */
	union {                     /* Link layer header */
		struct ethhdr *ethh;
		unsigned char *raw;
	} mac;
	
		/* Pointer for buffer used to store all skb content.
		 * Used by operations with pool, so it MUST NOT be changed
		 */
	unsigned char *head;
	
		/* After processing by (incoming) stack packet is used by
		 * socket structures. Socket (== User) may consume only a part
		 * of data. Taken data ends with p_data
		 * Note:
		 *	Quoting from man recvfrom "If a message is too long to fit in 
		 *	the supplied buffer, excess bytes may be discarded depending 
		 *	on the type of socket the message is received from"
		 * So the presence of this field isn't mandatory.
		 */
	unsigned char *p_data;
	
} sk_buff_t;

typedef struct sk_buff_head {
	struct sk_buff *next;
	struct sk_buff *prev;
} sk_buff_head_t;


/**
 * Allocate one instance of structure sk_buff. With pointed size and flags.
 * @return If size is more then mtu (now it is defined by macros
 * CONFIG_ETHERNET_V2_FRAME_SIZE) function will return queue of sk_buff.
 * Else function return single sk_buff.
 * Function return NULL if function can't allocate demanded buffer
 */
extern struct sk_buff * alloc_skb(unsigned int size, gfp_t priority);

/**
 * Free skb allocated by alloc_skb
 */
extern void kfree_skb(struct sk_buff *skb);

/**
 *	skb_checkcopy_expand	-	check, copy and expand sk_buff
 *	@skb: buffer to check, copy
 *	@headroom: required amount of free bytes at head
 *	@tailroom: required amount of free bytes at tail
 *	@priority: allocation priority
 *
 *	Make a copy of both an &sk_buff and its data and while doing so
 *	allocate additional space. Do nothing if we already have such amount 
 *	of free space and this sbk and data are completely ours.
 *
 *	Returns NULL on failure or the pointer to the buffer
 *	on success.
 *
 *	In current implementation there is no "extra-large packets pool"
 *	to allocate data from. So no allocation if new size doesn't fit.
 */
extern struct sk_buff *skb_checkcopy_expand(struct sk_buff *skb,
				int headroom, int tailroom, gfp_t priority);

/**
 *	skb_shifthead	-	shift pointers to headers in the head of the skb structure
 *	@skb: buffer to process
 */
extern void skb_shifthead(struct sk_buff *skb, int headshift);

/**
 * buff_to_skb parse buffer with size 'size' and write it to skb structure
 */
extern struct sk_buff * buff_to_skb(unsigned char *buff, unsigned int size);

/**
 * sk_buff clone it used as we want to queue sk_buff in several queue
 * In current implementation we don't have shared area for packets data,
 * so copy and clone are the same.
 */
extern struct sk_buff *skb_clone(struct sk_buff *skb, gfp_t priority);

/**
 * Create copy of skb
 * In current implementation we don't have shared area for packets data,
 * so copy and clone are the same.
 */
static inline struct sk_buff *skb_copy(struct sk_buff *skb, gfp_t priority) {
    return skb_clone(skb, priority);
}

/**
 * Allocate one instance of structure sk_buff_head.
 */
extern struct sk_buff_head * alloc_skb_queue(void);

/**
 * Free sk_buff_head structure with his elements
 */
extern void skb_queue_purge(struct sk_buff_head *queue);

/**
 * Get struct sk_buff from the head of the list.
 */
extern struct sk_buff * skb_dequeue(struct sk_buff_head *list);

/**
 * Get sk_buff from list without removing it from list
 */
extern struct sk_buff * skb_peek(struct sk_buff_head *list);

/**
 * Move newsk to tail of the list.
 */
extern void skb_queue_tail(struct sk_buff_head *list, struct sk_buff *newsk);

/**
 * Receive struct sk_buff from receive queue of the sock
 */
extern struct sk_buff * skb_recv_datagram(struct sock *sk, unsigned flags,
					 int noblock, int *err);
/**
 * Get sk_buff from queue of sock without removing it from sock's queue
 */
extern struct sk_buff * skb_peek_datagram(struct sock *sk, unsigned flags, 
					 int noblock, int *err);
#endif /* NET_SKBUFF_H_ */

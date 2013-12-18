/**
 * @file
 * @brief Definitions for the IP protocol.
 * @details RFC 791
 *
 * @date 11.03.09
 * @author Anton Bondarev
 */

#ifndef NET_L3_IPV4_IP_H_
#define NET_L3_IPV4_IP_H_

#include <netinet/in.h>
#include <endian.h>

#include <net/skbuff.h>
#include <endian.h>
#include <linux/types.h>
#include <embox/net/pack.h>


/**
 * Prototypes
 */
struct sk_buff;

#define IP_ADDR_LEN      4
#define IPv6_ADDR_LEN    16

/* IP flags. */
#define IP_CE           0x8000	/* Flag: "Congestion"       */
#define IP_DF           0x4000	/* Flag: "Don't Fragment"   */
#define IP_MF           0x2000	/* Flag: "More Fragments"   */
#define IP_OFFSET       0x1FFF	/* "Fragment Offset" part   */

typedef struct iphdr {
#if  __BYTE_ORDER == __LITTLE_ENDIAN
	__u8 ihl:4,  /* ihl = 5 */
	version: 4;  /* version = 4 */
#elif  __BYTE_ORDER == __BIG_ENDIAN
	__u8 version:4, /* version = 4 */
		 ihl:4; /* ihl = 5 */
#endif
	__u8        tos;          /**< Type of Services, always 0 */
	__be16      tot_len;      /**< packet length */
	__be16      id;           /**< for packet fragmentation */
	/** ________________________________________________________________
	 * |15_________________|14___________________|13______|12____________0|
	 * |MF (more fragments)|DF (don’t fragment)  |always 0|fragment offset|
	 * |___________________|_____________________|________|_______________|
	 */
	__be16      frag_off;     /**< flags + position of the fragment in the data flow */
	__u8        ttl;          /**< Time to live */
	__u8        proto;        /**< next header */
	__be16      check;        /**< header's checksum */
	in_addr_t   saddr;        /**< source address */
	in_addr_t   daddr;        /**< destination address */
} __attribute__((packed)) iphdr_t;

#define IP_MIN_HEADER_SIZE   (sizeof(struct iphdr))
#define IP_HEADER_SIZE(iph) (((iph)->ihl) << 2)

static inline iphdr_t *ip_hdr(const struct sk_buff *skb) {
	return skb->nh.iph;
}

/**
 * IP packet outgoing options
 */
extern const struct net_pack_out_ops *const ip_out_ops
		__attribute__ ((weak));

/* TODO remve this */
extern int ip_forward(struct sk_buff *skb);

#endif /* NET_L3_IPV4_IP_H_ */

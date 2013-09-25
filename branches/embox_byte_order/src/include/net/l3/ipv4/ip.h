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

#include <arpa/inet.h>
#include <netinet/in.h>

#include <net/skbuff.h>
#include <net/socket/inet_sock.h>
#include <hal/arch.h> /* endianess */
#include <net/util/checksum.h>
#include <net/netdevice.h>
#include <net/sock.h>
#include <linux/types.h>

/**
 * Prototypes
 */
struct sk_buff;
struct packet_type;
struct net_device;
struct sock;

#define IP_ADDR_LEN      4
#define IPv6_ADDR_LEN    16
#define ICMP_PROTO_TYPE  (unsigned short)0x01
#define UDP_PROTO_TYPE   (unsigned short)0x11

/* IP options */
#define IPOPT_COPY		0x80
#define IPOPT_CLASS_MASK	0x60
#define IPOPT_NUMBER_MASK	0x1f

#define	IPOPT_COPIED(o)		((o)&IPOPT_COPY)
#define	IPOPT_CLASS(o)		((o)&IPOPT_CLASS_MASK)
#define	IPOPT_NUMBER(o)		((o)&IPOPT_NUMBER_MASK)

#define	IPOPT_CONTROL		0x00
#define	IPOPT_RESERVED1		0x20
#define	IPOPT_MEASUREMENT	0x40
#define	IPOPT_RESERVED2		0x60

#define IPOPT_END	(0 |IPOPT_CONTROL)
#define IPOPT_NOOP	(1 |IPOPT_CONTROL)
#define IPOPT_SEC	(2 |IPOPT_CONTROL | IPOPT_COPY)
#define IPOPT_LSRR	(3 |IPOPT_CONTROL | IPOPT_COPY)
#define IPOPT_TIMESTAMP	(4 |IPOPT_MEASUREMENT)
//#define IPOPT_CIPSO	(6 |IPOPT_CONTROL|IPOPT_COPY)
#define IPOPT_RR	(7 |IPOPT_CONTROL)
#define IPOPT_SID	(8 |IPOPT_CONTROL | IPOPT_COPY)
#define IPOPT_SSRR	(9 |IPOPT_CONTROL | IPOPT_COPY)
//#define IPOPT_RA	(20|IPOPT_CONTROL |IPOPT_COPY)

#define	IPOPT_TS_TSONLY		0		/* timestamps only */
#define	IPOPT_TS_TSANDADDR	1		/* timestamps and addresses */
#define	IPOPT_TS_PRESPEC	3		/* specified modules only */

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
	__be16    check;        /**< header's checksum */
	in_addr_t   saddr;        /**< source address */
	in_addr_t   daddr;        /**< destination address */
} __attribute__((packed)) iphdr_t;



#define IP_MIN_HEADER_SIZE   (sizeof(struct iphdr))
#define IP_HEADER_SIZE(iph) (((iph)->ihl) << 2)

static inline iphdr_t *ip_hdr(const struct sk_buff *skb) {
	return skb->nh.iph;
}

/* Generate a checksum for an outgoing IP datagram. */
/* NOTE: maybe rename ip_send_check to ip_send_cheksum for clarity?
   current name is ambiguous*/
static inline void ip_send_check(iphdr_t *iph) {
	iph->check = 0;
	iph->check = ptclbsum((void *) iph, IP_HEADER_SIZE(iph));
}

/* Init IP header with given parameters */
static inline void init_ip_header(iphdr_t *hdr, uint8_t proto, __be16 ip_id, __be16 tot_len, __u8 tos,
		in_addr_t saddr, in_addr_t daddr) {
	hdr->version = 4;
	hdr->ihl = IP_MIN_HEADER_SIZE >> 2;
	hdr->saddr = saddr;
	hdr->daddr = daddr;
	hdr->tot_len = tot_len;
	hdr->ttl = 255;
	hdr->id = ip_id;
	hdr->tos = tos;
	hdr->frag_off = 0;
	hdr->proto = proto;
	ip_send_check(hdr);
}

/**
 * Functions provided by ip.c
 */

/**
 * Add an ip header to a net_packet and send it out.
 * It mignt be called with/without socket-related data.
 * Whan socket-related info is present we may use it to build some headers.
 * Current usage:
 *	ICMP: no socket, IP/ICMP headers are build, LL header unknown
 *	UDP: socket, UDP header is built, IP header is placed, LL header unknown
 *	RAW: socket, IP header is ready, but LL header unknown
 *	TCP: socket, TCP header is built, IP header is placed, LL header unknown
 */
extern int ip_send_packet(struct inet_sock *sk, struct sk_buff *pack);

/**
 * Perform forwarding of obtained packet
 */
extern int ip_forward_packet(struct sk_buff *skb);

extern int ip_queue_send(struct sk_buff *skb);
extern int ip_queue_xmit(struct sk_buff *skb);

extern int rebuild_ip_header(struct sk_buff *pack, unsigned char ttl,
			unsigned char proto, unsigned short id, unsigned short len,
			in_addr_t saddr, in_addr_t daddr/*, ip_options_t *opt*/);

/**
 * Functions provided by ip_options.c
 */

/*
 * Parses a block of options from an IP header
 * and initializes an instance of an ip_options structure accordingly
 */
extern int ip_options_compile(struct sk_buff *skb, struct ip_options *opt);

/*
 * Handles socket buffer route info due to SRR options
 */
extern int ip_options_handle_srr(struct sk_buff *skb);

extern struct net_proto_family inet_family_ops;

/**
 * notify an ip socket about icmp error
 **/
extern void ip_v4_icmp_err_notify(struct sock *sk, int type, int code);

#endif /* NET_L3_IPV4_IP_H_ */

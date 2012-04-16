/**
 * @file
 * @brief Definitions for the IP protocol.
 * @details RFC 791
 *
 * @date 11.03.09
 * @author Anton Bondarev
 */

#ifndef NET_IP_H_
#define NET_IP_H_

#include <net/in.h>
#include <net/skbuff.h>
#include <net/inet_sock.h>
#include <hal/arch.h>
#include <net/checksum.h>

#define IP_ADDR_LEN      4
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
#if defined(__LITTLE_ENDIAN)
	__u8 ihl:4,  /* ihl = 5 */
	version: 4;  /* version = 4 */
#elif defined (__BIG_ENDIAN)
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

/**< Standard well-defined IP protocols.  */
enum {
	IPPROTO_IP   = 0,     /* Dummy protocol for TCP            */
	IPPROTO_ICMP = 1,     /* Internet Control Message Protocol */
	IPPROTO_TCP  = 6,     /* Transmission Control Protocol     */
	IPPROTO_UDP  = 17,    /* User Datagram Protocol            */
	/* A protocol of IPPROTO_RAW is able to send any IP protocol
	 * that is specified in the passed header. Receiving of all
	 * IP protocols via IPPROTO_RAW is not possible using raw sockets. */
	IPPROTO_RAW  = 255,   /* Raw IP packets                    */
	IPPROTO_MAX
};

#define IP_MIN_HEADER_SIZE   (sizeof(struct iphdr))
#define IP_HEADER_SIZE(iph) (((iph)->ihl) << 2)

static inline iphdr_t *ip_hdr(const sk_buff_t *skb) {
	return skb->nh.iph;
}

/* Generate a checksum for an outgoing IP datagram. */
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
 * Main IP Receive routine.
 */
extern int ip_rcv(sk_buff_t *pack, net_device_t *dev,
				packet_type_t *pt, net_device_t *orig_dev);

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
extern int ip_send_packet(inet_sock_t *sk, sk_buff_t *pack);

/**
 * Perform forwarding of obtained packet
 */
extern int ip_forward_packet(sk_buff_t *skb);

extern int ip_queue_xmit(sk_buff_t *skb, int ipfragok);

extern int rebuild_ip_header(sk_buff_t *pack, unsigned char ttl,
			unsigned char proto, unsigned short id, unsigned short len,
			in_addr_t saddr, in_addr_t daddr/*, ip_options_t *opt*/);

/**
 * Functions provided by ip_options.c
 */

/*
 * Parses a block of options from an IP header
 * and initializes an instance of an ip_options structure accordingly
 */
extern int ip_options_compile(sk_buff_t *skb, ip_options_t *opt);

/*
 * Handles socket buffer route info due to SRR options
 */
extern int ip_options_handle_srr(sk_buff_t *skb);

extern struct proto tcp_prot;

extern const struct proto_ops inet_stream_ops;

extern struct net_proto_family inet_family_ops;


/**  
 * notify an ip socket about icmp error
 **/
extern void ip_v4_icmp_err_notify(struct sock *sk, int type, int code);

#endif /* NET_IP_H_ */

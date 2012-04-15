/**
 * @file
 * @brief Definitions for the ICMP protocol.
 * @details RFC 792
 *
 * @date 14.03.09
 * @author Alexander Batyukov
 * @author Nikolay Korotky
 * @author Ilia Vaprol
 * @author Vladimir Sokolov
 */

#ifndef NET_ICMP_H_
#define NET_ICMP_H_

#include <net/inet_sock.h>
#include <net/checksum.h>
#include <net/ip.h>

/* Types */
enum {
	ICMP_ECHOREPLY      = 0,  /* Echo Reply */
	ICMP_DEST_UNREACH   = 3,  /* Destination Unreachable */
	ICMP_SOURCE_QUENCH  = 4,  /* Source Quench */
	ICMP_REDIRECT       = 5,  /* Redirect (change route) */
	ICMP_ECHO           = 8,  /* Echo Request */
	ICMP_TIME_EXCEEDED  = 11, /* Time Exceeded */
	ICMP_PARAMETERPROB  = 12, /* Parameter Problem */
	ICMP_TIMESTAMP      = 13, /* Timestamp Request */
	ICMP_TIMESTAMPREPLY = 14, /* Timestamp Reply */
	ICMP_INFO_REQUEST   = 15, /* Information Request */
	ICMP_INFO_REPLY     = 16, /* Information Reply */
//	ICMP_ADDRESS        = 17, /* Address Mask Request */
//	ICMP_ADDRESSREPLY   = 18, /* Address Mask Reply */
	NR_ICMP_TYPES	/* See also icmp_lengths enum below */
};

/* Assumed length (bytes) of the ICMP (without possible data padding) */
enum icmp_lengths {
	ICMP_LEN_ECHOREPLY			= 8,  /* Echo Reply */
	ICMP_LEN_DEST_UNREACH		= 8,  /* Destination Unreachable (with path MTU discovery) */
	ICMP_LEN_SOURCE_QUENCH		= 8,  /* Source Quench */
	ICMP_LEN_REDIRECT			= 8,  /* Redirect (change route) */
	ICMP_LEN_ECHO				= 8,  /* Echo Request */
	ICMP_LEN_TIME_EXCEEDED		= 8, /* Time Exceeded */
	ICMP_LEN_PARAMETERPROB		= 8, /* Parameter Problem */
	ICMP_LEN_TIMESTAMP			= 20, /* Timestamp Request */
	ICMP_LEN_TIMESTAMPREPLY		= 20, /* Timestamp Reply */
	ICMP_LEN_INFO_REQUEST		= 8, /* Information Request */
	ICMP_LEN_INFO_REPLY			= 8, /* Information Reply */
	ICMP_LEN_ADDRESS			= 12, /* Address Mask Request */
	ICMP_LEN_ADDRESSREPLY		= 12, /* Address Mask Reply */
};

#define	ICMP_INFOTYPE(type)												\
	( ((type) == ICMP_ECHOREPLY) || ((type) == ICMP_ECHO) ||			\
	  ((type) == ICMP_TIMESTAMP) || ((type) == ICMP_TIMESTAMPREPLY) ||	\
	  ((type) == ICMP_INFO_REQUEST) || ((type) == ICMP_INFO_REPLY) )

/* Codes for UNREACH. */
enum {
	ICMP_NET_UNREACH    = 0, /* Network Unreachable          */
	ICMP_HOST_UNREACH   = 1, /* Host Unreachable             */
	ICMP_PROT_UNREACH   = 2, /* Protocol Unreachable         */
	ICMP_PORT_UNREACH   = 3, /* Port Unreachable             */
	ICMP_FRAG_NEEDED    = 4, /* Fragmentation Needed/DF set  */
	ICMP_SR_FAILED      = 5, /* Source Route failed          */
#if 0
	ICMP_NET_UNKNOWN    = 6,
	ICMP_HOST_UNKNOWN   = 7,
	ICMP_HOST_ISOLATED  = 8,
	ICMP_NET_ANO        = 9,
	ICMP_HOST_ANO       = 10,
	ICMP_NET_UNR_TOS    = 11,
	ICMP_HOST_UNR_TOS   = 12,
	ICMP_PKT_FILTERED   = 13, /* Packet filtered */
	ICMP_PREC_VIOLATION = 14, /* Precedence violation */
	ICMP_PREC_CUTOFF    = 15, /* Precedence cut off */
#endif
	NR_ICMP_UNREACH           /* instead of hardcoding immediate value */
};

/* Codes for REDIRECT. */
#define ICMP_REDIR_NET          0       /* Redirect Net          */
#define ICMP_REDIR_HOST         1       /* Redirect Host         */
#define ICMP_REDIR_NETTOS       2       /* Redirect Net for TOS  */
#define ICMP_REDIR_HOSTTOS      3       /* Redirect Host for TOS */

/* Codes for TIME_EXCEEDED. */
#define ICMP_EXC_TTL            0       /* TTL count exceeded           */
#define ICMP_EXC_FRAGTIME       1       /* Fragment Reass time exceeded */

typedef struct icmphdr {
	__u8     type;
	__u8     code;
	__be16 checksum;
	union {
		__u8  ih_pptr;				/* ICMP_PARAMETERPROB */
		struct {
			__be16 id;
			__be16 sequence;
		} echo;
		__be32 gateway;
		struct {
			__be16 __unused;
			__be16 mtu;
		} frag;
	} un;
} __attribute__((packed)) icmphdr_t;

/* Note:
 *	Be careful. It's just a common length of ICMPs
 *	See enum icmp_lengths for details
 */
#define ICMP_HEADER_SIZE	(sizeof(struct icmphdr))

static inline icmphdr_t *icmp_hdr(const sk_buff_t *skb) {
	return (icmphdr_t *) skb->h.raw;
}

/* Generate a checksum for an outgoing ICMP datagram. */
static inline void icmp_send_check(icmphdr_t *icmph, uint len) {
	icmph->checksum = 0;
	icmph->checksum = ptclbsum((void *)icmph, len);
}

/* Generate a checksum for an outgoing ICMP datagram if skb is correct 
 * So we can obtain ICMP len from it
 */
static inline void icmp_send_check_skb(sk_buff_t *skb) {
	icmp_send_check(skb->h.icmph, htons(skb->nh.iph->tot_len) - IP_HEADER_SIZE(skb->nh.iph));
}

/**
 * Functions provided by icmp.c
 */

/**
 * Send an ICMP message in response to a situation.
 * Used by the kernel to transmit ICMP error messages when
 * specific conditions are detected.
 *
 * @param skb_in input IP packet the error is assiciated with
 * (skb: modified; freed; privacy could be any, it's checked)
 * @param type field to use in the ICMP header
 * @param code field to use in the ICMP header
 * @param info additional information (with required shifts applying):
 * 			MTU for ICMP_FRAG_NEEDED
 * 			gateway address for ICMP_REDIRECT
 * 			offset for ICMP_PARAMETERPROB
 */
extern void icmp_send(sk_buff_t *skb_in, __be16 type, __be16 code, __be32 info);

#endif /* NET_ICMP_H_ */

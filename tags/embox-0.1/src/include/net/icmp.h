/**
 * @file
 * @brief Definitions for the ICMP protocol.
 * @details RFC 792
 *
 * @date 14.03.2009
 * @author Alexander Batyukov
 * @author Nikolay Korotky
 */
#ifndef ICMP_H_
#define ICMP_H_

#include <net/inet_sock.h>

/* Types */
#define ICMP_ECHOREPLY          0       /* Echo Reply                   */
#define ICMP_DEST_UNREACH       3       /* Destination Unreachable      */
//#define ICMP_SOURCE_QUENCH      4       /* Source Quench                */
//#define ICMP_REDIRECT           5       /* Redirect (change route)      */
#define ICMP_ECHO               8       /* Echo Request                 */
//#define ICMP_TIME_EXCEEDED      11      /* Time Exceeded                */
//#define ICMP_PARAMETERPROB      12      /* Parameter Problem            */
#define ICMP_TIMESTAMP          13      /* Timestamp Request            */
//#define ICMP_TIMESTAMPREPLY     14      /* Timestamp Reply              */
//#define ICMP_INFO_REQUEST       15      /* Information Request          */
//#define ICMP_INFO_REPLY         16      /* Information Reply            */
#define ICMP_ADDRESS            17      /* Address Mask Request         */
#define ICMP_ADDRESSREPLY       18      /* Address Mask Reply           */
#define NR_ICMP_TYPES           18

/* Codes for UNREACH. */
#define ICMP_NET_UNREACH        0       /* Network Unreachable          */
#define ICMP_HOST_UNREACH       1       /* Host Unreachable             */
#define ICMP_PROT_UNREACH       2       /* Protocol Unreachable         */
#define ICMP_PORT_UNREACH       3       /* Port Unreachable             */
#define ICMP_FRAG_NEEDED        4       /* Fragmentation Needed/DF set  */
#define ICMP_SR_FAILED          5       /* Source Route failed          */
#define ICMP_NET_UNKNOWN        6
#define ICMP_HOST_UNKNOWN       7
#define ICMP_HOST_ISOLATED      8
#define ICMP_NET_ANO            9
#define ICMP_HOST_ANO           10
#define ICMP_NET_UNR_TOS        11
#define ICMP_HOST_UNR_TOS       12
#define ICMP_PKT_FILTERED       13      /* Packet filtered */
#define ICMP_PREC_VIOLATION     14      /* Precedence violation */
#define ICMP_PREC_CUTOFF        15      /* Precedence cut off */
#define NR_ICMP_UNREACH         15      /* instead of hardcoding immediate value */

typedef struct icmphdr {
	__u8     type;
	__u8     code;
	uint16_t checksum;
	union {
		struct {
			__be16 id;
			__be16 sequence;
		} echo;
		__be16 gateway;
		struct {
			__be16 __unused;
			__be16 mtu;
		} frag;
	} un;
} __attribute__((packed)) icmphdr_t;

#define ICMP_HEADER_SIZE	(sizeof(struct icmphdr))

typedef void (*ICMP_CALLBACK)(struct sk_buff* response);

static inline icmphdr_t *icmp_hdr(const sk_buff_t *skb) {
	return (icmphdr_t *)skb->h.raw;
}

/**
 * Functions provided by icmp.c
 */

/**
 * set all realized handlers
 */
extern void icmp_init(void);

/**
 * receive packet
 */
extern int icmp_rcv(sk_buff_t *pack);

/**
 * Send an ICMP message in response to a situation
 */
extern void icmp_send(sk_buff_t *pack, int type, int code, uint32_t info);

extern int icmp_send_echo_request(void *in_dev, in_addr_t dstaddr, int ttl,
		ICMP_CALLBACK callback, unsigned size, __u16 pattern, unsigned seq);

extern int icmp_abort_echo_request(void *in_dev);

#endif /* ICMP_H_ */

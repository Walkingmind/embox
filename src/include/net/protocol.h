/**
 * @file
 * @brief Definitions for the protocol dispatcher.
 *
 * @date 12.08.09
 * @author Nikolay Korotky
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <lib/list.h>
#include <net/skbuff.h>

#define MAX_INET_PROTOS 256

/* This is used to register protocols. */
typedef struct net_protocol {
	int (*handler)(sk_buff_t *pack);
	void (*err_handler)(sk_buff_t *pack, uint32_t info);
#if 0
	int (*gso_send_check)(sk_buff_t *pack);
	sk_buff_t *(*gso_segment)(sk_buff_t *pack, int features);
	int no_policy;
#endif
	__be16 type;
} net_protocol_t;

/**
 * Add a protocol handler to the hash tables
 */
extern int inet_add_protocol(net_protocol_t *prot, unsigned char num);

/**
 * Add a protocol handler to the hash tables
 */
extern int inet_add_protocol(net_protocol_t *prot, unsigned char num);

/**
 * Remove a protocol from the hash tables.
 */
extern int inet_del_protocol(net_protocol_t *prot, unsigned char num);

/* For Linux compatible */
/* This is used to register socket interfaces for IP protocols.  */
typedef struct inet_protosw {
	struct list_head list;

	/* These two fields form the lookup key.  */
	unsigned short type; /* This is the 2nd argument to socket(2). */
	unsigned short protocol; /* This is the L4 protocol number.  */

	const struct proto *prot;
	const struct proto_ops *ops;
	char no_check; /* checksum on rcv/xmit/none? */
	bool deflt;
} inet_protosw_t;

extern const net_protocol_t *inet_protos[MAX_INET_PROTOS];

#endif /* PROTOCOL_H_ */

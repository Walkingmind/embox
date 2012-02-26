/**
 * @file
 * @brief Type declarations shared between net sockets framework and each net socket suite.
 *
 * @date 05.07.11
 * @author Dmitry Zubarevich
 */

#ifndef FRAMEWORK_NET_SOCK_TYPES_H_
#define FRAMEWORK_NET_SOCK_TYPES_H_

#include <util/location.h>
#include <net/protocol.h>
#include <net/net.h>

/**
 * Each netsock implements this interface.
 */

typedef struct net_sock {
	struct net_proto_family *net_proto_family;
	struct inet_protosw *netsock;
	/** The corresponding mod. */
	const struct mod *mod;
} net_sock_t;

#endif /* FRAMEWORK_NET_SOCK_TYPES_H_ */

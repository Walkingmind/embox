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

/**
 * Each netsock implements this interface.
 */

struct net_sock {
	inet_protosw_t *netsock;
	/** The corresponding mod. */
	const struct mod *mod;
};

#endif /* FRAMEWORK_NET_SOCK_TYPES_H_ */

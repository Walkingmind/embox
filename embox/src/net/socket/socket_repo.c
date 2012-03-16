/**
 * @file
 *
 * @brief
 *
 * @date 08.11.2011
 * @author Anton Bondarev
 */
#include <net/net.h>
#include <errno.h>
/*
 * The protocol list. Each protocol is registered in here.
 */
/* TODO: actually could be quite a big todo. net families asks
   for a way bigger space amount than actually requires. */
static const struct net_proto_family *net_families[NPROTO] = {0};

int sock_register(const struct net_proto_family *ops) {
	if (ops->family >= NPROTO) {
		return -ENOBUFS; /* FIXME mb -EINVAL ? */
	}
	if (net_families[ops->family] != NULL) {
		return -EEXIST;
	}

	net_families[ops->family] = ops;

	return ENOERR;
}

void sock_unregister(int family) {
	if ((family < 0) || (family >= NPROTO)) {
		return;
	}

	net_families[family] = NULL;
}

const struct net_proto_family * socket_repo_get_family(int family) {
	/*
	 * Check protocol is in range
	 */
	if ((family < 0) || (family >= NPROTO)) {
		return NULL;
	}

	/*pf = rcu_dereference(net_families[family]);*/

	return net_families[family];
}

inline bool is_a_valid_sock_type(int type){
	return ((type == SOCK_STREAM) ||
					(type == SOCK_DGRAM) ||
					(type == SOCK_RAW) ||
					(type == SOCK_SEQPACKET) ||
					(type == SOCK_PACKET));
}

inline bool is_a_valid_family(int family){
	return ((family == AF_UNSPEC) ||
					(family == AF_UNIX) ||
					(family == AF_INET) ||
					(family == AF_PACKET));
}

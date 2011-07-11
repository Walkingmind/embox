/**
 * @file
 * @brief
 *
 * @date 05.07.11
 * @author Dmitry Zubarevich
 */

#include <string.h>

#include <framework/net/sock/api.h>
#include <net/protocol.h>

ARRAY_SPREAD_DEF(const struct net_sock, __net_sock_registry);

static int net_sock_mod_enable(struct mod *mod);
static int net_sock_mod_disable(struct mod *mod);

const struct mod_ops __net_sock_mod_ops = {
	.enable  = &net_sock_mod_enable,
	.disable = &net_sock_mod_disable
};

static int net_sock_mod_enable(struct mod *mod) {
	int ret = 0;

	net_proto_family_t *net_proto_family = ((net_sock_t *) mod_data(mod))->net_proto_family;
	TRACE("NET: initializing socket %s.%s: ", mod->package->name, mod->name);
	TRACE("done\n");

	if (net_proto_family != NULL) {
		TRACE("NET: initializing protocol family %s.%s: ", mod->package->name, mod->name);
		if(!sock_register(net_proto_family)) {
			TRACE("done\n");
		} else {
			TRACE("error: %s\n", strerror(-ret));
		}
	}

	return ret;
}

static int net_sock_mod_disable(struct mod *mod) {
	int ret = 0;

	net_proto_family_t *net_proto_family = ((net_sock_t *) mod_data(mod))->net_proto_family;

	if (net_proto_family != NULL) {
		TRACE("NET: finalizing protocol family %s: ", mod->name);
		sock_unregister(net_proto_family->family);
			TRACE("done\n");
	}

	return ret;
}

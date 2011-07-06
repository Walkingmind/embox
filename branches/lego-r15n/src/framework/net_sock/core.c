/**
 * @file
 * @brief
 *
 * @date 05.07.11
 * @author Dmitry Zubarevich
 */

#include <string.h>

#include <framework/net_sock/api.h>
#include <net/protocol.h>

ARRAY_SPREAD_DEF(const struct net_sock, __net_sock_registry);

static int net_sock_mod_enable(struct mod *mod);

const struct mod_ops __net_sock_mod_ops = {
	.enable  = &net_sock_mod_enable,
};

static int net_sock_mod_enable(struct mod *mod) {
	int ret = 0;

	TRACE("NET: initializing socket %s.%s: ", mod->package->name, mod->name);
	TRACE("done\n");

	return ret;
}



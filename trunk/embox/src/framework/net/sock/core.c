/**
 * @file
 * @brief
 *
 * @date 05.07.11
 * @author Dmitry Zubarevich
 */

#include <prom/prom_printf.h>
#include <string.h>
#include <framework/mod/ops.h>
#include <framework/mod/member/ops.h>
#include <framework/net/sock/api.h>
#include <net/protocol.h>
#include <util/array.h>

ARRAY_SPREAD_DEF(const struct net_sock, __net_sock_registry);

#if 0
static int net_sock_mod_enable(struct mod_member *mod);
static int net_sock_mod_disable(struct mod_member *mod);

const struct mod_member_ops __net_sock_mod_ops = {
	.init  = &net_sock_mod_enable,
	.fini = &net_sock_mod_disable
};

static int net_sock_mod_enable(struct mod_member *mod) {
	int ret = 0;

	net_proto_family_t *net_proto_family = ((net_sock_t *) mod->data)->net_proto_family;
	prom_printf("NET: initializing socket %s.%s: ",
		mod->mod->package->name, mod->mod->name);

	if (NULL != net_proto_family) {
		ret = sock_register(net_proto_family);
	}

	if (0 == ret) {
		prom_printf("done\n");
	} else {
		prom_printf("error: %s\n", strerror(-ret));
	}

	return ret;
}

static int net_sock_mod_disable(struct mod_member *mod) {
	int ret = 0;

	net_proto_family_t *net_proto_family = ((net_sock_t *) mod->data)->net_proto_family;

	if (NULL != net_proto_family) {
		sock_unregister(net_proto_family->family);
	}

	return ret;
}
#endif

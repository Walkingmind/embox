/**
 * @file
 * @brief
 *
 * @date 01.07.11
 * @author Dmitry Zubarevich
 */

#include <string.h>

#include <framework/net_pack/api.h>
#include <net/netdevice.h>

ARRAY_SPREAD_DEF(const struct net_pack, __net_pack_registry);

static int net_pack_mod_enable(struct mod *mod);

const struct mod_ops __net_pack_mod_ops = {
	.enable  = &net_pack_mod_enable,
};

static int net_pack_mod_enable(struct mod *mod) {
	int ret = 0;
	struct net_pack *net_pack = (struct net_pack *) mod_data(mod);

	if (NULL == net_pack->netpack || NULL == net_pack->netpack->init) {
		TRACE ("\nWrong packet descriptor\n");
		return 0;
	}
	TRACE("NET: initializing %s.%s: ", mod->package->name, mod->name);

	if (0 == (ret = net_pack->netpack->init())) {
		dev_add_pack(net_pack->netpack);
		TRACE("done\n");
	} else {
		TRACE("error: %s\n", strerror(-ret));
	}

	return ret;
}

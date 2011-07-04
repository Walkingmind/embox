/**
 * @file
 * @brief
 *
 * @date 04.07.11
 * @author Dmitry Zubarevich
 */

#include <string.h>

#include <framework/net_proto/api.h>
#include <net/protocol.h>
#if 0
ARRAY_SPREAD_DEF(const struct net_proto, __net_proto_registry);

static int net_proto_mod_enable(struct mod *mod);

const struct mod_ops __net_proto_mod_ops = {
	.enable  = &net_proto_mod_enable,
};

static int net_proto_mod_enable(struct mod *mod) {
	int ret = 0;
	struct net_proto *net_proto = (struct net_proto *) mod_data(mod);

	TRACE("NET: initializing %s.%s: ", mod->package->name, mod->name);

//	if (inet_add_protocol((*p_netproto), (*p_netproto)->type) < 0) {
//				LOG_ERROR("inet_protocols_init: Cannot add 0x%X protocol - %s\n",
//						(*p_netproto)->type, trace_proto_info((*p_netproto)->type));
//			}
//	TRACE("Added 0x%X protocol - %s\n", (*p_netproto)->type,
//			trace_proto_info((*p_netproto)->type));

	return ret;
}

#endif

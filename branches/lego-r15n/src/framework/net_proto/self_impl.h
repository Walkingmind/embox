/**
 * @file
 * @brief Internal implementation of net proto self definition macros.
 *
 * @date 04.07.11
 * @author Dmitry Zubarevich
 */

#ifndef FRAMEWORK_NET_PROTO_SELF_IMPL_H_
#define FRAMEWORK_NET_PROTO_SELF_IMPL_H_

#include <stddef.h>

#include <util/array.h>
#include <framework/mod/self.h>

#include "types.h"

#define __EMBOX_NET_PROTO(_proto) \
	extern const struct mod_ops __net_proto_mod_ops;         \
	extern const struct net_proto __net_proto_registry[];    \
	ARRAY_SPREAD_ADD_NAMED(__net_proto_registry, __net##_proto,   {  \
			.netproto = &_proto,                     \
			.mod = &mod_self                   \
		});                                        \
	MOD_SELF_BIND(&__net##_proto, &__net_proto_mod_ops)

#endif /* FRAMEWORK_NET_PROTO_SELF_IMPL_H_ */

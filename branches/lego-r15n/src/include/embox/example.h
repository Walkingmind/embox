/**
 * @file
 *
 * @brief
 *
 * @date 06.07.2011
 * @author Anton Bondarev
 */

#ifndef EXAMPLE_H_
#define EXAMPLE_H_

#include <stddef.h>

#include <util/array.h>
#include <framework/mod/self.h>

#include __impl_x(framework/example/self_impl.h)

#define EMBOX_EXAMPLE(_exec) \
	extern const struct example __example_registry[];          \
	static int _exec(int argc, char **argv);           \
	ARRAY_SPREAD_ADD_NAMED(__example_registry, __example,   {  \
			.exec = _exec,                     \
			.mod = &mod_self                   \
		});                                        \
	MOD_SELF_BIND(__example, NULL) /* TODO not used. -- Eldar */


#endif /* EXAMPLE_H_ */

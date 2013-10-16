/**
 * @file
 * @brief TODO
 *
 * @date 01.03.11
 * @author Anton Bondarev
 */

#ifndef FRAMEWORK_EXAMPLE_SELF_H_
#define FRAMEWORK_EXAMPLE_SELF_H_

#include <util/array.h>
#include <framework/mod/self.h>
#include <framework/mod/ops.h>

#include __impl_x(framework/example/types.h) /* TODO this is external API header */

#ifndef __cplusplus
#define EMBOX_EXAMPLE(_exec)                                   \
	ARRAY_SPREAD_DECLARE(const struct example,                 \
			__example_registry);                               \
	extern const struct mod_ops __example_mod_ops;             \
	static int _exec(int argc, char **argv);                   \
	ARRAY_SPREAD_ADD_NAMED(__example_registry, __example,   {  \
			.mod = &mod_self,                                  \
			.exec = _exec,                                     \
		});                                                    \
	MOD_INFO_BIND(&__example_mod_ops, __example)
#else
#define EMBOX_EXAMPLE(_exec)                                   \
	ARRAY_SPREAD_DECLARE(const struct example, __example_registry); \
	extern const struct mod_ops __example_mod_ops; \
	static int _exec(int argc, char **argv);                   \
	ARRAY_SPREAD_ADD_NAMED(__example_registry, __example,   {  \
			&mod_self,                                  \
			_exec,                                     \
		});                                                    \
	MOD_INFO_BIND(&__example_mod_ops, __example)
#endif


#ifdef __CDT_PARSER__

# undef  EMBOX_EXAMPLE
# define EMBOX_EXAMPLE(function_nm) \
	static int function_nm(int, char **); \
	typedef typeof(function_nm) __example_placeholder; \
	static int function_nm(int, char **)

#endif /* __CDT_PARSER__ */

#endif /* FRAMEWORK_EXAMPLE_SELF_H_ */

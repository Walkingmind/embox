/**
 * @file
 * @brief Object pool allocator types and definition macros.
 *
 * @date 07.03.11
 * @author Kirill Tyushev
 * @author Eldar Abusalimov
 */

#ifndef MEM_UTIL_POOL_IMPL_H_
#define MEM_UTIL_POOL_IMPL_H_

#include <util/macro.h>
#include <lib/list.h>

struct pool {
	void * const storage;
	const size_t object_sz;
	size_t objects_free;
	struct list_head free_blocks;
};

struct __pool_free_block {
	struct list_head link;
	size_t bytes_free;
};

#define __POOL_DEF(pool_nm, object_t, objects_nr) \
	__POOL_DEF__(pool_nm, object_t, objects_nr, MACRO_GUARD(__pool_##pool_nm))

#define __POOL_DEF__(pool_nm, object_t, objects_nr, storage_nm) \
	static union {                                    \
		typeof(object_t) object;                      \
		struct __pool_free_block block;               \
	} storage_nm[objects_nr] __attribute__((section(".reserve.pool"))); \
	static struct pool pool_nm = {                    \
		.storage = storage_nm,                        \
		.object_sz = sizeof(*storage_nm),             \
		.objects_free = objects_nr,                   \
		/* .free_blocks field is initially zeroed. */ \
	}

#ifdef __CDT_PARSER__

#undef __POOL_DEF
#define __POOL_DEF(pool_nm, object_t, objects_nr) \
	static struct pool pool_nm

#endif

#endif /* MEM_UTIL_POOL_IMPL_H_ */

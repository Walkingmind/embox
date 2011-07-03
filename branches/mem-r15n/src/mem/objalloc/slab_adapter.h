/**
 * @brief Adapt cache structure to objalloc interface.
 *
 * @see mem/objalloc.h
 *
 * @date   30.06.11
 * @author Alexandr Kalmuk
 */

#include <mem/misc/slab.h>

#define __OBJALLOC_DEF(allocator_nm, object_t, objects_nr) \
	CACHE_DEF(allocator_nm, object_t, objects_nr)

typedef struct cache __objalloc_t;

static inline int objalloc_init(__objalloc_t *allocator, size_t object_sz,
		size_t objects_nr) {
	return cache_init(allocator, objects_sz, objects_nr);
}

static inline int objalloc_destroy(__objalloc_t *allocator) {
	return cache_destroy(allocator);
}

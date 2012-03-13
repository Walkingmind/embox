/**
 * @file
 *
 * @brief
 *
 * @date 02.03.2012
 * @author Anton Bondarev
 */
#include <util/array.h>
#include <pnet/pnet_pack.h>
#include <mem/objalloc.h>

ARRAY_SPREAD_DEF(const struct pnet_pack_desc, __pnet_pack_registry);

static const struct pnet_pack_desc *find_pack_desc(uint32_t type) {
	const struct pnet_pack_desc *ptr;

	array_foreach_ptr(ptr, __pnet_pack_registry,
			ARRAY_SPREAD_SIZE(__pnet_pack_registry)) {
		if(ptr->type == type) {
			return ptr;
		}
	}

	return NULL;
}

struct pnet_pack *pnet_pack_create(void *buff, size_t size, uint32_t type) {
	const struct pnet_pack_desc *desc;
	if(NULL == (desc = find_pack_desc(type))) {
		return NULL;
	}

	return desc->create(buff, size);
}

void __pnet_pack_destroy(struct pnet_pack *pack, uint32_t type) {
	const struct pnet_pack_desc *desc;
	desc = find_pack_desc(type);

	desc->destroy(pack);
}


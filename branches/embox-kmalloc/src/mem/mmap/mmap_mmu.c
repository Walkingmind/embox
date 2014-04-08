/**
 * @file
 * @brief
 *
 * @date 09.11.12
 * @author Anton Bulychev
 */

#include <embox/unit.h>

#include <errno.h>
#include <stdlib.h>

#include <mem/mmap.h>
#include <mem/vmem.h>
#include <mem/kmalloc.h>

#include <kernel/thread/types.h>

#define INSIDE(x,a,b)       (((a) <= (x)) && ((x) < (b)))
#define INTERSECT(a,b,c,d)  (INSIDE(a,c,d) || INSIDE(c,a,b))

EMBOX_UNIT(init, fini);

static uint32_t mem_start;
static uint32_t mem_end;

static int initialized = 0;

static inline struct marea *build_marea(uint32_t start, uint32_t end, uint32_t flags) {
	struct marea *marea;

	if (!(marea = kmalloc(sizeof(struct marea)))) {
		return NULL;
	}

	marea->start = start;
	marea->end   = end;
	marea->flags = flags;

	dlist_head_init(&marea->mmap_link);

	return marea;
}

static inline void add_marea_to_mmap(struct emmap *mmap, struct marea *marea) {
	dlist_add_prev(&marea->mmap_link, &mmap->marea_list);
}

void mmap_init(struct emmap *mmap) {
	dlist_init(&mmap->marea_list);
	mmap->stack_marea = NULL;
	mmap->heap_marea = NULL;

	assert(!vmem_init_context(&mmap->ctx));

	if (!initialized) {
		/* It's kernel task. Set virtual context for it. */
		vmem_set_context(mmap->ctx);

		/* Now we can turn on MMU */
		vmem_on();

		initialized = 1;
	}
}

void mmap_free(struct emmap *mmap) {
	mmap_clear(mmap);
	vmem_free_context(mmap->ctx);
}

void mmap_clear(struct emmap *mmap) {
	struct marea *marea;

	dlist_foreach_entry(marea, &mmap->marea_list, mmap_link) {
		dlist_del(&marea->mmap_link);

		vmem_unmap_region(mmap->ctx, marea->start, marea->end - marea->start, 1);

		free(marea);
	}
}


struct marea *mmap_place_marea(struct emmap *mmap, uint32_t start, uint32_t end, uint32_t flags) {
	struct marea *marea;

	start = MAREA_ALIGN_DOWN(start);
	end   = MAREA_ALIGN_UP(end);

	if (!(INSIDE(start, mem_start, mem_end) && INSIDE(end, mem_start, mem_end))) {
		return NULL;
	}

	dlist_foreach_entry(marea, &mmap->marea_list, mmap_link) {
		if (INTERSECT(start, end, marea->start, marea->end)) {
			return NULL;
		}
	}

	if (!(marea = build_marea(start, end, flags))) {
		return NULL;
	}

	if (vmem_create_space(mmap->ctx, start, end-start, VMEM_PAGE_WRITABLE | VMEM_PAGE_USERMODE)) {
		free(marea);
		return NULL;
	}

	add_marea_to_mmap(mmap, marea);

	return marea;
}

struct marea *mmap_alloc_marea(struct emmap *mmap, size_t size, uint32_t flags) {
	struct dlist_head *item = &mmap->marea_list;
	uint32_t s_ptr = mem_start;
	struct marea *marea;

	size = MAREA_ALIGN_UP(size);

	do {
		if ((marea = mmap_place_marea(mmap, s_ptr, s_ptr + size, flags))) {
			return marea;
		}

		item = item->next;
		if (item == &mmap->marea_list) {
			break;
		}

		marea = dlist_entry(item, struct marea, mmap_link);
		s_ptr = marea->end;
	} while(1);

	return NULL;
}

uint32_t mmap_create_stack(struct emmap *mmap) {
	mmap->stack_marea = mmap_alloc_marea(mmap, 4096, 0);

	if (!mmap->stack_marea) {
		return 0;
	}

	return mmap->stack_marea->end;
}

void* mmap_create_heap(struct emmap *mmap) {
	//TODO: stub
	return NULL;
}

int mmap_inherit(struct emmap *mmap, struct emmap *p_mmap) {
	struct marea *marea, *new_marea;
	int res;

	dlist_foreach_entry(marea, &p_mmap->marea_list, mmap_link) {
		if (!(new_marea = build_marea(marea->start, marea->end, marea->flags))) {
			return -ENOMEM;
		}

		if ((res = vmem_copy_region(mmap->ctx, p_mmap->ctx, marea->start, marea->end - marea->start))) {
			free(marea);
			return res;
		}

	}
	return 0;
}

static int init() {
	mem_start = 0x04000000;
	mem_end   = 0xFFFFF000;

	return 0;
}

static int fini() {

	return 0;
}

/**
 * @file 
 * @brief 
 *
 * @author  Denis Deryugin
 * @date    4 Aug 2014
 */

#include "fork_copy_addr_space.h"
#include <kernel/task.h>
#include <kernel/task/resource/task_heap.h>
#include <kernel/task/resource/task_fork.h>
#include <mem/page.h>
#include <mem/phymem.h>
#include <sys/types.h>

extern size_t mspace_deep_copy_size(struct dlist_head *mspace);
extern void mspace_deep_store(struct dlist_head *mspace, struct dlist_head *store_space, void *buf);
extern void mspace_deep_restore(struct dlist_head *mspace, struct dlist_head *store_space, void *buf);

static inline struct dlist_head *task_mspace(struct task *tk) {
	struct task_heap *task_heap;

	task_heap = task_heap_get(task_self());
	return &task_heap->mm;
}

void fork_heap_store(struct heap_space *hpspc, struct task *tk) {
	size_t size;

	size = mspace_deep_copy_size(task_mspace(tk));
	
	if (hpspc->heap_sz != size) {
		if (hpspc->heap) {
			page_free(__phymem_allocator, hpspc->heap, hpspc->heap_sz / PAGE_SIZE());
		}

		hpspc->heap = page_alloc(__phymem_allocator, size / PAGE_SIZE());
		assert(hpspc->heap);
	}
	mspace_deep_store(task_mspace(tk), &hpspc->store_space, hpspc->heap);
}

void fork_heap_restore(struct heap_space *hpspc, struct task *tk) {
	mspace_deep_restore(task_mspace(tk), &hpspc->store_space, hpspc->heap);
}

void fork_heap_cleanup(struct heap_space *hpspc) {
	if (hpspc->heap) {
		page_free(__phymem_allocator, hpspc->heap, hpspc->heap_sz / PAGE_SIZE());
		hpspc->heap = NULL;
	}
}


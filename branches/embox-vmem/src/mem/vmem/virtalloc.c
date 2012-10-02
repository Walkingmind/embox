/**
 * @file
 * @brief
 *
 * @date 24.09.2012
 * @author Anton Bulychev
 */

#include <mem/vmem/virtalloc.h>
#include <hal/mm/mmu_core.h>
#include <mem/page.h>
#include <string.h>

static inline void *alloc_pages(size_t count) {
	void *addr = page_alloc(count);
	memset(addr, 0, count * MMU_PAGE_SIZE);
	return addr;
}

mmu_pte_t *alloc_pte_table() {
	return (mmu_pte_t *) alloc_pages(1);
}

mmu_pmd_t *alloc_pmd_table() {
	return (mmu_pmd_t *) alloc_pages(1);
}

void *alloc_virt_memory(size_t size) {
	/* XXX: size must be equal x*MMU_PAGE_SIZE */
	return alloc_pages(size / MMU_PAGE_SIZE);
}


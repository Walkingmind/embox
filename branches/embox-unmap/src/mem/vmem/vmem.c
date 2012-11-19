/**
 * @file
 * @brief Virtual memory subsystem
 *
 * @date 05.10.2012
 * @author Anton Bulychev
 */

#include <embox/unit.h>

#include <assert.h>
#include <errno.h>
#include <types.h>
#include <prom/prom_printf.h>
#include <hal/mmu.h>
#include <mem/vmem.h>
#include <mem/vmem/vmem_alloc.h>

#include "../kernel/task/common.h"
#include "../kernel/thread/types.h"

/* Section pointers. */
extern char _text_vma, _rodata_vma, _bss_vma, _data_vma, _reserve_vma, _stack_vma, _heap_vma;
extern char _text_len, _rodata_len, _bss_len, _data_len, _reserve_len, _stack_len, _heap_len;

static inline int vmem_map_kernel(mmu_ctx_t ctx);

static inline int vmem_map_on_itself(mmu_ctx_t ctx, void *addr, size_t size, vmem_page_flags_t flags) {
	/* Considering that address was aligned, but size may be not */
	size = (size + MMU_PAGE_MASK) & (~MMU_PAGE_MASK);
	return vmem_map_region(ctx, (mmu_paddr_t) addr, (mmu_vaddr_t) addr, (size_t) size, flags);
}

static inline int vmem_map_kernel(mmu_ctx_t ctx) {
	int err = 0;

	/* Map sections. */
	err |= vmem_map_on_itself(ctx, &_text_vma, (size_t) &_text_len, VMEM_PAGE_WRITABLE);
	err |= vmem_map_on_itself(ctx, &_rodata_vma, (size_t) &_rodata_len, VMEM_PAGE_WRITABLE);
	err |= vmem_map_on_itself(ctx, &_bss_vma, (size_t) &_bss_len, VMEM_PAGE_WRITABLE);
	err |= vmem_map_on_itself(ctx, &_data_vma, (size_t) &_data_len, VMEM_PAGE_WRITABLE);
	err |= vmem_map_on_itself(ctx, &_reserve_vma, (size_t) &_reserve_len, VMEM_PAGE_WRITABLE);
	err |= vmem_map_on_itself(ctx, &_stack_vma, (size_t) &_stack_len, VMEM_PAGE_WRITABLE);
	err |= vmem_map_on_itself(ctx, &_heap_vma, (size_t) &_heap_len, VMEM_PAGE_WRITABLE);

	/* Map special info. */
	err |= vmem_map_on_itself(ctx, VIRTUAL_TABLES_START, VIRTUAL_TABLES_LEN, VMEM_PAGE_WRITABLE);
	err |= vmem_map_on_itself(ctx, VIRTUAL_PAGES_INFO_START, VIRTUAL_PAGES_INFO_LEN, VMEM_PAGE_WRITABLE);

	// XXX below
	// for sparc
	err |= vmem_map_on_itself(ctx, (void *) 0x80000000, (size_t) 0x1000, VMEM_PAGE_WRITABLE);

	// mapping x86 video buffer
	err |= vmem_map_on_itself(ctx, (void *) 0xB8000, (size_t) 0x1000, VMEM_PAGE_WRITABLE);

	return err;
}

int vmem_create_context(mmu_ctx_t *ctx) {
	mmu_pgd_t *pgd = vmem_alloc_pgd_table();
	if (!pgd) {
		return -ENOMEM;
	}
	*ctx = mmu_create_context(pgd);
	return vmem_map_kernel(*ctx);
}

/*
static inline void vmem_print_info(void) {
	prom_printf("\n");
	prom_printf("MMU_PTE_MASK = 0x%08x\n", (unsigned int) MMU_PTE_MASK);
	prom_printf("MMU_PMD_MASK = 0x%08x\n", (unsigned int) MMU_PMD_MASK);
	prom_printf("MMU_PGD_MASK = 0x%08x\n", (unsigned int) MMU_PGD_MASK);

	prom_printf("\n");
	prom_printf("   text: start = 0x%08x, size = 0x%08x\n", (unsigned int) &_text_vma, (unsigned int) &_text_len);
	prom_printf(" rodata: start = 0x%08x, size = 0x%08x\n", (unsigned int) &_rodata_vma, (unsigned int) &_rodata_len);
	prom_printf("    bss: start = 0x%08x, size = 0x%08x\n", (unsigned int) &_bss_vma, (unsigned int) &_bss_len);
	prom_printf("   data: start = 0x%08x, size = 0x%08x\n", (unsigned int) &_data_vma, (unsigned int) &_data_len);
	prom_printf("reserve: start = 0x%08x, size = 0x%08x\n", (unsigned int) &_reserve_vma, (unsigned int) &_reserve_len);
	prom_printf("  stack: start = 0x%08x, size = 0x%08x\n", (unsigned int) &_stack_vma, (unsigned int) &_stack_len);
	prom_printf("   heap: start = 0x%08x, size = 0x%08x\n", (unsigned int) &_heap_vma, (unsigned int) &_heap_len);
}
*/

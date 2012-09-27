/**
 * @file
 * @brief Virtual memory subsystem
 *
 * @date 29.07.11
 * @author Anton Kozlov
 */

#include <embox/unit.h>

#include <assert.h>
#include <types.h>
#include <stdio.h>
#include <hal/mm/mmu_core.h>
#include <hal/env/traps_core.h>
#include <hal/test/traps_core.h>
#include <mem/page.h>

extern char _mem_begin;
extern char _mem_length;

extern char __KERNEL_START;
extern char __KERNEL_END;

#define MEM_BEGIN       (&_mem_begin)
#define MEM_LENGTH      (&_mem_length)
#define MEM_END         (MEM_BEGIN + MEM_LENGTH)

#define KERNEL_START 	(&__KERNEL_START)
#define KERNEL_END		(&__KERNEL_END)
#define KERNEL_SIZE     (KERNEL_END - KERNEL_START)

#define INITIAL_SPACE   3*1024*4096

EMBOX_UNIT(vmem_init, vmem_fini);

static void vmem_map_kernel(mmu_ctx_t ctx);

void vmem_on(void) {
	mmu_on();
}

void vmem_off(void) {
	mmu_off();
}

static void vmem_map_kernel(mmu_ctx_t ctx) {
	mmu_map_region(ctx, (paddr_t) KERNEL_START, (vaddr_t) KERNEL_START,
			KERNEL_SIZE, MMU_PAGE_CACHEABLE | MMU_PAGE_WRITEABLE);
}

void vmem_create_virtual_space(mmu_ctx_t ctx) {
	int page_count;
	void *addr;

	vmem_map_kernel(ctx);

	page_count = INITIAL_SPACE / MMU_PAGE_SIZE;
	addr = page_alloc(page_count);

	// Map INITIAL_SPACE after KERNEL_END
	mmu_map_region(ctx, (paddr_t) addr, (vaddr_t) KERNEL_END,
			INITIAL_SPACE, MMU_PAGE_CACHEABLE | MMU_PAGE_WRITEABLE);
}

/*

static int pagefault_handler(uint32_t nr, void *data) {
	int err_addr = mmu_get_fault_address() & ~(PAGE_SIZE() - 1);
	mmu_off();

	mmu_map_region((mmu_ctx_t) 0, (paddr_t) page_alloc() ,
			(vaddr_t) err_addr & ~(PAGE_SIZE() - 1), PAGE_SIZE(), MMU_PAGE_CACHEABLE |
			MMU_PAGE_WRITEABLE);

	mmu_on();
	return 1; // execute exception-cause instruction once more
}

*/

/* Checks mapping */
static inline void vmem_test_mem(void) {
	char c;
	for (char *i = KERNEL_START; i < KERNEL_END; i++) {
		assert(mmu_translate((mmu_ctx_t) 0, (vaddr_t) i) == (paddr_t) i);
		c = *i;
		c = c;
	}
}

static int vmem_init(void) {
#if 0
	printf("\n\n");
	printf("KERNEL_START = 0x%08x\n", (unsigned int) KERNEL_START);
	printf("KERNEL_END = 0x%08x\n", (unsigned int) KERNEL_END);
	printf("KERNEL_SIZE = 0x%08x\n", (unsigned int) KERNEL_SIZE);
	printf("\n");
	printf("MEM_BEGIN = 0x%08x\n", (unsigned int) MEM_BEGIN);
	printf("MEM_LENGTH = 0x%08x\n", (unsigned int) MEM_LENGTH);
	printf("\n");
#endif

	vmem_create_virtual_space((mmu_ctx_t) 0);

	vmem_on();

	vmem_test_mem();

	return 0;
}

static int vmem_fini(void) {
	vmem_off();

	return 0;
}


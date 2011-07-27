/**
 * @file
 * @brief Testing page fault in virtual mode
 *
 * @date 07.04.10
 * @author Nikolay Korotky
 */

#include <types.h>
#include <embox/test.h>
#include <hal/mm/mmu_core.h>
#include <hal/mm/mmu_page.h>
#include <hal/env/traps_core.h>
#include <hal/test/mmu_core.h>
#include <hal/test/traps_core.h>

EMBOX_TEST(run);

#define VADDR(region, phyaddr) (region + ((uint32_t)(phyaddr) & 0xfff))

static uint32_t addr;

static int dfault_happend = 0;

/* MMU data access exception handler */
static int dfault_handler(uint32_t trap_nr, void *data) {
	dfault_happend = 1;
	return 0;
}

static int test_for_dfault(void) {
	uint32_t vaddr = VADDR(0xf0000000, &addr);

	mmu_map_region((mmu_ctx_t)0, (paddr_t)(&addr) & ~0xfff, 0xf0000000, 0x1000,
			MMU_PAGE_CACHEABLE | MMU_PAGE_WRITEABLE | MMU_PAGE_EXECUTEABLE);

	mmu_on();

	*((volatile uint32_t *) vaddr) = 0x11111111;

	mmu_off();

	mmu_map_region((mmu_ctx_t)0, (paddr_t)(&addr) & ~0xfff, 0xf0001000, 0x1000,
				MMU_PAGE_CACHEABLE | MMU_PAGE_EXECUTEABLE);
	mmu_on();

	/* Data access exception */
	vaddr = VADDR(0xf0001000, &addr);
	*((volatile uint32_t *) vaddr) = 0x77777777;


	return (addr == 0x11111111 && dfault_happend) ? 0 : -1;
}

static int run(void) {
	extern char _text_start, __stack, _data_image_start;
	mmu_env_t prev_mmu_env;
	traps_env_t old_env;
	unsigned long var;

	mmu_save_env(&prev_mmu_env);
	mmu_set_env(testmmu_env());

	traps_save_env(&old_env);
	traps_set_env(testtraps_env());

	/* map one to one section text and may be whole image with stack */
	mmu_map_region((mmu_ctx_t)0, (uint32_t) &_text_start,
			(uint32_t) &_text_start, 0x1000000,
			MMU_PAGE_CACHEABLE | MMU_PAGE_WRITEABLE | MMU_PAGE_EXECUTEABLE);

	if (&__stack > (&_text_start + 0x1000000)) {
		/* if have to map data sections */
		mmu_map_region((mmu_ctx_t)0, (paddr_t)&_data_image_start, (vaddr_t)&_data_image_start,
				0x1000000, MMU_PAGE_CACHEABLE | MMU_PAGE_WRITEABLE);
	}

	testtraps_set_handler(TRAP_TYPE_HARDTRAP, MMU_DFAULT, dfault_handler);

	traps_restore_env(&old_env);
	mmu_restore_env(&prev_mmu_env);

	return test_for_dfault();
}

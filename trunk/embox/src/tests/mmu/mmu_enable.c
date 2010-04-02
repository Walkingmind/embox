/**
 * @file
 *
 * @brief Testing page translating in virtual mode
 *
 * @details This is the simplest test for MMU module. It just maps one to one
 *         memory region where lay sections '.text', '.data', '.bss' and stack.
 *         And than switch on virtual mode, and immediately restore mode
 *         (virtual or real).
 *
 * @date 09.03.2010
 * @author Anton Bondarev
 */

#include <types.h>

#include <embox/test.h>
#include <hal/mm/mmu_core.h>
#include <test/testmmu_core.h>

/* declare test in system */
EMBOX_TEST(run);

/* starting function for test */
static int run() {
	extern char _text_start, __stack, _data_start;
	mmu_env_t prev_mmu_env;

	mmu_save_env(&prev_mmu_env);
	mmu_set_env(testmmu_env());

	/* map one to one section text and may be whole image with stack */
	mmu_map_region((uint32_t) &_text_start, (uint32_t) &_text_start, 0x1000000,
			MMU_PAGE_CACHEABLE | MMU_PAGE_WRITEABLE | MMU_PAGE_EXECUTEABLE);

	if (&__stack > (&_text_start + 0x1000000)) {
		/* if have to map data sections */
		mmu_map_region(_data_start, _data_start, 0x1000000, MMU_PAGE_CACHEABLE
				| MMU_PAGE_WRITEABLE);
	}

	mmu_on();

	mmu_restore_env(&prev_mmu_env);
	return 0;
}

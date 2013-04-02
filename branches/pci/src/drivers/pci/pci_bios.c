/**
 * @file
 * @brief
 *
 * @date 02.04.13
 * @author Ilia Vaprol
 */

#include <errno.h>
#include <embox/unit.h>
#include <mem/page.h>
#include <framework/mod/options.h>

#define MEMORY OPTION_GET(NUMBER, memory)
#define MEMORY_SZ OPTION_GET(NUMBER, memory_sz)

EMBOX_UNIT_INIT(pci_bios_init);

static int pci_bios_init(void) {
	struct page_allocator *pci_allocator;

	pci_allocator = page_allocator_init(MEMORY, MEMORY_SZ, PAGE_SIZE());
	if (pci_allocator == NULL) {
		return -ENOMEM;
	}

	void *mem = page_alloc_zero(pci_allocator, PAGE_SIZE());
	mem = mem;

	return 0;
}

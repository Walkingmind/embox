/**
 * @file
 * @brief
 *
 * @date 02.04.13
 * @author Ilia Vaprol
 */

#include <errno.h>
#include <embox/unit.h>
#include <stddef.h>
#include <framework/mod/options.h>

#define PCI_SPACE_BASE  OPTION_GET(NUMBER, pci_space_base)
#define PCI_SPACE_SIZE  OPTION_GET(NUMBER, pci_space_size)
#define PCI_WINDOW_SIZE OPTION_GET(NUMBER, pci_window_size)

EMBOX_UNIT_INIT(pci_bios_init);

struct space_allocator {
	void *space_base;
	size_t space_size;
};

static struct space_allocator  pci_allocator = {
		.space_base = (void *)PCI_SPACE_BASE,
		.space_size = PCI_SPACE_SIZE,
};

void *space_alloc(struct space_allocator *allocator, size_t window, size_t align) {
	return (void *)((size_t)allocator->space_base + PCI_WINDOW_SIZE);
}

static int pci_bios_init(void) {

	space_alloc(&pci_allocator, PCI_WINDOW_SIZE, PCI_WINDOW_SIZE);

	return 0;
}

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
#include <prom/prom_printf.h>
#include <drivers/pci/pci.h>

#define PCI_SPACE_BASE  OPTION_GET(NUMBER, pci_space_base)
#define PCI_SPACE_SIZE  OPTION_GET(NUMBER, pci_space_size)
#define PCI_WINDOW_SIZE OPTION_GET(NUMBER, pci_window_size)

EMBOX_UNIT_INIT(pci_bios_init);

struct space_allocator {
	void *space_base;
	size_t space_size;
};

static struct space_allocator pci_allocator = {
		.space_base = (void *)PCI_SPACE_BASE,
		.space_size = PCI_SPACE_SIZE,
};

void *space_alloc(struct space_allocator *allocator, size_t win, size_t align) {
	void *ret = allocator->space_base;

	allocator->space_base = (void *)((size_t)(allocator->space_base) + win);

	return ret;
}

int pci_slot_configure(uint32_t busn, uint32_t devfn){
	int bar_num;
	uint32_t length;
	uint32_t bar[6];
	void *window;

	for(bar_num = 0; bar_num < 6; bar_num ++) {
		// Write all '1'
		pci_write_config32(busn, devfn, PCI_BASE_ADDR_REG_0 + (bar_num << 2), 0xFFFFFFFF);
		// Read back size
		pci_read_config32(busn, devfn, PCI_BASE_ADDR_REG_0 + (bar_num << 2), &bar[bar_num]);
		if (bar[bar_num] == 0)
			continue;
		if(bar[bar_num] & 0x1F) {
			continue;
		}
		length = 1 + ~(bar[bar_num] & 0xFFFFFFF0);

		window = space_alloc(&pci_allocator, length, length);
		pci_write_config32(busn, devfn, PCI_BASE_ADDR_REG_0 + (bar_num << 2), (uint32_t)window);
		prom_printf("pci bus %d fn = %d bar_num %d bar = 0x%X win = 0x%X len = 0x%X\n", busn, devfn, bar_num, bar[bar_num], (uint32_t)window, (uint32_t)length);
	}
	return 0;
}

static void pci_bus_configure(uint32_t busn) {
	uint32_t bus=busn, devfn;
	uint8_t hdr_type, is_multi = 0;

	for (devfn = MIN_DEVFN; devfn < MAX_DEVFN; ++devfn) {
		/* Devices are required to implement function 0, so if
		 * it's missing then there is no device here. */
		if (PCI_FUNC(devfn) && !is_multi) {
			/* Not a multiple function device */
			continue;
		}

		pci_read_config8(bus, devfn, PCI_HEADER_TYPE, &hdr_type);
		if (!PCI_FUNC(devfn)) {
			/* If bit 7 of this register is set, the device
			 * has multiple functions;
			 * otherwise, it is a single function device */
			is_multi = hdr_type & (1 << 7);
		}

		/*The header type is devided into two sections.
		 * Bits 6..0 comprise the header type. Bit 7 is the single/multi
		 * funtion device flag (0=single 1=multi). The header type specifies
		 * the format of bytes 0x10 to 0x3f. The two defined types are 0x00,
		 * the standard header type (pictured above), and 0x01,
		 * PCI-PCI bridge.*/
		if((hdr_type & 0x7F) == 1) { /* PCI-PCI bridge */
			/* align space at 1Mb */
			space_alloc(&pci_allocator, PCI_WINDOW_SIZE, PCI_WINDOW_SIZE);
			pci_write_config32(busn, (dev->slot << 3) | devfn, PCI_PRIMARY_BUS, (dev->primary) | (dev->secondary << 8) | (dev->subordinate << 16));
			//pci_write_config32(busn, (slot << 3) | func, PCI_PRIMARY_BUS, (new_dev->primary) | (new_dev->secondary << 8) | (new_dev->subordinate << 16));
			prom_printf("\nbridge start configure bus %d\n*******\n", busn+1);
			pci_bus_configure(busn + 1);

		} else { /* not bridge */
			pci_slot_configure(bus, devfn);
		}
	}
	/* Enable bus mastering and memory requests processing */
	pci_write_config32(busn, devfn, PCI_COMMAND, 6);
}

static int pci_bios_init(void) {
	pci_bus_configure(0);
	return 0;
}

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

static struct space_allocator  pci_allocator = {
		.space_base = (void *)PCI_SPACE_BASE,
		.space_size = PCI_SPACE_SIZE,
};

void *space_alloc(struct space_allocator *allocator, size_t win, size_t align) {
	return (void *)((size_t)allocator->space_base + win);
}

static int pci_slot_configure(uint32_t busn, uint32_t devfn){
	int bar_num;
	uint32_t length;
	uint32_t bar[6];

	for(bar_num = 0; bar_num < 6; bar_num ++) {
		// Write all '1'
		pci_write_config32(busn, devfn, PCI_BASE_ADDR_REG_0 + (bar_num << 2), 0xFFFFFFFF);
		// Read back size
		pci_read_config32(busn, devfn, PCI_BASE_ADDR_REG_0 + (bar_num << 2), &bar[bar_num]);
		if (bar[bar_num] == 0)
			continue;
		length = 1 + ~(bar[bar_num] & 0xFFFFFFF0);
#if 0
		//printk("bar%d, value: %x, length=%x\n", bar_num, dev->bar[bar_num], length);
		// Calculate memory base address
		next_memory_address = (next_memory_address + length - 1)&bar[bar_num]&0xFFFFFFF0;
		// Assign memory size
		pci_write_config32(dev->busn, devfn, PCI_BASE_ADDR_REG_0 + (bar_num << 2), next_memory_address);
		next_memory_address += length;
		// Read back actual address base
		pci_read_config32(dev->busn, devfn, PCI_BASE_ADDR_REG_0 + (bar_num << 2), &dev->bar[bar_num]);
		//printk("bar%d, assigned value: %x\n", bar_num, dev->bar[bar_num]);
#endif
	}
	return 0;
}

extern uint32_t pci_get_vendor_id(uint32_t bus, uint32_t devfn) ;
static int pci_bios_init(void) {
	uint32_t bus, devfn;
	uint8_t hdr_type, is_multi = 0;

	for (bus = 0; bus < PCI_BUS_QUANTITY; ++bus) {
		for (devfn = MIN_DEVFN; devfn < MAX_DEVFN; ++devfn) {
			uint32_t vendor_reg;

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

			if (-1 == (vendor_reg = pci_get_vendor_id(bus, devfn))) {
				is_multi = 0;
				continue;
			}
			/*The header type is devided into two sections.
			 * Bits 6..0 comprise the header type. Bit 7 is the single/multi
			 * funtion device flag (0=single 1=multi). The header type specifies
			 * the format of bytes 0x10 to 0x3f. The two defined types are 0x00,
			 * the standard header type (pictured above), and 0x01,
			 * PCI-PCI bridge.*/
			if((hdr_type & 0x7F) == 1) { /* PCI-PCI bridge */
				space_alloc(&pci_allocator, PCI_WINDOW_SIZE, PCI_WINDOW_SIZE);
			} else { /* not bridge */
				pci_slot_configure(bus,devfn);

			}

		}
	}



	return 0;
}

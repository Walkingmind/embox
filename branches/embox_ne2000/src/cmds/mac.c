/**
 *  @file mac.c
 *  @brief show physical address net device
 *  @date 01.07.11
 *  @author: Gleb Efimov
 */

#include <types.h>
#include <stdio.h>
#include <drivers/pci.h>
#include <net/ne2k_pci.h>
#include <embox/cmd.h>
#include <asm/io.h>

EMBOX_CMD(exec);

static int exec(int argv, char **argc){
	struct pci_dev *pci_dev;
	uint32_t base_addr;
	uint8_t mac_addr[6];

	pci_dev = pci_find_dev(0x10EC, 0x8029);
		if (NULL == pci_dev) {
			printf("Couldn't find NE2K_PCI device");
			return 0;
		}

	base_addr = (pci_dev->bar[0]) & (~0xf);

	printf("base_addr = 0x%X\n", base_addr);
	out8(in8(base_addr) | (0x1 << 6), base_addr); /* set PS0=0, PS1=1 */

	for (uint8_t i = 0; i < 6; i++ ){
		mac_addr[i] = in8(base_addr + i);
		printf("0x%X:",mac_addr[i]);
	}
	return 0;
}


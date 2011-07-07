/**
 *  @file mac.c
 *  @brief show physical address net device
 *  @date 01.07.11
 *  @author: Gleb Efimov
 *  @author: Ilia Vaprol
 */

#include <types.h>
#include <stdio.h>
#include <drivers/pci.h>
//#include <net/ne2k_pci.h>
#include <embox/cmd.h>
#include <asm/io.h>

#define NE_DATAPORT		0x10	/* NatSemi-defined port window offset. */
#define NS_RESET		0x1f	/* Issue a read to reset, a write to clear. */

#define E8390_CMD		0x00	/* The command register (for all pages) */
#define E8390_STOP		0x01	/* Stop and reset the chip */
#define E8390_START		0x02	/* Start the chip, clear reset */
#define E8390_RREAD		0x08	/* Remote read */
#define E8390_NODMA		0x20	/* Remote DMA */
#define E8390_PAGE0		0x00	/* Select page chip registers */
#define E8390_PAGE1		0x40	/* using the two high-order bits */
#define E8390_PAGE2		0x80
#define E8390_PAGE3		0xC0	/* Page 3 is invalid on the real 8390. */
#define E8390_RXOFF 0x20		/* EN0_RXCR: Accept no packets */
#define E8390_TXOFF 0x02		/* EN0_TXCR: Transmitter off */

/* Page 0 register offsets. */
#define EN0_ISR			0x07	/* Interrupt status reg RD WR */
#define EN0_CRDALO		0x08	/* low byte of current remote dma address RD */
#define EN0_RSARLO		0x08	/* Remote start address reg 0 */
#define EN0_CRDAHI		0x09	/* high byte, current remote dma address RD */
#define EN0_RSARHI		0x09	/* Remote start address reg 1 */
#define EN0_RCNTLO		0x0a	/* Remote byte count reg WR */
#define EN0_RCNTHI		0x0b	/* Remote byte count reg WR */
#define EN0_RXCR		0x0c	/* RX configuration reg WR */
#define EN0_TXCR		0x0d	/* TX configuration reg WR */
#define EN0_DCFG		0x0e	/* Data configuration reg WR */
#define EN0_IMR			0x0f	/* Interrupt mask reg WR */

EMBOX_CMD(exec);

#define STATION_ADDRESS_SZ	32

static int exec(int argv, char **argc) {
	struct pci_dev *pci_dev;
	uint32_t base_addr, i, page;
	unsigned char SA_prom[STATION_ADDRESS_SZ];
	int wordlength;
	struct {unsigned char value, offset; } program_seq[] = {
		{E8390_NODMA + E8390_PAGE0 + E8390_STOP, E8390_CMD}, /* Select page 0*/
		{0x48, EN0_DCFG},		/* Set byte-wide (0x48) access. */
		{0x00, EN0_RCNTLO},	/* Clear the count regs. */
		{0x00, EN0_RCNTHI},
		{0x00, EN0_IMR},		/* Mask completion irq. */
		{0xFF, EN0_ISR},
		{E8390_RXOFF, EN0_RXCR},		/* 0x20	 Set to monitor */
		{E8390_TXOFF, EN0_TXCR},		/* 0x02	 and loopback mode. */
		{32, EN0_RCNTLO},
		{0x00, EN0_RCNTHI},
		{0x00, EN0_RSARLO},	/* DMA starting at 0x0000. */
		{0x00, EN0_RSARHI},
		{E8390_RREAD + E8390_START, E8390_CMD},
	};

	pci_dev = pci_find_dev(0x10EC, 0x8029);
		if (NULL == pci_dev) {
			printf("Couldn't find NE2K_PCI device");
			return 0;
		}
	base_addr = pci_dev->bar[0] & ~0x0F;

	for (i = 0; i < sizeof(program_seq)/sizeof(program_seq[0]); i++)
		out8(program_seq[i].value, base_addr + program_seq[i].offset);

	wordlength = 2;
	/* Get Station Address */
	for(i = 0; i < STATION_ADDRESS_SZ ; i += 2) {
		SA_prom[i] = in8(base_addr + NE_DATAPORT);
		SA_prom[i+1] = in8(base_addr + NE_DATAPORT);
		if (SA_prom[i] != SA_prom[i+1])
			wordlength = 1;
	}
	printf("Station Address PROM  0:");
	for(i = 0; i < STATION_ADDRESS_SZ / 2; i++)
		printf(" %2x", SA_prom[i]);
	printf("\nStation Address PROM %2x:", i);
	for(; i < STATION_ADDRESS_SZ; i++)
		printf(" %2x", SA_prom[i]);
	printf("\n");

#if 0
	/* PAGE0[READ]:07 (ISR) */
	if (wordlength == 2) {
		/* We must set the 8390 for word mode, AND RESET IT. */
		int tmp;
		out8(0x49, base_addr + EN0_DCFG);
		tmp = in8(base_addr + NS_RESET);
		outb(tmp, base_addr + NS_RESET);
		/* Un-double the SA_prom values. */
		for (i = 0; i < 16; i++)
			SA_prom[i] = SA_prom[i+i];
	}
#endif

#if 0
	for (i = 1; i < 6; i++) {
		out8(i, ioaddr + i);
	}
	out8(i, ioaddr + i);
#endif

	/* Get MAC-Address */
	out8(E8390_NODMA + E8390_PAGE1, base_addr + E8390_CMD);
	printf("The current MAC stations address is ");
	for (i = 1; i < 6; i++) {
		printf("%2X:", in8(base_addr + i));
	}
	printf("%2X.\n", in8(base_addr + i));

	/* Page Dump*/
	for (page = 0; page < 4; page++) {
		printf("8390 page %d:", page);
		out8(E8390_NODMA + (page << 6), base_addr + E8390_CMD);
		for(i = 0; i < 16; i++) {
			printf(" %2x", in8(base_addr + i));
		}
		printf(".\n");
	}

	return 0;
}


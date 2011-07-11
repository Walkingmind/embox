/**
 * @file
 * @brief An implementation of an ne2000 PCI ethernet adapter.
 * @details Driver to fool Qemu into sending and receiving
 *          packets for us via it's ne2k_isa emulation
 *          This driver is unlikely to work with real hardware
 *          without substantial modifications and is purely for
 *          helping with the development of network stacks.
 *          Interrupts are not supported.
 *
 * @date 11.01.11
 * @author Biff
 *         - Initial implementation
 * @author Nikolay Korotky
 *         - Adaptation for embox
 */

#include <types.h>
#include <string.h>
#include <asm/io.h>
#include <kernel/irq.h>
#include <net/if_ether.h>
#include <net/skbuff.h>
#include <net/netdevice.h>
#include <net/net.h>
#include <net/etherdevice.h>
#include <embox/unit.h>
#include <linux/init.h>
#include <drivers/pci.h>
#include <net/ne2k_pci.h>
#include <stdio.h>

EMBOX_UNIT_INIT(unit_init);

#define E8390_CMD    0x00 /* The command register (for all pages) */
#define E8390_STOP   0x01 /* Stop and reset the chip */
#define E8390_START  0x02 /* Start the chip, clear reset */
#define E8390_RREAD  0x08 /* Remote read */
#define E8390_RWRITE 0x10 /* Remote write  */
#define E8390_NODMA  0x20 /* Remote DMA */
#define E8390_PAGE0  0x00 /* Select page chip registers */
#define E8390_PAGE1  0x40 /* using the two high-order bits */
#define E8390_PAGE2  0x80
#define E8390_PAGE3  0xC0 /* Page 3 is invalid on the real 8390. */
#define E8390_RXOFF  0x20 /* EN0_RXCR: Accept no packets */
#define E8390_TXOFF  0x02 /* EN0_TXCR: Transmitter off */

/* Page 0 register offsets. */
#define EN0_CRDALO  0x08  /* low byte of current remote dma address RD */
#define EN0_CRDAHI  0x09  /* high byte, current remote dma address RD */

static inline void rx_enable(void) {
	out8(NE_PAGE0_STOP,   NE_CMD);
	out8(RX_BUFFER_START, EN0_BOUNDARY);
	out8(NE_PAGE1_STOP,   NE_CMD);
	out8(RX_BUFFER_START, EN1_CURPAG);
	out8(NE_START,        NE_CMD);
}

static inline void rx_disable(void) {
	/* do nothing */
	out8(NE_STOP, NE_CMD);
}

static inline void set_tx_count(uint16_t val) {
	/* Set how many bytes we're going to send. */
	out8(val & 0xff, EN0_TBCR_LO);
	out8(val >> 8, EN0_TBCR_HI);
}

static inline void set_rem_address(uint16_t val) {
	/* Set how many bytes we're going to send. */
	out8(val & 0xff, EN0_RSARLO);
	out8(val >> 8, EN0_RSARHI);
}

static inline void set_rem_byte_count(uint16_t val) {
	/* Set how many bytes we're going to send. */
	out8(val & 0xff, EN0_RCNTLO);
	out8(val >> 8, EN0_RCNTHI);
}
#if 0
static void copy_data_to_card(uint16_t dest, uint8_t* src, uint16_t length) {
	uint16_t i;
	set_rem_address(dest);
	set_rem_byte_count(length);
	for (i = 0; i < length; i++) {
		out8(*src, NE_BASE + 0x10);
		src++;
	}
}
// XXX defined but not used
static void copy_data_from_card(uint32_t src, uint8_t *dest, uint32_t length) {
	uint32_t i;
	set_rem_address(src);
	set_rem_byte_count(length);
	for (i = 0; i < length; i++) {
		*dest = in8(NE_BASE + 0x10);
		dest++;
	}
}

/**
 * Copy data out of the receive buffer.
 */
static size_t copy_pkt_from_card(uint8_t *dest, uint32_t max_len) {
	uint32_t next, total_length;
	uint8_t header[4];
	/* Find out where the next packet is in card memory */
	uint32_t src = in8(EN0_BOUNDARY) * 256;

	copy_data_from_card(src, header, sizeof(header));

	next = header[1];

	total_length = header[3];
	total_length <<= 8;
	total_length |=  header[2];

	/* Now copy it to buffer, if possible, skipping the info header. */
	src += 4;
	total_length -= 4;
	copy_data_from_card(src, dest, total_length);

	/* Release the buffer by increasing the boundary pointer. */
	out8(next, EN0_BOUNDARY);

	return total_length;
}

/**
 * Returns size of pkt, or zero if none received.
 */
static size_t pkt_receive(struct sk_buff *skb) {
	uint32_t boundary, current;
	size_t ret = 0;

	out8(NE_PAGE1, NE_CMD);
	current = in8(EN1_CURPAG);

	/* Check if rsr fired. */
	out8(NE_PAGE0, NE_CMD);
	boundary = in8(EN0_BOUNDARY);

	if (boundary != current) {
		ret = copy_pkt_from_card(skb->data, skb->len);
	}
	return ret;
}
#endif

/**
 * queue packet for transmission
 */
static int start_xmit(struct sk_buff *skb, struct net_device *dev) {
#if 0
	/* Set TPSR, start of tx buffer memory to zero
	 * (this value is count of pages) */
	out8(TX_BUFFER_START, EN0_TPSR);

	copy_data_to_card(16 * 1024, skb->data, skb->len);

	/* Set how many bytes to transmit */
	set_tx_count(skb->len);

	/* issue command to actually transmit a frame */
	out8(0x04, NE_CMD);

	/* Wait for transmission to complete. */
	while (in8(NE_CMD) & 0x04);

	TRACE("Done transmit\n");

	return skb->len;
#endif

	unsigned long nic_base = dev->base_addr;
    unsigned int i, count = skb->len;
    unsigned char *buf = skb->data;
    int start_page = 16 * 1024;

    /* We should already be in page 0, but to be safe... */
    out8(E8390_PAGE0 + E8390_START + E8390_NODMA, nic_base + NE_CMD);

    /* Now the normal output. */
    out8(count & 0xff, nic_base + EN0_RCNTLO);
    out8(count >> 8,   nic_base + EN0_RCNTHI);
    out8(0x00, nic_base + EN0_RSARLO);
    out8(start_page, nic_base + EN0_RSARHI);

    out8(E8390_RWRITE+E8390_START, nic_base + NE_CMD);
	for (i = 0; i < count; i++) {
		out8(*buf, nic_base + NE_DATAPORT);
		buf++;
	}

    return count;
}

static int open(net_device_t *dev) {
	unsigned long nic_base;
	if (NULL == dev) {
		return -1;
	}
	nic_base = dev->base_addr;
	/* 8-bit access only, makes the maths simpler. */
	out8(0, nic_base + 0x0e);

	/* setup receive buffer location */
	out8(RX_BUFFER_START, EN0_STARTPG);
	out8(RX_BUFFER_END, EN0_STOPPG);

	return 0;
}

static int stop(net_device_t *dev) {
	if (NULL == dev) {
		return 0;
	}
	//TODO
	return 1;
}

static int set_mac_address(struct net_device *dev, void *addr) {
	if (NULL == dev || NULL == addr) {
		return -1;
	}
	//TODO
	return 0;
}

/**
 * Get RX/TX stats
 */
static net_device_stats_t *get_eth_stat(net_device_t *dev) {
	return &(dev->stats);
}

static irq_return_t ne2k_handler(irq_nr_t irq_num, void *dev_id) {
	TRACE("irq fired\n");
	return IRQ_HANDLED;
}

static const struct net_device_ops _netdev_ops = {
        .ndo_start_xmit      = start_xmit,
        .ndo_open            = open,
        .ndo_stop            = stop,
        .ndo_get_stats       = get_eth_stat,
        .ndo_set_mac_address = set_mac_address
};

static int __init unit_init(void) {
	net_device_t *nic;
	uint16_t new_command, pci_command;
	uint8_t  pci_latency;
	struct pci_dev *pci_dev;

	pci_dev = pci_find_dev(0x10EC, 0x8029);
	if (NULL == pci_dev) {
		LOG_WARN("Couldn't find NE2K_PCI device");
		return 0;
	}

	if (NULL != (nic = alloc_etherdev(0))) {
		nic->netdev_ops = &_netdev_ops;
		//TODO: get devfn=0x18 from pci_find_dev
		pci_read_config32(0, 0x18, PCI_BASE_ADDR_REG_0, (uint32_t *) &nic->base_addr);
		pci_read_config8(0, 0x18, PCI_INTERRUPT_LINE, (uint8_t *) &nic->irq);
		nic->base_addr &= PCI_BASE_ADDR_IO_MASK;
	}

	/* Set device to be bus master */
	pci_read_config16(0, 0x18, PCI_COMMAND, &pci_command);
	new_command = pci_command | PCI_COMMAND_MASTER | PCI_COMMAND_IO;
	pci_write_config16(0, 0x18, PCI_COMMAND, new_command);

	/* Set latency */
	pci_read_config8(0, 0x18, PCI_LATENCY_TIMER, &pci_latency);
	if (pci_latency < 32) {
		pci_write_config8(0, 0x18, PCI_LATENCY_TIMER, 32);
	}

	/* Reset */
	out8(in8(nic->base_addr + NE_RESET), nic->base_addr + NE_RESET);
	out8(ENISR_RESET, nic->base_addr + EN0_ISR);

	if (-1 == irq_attach(nic->irq, ne2k_handler, 0, nic, "ne2k")) {
		return -1;
	}


	/* Back to page 0 */
	out8(NE_PAGE0_STOP, NE_CMD);

	/* That's for the card area, however we must also set the mac
	 * in the card ram as well, because that's what the
	 * qemu emulation actually uses to determine if the packet's
	 * bound for this NIC.
	 */

	return 0;
}

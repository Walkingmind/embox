/**
 * @file
 * @brief Interrupt controller driver for i8952 chip 9x86 platform).
 *
 * @details This driver believes that there are two i8952 chip in the system
 *        and slave connect to master's second line. We also suppose that we
 *        use only x86 platform.
 *
 * @date 22.12.10
 * @author Nikolay Korotky
 */

#include <types.h>

#include <asm/regs.h>
#include <asm/traps.h>
#include <asm/io.h>
#include <asm/cpu.h>
#include <drivers/i8259.h>
#include <hal/arch.h>
#include <hal/reg.h>
#include <hal/interrupt.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(unit_init);

/**
 * Initialize the PIC
 */
static int unit_init(void) {
	/* Initialize the master */
	out8(PIC1_ICW1, PIC1_COMMAND);
	out8(PIC1_BASE, PIC1_DATA);
	out8(PIC1_ICW3, PIC1_DATA);
	out8(PIC1_ICW4, PIC1_DATA);

	/* Initialize the slave */
	out8(PIC2_ICW1, PIC2_COMMAND);
	out8(PIC2_BASE, PIC2_DATA);
	out8(PIC2_ICW3, PIC2_DATA);
	out8(PIC2_ICW4, PIC2_DATA);

	out8(NON_SPEC_EOI, PIC1_COMMAND);
	out8(NON_SPEC_EOI, PIC2_COMMAND);

	apic_disable_all();
	interrupt_enable(7); /* enable slave irq controller irq 8-16 */
	irq_enable();

	return 0;
}

void interrupt_enable(interrupt_nr_t int_nr) {
	if (int_nr > 8) {
		out8(in8(PIC2_DATA) & ~(1 << int_nr), PIC2_DATA);
	} else {
		out8(in8(PIC1_DATA) & ~(1 << int_nr), PIC1_DATA);
	}
}

void interrupt_disable(interrupt_nr_t int_nr) {
	if (int_nr > 8) {
		out8(in8(PIC2_DATA) | (1 << int_nr), PIC2_DATA);
	} else {
		out8(in8(PIC1_DATA) | (1 << int_nr), PIC1_DATA);
	}
}

void interrupt_force(interrupt_nr_t irq_num) {
	// TODO Emm?.. -- Eldar
}

void irqc_set_mask(__interrupt_mask_t mask) {
	out8(mask & 0xff, PIC1_DATA);
	out8((mask >> 8) & 0xff, PIC2_DATA);
}

__interrupt_mask_t irqc_get_mask(void) {
	return (in8(PIC2_DATA) << 8) | in8(PIC1_DATA);
}

/**
 * @file
 * @brief
 *
 * @date 06.01.11
 * @author Anton Bondarev
 */

#include <types.h>
#include <hal/reg.h>
#include <kernel/irq.h>
#include <asm/regs.h>
#include <asm/traps.h>
#include <asm/io.h>
#include <drivers/i8259.h>

void irq_handler(pt_regs_t regs) {
	/* Send an EOI (end of interrupt) signal to the PICs.
	   If this interrupt involved the slave. */
	if (regs.trapno >= 40) {
		/* Send reset signal to slave. */
		out8(PIC2_COMMAND, NON_SPEC_EOI);
		printk("big irq\n");
	}
	if ((32 + 2) == regs.trapno) {
		printk("irq = 2\n");
	}
	/* Send reset signal to master. (As well as slave, if necessary). */
	out8(PIC1_COMMAND, NON_SPEC_EOI);
#ifdef CONFIG_IRQ
	if (regs.trapno != (32 + 2)) {
		irq_dispatch(regs.trapno - 32);
	}
#endif
}

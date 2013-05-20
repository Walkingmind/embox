/**
 * @file
 * @brief
 *
 * @date 06.01.11
 * @author Anton Bondarev
 */

#include <assert.h>

#include <asm/io.h>
#include <asm/regs.h>
#include <asm/traps.h>
#include <asm/linkage.h>
#include <drivers/irqctrl.h>
#include <drivers/i8259.h>
#include <hal/reg.h>
#include <kernel/irq.h>
#include <profiler/tracing/trace.h>

#include <kernel/printk.h>

fastcall void irq_handler(pt_regs_t *regs) {
//	static int k;
//	int n;
	TRACE_BLOCK_DEF(irq_handler_tb);

//	if (regs->trapno - 0x20 != 0) {
//		n = k++;
//		printk("irq %d enter (%d)\n", regs->trapno - 0x20, n);
//	}

//	printk("INTERRUPT\n");

	trace_block_enter(&irq_handler_tb);

	assert(!critical_inside(CRITICAL_IRQ_LOCK));

	critical_enter(CRITICAL_IRQ_HANDLER);
	{
		int irq = regs->trapno - 0x20;

		ipl_enable();

		irq_dispatch(irq);

		i8259_send_eoi(irq);

		ipl_disable();
	}
	critical_leave(CRITICAL_IRQ_HANDLER);
	critical_dispatch_pending();

	trace_block_leave(&irq_handler_tb);

//	if (regs->trapno - 0x20 != 0) {
//		printk("irq %d leave (%d)\n", regs->trapno - 0x20, n);
//	}
}

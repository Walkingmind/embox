/**
 * @file
 * @brief TODO
 *
 * @date 13.07.11
 * @author Alexandr Kalmuk
 */

#ifndef KERNEL_IRQ_LOCK_H_
#define KERNEL_IRQ_LOCK_H_

#include <kernel/critical.h>
#include <hal/ipl.h>

/**
 * Locks hardware interrupt.
 *
 * When hardirq locked do not call softirq_dispatch, sched_dispatch.
 * This function will be called after hardirq_unlock().
 *
 * Each lock must be balanced with the corresponding unlock.
 */
static inline void irq_lock(void) {
	extern ipl_t __irq_lock_ipl;

	if (!critical_inside(CRITICAL_IRQ_LOCK)) {
		__irq_lock_ipl = ipl_save();
	}

	critical_enter(CRITICAL_IRQ_LOCK);
}

/**
 * Unlock hardirq and to came out from critical section.
 * Must be called on the previously locked irq only.
 *
 * @see irq_lock()
 */
static inline void irq_unlock(void) {
	extern ipl_t __irq_lock_ipl;

	critical_leave(CRITICAL_IRQ_LOCK);

	if (!critical_inside(CRITICAL_IRQ_LOCK)) {
		ipl_restore(__irq_lock_ipl);
		/* We know there is no level more critical than the IRQ lock. */
		critical_dispatch_pending();
	}
}

/**
 * Evaluate a given @a expr inside an IRQ-protected block.
 */
#define IRQ_LOCKED_DO(expr) \
	({                      \
		typeof(expr) __ret; \
		irq_lock();         \
		__ret = (expr);     \
		irq_unlock();       \
		__ret;              \
	})

#endif /* KERNEL_IRQ_LOCK_H_ */

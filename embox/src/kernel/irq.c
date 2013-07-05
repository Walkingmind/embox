/**
 * @file
 * @brief Kernel interrupt requests handling.
 *
 * @date 01.12.2008
 * @author Anton Bondarev
 *           - Initial contribution for SPARC
 *           - Extracting arch-independent code
 * @author Alexandr Batyukov, Alexey Fomin
 *           - Reviewing and rewriting some parts
 * @author Eldar Abusalimov
 *           - Rewriting from scratch:
 *               - Adapting for new HAL interface
 *               - Introducing locks and statistics accounting
 *               - Documentation
 *           - Using object allocator for internal structures
 */

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdbool.h>

#include <kernel/irq.h>
#include <kernel/irq_lock.h>
#include <kernel/irq_stack.h>
#include <kernel/critical.h>
#include <drivers/irqctrl.h>
#include <hal/ipl.h>
#include <mem/objalloc.h>
#include <profiler/tracing/trace.h>
#include <util/dlist.h>

struct irq_entry {
	irq_handler_t handler;
	void *dev_id;
	struct dlist_head action_link;
};

struct irq_action {
	struct irq_entry entry;
	struct dlist_head entry_list;
	int sharing_supported;
};

OBJALLOC_DEF(irq_actions, struct irq_action, IRQ_NRS_TOTAL);

static struct irq_action *irq_table[IRQ_NRS_TOTAL];

int irq_attach(unsigned int irq_nr, irq_handler_t handler, unsigned int flags,
		void *dev_id, const char *dev_name) {
	struct irq_action *action;
	int ret = ENOERR;

	if (!irq_nr_valid(irq_nr) || !handler) {
		return -EINVAL;
	}

	irq_lock();

	trace_point("irq attach");

	/* Check if irq exists and device support sharing
	 * and new device also support sharing */
	if (irq_table[irq_nr] && (! (irq_table[irq_nr]->sharing_supported
			&& (flags & IF_SHARESUP))) ) {
		/* IRQ sharing is not supported for this IRQ number */
		ret = -EBUSY;
		goto out_unlock;
	}

	/* Action allocation. */
	if (!(action = objalloc(&irq_actions))) {
		ret = -ENOMEM;
		goto out_unlock;
	}

	action->entry.handler = handler;
	action->sharing_supported = (flags & IF_SHARESUP) ? 1 : 0;
	action->entry.dev_id = dev_id;

	if (irq_table[irq_nr]) {
		/* Add new device to list */
		dlist_add_next(dlist_head_init(&(action->entry.action_link)),
				&(irq_table[irq_nr]->entry_list));
	} else {
		/* Initialize list if it is first device on this IRQ line */
		irq_table[irq_nr] = action;
		dlist_init(&action->entry_list);
		dlist_add_next(dlist_head_init(&(action->entry.action_link)),
				&(irq_table[irq_nr]->entry_list));
		irqctrl_enable(irq_nr);
	}

	out_unlock: irq_unlock();
	return ret;
}

int irq_detach(unsigned int irq_nr, void *dev_id) {
	struct irq_action *action;
	struct dlist_head *item, *next;
	int ret = ENOERR;

	if (!irq_nr_valid(irq_nr)) {
		return -EINVAL;
	}

	irq_lock();

	trace_point("irq detach");

	/* Go thru list to determine which IRQ/DEV pair should be detached */
	if (!(action = irq_table[irq_nr])) {
		ret = -ENOENT;
		goto out_unlock;
	}

	dlist_foreach(item, next, &(irq_table[irq_nr]->entry_list)) {
		action = dlist_entry(item, struct irq_action, entry.action_link);

		if (action->entry.dev_id == dev_id) {
			dlist_del(&(action->entry.action_link));

			if (dlist_empty(&(irq_table[irq_nr]->entry_list))) {
				objfree(&irq_actions, action);
				irq_table[irq_nr] = NULL;
				irqctrl_disable(irq_nr);
				break;
			} else {
				objfree(&irq_actions, action);
			}
		}
	}

	out_unlock: irq_unlock();
	return ret;
}

void irq_dispatch(unsigned int irq_nr) {
	struct irq_entry *entry;
	irq_handler_t handler = NULL;
	void *dev_id = NULL;
	ipl_t ipl;
	struct dlist_head *item, *next;
	TRACE_BLOCK_DEF(interrupt_tb);

	assert(irq_nr_valid(irq_nr));

	trace_point("interrupt");

	trace_block_enter(&interrupt_tb);

	assert(irq_stack_protection() == 0, 
			"Stack overflow detected on irq dispatch");

	if (irq_table[irq_nr]) {
		ipl = ipl_save();
		dlist_foreach(item, next, &(irq_table[irq_nr]->entry_list)) {

			{
				if ((entry =
						dlist_entry(item, struct irq_entry, action_link))) {
					handler = entry->handler;
					dev_id = entry->dev_id;
				}
			}
			assert(handler != NULL);
			ipl_restore(ipl);
			handler(irq_nr, dev_id);
			ipl = ipl_save();
		}
		ipl_restore(ipl);
	}

	trace_block_leave(&interrupt_tb);
}

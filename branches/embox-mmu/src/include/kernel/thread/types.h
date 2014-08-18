/**
 * @file
 *
 * @brief Describes thread descriptor structure
 *
 * @date 23.03.11
 * @author Alina Kramar
 */

#ifndef KERNEL_THREAD_TYPES_H_
#define KERNEL_THREAD_TYPES_H_

#include <hal/context.h>
#include <hal/cpu.h>

#include <kernel/spinlock.h>
#include <kernel/sched/sched_strategy.h>
#include <kernel/thread/signal.h>
#include <kernel/thread/thread_stack.h>
#include <kernel/thread/thread_local.h>
#include <kernel/thread/thread_cancel.h>
#include <kernel/schedee/schedee.h>
#include <kernel/thread/thread_wait.h>

#include <util/dlist.h>

/* Resource mgmt flags. */
#define TS_INIT         (0x0)
#define TS_LAUNCHED     (0x1 << 0)
#define TS_EXITED       (0x1 << 1)
#define TS_DETACHED     (0x1 << 2)

#ifdef SMP
# define TW_SMP_WAKING  (~0x0)  /**< In the middle of sched_wakeup. */
#else
# define TW_SMP_WAKING  (0x0)   /* Not used in non-SMP kernel. */
#endif


typedef int __thread_id_t;

struct task;

/**
 * Thread control block.
 *
 * Locking:
 *   t->lock    - used during waking up
 *   t->active  - (SMP) only current is allowed to modify it,
 *                reads are usually paired with t->waiting
 *   t->ready   - any access must be protected with rq lock and interrupts off,
 *                only current can reset it to zero (during 'schedule'),
 *                others can set it to a non-zero during wake up
 *   t->waiting - current can change it from zero to a non-zero with no locks,
 *                others access it with t->lock held and interrupts off
 */
struct thread {
	/* schedee member HAVE TO be first. Please, do NOT move!*/
	struct schedee    schedee;     /**< Schedee interface for scheduler */
	
	unsigned int       critical_count;
	unsigned int       siglock;

	unsigned int       state;        /**< Thread-specific state. */

	struct context     context;      /**< Architecture-dependent CPU state. */

	union {
		void          *run_ret;      /**< Return value of the routine. */
		void          *joining;      /**< A joining thread (if any). */
	} /* unnamed */;

	thread_stack_t     stack;        /**< Handler for work with thread stack */

	__thread_id_t      id;           /**< Unique identifier. */

	struct task       *task;         /**< Task belong to. */
	struct dlist_head  thread_link;  /**< list's link holding task threads. */

	struct sigstate    sigstate;     /**< Pending signal(s). */

	thread_local_t     local;
	thread_cancel_t    cleanups;

	struct thread_wait thread_wait;
};

#endif /* KERNEL_THREAD_TYPES_H_ */

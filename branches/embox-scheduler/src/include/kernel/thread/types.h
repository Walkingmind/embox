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

#include <stddef.h> /* only for stack size */

#include <hal/context.h>

#include <kernel/thread/state.h>
#include <kernel/sched/sched_strategy.h>
#include <util/dlist.h>
#include <kernel/thread/wait_data.h>

typedef int __thread_id_t;

struct task;

struct thread {
	thread_state_t   state;           /**< Current state. */

	struct context     context;       /**< Architecture-dependent CPU state. */

	void            *(*run)(void *);  /**< Start routine. */
	union {
		void          *run_arg;       /**< Argument to pass to start routine. */
		void          *run_ret;       /**< Return value of the routine. */
		void          *join_ret;      /**< Exit value of a join target. */
	} /* unnamed */;
	/* TODO extract work with stack to separate module */
	void              *stack;         /**< Allocated thread stack buffer. */
	size_t             stack_sz;      /**< Stack size. */

	__thread_id_t      id;            /**< Unique identifier. */

	struct task       *task;          /**< Task belong to. */
	struct dlist_head  thread_link;   /**< list's link holding task threads. */

	struct thread     *joined;        /**< Thread which joined to this. */

	struct wait_data   wait_data;     /**< Hold data for waiting mode */

	/* TODO may be named 'struct sched_attributes' */
	struct sched_strategy_data sched_priv; /**< Scheduler-private data. */
};

#endif /* KERNEL_THREAD_TYPES_H_ */

/**
 * @file
 * @brief TODO documentation for types.h -- Alina
 *
 * @date 23.03.11
 * @author Alina Kramar
 */

#ifndef KERNEL_THREAD_TYPES_H_
#define KERNEL_THREAD_TYPES_H_

typedef int __thread_id_t;
typedef short __thread_priority_t;
typedef unsigned int __thread_state_t;

#include <hal/context.h>
#include <kernel/thread/startq.h>
#include <kernel/thread/sched_strategy.h>
#include <util/slist.h>
#include <util/list.h>
#include <linux/list.h>
#include <stddef.h>
#include <sys/types.h>

struct context;

struct runq;
struct sleepq;
struct event;
//struct list_head;

struct thread {

	__thread_state_t  state;         /**< Current state. */

	struct context    context;       /**< Architecture-dependent CPU state. */

	void           *(*run)(void *);  /**< Start routine. */
	union {
		void         *run_arg;       /**< Argument to pass to start routine. */
		void         *run_ret;       /**< Return value of the routine. */
		void         *join_ret;      /**< Exit value of a join target. */
	} /* unnamed */;
	void             *stack;         /**< Allocated thread stack buffer. */
	size_t            stack_sz;      /**< Stack size. TODO unused. -- Eldar */

	struct sched_strategy_data sched;/**< Scheduler-private data. */

	__thread_priority_t initial_priority; /**< Scheduling priority. */
	__thread_priority_t priority;    /**< Current scheduling priority. */

	struct startq_data startq_data;   /**< Resuming the thread from critical. */

	union {
		struct runq      *runq;      /**< For running/ready state. */
		struct sleepq    *sleepq;    /**< For sleeping state. */
	} /* unnamed */;

	struct mutex     *mutex_waiting; /**< Mutex we are waiting for (if any). */

	__thread_id_t     id;            /**< Unique identifier. */
	struct list_head  thread_link;   /**< Linkage on all threads. */

	struct sleepq     exit_sleepq;   /**< Thread exit event. */

	int               sleep_res;     /**< Result shed_sleep */

	struct task      *task;          /**< Task belong to. */
	struct list_head  task_link;     /**< Link in list holding task threads. */

	clock_t           running_time;  /**< Running time of thread in clocks. */
};

#endif /* KERNEL_THREAD_TYPES_H_ */

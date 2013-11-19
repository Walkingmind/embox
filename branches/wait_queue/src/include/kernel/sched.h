/**
 * @file
 * @brief TODO -- Alina.
 *
 * @date 22.04.10
 * @author Dmitry Avdyukhin
 * @author Kirill Skorodumov
 * @author Alina Kramar
 */

#ifndef KERNEL_SCHED_H_
#define KERNEL_SCHED_H_

#include <sys/types.h>

#include <kernel/sched/sched_lock.h>
#include <kernel/sched/sched_priority.h>


#define SCHED_TIMEOUT_INFINITE     (unsigned long)(-1)

struct thread;
struct event;
struct runq;

/**
 * Initializes scheduler.
 *
 * @param current
 *   Thread structure corresponding to the current control flow.
 * @param idle
 *   Thread that should be executed in the last resort.
 * @return
 *   Operation result.
 * @retval 0
 *   If initialization succeeds.
 * @retval non-zero
 *   Error code if initialization of the underlying policy implementation has
 *   failed.
 */
extern int sched_init(struct thread *current, struct thread *idle);

extern void sched_ticker_init(void);
extern void sched_ticker_fini(void);
extern void sched_ticker_switch(struct thread *prev, struct thread *next);

/**
 * Makes active or waking thread and adds thread to the queue of ready to
 * executing threads.
 *
 * @param thread
 *   Thread which will be added.
 */
extern void sched_wake(struct thread *t);

/**
 * Makes exit thread and removes thread from scheduler.
 */
extern void sched_finish(struct thread *thread);

/**
 * Changes scheduling priority of the thread. If the thread is running now
 * (present in the runq) calls runq_change_priority() for rescheduling runq
 * and thread_set_priority() else just calls thread_set_priority() for setup
 * a new value for priority field in sched_strategy_data structure
 *
 * @param t
 *   Thread to operate with.
 * @param priority
 *   New scheduling priority of the the thread.
 */
extern int sched_change_priority(struct thread *t, sched_priority_t priority);


/**
 * Requests switching of the current thread.
 */
extern void sched_post_switch(void);

/**
 * @brief Makes thread to run regardless of it's state if thread is scheduling
 *
 * @param thread Thread to operate with
 *
 * @return
 *   Operation result
 * @retval 0
 *   On success.
 * @retval non-zero
 *   On operation fail.
 */
extern void sched_signal(struct thread *thread);


#endif /* KERNEL_SCHED_H_ */

/**
 * @file
 * @brief TODO -- Alina.
 *
 * @date 22.04.10
 * @author Dmitry Avdyukhin
 * @author Kirill Skorodumov
 * @author Alina Kramar
 */

#ifndef KERNEL_THREAD_SCHED_H_
#define KERNEL_THREAD_SCHED_H_

#include <kernel/thread/sched_lock.h>
#include <kernel/thread/sched_priority.h>

#include __impl_x(kernel/thread/sched_impl.h)
#include __impl_x(kernel/thread/types.h)

struct thread;

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

extern struct thread *sched_current(void);

#if 0
/**
 * Starts scheduling of the given @a thread.
 *
 * @param thread
 *   The thread to be added into the scheduler.
 */
extern void sched_start(struct thread *thread);

/**
 * Removes a @a thread from the scheduler.
 *
 * @param thread
 *   The thread being stopped.
 */
extern void sched_stop(struct thread *thread);
#endif

extern void sched_set_priority(struct thread *thread,
		__thread_priority_t new_priority);

extern int sched_change_scheduling_priority(struct thread *t,
		__thread_priority_t new);

/**
 * Makes the current thread sleep until the specified @a event occurs.
 * Execution is suspended until #sched_wake() or #sched_wake_one() is called on
 * the @a event.
 *
 * <b>Must not</b> be called with the scheduler @link #sched_lock()
 * locked @endlink or within any other critical context.
 *
 * @param event
 *   The event to sleep on.
 * @return
 *   Operation result.
 * @retval 0
 *   Always. TODO sleep cancellation is not implemented.
 */
extern int sched_sleep(struct event *event);

/**
 * Does the same as #sched_sleep() but assumes that the scheduler is
 * @link #sched_lock() locked @endlink once. However it still must not be
 * called inside any other critical section or with the scheduler locked more
 * than once.
 *
 * @param event
 *   The event to sleep on.
 * @return
 *   Operation result.
 * @retval 0
 *   Always. TODO sleep cancellation is not implemented.
 */
extern int sched_sleep_locked(struct event *event);

/**
 * Wakes up all threads that sleep on the given @a event.
 *
 * @param event
 *   The occurred event.
 */
extern void sched_wake(struct event *event);

/**
 * Wakes up one of the threads sleeping on the given @a event.
 *
 * @param event
 *   The occurred event.
 */
extern void sched_wake_one(struct event *event);

/**
 * Moves the current thread to the end of the queue for its priority.
 */
extern void sched_yield(void);

extern void sched_suspend(struct thread *thread);

extern void sched_resume(struct thread *thread);

#endif /* KERNEL_THREAD_SCHED_H_ */


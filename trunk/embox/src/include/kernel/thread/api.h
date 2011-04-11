/**
 * @file
 * @brief Defines structure of threads and methods,
 * which allows working with them.
 *
 * @date 22.04.2010
 * @author Dmitry Avdyukhin
 *         - Initial implementation
 * @author Alina Kramar
 *         - Extracting internal implementation to separate header
 *         - Thread iteration code
 */

#ifndef KERNEL_THREAD_API_H_
#define KERNEL_THREAD_API_H_

#include __impl_x(kernel/thread/api_impl.h)

/**
 * Thread control block.
 */
struct thread;

/**
 * Every thread can be identified using a number which is unique across the
 * system.
 */
typedef __thread_id_t thread_id_t;

typedef __thread_priority_t thread_priority_t;

/** The lowest priority is set to 255. */
#define THREAD_PRIORITY_MIN 255

/** The highest priority is zero. */
#define THREAD_PRIORITY_MAX 0

/** Total amount of valid priorities. */
#define THREAD_PRIORITY_TOTAL \
	(THREAD_PRIORITY_MIN - THREAD_PRIORITY_MAX + 1)

/** User-space thread. */
#define THREAD_FLAG_USER      (0x1 << 0)
/** Thread is created in detached state. */
#define THREAD_FLAG_DETACHED  (0x1 << 1)
/** Thread is created suspended. */
#define THREAD_FLAG_SUSPENDED (0x1 << 2)

/**
 * Iterates over the list of all threads existing in the system.
 *
 * @param thread
 *   <em> struct thread * </em> iteration variable.
 */
#define thread_foreach(thread) \
	  __thread_foreach(thread)

/**
 * Searches for a thread by the given ID.
 *
 * @param id
 *   The thread ID to look up by.
 * @return
 *   Found thread if such exists.
 * @retval NULL
 *   If there is no thread with such ID.
 */
extern struct thread *thread_lookup(thread_id_t id);

/**
 * Obtains a pointer to the calling thread.
 *
 * @return
 *   The currently executing thread.
 */
extern struct thread *thread_self(void);

/**
 * Creates a new thread.
 *
 * The new thread starts execution by invoking @a run with @a arg as its sole
 * argument.
 *
 * A memory for the thread control block and its stack is dynamically allocated
 * from an internal object pool. As far as an order of threads execution is
 * generally undefined, resource reclamation becomes a bit complicated.
 *
 * Thread becomes terminated either when it returns from its @a run function or
 * after explicit call to #thread_exit(). In order to give other threads a
 * chance to safely synchronize with the given thread or to inspect its return
 * value, the memory can't be freed immediately after the thread terminates.
 * Thus resources used by the thread may remain occupied even if it terminates.
 *
 * Kernel tracks an internal state of a thread called detach state which is
 * either @c joinable or @c detached. Resources of a terminated thread are
 * released when one of the following conditions becomes satisfied:
 *
 *   - The thread is in the joinable state and another thread has called
 *     #thread_join() on it.
 *
 *   - The thread has been detached using #thread_detach() method or it was
 *     initially created in the detached state using #THREAD_FLAG_DETACHED
 *     flag.
 *
 * To avoid possible race conditions and memory leaks TODO
 *
 * @param p_thread
 * @param flags
 *   Depending on the given @a flags the behavior may differ as follows:
 *     @n
 *   - If no flags are specified (@a 0 is passed as the value of @a flags
 *     argument), then the new thread is created in a joinable state (see
 *     below) and starts immediately.
 *     @n
 *   - The #THREAD_FLAG_SUSPENDED flag suspends the execution of the thread
 *     being created instead of starting it immediately.
 *     The effect is alike as if #thread_suspend() has been called on the
 *     thread before actually transferring the control to it. In order to start
 *     the thread, #thread_resume() should be called on it.
 *     Using this flag allows the caller to perform some additional actions
 *     on the newly created thread safely without a risk of being preempted by
 *     it. Adjusting its priority is an obvious example.
 *     @n
 *   - Presence of the #THREAD_FLAG_DETACHED flag causes the thread to be
 *     created in a detached state.
 *
 * @param run
 * @param arg
 * @return
 */
extern int thread_create(struct thread **p_thread, unsigned int flags,
		void *(*run)(void *), void *arg);

/**
 * Performs basic thread initialization.
 *
 * @param thread
 *   The thread being initialized.
 * @param run
 *   The thread start routine.
 * @param stack_address
 *   address of thread's stack.
 * @return
 *   The first argument if the initialization has succeeded.
 * @return NULL
 *   If something went wrong (e.g. invalid arguments).
 */
extern struct thread *thread_init(struct thread *thread, void *(*run)(void *),
		void *stack_address, size_t stack_size);

extern int thread_detach(struct thread *thread);

/**
 * Starts a thread.
 */
extern void thread_start(struct thread *thread);

/**
 * Stops chosen thread.
 * Deletes previous zombie.
 * Makes it a zombie.
 */
extern int thread_stop(struct thread *stopped_thread);
#if 0
extern void __attribute__((noreturn)) thread_exit(void *ret);
#endif

/**
 * Changes thread's priority.
 */
extern void thread_change_priority(struct thread *thread, int new_priority);

/**
 * Switches context to another thread.
 * Currently working thread leaves CPU for some time.
 */
extern void thread_yield(void);

extern int thread_join(struct thread *thread, void **p_ret);

extern int thread_suspend(struct thread *thread);
extern int thread_resume(struct thread *thread);

extern struct thread *thread_alloc(void);

extern void thread_free(struct thread *thread);

#endif /* KERNEL_THREAD_API_H_ */

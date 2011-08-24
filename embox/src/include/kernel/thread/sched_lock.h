/**
 * XXX docs. -- Eldar
 *  @brief Implements sched locks interface.
 *  @details This header in use also if mod 'sched' is not enable.
 *  @date 13.07.11
 *  @author Alexandr Kalmuk
 */

#ifndef KERNEL_THREAD_SCHED_LOCK_H_
#define KERNEL_THREAD_SCHED_LOCK_H_

#include <kernel/critical/api.h>

/**
 * Locks the scheduler which means disabling thread switch until
 * #sched_unlock() is called. Each lock must be balanced with the corresponding
 * unlock.
 *
 * @see sched_unlock()
 */
static inline void sched_lock(void) {
	critical_enter(CRITICAL_SCHED_LOCK);
}

/**
 * Unlocks the scheduler after #sched_lock(). Must be called on the
 * previously locked scheduler only. Outermost unlock (which corresponds to
 * the first lock call) also dispatches pending thread switches (if any).
 *
 * @see sched_lock()
 */
static inline void sched_unlock(void) {
	critical_leave(CRITICAL_SCHED_LOCK);
	critical_check_dispatch(CRITICAL_SCHED_LOCK);
}

/**
 * Does the same as #sched_unlock() except that the outermost call does not
 * perform a check for pending switches.
 *
 * @note This function is not intended for wide usage.
 */
static inline void sched_unlock_noswitch(void) {
	critical_leave(CRITICAL_SCHED_LOCK);
}

#endif /* KERNEL_THREAD_SCHED_LOCK_H_ */

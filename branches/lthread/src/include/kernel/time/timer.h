/**
 * @file
 *
 * @brief Interface of periodical timers with milliseconds precision.
 *
 * @details
 *   for set timer use `timer_init' or `timer_set' functions.
 *   for emulate non-periodical behavior use timer_close function in the end of handler.
 *
 * @date 20.07.10
 * @author Fedor Burdun
 * @author Ilia Vaprol
 */

#ifndef KERNEL_TIMER_H_
#define KERNEL_TIMER_H_

#include <stdint.h>
#include <stdbool.h>

#include <kernel/time/timer_strat.h>
#include <defines/clock_t.h>

struct sys_timer;

/**
 * Type of timer's handler. Function that will be called by timers every n-th
 * milliseconds.
 */
typedef void (*sys_timer_handler_t)(struct sys_timer *timer, void *param);

#define TIMER_PERIODIC      0x1
#define TIMER_ONESHOT       0x0
#define TIMER_REALTIME      0x80000000

#define TIMER_STATE_PREALLOC 0x1
#define TIMER_STATE_STARTED  0x2

/**
 * system timer structure
 */
struct sys_timer {
	sys_timer_queue_t lnk;

	uint32_t   load;
	uint32_t   cnt;
	sys_timer_handler_t handle;
	void       *param;
	unsigned int flags;
	uint32_t   state; /**< do we use timer_set or timer_init? */
};

static inline bool timer_is_preallocated(struct sys_timer *tmr) {
	return tmr->state & TIMER_STATE_PREALLOC;
}
static inline void timer_set_preallocated(struct sys_timer *tmr) {
	tmr->state |= TIMER_STATE_PREALLOC;
}

static inline bool timer_is_started(struct sys_timer *tmr) {
	return tmr->state & TIMER_STATE_STARTED;
}

static inline void timer_set_started(struct sys_timer *tmr) {
	tmr->state |= TIMER_STATE_STARTED;
}

static inline void timer_set_stopped(struct sys_timer *tmr) {
	tmr->state &= ~TIMER_STATE_STARTED;
}

static inline bool timer_is_periodic(struct sys_timer *tmr) {
	return tmr->flags & TIMER_PERIODIC;
}

/** Type declaration for system timer structure */
typedef struct sys_timer sys_timer_t;

/**
 * Set 'handle' timer for executing every 'ticks' ms.
 * Memory for set_tmr instance should be allocated before run timer_init.
 *
 * @param ptimer is pointer to preallocated buffer for system timer pointer.
 * @param ticks assignable time (quantity of milliseconds)
 * @param handler the function to be executed
 *
 * @return whether the timer is set
 * @retval 0 if the timer is set
 * @retval non-0 if the timer isn't set
 */
extern int timer_init_msec(struct sys_timer *tmr, unsigned int flags, uint32_t ticks,
		sys_timer_handler_t handle, void *param);

extern int timer_init(struct sys_timer *tmr, unsigned int flags, clock_t jiffies,
		sys_timer_handler_t handler, void *param);

/**
 * Set 'handle' timer for executing every 'ticks' ms.
 * Memory for set_tmr instance will be allocated inside timer_set.
 *
 * @param ptimer is pointer to buffer of sys_timer_t *.
 *
 * @param ticks assignable time (quantity of milliseconds)
 * @param handler the function to be executed
 *
 * @return whether the timer is set
 * @retval 0 if the timer is set
 * @retval non-0 if the timer isn't set
 */
extern int timer_set(struct sys_timer **ptimer, unsigned int flags, uint32_t ticks,
		sys_timer_handler_t handle, void *param);

/**
 * Shut down timer with system_tmr_t identity
 *
 * @param id timer identifier
 */
extern int timer_close(struct sys_timer *ptimer);

#endif /* KERNEL_TIMER_H_ */

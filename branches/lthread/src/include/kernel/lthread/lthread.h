/**
 * @file
 * @brief Describes lightweight thread structure
 *
 * @date 10.12.2013
 * @author Andrey Kokorev
 */

#ifndef _KERNEL_LTHREAD_H_
#define _KERNEL_LTHREAD_H_


#include <module/embox/kernel/lthread/lthread_api.h>

#include <kernel/schedee/schedee.h>
#include <kernel/schedee/current.h>

struct lthread {
	struct schedee schedee;
};

#define lthread_self() mcast_out(schedee_get_current(), struct lthread, schedee)

/**
 * Called by sched in __schedule to start routine.
 *
 * @param s
 *   schedee in struct lthread
 */
extern void lthread_trampoline(struct schedee *s);

/**
 * Creates a new light thread.
 * @param run
 *   The light thread start routine.
 * @param arg
 *   A value to pass to the start routine as the argument.
 * @return
 *   Light thread created.
 */
extern struct lthread * lthread_create(void *(*run)(void *), void *arg);

/**
 * Deletes light thread from pool
 * @param lt
 *   The light thread to delete
 */
extern void lthread_delete(struct lthread *lt);

/**
 * Adds a light thread in runq
 * @param lt
 *   The light thread to launch
 */
extern void lthread_launch(struct lthread *lt);


#endif /* _KERNEL_LTHREAD_H_ */

/**
 * @file
 * @brief
 *
 * @date 7.08.2014
 * @author Vita Loginova
 */

#ifndef KERNEL_SCHEDEE_SYNC_MUTEX_H_
#define KERNEL_SCHEDEE_SYNC_MUTEX_H_

#include <kernel/schedee/sync/mutexattr.h>
#include <kernel/sched/waitq.h>

struct thread;

/**
 * Defines Mutex structure.
 */
struct mutex {
	struct waitq wq;
	struct schedee *holder;
	struct mutexattr attr;

	int lock_count;
};

extern void mutex_init_schedee(struct mutex *m);
extern int mutex_unlock_schedee(struct mutex *locked_mutex);
extern int mutex_trylock_schedee(struct mutex *free_mutex);

extern void priority_inherit(struct schedee *t, struct mutex *m);
extern void priority_uninherit(struct schedee *t);


#endif /* KERNEL_SCHEDEE_SYNC_MUTEX_H_ */

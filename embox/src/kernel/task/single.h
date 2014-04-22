/**
 * @file
 * @brief
 *
 * @date 04.03.14
 * @author Ilia Vaprol
 */

#ifndef KERNEL_TASK_SINGLE_H_
#define KERNEL_TASK_SINGLE_H_

#include <assert.h>
#include <errno.h>
#include <time.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

#include <kernel/task/kernel_task.h>
#include <kernel/task/resource.h>
#include <kernel/task/task_priority.h>
#include <kernel/thread.h>

struct task {
	struct thread *tsk_main;
	char resources[];
};
__BEGIN_DECLS

static inline int task_get_id(const struct task *tsk) {
	assert(tsk == task_kernel_task());
	return 0;
}

static inline const char * task_get_name(const struct task *tsk) {
	assert(tsk == task_kernel_task());
	return "kernel";
}

static inline struct thread * task_get_main(const struct task *tsk) {
	assert(tsk == task_kernel_task());
	return tsk->tsk_main;
}

static inline void task_set_main(struct task *tsk,
		struct thread *main_thread) {
	assert(tsk == task_kernel_task());
	assert(main_thread != NULL);
	tsk->tsk_main = main_thread;
	main_thread->task = tsk;
}

static inline task_priority_t task_get_priority(const struct task *tsk) {
	assert(tsk == task_kernel_task());
	return TASK_PRIORITY_DEFAULT;
}

static inline int task_set_priority(struct task *tsk,
		task_priority_t new_priority) {
	assert(tsk == task_kernel_task());
	return -ENOSYS;
}

static inline clock_t task_get_clock(const struct task *tsk) {
	assert(tsk == task_kernel_task());
	return clock();
}

static inline void task_set_clock(struct task *tsk, clock_t new_clock) {
	assert(tsk == task_kernel_task());
}

static inline struct task * task_self(void) {
	/* Since there is only one task, actually it means --
	 * that task is kernel's.
	 */
	return task_kernel_task();
}

static inline int new_task(const char *name, void *(*run)(void *), void *arg) {
	return -EPERM;
}

static inline void task_init(struct task *tsk, int id, struct task *parent, 
		const char *name, struct thread *main_thread, 
		task_priority_t priority) {
	assert(tsk == task_kernel_task());
	assert(id == task_get_id(tsk));
	assert(0 == strcmp(name, task_get_name(tsk)));
	assert(main_thread == task_get_main(tsk));
	assert(TASK_PRIORITY_DEFAULT == task_get_priority(tsk));

	if (main_thread != NULL) { /* check for thread.NoThreads module */
		main_thread->task = tsk;
	}

	task_resource_init(tsk);
}

static inline void __attribute__((noreturn)) task_exit(void *res) {
	while (1) {
	}
}

static inline int task_notify_switch(struct thread *prev, struct thread *next) {
	return 0;
}

__END_DECLS

#endif /* KERNEL_TASK_SINGLE_H_ */

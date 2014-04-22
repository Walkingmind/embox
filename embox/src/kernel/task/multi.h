/**
 * @file
 * @brief
 *
 * @date 04.03.14
 * @author Ilia Vaprol
 */

#ifndef KERNEL_TASK_MULTI_H_
#define KERNEL_TASK_MULTI_H_

#include <assert.h>

#include <sys/cdefs.h>
#include <sys/types.h>

#include <kernel/thread.h>
#include <kernel/task/task_priority.h>

#define MAX_TASK_NAME_LEN 20

struct thread;

struct task {
	int tsk_id;
	struct task *parent;
	char tsk_name[MAX_TASK_NAME_LEN];
	struct thread *tsk_main;
	task_priority_t tsk_priority;
	clock_t tsk_clock;
	char resources[];
};

__BEGIN_DECLS

static inline int task_get_id(const struct task *tsk) {
	assert(tsk != NULL);
	return tsk->tsk_id;
}

static inline const char * task_get_name(const struct task *tsk) {
	assert(tsk != NULL);
	return tsk->tsk_name;
}

static inline struct thread * task_get_main(const struct task *tsk) {
	assert(tsk != NULL);
	return tsk->tsk_main;
}

static inline void task_set_main(struct task *tsk,
		struct thread *main_thread) {
	assert(tsk != NULL);
	assert(main_thread != NULL);
	tsk->tsk_main = main_thread;
	main_thread->task = tsk;
}

static inline task_priority_t task_get_priority(const struct task *tsk) {
	assert(tsk != NULL);
	return tsk->tsk_priority;
}

static inline clock_t task_get_clock(const struct task *tsk) {
	assert(tsk != NULL);
	return tsk->tsk_clock;
}

static inline void task_set_clock(struct task *tsk, clock_t new_clock) {
	assert(tsk != NULL);
	tsk->tsk_clock = new_clock;
}

__END_DECLS

#endif /* KERNEL_TASK_MULTI_H_ */

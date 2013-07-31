/**
 * @file
 *
 * @date Jul 31, 2013
 * @author: Anton Bondarev
 */
#include <kernel/thread.h>
#include <kernel/task.h>
#include <hal/cpu.h>

/** Default thread affinity mask */
#define THREAD_AFFINITY_NONE         ((unsigned int)-1)

int sched_affinity_check(struct thread *t) {
	unsigned int mask = 1 << cpu_get_id();

	if ((t->sched_priv.affinity & mask)
			&& (task_get_affinity(t->task) & mask)) {
		return 1;
	}
	return 0;
}

void sched_affinity_init(struct thread *t) {
	t->sched_priv.affinity = THREAD_AFFINITY_NONE;
}

void sched_affinity_set(struct thread *t, int mask) {
	t->sched_priv.affinity = mask;
}

int sched_affinity_get(struct thread *t) {
	return t->sched_priv.affinity;
}

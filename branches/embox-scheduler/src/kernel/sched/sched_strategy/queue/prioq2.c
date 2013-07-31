/**
 * @file
 * @brief
 *
 * @date 06.03.2013
 * @author Anton Bulychev
 */

#include <util/dlist.h>
#include <util/prioq.h>

#include <kernel/thread.h>
#include <kernel/task.h>
#include <kernel/sched/sched_strategy.h>

#include <module/embox/arch/smp.h>
#include <kernel/cpu/cpu.h>

void sched_strategy_init(struct thread *t) {
	dlist_head_init(&t->sched_priv.runq_link);
	sched_affinity_init(t);
}

/* runq operations */

void runq_queue_init(runq_queue_t *queue) {
	int i;

	for (i = SCHED_PRIORITY_MIN; i <= SCHED_PRIORITY_MAX; i++) {
		dlist_init(&queue->list[i]);
	}
}

void runq_queue_insert(runq_queue_t *queue, struct thread *thread) {
	dlist_add_prev(&thread->sched_priv.runq_link,
			&queue->list[thread->thread_priority.sched_priority]);
}

void runq_queue_remove(runq_queue_t *queue, struct thread *thread) {
	dlist_del(&thread->sched_priv.runq_link);
}

struct thread *runq_queue_extract(runq_queue_t *queue) {
	struct thread *thread = NULL;
	int i;

	for (i = SCHED_PRIORITY_MAX; i >= SCHED_PRIORITY_MIN; i--) {
		struct thread *t, *nxt;
		dlist_foreach_entry(t, nxt, &queue->list[i], sched_priv.runq_link) {
			/* Checking the affinity */
			if (sched_affinity_check(t)) {
				thread = t;
				break;
			}
		}

		if (thread) {
			runq_queue_remove(queue, thread);
			break;
		}
	}

	return thread;
}

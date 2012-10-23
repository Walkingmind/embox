/**
 * @file
 * @brief Trivial scheduler based on lists.
 *
 * @date Oct 10, 2011
 * @author Avdyukhin Dmitry
 * @author Anton Bulychev
 */

#include <kernel/thread/api.h>
#include <kernel/thread/sched_strategy.h>
#include <kernel/thread/state.h>

static void move_thread_to_another_q(struct dlist_head *q, struct thread *thread);

inline void sched_strategy_init(struct sched_strategy_data *data) {
	dlist_head_init(&data->l_link);
}

void runq_init(struct runq *runq, struct thread *current, struct thread *idle) {
	assert(current && idle);
	dlist_init(&runq->rq);

	current->runq = runq;
	idle->runq = runq;

	current->state = thread_state_do_resume(current->state);
	runq->current = current;

	runq_resume(runq, idle);
}

inline struct thread *runq_current(struct runq *runq) {
	assert(runq);
	return runq->current;
}

int runq_resume(struct runq *runq, struct thread *thread) {
	assert(runq && thread);
	assert(thread_state_suspended(thread->state));

	thread->state = thread_state_do_resume(thread->state);
	thread->runq = runq;
	if (thread != runq->current) {
		dlist_add_prev(&thread->sched.l_link, &runq->rq);
	}

	return 0;
}

int runq_suspend(struct runq *runq, struct thread *thread) {
	assert(runq && thread);
	assert(thread_state_running(thread->state));

	thread->state = thread_state_do_suspend(thread->state);
	thread->runq = NULL;

	if (thread == runq->current) {
		return 1;
	}

	dlist_del(&thread->sched.l_link);
	return 0;
}

int sleepq_wake_resumed_thread(struct runq *runq, struct sleepq *sleepq, struct thread *thread) {
	assert(runq && sleepq && thread);
	assert(thread_state_sleeping(thread->state) && !thread_state_suspended(thread->state));

	dlist_del(&thread->sched.l_link);

	thread->state = thread_state_do_wake(thread->state);
	thread->runq = runq;

	if (thread != runq->current) {
		dlist_add_prev(&thread->sched.l_link, &runq->rq);
	}
	return 0;
}

void sleepq_wake_suspended_thread(struct sleepq *sleepq, struct thread *thread) {
	assert(sleepq && thread);
	assert(thread_state_sleeping(thread->state) && thread_state_suspended(thread->state));

	dlist_del(&thread->sched.l_link);

	thread->state = thread_state_do_wake(thread->state);
	thread->sleepq = NULL;
}

int sleepq_wake(struct runq *runq, struct sleepq *sleepq, int wake_all) {
	struct thread *thread;
	assert(runq && sleepq);

	if (sleepq_empty(sleepq)) {
		return 0;
	}

	if (!dlist_empty(&sleepq->rq)) {
		thread = dlist_entry(sleepq->rq.next, struct thread, sched.l_link);
		sleepq_wake_resumed_thread(runq, sleepq, thread);
	} else {
		assert(!dlist_empty(&sleepq->sq));
		thread = dlist_entry(sleepq->sq.next, struct thread, sched.l_link);
		sleepq_wake_suspended_thread(sleepq, thread);
	}

	if (wake_all) {
		while (!dlist_empty(&sleepq->rq)) {
			thread = dlist_entry(sleepq->rq.next, struct thread, sched.l_link);
			sleepq_wake_resumed_thread(runq, sleepq, thread);
		}
		while (!dlist_empty(&sleepq->sq)) {
			thread = dlist_entry(sleepq->sq.next, struct thread, sched.l_link);
			sleepq_wake_suspended_thread(sleepq, thread);
		}
	}

	return 0;
}

void runq_sleep(struct runq *runq, struct sleepq *sleepq) {
	struct thread *current;
	assert(runq && sleepq);

	current = runq->current;
	assert(current->runq == runq);

	dlist_add_prev(&current->sched.l_link, &sleepq->rq);

	current->sleepq = sleepq;
	current->state = thread_state_do_sleep(current->state);
}

int runq_change_priority(struct runq *runq, struct thread *thread, int new_priority) {
	assert(runq && thread);
	thread->priority = new_priority;
	return 0;
}

int runq_switch(struct runq *runq) {
	struct thread *prev, *next;
	assert(runq);

	prev = runq->current;
	if (thread_state_running(prev->state)) {
		dlist_add_prev(&prev->sched.l_link, &runq->rq);
	}

	assert(!dlist_empty(&runq->rq));

	next = dlist_entry(runq->rq.next, struct thread, sched.l_link);
	dlist_del(&next->sched.l_link);

	assert(next);
	assert(thread_state_running(next->state));

	runq->current = next;
	return prev != next;
}

inline void sleepq_init(struct sleepq *sleepq) {
	dlist_init(&sleepq->rq);
	dlist_init(&sleepq->sq);
}

int sleepq_empty(struct sleepq *sleepq) {
	assert(sleepq);
	return dlist_empty(&sleepq->rq) && dlist_empty(&sleepq->sq);
}

void sleepq_change_priority(struct sleepq *sleepq, struct thread *thread, int new_priority) {
	assert(sleepq && thread);
	thread->priority = new_priority;
}

static void move_thread_to_another_q(struct dlist_head *q, struct thread *thread) {
	struct dlist_head *link;
	assert(q && thread);

	link = &thread->sched.l_link;
	dlist_del(link);
	dlist_add_prev(link, q);
}

void sleepq_suspend(struct sleepq *sleepq, struct thread *thread) {
	assert(sleepq && thread);
	assert(!thread_state_suspended(thread->state));

	thread->state = thread_state_do_suspend(thread->state);
	move_thread_to_another_q(&sleepq->sq, thread);
}

void sleepq_resume(struct sleepq *sleepq, struct thread *thread) {
	assert(sleepq && thread);
	assert(thread_state_suspended(thread->state));

	thread->state = thread_state_do_resume(thread->state);
	move_thread_to_another_q(&sleepq->rq, thread);
}

struct thread *sleepq_get_thread(struct sleepq *sleepq) {
	struct dlist_head *q;
	assert(sleepq && !sleepq_empty(sleepq));

	q = dlist_empty(&sleepq->rq) ? &sleepq->sq : &sleepq->rq;
	return dlist_entry(q->next, struct thread, sched.l_link);
}

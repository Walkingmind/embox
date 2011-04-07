/**
 * @file
 * @brief TODO --Alina
 *
 * @date 22.04.2010
 * @author Dmitry Avdyukhin
 * @author Kirill Skorodumov
 * @author Alina Kramar
 */

#include <assert.h>
#include <errno.h>

#include <embox/unit.h>
#include <lib/list.h>
#include <kernel/critical/api.h>
#include <kernel/thread/api.h>
#include <kernel/thread/event.h>
#include <kernel/thread/sched.h>
#include <kernel/thread/sched_policy.h>
#include <kernel/timer.h>
#include <hal/context.h>
#include <hal/ipl.h>

#include "types.h"
#include "state.h"

/** Timer, which calls scheduler_tick. */
#define SCHED_TICK_TIMER_ID 17

/** Interval, what scheduler_tick is called in. */
#define SCHED_TICK_INTERVAL 100

int sched_init(struct thread* current, struct thread *idle) {
	sched_policy_init(current, idle);

	current->state = thread_state_transition(current->state,
			THREAD_STATE_ACTION_START);
	assert(current->state == THREAD_STATE_RUNNING);

	idle->state = thread_state_transition(idle->state,
			THREAD_STATE_ACTION_START);
	assert(idle->state == THREAD_STATE_RUNNING);

	return 0;
}

/**
 * Is regularly called to show that current thread to be changed.
 * @param id nothing significant
 */
static void sched_tick(uint32_t id) {
	sched_current()->reschedule = true;
}

/**
 * Switches thread to another thread and their contexts.
 */
static void sched_switch(void) {
	struct thread *current, *next;
	ipl_t ipl;

	current = sched_current();
	next = sched_policy_switch(current);

	if (next == current) {
		return;
	}

#ifdef CONFIG_PP_ENABLE
	if (next->pp != current->pp) {
		pp_store(current->pp);
		pp_restore(next->pp);
	}
#endif

	ipl = ipl_save();
	context_switch(&current->context, &next->context);
	ipl_restore(ipl);

}

void __sched_dispatch(void) {
	struct thread *current;

	assert(critical_allows(CRITICAL_PREEMPT));

	sched_lock();

	current = sched_current();

	while (current->reschedule) {
		current->reschedule = false;
		sched_switch();
	}

	sched_unlock();
}

void sched_add(struct thread *t) {
	struct thread *current;

	sched_lock();

	current = sched_current();
	assert(current);

	current->reschedule |= sched_policy_add(t);

	t->state = thread_state_transition(t->state, THREAD_STATE_ACTION_START);
	assert(t->state);

	sched_unlock();
}

void sched_remove(struct thread *t) {
	assert(t != NULL);

	sched_lock();

	sched_current()->reschedule |= sched_policy_remove(t);
	t->state = thread_state_transition(t->state, THREAD_STATE_ACTION_STOP);

	sched_unlock();
}

int sched_sleep(struct event *e) {
	struct thread *current;

	sched_lock();

	current = sched_current();
	current->state = thread_state_transition(current->state,
			THREAD_STATE_ACTION_SLEEP);
	list_add(&current->wait_list, &e->sleep_queue);
	current->reschedule |= sched_policy_remove(current);

	sched_unlock();

	return 0;
}

int sched_wake(struct event *e) {
	struct thread *t, *tmp;
	struct thread *current;

	sched_lock();

	current = sched_current();

	list_for_each_entry_safe(t, tmp, &e->sleep_queue, wait_list) {
		list_del_init(&t->wait_list);
		t->state = thread_state_transition(t->state, THREAD_STATE_ACTION_WAKE);
		current->reschedule |= sched_policy_add(t);
	}

	sched_unlock();

	return 0;
}

int sched_wake_one(struct event *e) {
	struct thread *t;

	sched_lock();

	t = list_entry(e->sleep_queue.next, struct thread, wait_list);
	list_del_init(&t->wait_list);
	sched_current()->reschedule |= sched_policy_add(t);
	t->state = thread_state_transition(t->state, THREAD_STATE_ACTION_WAKE);

	sched_unlock();

	return 0;
}

void sched_start(void) {
	set_timer(SCHED_TICK_TIMER_ID, SCHED_TICK_INTERVAL, sched_tick);
	sched_policy_start();

	sched_unlock();
}

void sched_stop(void) {
	sched_lock();

	close_timer(SCHED_TICK_TIMER_ID);
	sched_policy_stop();
}

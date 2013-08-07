/**
 * @file
 * @brief TODO --Alina
 *
 * @date 22.04.10
 * @author Dmitry Avdyukhin
 *          - Initial implementation
 * @author Kirill Skorodumov
 *          - Some insignificant contribution
 * @author Alina Kramar
 *          - Initial work on priority inheritance support
 * @author Eldar Abusalimov
 *          - Rewriting from scratch:
 *              - Interrupts safety, adaptation to Critical API
 *              - @c startq for deferred wake/resume processing
 */

#include <assert.h>
#include <errno.h>
#include <time.h>

#include <kernel/critical.h>
#include <kernel/irq_lock.h>
#include <kernel/sched.h>
#include <kernel/thread/current.h>
#include <kernel/sched/sched_strategy.h>
#include <kernel/thread/state.h>
#include <kernel/time/timer.h>
#include <kernel/task.h>
#include <kernel/task/signal.h>
#include <kernel/work.h>
#include <hal/context.h>
#include <hal/ipl.h>

#include <profiler/tracing/trace.h>


#include <util/member.h>

#include <embox/unit.h>



static void post_switch_if(int condition);

static void sched_switch(void);


CRITICAL_DISPATCHER_DEF(sched_critical, sched_switch, CRITICAL_SCHED_LOCK);

//TODO these variable for scheduler (may be create object scheduler?)
static struct runq rq;
static struct work_queue startq;
static int switch_posted;


static inline int in_harder_critical(void) {
	return critical_inside(__CRITICAL_HARDER(CRITICAL_SCHED_LOCK));
}

static inline int in_sched_locked(void) {
	return !critical_allows(CRITICAL_SCHED_LOCK);
}

int sched_init(struct thread *idle, struct thread *current) {
	assert(idle && current);

	work_queue_init(&startq);
	runq_init(&rq);

	runq_start(&rq, idle);

	sched_ticker_init();

	return 0;
}

void sched_start(struct thread *t) {
	assert(t);
	assert(!in_harder_critical());
	assert(!thread_state_active(t->state));

	sched_lock();
	{
		post_switch_if(runq_start(&rq, t));
	}
	sched_unlock();
}

void sched_finish(struct thread *t) {
	assert(!in_harder_critical());

	sched_lock();
	{
		assert(!thread_state_exited(t->state));

		if (thread_state_running(t->state)) {
			post_switch_if(runq_finish(&rq, t));
		} else {
			if (thread_state_sleeping(t->state)) {
				t->wait_data.on_notified(t, t->wait_data.data);
			}
			t->state = thread_state_do_exit(t->state);
		}

		assert(thread_state_exited(t->state));
	}
	sched_unlock();
}

static void do_wait_locked(void) {
	struct thread *current = thread_get_current();
	assert(in_sched_locked() && !in_harder_critical());
	assert(thread_state_running(current->state));

	runq_wait(&rq);

	assert(thread_state_sleeping(current->state));

	post_switch_if(1);
}


static int notify_work(struct work *work) {
	struct wait_data *wait_data = member_cast_out(work, struct wait_data, work);
	struct thread *thread = member_cast_out(wait_data, struct thread, wait_data);

	assert(in_sched_locked());

	post_switch_if(runq_wake_thread(&rq, thread));

	if (wait_data->on_notified) {
		wait_data->on_notified(thread, wait_data->data);
	}

	return 1;
}

void sched_thread_notify(struct thread *thread, int result) {
	irq_lock();
	{
		if (thread->wait_data.status == WAIT_DATA_STATUS_WAITING) {
			work_post(&thread->wait_data.work, &startq);

			thread->wait_data.status = WAIT_DATA_STATUS_NOTIFIED;
			thread->wait_data.result = result;

			critical_request_dispatch(&sched_critical);
		}
	}
	irq_unlock();
}

void sched_prepare_wait(notify_handler on_notified, void *data) {
	struct wait_data *wait_data = &thread_get_current()->wait_data;

	wait_data->data = data;
	wait_data->on_notified = on_notified;

	wait_data_prepare(wait_data, &notify_work);
}

void sched_cleanup_wait(void) {
	wait_data_cleanup(&thread_get_current()->wait_data);
}


static void timeout_handler(struct sys_timer *timer, void *sleep_data) {
	struct thread *thread = (struct thread *) sleep_data;
	sched_thread_notify(thread, -ETIMEDOUT);
}

int sched_wait_locked(unsigned long timeout) {
	int ret;
	struct sys_timer tmr;
	struct thread *current = thread_get_current();

	assert(in_sched_locked() && !in_harder_critical());
	assert(thread_state_running(current->state));
	assert(current->wait_data.status != WAIT_DATA_STATUS_NONE); /* Should be prepared */

	if (timeout != SCHED_TIMEOUT_INFINITE) {
		ret = timer_init(&tmr, TIMER_ONESHOT, (uint32_t)timeout, timeout_handler, current);
		if (ret != ENOERR) {
			return ret;
		}
	}

	work_enable(&current->wait_data.work);
	do_wait_locked();

	sched_unlock();

	/* At this point we have been awakened and are ready to go. */
	assert(!in_sched_locked());
	assert(thread_state_running(current->state));

	sched_lock();

	if (timeout != SCHED_TIMEOUT_INFINITE) {
		timer_close(&tmr);
	}

	return current->wait_data.result;
}

int sched_wait(unsigned long timeout) {
	int sleep_res;
	assert(!in_sched_locked());

	sched_lock();
	{
		sleep_res = sched_wait_locked(timeout);
	}
	sched_unlock();

	return sleep_res;
}

void sched_post_switch(void) {
	sched_lock();
	{
		post_switch_if(1);
	}
	sched_unlock();
}

int sched_change_priority(struct thread *t, sched_priority_t prior) {
	assert(t);
	assert((prior >= SCHED_PRIORITY_MIN) && (prior <= SCHED_PRIORITY_MAX));

	sched_lock();
	{
		assert(!thread_state_exited(t->state));

		thread_priority_set(t, prior);

		if (thread_state_running(t->state)) {
			post_switch_if(runq_change_priority(&rq, t, prior));
		}

		assert(thread_priority_get(t) == prior);
	}
	sched_unlock();

	return 0;
}


static void post_switch_if(int condition) {
	assert(in_sched_locked());

	if (condition) {
		switch_posted = 1;
		critical_request_dispatch(&sched_critical);
	}
}

/**
 * Called by critical dispatching code with IRQs disabled.
 */
static void sched_switch(void) {
	struct thread *prev, *next;
	clock_t new_clock;

	assert(!in_sched_locked());

	sched_lock();
	{
		work_queue_run(&startq);

		if (!switch_posted) {
			goto out;
		}
		switch_posted = 0;

		ipl_enable();

		prev = thread_get_current();

		if (prev == (next = runq_switch(&rq))) {
			ipl_disable();
			goto out;
		}

		/* Running time recalculation */
		new_clock = clock();
		sched_timing_stop(prev, new_clock);
		sched_timing_start(next, new_clock);

		assert(thread_state_running(next->state));

		trace_point("context switch");

		ipl_disable();

		thread_set_current(next);
		context_switch(&prev->context, &next->context);
	}

out:
	task_signal_hnd();
	sched_unlock_noswitch();
}

//TODO this function looking for a sleep thread for send a signal
int sched_tryrun(struct thread *thread) {
	int res = 0;

	sched_lock();
	{
		if (thread_state_sleeping(thread->state)) {
			sched_thread_notify(thread, -EINTR);
		} else if (!thread_state_running(thread->state)) {
			res = -1;
		}
	}
	sched_unlock();

	return res;
}

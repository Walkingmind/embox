/**
 * @file
 * @brief Implements condition variable methods.
 *
 * @date 03.09.2012
 * @author Anton Bulychev
 */

#include <assert.h>
#include <errno.h>
#include <kernel/thread/sync/cond.h>
#include <kernel/sched.h>

void cond_init(cond_t *c) {
	wait_queue_init(&c->wq);
}

void cond_destroy(cond_t *c) {

}

void cond_wait(cond_t *c, struct mutex *m) {
	assert(c && m);
	assert(critical_allows(CRITICAL_SCHED_LOCK));

	sched_lock();
	{
		mutex_unlock(m);
		wait_queue_wait_locked(&c->wq, SCHED_TIMEOUT_INFINITE);
	}
	sched_unlock();

	mutex_lock(m);
}

void cond_signal(cond_t *c) {
	assert(c);
	assert(!critical_inside(__CRITICAL_HARDER(CRITICAL_SCHED_LOCK)));

	wait_queue_notify(&c->wq);
}

void cond_broadcast(cond_t *c) {
	assert(c);
	assert(!critical_inside(__CRITICAL_HARDER(CRITICAL_SCHED_LOCK)));

	wait_queue_notify_all(&c->wq);
}
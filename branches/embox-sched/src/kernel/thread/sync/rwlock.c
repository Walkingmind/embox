/**
 * @file
 * @brief Implements read-write lock methods.
 *
 * @date 04.09.12
 * @author Anton Bulychev
 */

#include <assert.h>
#include <errno.h>
#include <kernel/thread/sync/rwlock.h>
#include <kernel/sched.h>

#define RWLOCK_STATUS_NONE    0
#define RWLOCK_STATUS_READING 1
#define RWLOCK_STATUS_WRITING 2

static void do_up(rwlock_t *r, int status);
static void do_down(rwlock_t *r);
static int tryenter_sched_lock(rwlock_t *s, int status);

void rwlock_init(rwlock_t *r) {
	waitq_init(&r->wq);
	r->status = RWLOCK_STATUS_NONE;
	r->count = 0;
}

void rwlock_read_up(rwlock_t *r) {
	assert(r);
	assert(critical_allows(CRITICAL_SCHED_LOCK));

	do_up(r, RWLOCK_STATUS_READING);
}

void rwlock_write_up(rwlock_t *r) {
	assert(r);
	assert(critical_allows(CRITICAL_SCHED_LOCK));

	do_up(r, RWLOCK_STATUS_WRITING);
}

static void do_up(rwlock_t *r, int status) {
	assert(r);
	assert(critical_allows(CRITICAL_SCHED_LOCK));

	sched_lock();
	{
		while (tryenter_sched_lock(r, status) != 0) {
			waitq_wait_locked(&r->wq, SCHED_TIMEOUT_INFINITE);
		}
	}
	sched_unlock();
}

static int tryenter_sched_lock(rwlock_t *r, int status) {
	assert(r);
	assert(critical_inside(CRITICAL_SCHED_LOCK));

	if (r->status == RWLOCK_STATUS_NONE) {
		r->status = status;
		r->count = 1;
		return 0;
	}

	if (r->status == status && status == RWLOCK_STATUS_READING) {
		r->count++;
		return 0;
	}

	return -EAGAIN;
}

void rwlock_read_down(rwlock_t *r) {
	assert(r);
	assert(!critical_inside(__CRITICAL_HARDER(CRITICAL_SCHED_LOCK)));

	do_down(r);
}

void rwlock_write_down(rwlock_t *r) {
	assert(r);
	assert(!critical_inside(__CRITICAL_HARDER(CRITICAL_SCHED_LOCK)));

	do_down(r);
}

static void do_down(rwlock_t *r) {
	assert(r);
	assert(!critical_inside(__CRITICAL_HARDER(CRITICAL_SCHED_LOCK)));

	sched_lock();
	{
		r->count--;
		if (r->count == 0) {
			r->status = RWLOCK_STATUS_NONE;
			waitq_notify_all(&r->wq);
		}
	}
	sched_unlock();
}

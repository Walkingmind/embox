/**
 * @file
 * @brief Implements semaphore methods.
 *
 * @date 02.09.12
 * @author Anton Bulychev
 */

#include <assert.h>
#include <errno.h>
#include <kernel/thread/sync/semaphore.h>
#include <kernel/sched.h>

static int tryenter_sched_lock(struct sem *s);

void semaphore_init(struct sem *s, int val) {
	waitq_init(&s->wq);
	s->value = 0;
	s->max_value = val;
}

void semaphore_enter(struct sem *s) {
	assert(s);
	assert(critical_allows(CRITICAL_SCHED_LOCK));

	WAITQ_WAIT(&s->wq, (tryenter_sched_lock(s) == 0));
}

int semaphore_timedwait(struct sem *restrict s, const struct timespec *restrict abs_timeout) {
	struct timespec current_time;
	int ret = 0;
	int diff;

	assert(s);
	assert(critical_allows(CRITICAL_SCHED_LOCK));

	if (tryenter_sched_lock(s) != 0) {

		while (1) {
			sched_wait_prepare(&s->wq, 0);

			if (tryenter_sched_lock(s) != 0) {
				ret = 0;
				break;
			}

			clock_gettime(CLOCK_REALTIME, &current_time);
			diff = abs_timeout->tv_nsec - current_time.tv_nsec;

			if (diff > 0)
				ret = sched_wait_timeout(diff);
			else
				ret = -ETIMEDOUT;

			if (ret == -ETIMEDOUT || ret == -EINTR)
				break;
		}

		if (tryenter_sched_lock(s) != 0)
			ret = 0;

		sched_wait_cleanup(&s->wq);
	}

	return ret;
}

static int tryenter_sched_lock(struct sem *s) {
	assert(s);
	assert(critical_inside(CRITICAL_SCHED_LOCK));

	if (s->value == s->max_value) {
		return -EAGAIN;
	}

	s->value++;
	return 0;
}

int semaphore_tryenter(struct sem *s) {
	int err;
	sched_lock();
	{
		err = tryenter_sched_lock(s);
	}
	sched_unlock();
	return err;
}

void semaphore_leave(struct sem *s) {
	assert(s);
	assert(!critical_inside(__CRITICAL_HARDER(CRITICAL_SCHED_LOCK)));

	sched_lock();
	{
		s->value--;
		waitq_wakeup_all(&s->wq);
	}
	sched_unlock();
}

int semaphore_getvalue(struct sem *restrict s, int *restrict sval) {
	*sval = s->value;

	return 0;
}

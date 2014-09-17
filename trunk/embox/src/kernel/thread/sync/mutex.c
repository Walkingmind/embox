/**
 * @file
 * @brief Implements mutex methods.
 *
 * @date 05.05.10
 * @author Nikolay Malkovsky, Kirill Skorodumov
 *          - Initial contribution
 * @author Alina Kramar
 *          - Priority inheritance
 * @author Eldar Abusalimov
 *          - Debugging and code cleanup
 */

#include <assert.h>
#include <errno.h>

#include <kernel/thread/sync/mutex.h>
#include <kernel/thread/waitq.h>

static inline int mutex_is_static_inited(struct mutex *m) {
	/* Static initializer can't really init list now, so if this condition's
	 * true initialization is not finished */
	return !(m->wq.list.next && m->wq.list.prev);
}

static inline void mutex_complete_static_init(struct mutex *m) {
	waitq_init(&m->wq);
}

void mutex_init_default(struct mutex *m, const struct mutexattr *attr) {
	waitq_init(&m->wq);
	m->lock_count = 0;
	m->holder = NULL;

	if (attr) {
		mutexattr_copy(attr, &m->attr);
	} else {
		mutexattr_init(&m->attr);
	}
}

void mutex_init(struct mutex *m) {
	mutex_init_default(m, NULL);
	mutexattr_settype(&m->attr, MUTEX_RECURSIVE | MUTEX_ERRORCHECK);
}

int mutex_lock(struct mutex *m) {
	struct schedee *current = schedee_get_current();
	int errcheck;
	int ret, wait_ret;

	assert(m);

	errcheck = (m->attr.type & MUTEX_ERRORCHECK);

	wait_ret = WAITQ_WAIT(&m->wq, ({
		int done;

		sched_lock();
		ret = mutex_trylock(m);
		done = (ret == 0) || (errcheck && ret == -EDEADLK);
		if (!done)
			priority_inherit(current, m);
		sched_unlock();
		done;
	}));

	if (wait_ret != 0) {
		ret = wait_ret;
	}

	return ret;
}

int mutex_trylock(struct mutex *m) {
	struct schedee *current = schedee_get_current();

	assert(m);
	assert(!critical_inside(__CRITICAL_HARDER(CRITICAL_SCHED_LOCK)));

	if (mutex_is_static_inited(m))
		mutex_complete_static_init(m);

	if (m->holder == current) {
		if (m->attr.type & MUTEX_ERRORCHECK) {
			/* Nested locks. */
			return -EDEADLK;
		}
		if (m->attr.type & MUTEX_RECURSIVE) {
			/* Nested locks. */
			m->lock_count++;
			return 0;
		}
	}

	return mutex_trylock_schedee(m);
}

int mutex_unlock(struct mutex *m) {
	struct schedee *current = schedee_get_current();

	assert(m);

	if ((!m->holder || m->holder != current) &&
			(m->attr.type & (MUTEX_ERRORCHECK | MUTEX_RECURSIVE))){
		return -EPERM;
	}

	assert(m->lock_count > 0);

	if (--m->lock_count != 0 && (m->attr.type & MUTEX_RECURSIVE)) {
		return 0;
	}

	mutex_unlock_schedee(m);

	return 0;
}

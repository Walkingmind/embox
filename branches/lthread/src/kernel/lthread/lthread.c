/**
 * @file
 * @brief
 *
 * @author  Andrey Kokorev
 * @author  Vita Loginova
 * @date    21.11.2013
 */

#include <assert.h>
#include <errno.h>
#include <err.h>
#include <kernel/sched.h>
#include <kernel/lthread/lthread.h>
#include <kernel/runnable/runnable.h>
#include <kernel/lthread/lthread_priority.h>
#include <mem/misc/pool.h>

/**
 * Memory have to be allocated only for lthread structure, while lthread uses
 * thread stack when executed
 */
#define LTHREAD_POOL_SIZE OPTION_GET(NUMBER, lthread_pool_size)

POOL_DEF(lthread_pool, struct lthread, LTHREAD_POOL_SIZE);

static void *lthread_prepare(struct runnable *prev, struct runnable *next,  struct runq *rq) {
	next->run(next->run_arg);
	ipl_restore(rq->ipl);
	return NULL;
}

static void lthread_init(struct lthread *lt, void *(*run)(void *), void *arg) {
	assert(lt);

	lt->runnable.run = run;
	lt->runnable.prepare = lthread_prepare;
	lt->runnable.run_arg = arg;

	runq_item_init(&lt->runnable.sched_attr.runq_link);
	sched_affinity_init(&lt->runnable);
	lthread_priority_init(lt, LTHREAD_PRIORITY_DEFAULT);
}

struct lthread *lthread_create(void *(*run)(void *), void *arg) {
	struct lthread *lt;

	if (!run) {
		return err_ptr(EINVAL);
	}

	if (!(lt = (struct lthread *) pool_alloc(&lthread_pool))) {
		return err_ptr(ENOMEM);
	}

	lthread_init(lt, run, arg);

	return lt;
}

void lthread_delete(struct lthread *lt) {
	assert(lt);
	pool_free(&lthread_pool, lt);
}

void lthread_launch(struct lthread *lt) {
	assert(lt);
	sched_wakeup_l(lt);
}

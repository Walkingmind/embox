/**
 * @file
 * @brief
 *
 * @date 06.05.2013
 * @author Anton Bulychev
 */

#include <assert.h>
#include <errno.h>

#include <kernel/irq.h>
#include <kernel/spinlock.h>
#include <kernel/sched.h>
#include <kernel/sched/waitq.h>
#include <kernel/thread.h>

#include <util/member.h>
#include <util/dlist.h>

#include <kernel/critical.h>
#include <kernel/time/timer.h>

void __waitq_add(struct waitq *wq, struct waitq_link *wql) {
	assert(wq && wql);

	dlist_head_init(&wql->link);
	dlist_add_prev(&wql->link, &wq->list);
}

void waitq_add(struct waitq *wq, struct waitq_link *wql) {
	ipl_t ipl;

	assert(wq && wql);

	ipl = spin_lock_ipl(&wq->lock);
	__waitq_add(wq, wql);
	spin_unlock_ipl(&wq->lock, ipl);
}

void __waitq_del(struct waitq *wq, struct waitq_link *wql) {
	assert(wq && wql);

	if (!dlist_empty(&wql->link))
		dlist_del(&wql->link);
}

void waitq_del(struct waitq *wq, struct waitq_link *wql) {
	ipl_t ipl;

	assert(wq && wql);

	ipl = spin_lock_ipl(&wq->lock);
	__waitq_del(wq, wql);
	spin_unlock_ipl(&wq->lock, ipl);
}

void waitq_wait_prepare(struct waitq *wq, struct waitq_link *wql) {
	waitq_add(wq, wql);
	sched_wait_prepare();
}

void waitq_wait_cleanup(struct waitq *wq, struct waitq_link *wql) {
	sched_wait_cleanup();
	waitq_del(wq, wql);
}

void __waitq_wakeup(struct waitq *wq, int nr, int result) {
	struct wait_link *wql, *next_wql;

	assert(wq);

	dlist_foreach_entry(wql, next_wql, &wait_queue->list, link) {
		if (!__sched_wakeup(wql->thread))
			continue;

		wql->result = result;
		if (!--nr)
			break;
	}
}

void waitq_wakeup(struct waitq *wq, int nr, int result) {
	ipl_t ipl;

	assert(wq);

	ipl = spin_lock_ipl(&wq->lock);
	__waitq_wakeup(wq, nr, result);
	spin_unlock_ipl(&wq->lock, ipl);
}

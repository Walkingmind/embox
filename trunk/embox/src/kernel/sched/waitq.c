/**
 * @file
 * @brief
 *
 * @date 06.05.2013
 * @author Anton Bulychev
 */

#include <assert.h>
#include <errno.h>

#include <kernel/sched/waitq.h>

#include <kernel/irq.h>
#include <kernel/spinlock.h>
#include <kernel/sched.h>
#include <kernel/thread.h>

#include <util/member.h>
#include <util/dlist.h>

#include <kernel/critical.h>
#include <kernel/time/timer.h>

#include <mem/sysmalloc.h>
#include "waitq_protect_link.h"

void __waitq_add(struct waitq *wq, struct waitq_link *wql) {
	assert(wq && wql);

	if (dlist_empty(&wql->link))
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
		dlist_del_init(&wql->link);
}

void waitq_del(struct waitq *wq, struct waitq_link *wql) {
	ipl_t ipl;

	assert(wq && wql);

	ipl = spin_lock_ipl(&wq->lock);
	__waitq_del(wq, wql);
	spin_unlock_ipl(&wq->lock, ipl);
}

void waitq_wait_prepare(struct waitq *wq, struct waitq_link *_wql) {
	struct waitq_link *wql;

	wql = waitq_link_create_protected(_wql);

	waitq_add(wq, wql);
	sched_wait_prepare();
}

void waitq_wait_cleanup(struct waitq *wq, struct waitq_link *_wql) {
	struct waitq_link *wql;

	sched_wait_cleanup();

	wql = waitq_link_find_protected(_wql);

	waitq_del(wq, wql);

	waitq_link_delete_protected(wql);
}

void __waitq_wakeup(struct waitq *wq, int nr) {
	struct waitq_link *wql;

	assert(wq);

	dlist_foreach_entry(wql, &wq->list, link) {
		assert(wql->thread);
		if (!sched_wakeup(wql->thread))
			continue;

		// TODO mark this wql as the one who has woken the thread up? -- Eldar

		if (!--nr)
			break;
	}
}

void waitq_wakeup(struct waitq *wq, int nr) {
	assert(wq);
	SPIN_IPL_PROTECTED_DO(&wq->lock, __waitq_wakeup(wq, nr));
}

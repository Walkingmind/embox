/**
 * @file
 * @brief
 *
 * @date 06.05.2013
 * @author Anton Bulychev
 */

#ifndef KERNEL_SCHED_WAITQ_H_
#define KERNEL_SCHED_WAITQ_H_

#include <assert.h>

#include <sys/cdefs.h>
#include <util/dlist.h>
#include <kernel/spinlock.h>
#include <kernel/sched/current.h>
#include <kernel/thread/signal_lock.h>

#include <kernel/time/time.h>

__BEGIN_DECLS

struct schedee;

struct waitq {
	struct dlist_head list;
	spinlock_t lock;
};

struct waitq_link {
	struct dlist_head link;
	struct schedee *schedee;
};

#define WAITQ_INIT(wq)  { \
	.list = DLIST_INIT(wq.list),  \
	.lock = SPIN_STATIC_UNLOCKED, \
}

static inline void waitq_init(struct waitq *wq) {
	dlist_init(&wq->list);
	wq->lock = SPIN_UNLOCKED;
}

static inline void waitq_link_init(struct waitq_link *wql) {
	wql->schedee = schedee_get_current();
	dlist_head_init(&wql->link);
}

extern void __waitq_add(struct waitq *, struct waitq_link *);
extern void waitq_add(struct waitq *, struct waitq_link *);

extern void __waitq_del(struct waitq *, struct waitq_link *);
extern void waitq_del(struct waitq *, struct waitq_link *);

extern void waitq_wait_prepare(struct waitq *, struct waitq_link *);
extern void waitq_wait_cleanup(struct waitq *, struct waitq_link *);

extern void __waitq_wakeup(struct waitq *, int nr);
extern void waitq_wakeup(struct waitq *, int nr);

static inline void waitq_wakeup_all(struct waitq *wq) {
	waitq_wakeup(wq, 0);
}

__END_DECLS

#endif /* KERNEL_SCHED_WAITQ_H_ */

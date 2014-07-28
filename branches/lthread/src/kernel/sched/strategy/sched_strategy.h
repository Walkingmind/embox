/**
 * @file
 * @brief
 *
 * @date 06.03.2013
 * @author Anton Bulychev
 */

#ifndef KERNEL_THREAD_SCHED_STRATEGY_H_
#define KERNEL_THREAD_SCHED_STRATEGY_H_

#include <kernel/spinlock.h>
#include <kernel/sched/affinity.h>
#include <kernel/sched/runq.h>
#include <kernel/sched/sched_timing.h>
#include <kernel/sched/sched_priority.h>
#include <kernel/runnable/runnable_priority.h>

struct runq {
	runq_t     queue;
	spinlock_t lock;
	ipl_t ipl;
};

struct sched_attr {
	runq_item_t runq_link;
	affinity_t affinity;
	sched_timing_t sched_time;
	runnable_priority_t thread_priority;
	int policy;
};

#endif /* KERNEL_THREAD_SCHED_STRATEGY_H_ */

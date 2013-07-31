/**
 * @file
 * @brief
 *
 * @date 06.03.2013
 * @author Anton Bulychev
 */

#ifndef KERNEL_THREAD_SCHED_STRATEGY_SIMPLE_QUEUE_H_
#define KERNEL_THREAD_SCHED_STRATEGY_SIMPLE_QUEUE_H_

#include <kernel/sched/affinity.h>
#include <kernel/sched/runq.h>
#include <kernel/sched/sched_timing.h>

struct runq {
	runq_queue_t queue;
};

struct sched_strategy_data {
	runq_item_t runq_link;
	affinity_t affinity;
	sched_timing_t sched_time;
};

#endif /* KERNEL_THREAD_SCHED_STRATEGY_SIMPLE_QUEUE_H_ */

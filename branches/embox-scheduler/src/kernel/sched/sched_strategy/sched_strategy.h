/**
 * @file
 * @brief
 *
 * @date 06.03.2013
 * @author Anton Bulychev
 */

#ifndef KERNEL_THREAD_SCHED_STRATEGY_SIMPLE_QUEUE_H_
#define KERNEL_THREAD_SCHED_STRATEGY_SIMPLE_QUEUE_H_

#include <module/embox/kernel/sched/strategy/queue/api.h>
#include <module/embox/kernel/sched/strategy/affinity_api.h>

struct runq {
	runq_queue_t queue;

};

struct sched_strategy_data {
	runq_item_t runq_link;
	AFFINITY_DEFINE;
};

#endif /* KERNEL_THREAD_SCHED_STRATEGY_SIMPLE_QUEUE_H_ */

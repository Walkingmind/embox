/**
 * @file
 * @brief
 *
 * @date 14.05.13
 * @author Anton Bulychev
 * @author Ilia Vaprol
 */

#ifndef KERNEL_EVENT_EVENT_SCHED_H_
#define KERNEL_EVENT_EVENT_SCHED_H_

#include <kernel/sched.h>
#include <kernel/sched/wait_queue.h>

#define EVENT_TIMEOUT_INFINITE SCHED_TIMEOUT_INFINITE

struct event {
	struct wait_queue wait_queue;
};
__BEGIN_DECLS

extern int __event_wait(unsigned long timeout); /* TODO: Remove this */

__END_DECLS

#define __EVENT_WAIT(event, cond_expr, timeout, intr)   \
	((cond_expr) ? 0 : ({                               \
		struct wait_link __wait_link;                   \
		int __wait_ret;                                 \
		do {                                            \
			wait_queue_prepare(&__wait_link);           \
			if (cond_expr) {                            \
				__wait_ret = 0;                         \
			}                                           \
			else {                                      \
				wait_queue_insert(&(event)->wait_queue, \
						&__wait_link);                  \
				__wait_ret = __event_wait(timeout);     \
			}                                           \
			wait_queue_cleanup(&__wait_link);           \
			if (!intr && (__wait_ret == -EINTR)) {      \
				continue;                               \
			}                                           \
		} while (0);                                    \
		__wait_ret;                                     \
	}))

#define EVENT_WAIT(event, cond_expr, timeout) \
	__EVENT_WAIT(event, cond_expr, timeout, 0)

#define EVENT_WAIT_OR_INTR(event, cond_expr, timeout) \
	__EVENT_WAIT(event, cond_expr, timeout, 1)

#endif /* KERNEL_EVENT_EVENT_SCHED_H_ */

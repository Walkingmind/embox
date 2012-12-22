/**
 * @file
 * @brief Threads internal implementation.
 *
 * @date 24.02.11
 * @author Alina Kramar
 */

#ifndef KERNEL_THREAD_API_IMPL_H_
#define KERNEL_THREAD_API_IMPL_H_

#include <kernel/thread/sched.h>

#include "types.h"

#define __thread_foreach(thread_ptr) \
	list_for_each_entry(thread_ptr, __extension__ ({   \
				extern struct list_head __thread_list; \
				&__thread_list;                        \
			}), thread_link)                           \

static inline struct thread *thread_self(void) {
	return sched_current();
}

#endif /* KERNEL_THREAD_API_IMPL_H_ */

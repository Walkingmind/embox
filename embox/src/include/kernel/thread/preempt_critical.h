/**
 * @file
 * @brief TODO
 *
 * @date Apr 9, 2011
 * @author Eldar Abusalimov
 */

#ifndef KERNEL_THREAD_PREEMPT_CRITICAL_H_
#define KERNEL_THREAD_PREEMPT_CRITICAL_H_

#include __impl_x(kernel/thread/preempt_critical_impl.h)

#define PREEMPT_CRITICAL_BITS \
	  __PREEMPT_CRITICAL_BITS

#endif /* KERNEL_THREAD_PREEMPT_CRITICAL_H_ */

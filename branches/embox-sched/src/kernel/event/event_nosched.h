/**
 * @file
 * @brief
 *
 * @date 14.05.2013
 * @author Anton Bulychev
 */

#ifndef KERNEL_EVENT_NOSCHED_H_
#define KERNEL_EVENT_NOSCHED_H_

#include <errno.h>

#define EVENT_TIMEOUT_INFINITE -1

struct event {
};

#define __EVENT_WAIT(event, cond_expr, timeout, intr) ENOERR

#endif /* KERNEL_EVENT_NOSCHED_H_ */

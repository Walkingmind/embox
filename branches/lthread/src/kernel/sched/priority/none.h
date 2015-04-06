/**
 * @file
 *
 * @date Aug 1, 2013
 * @author: Anton Bondarev
 */

#ifndef STRATEGY_NO_PRIORITY_H_
#define STRATEGY_NO_PRIORITY_H_

#include <sys/cdefs.h>

struct schedee;

struct schedee_priority {
	EMPTY_STRUCT_BODY
};

typedef struct schedee_priority __schedee_priority_t;

static inline int schedee_priority_set(struct schedee *s,
		sched_priority_t new_priority) {
	return 0;
}

static inline sched_priority_t schedee_priority_get(struct schedee *s) {
	return 0;
}

static inline sched_priority_t schedee_priority_inherit(struct schedee *s,
		sched_priority_t priority) {
	return 0;
}

static inline sched_priority_t schedee_priority_reverse(struct schedee *s) {
	return 0;
}

#endif /* STRATEGY_NO_PRIORITY_H_ */

/**
 * @file
 *
 * @date Aug 1, 2013
 * @author: Anton Bondarev
 */

#ifndef STRATEGY_RUNNABLE_PRIORITY_H_
#define STRATEGY_RUNNABLE_PRIORITY_H_



struct runnable_priority {
	short base_priority;      /**< Priority was set for the runnable. */
	short current_priority;   /**< Current runnable scheduling priority. */
};

typedef struct runnable_priority __runnable_priority_t;

extern int runnable_priority_init(struct runnable *r, sched_priority_t new_priority);
extern int runnable_priority_set(struct runnable *r, sched_priority_t new_priority);
extern sched_priority_t runnable_priority_get(struct runnable *r);
extern sched_priority_t runnable_priority_reverse(struct runnable *r);

#endif /* STRATEGY_RUNNABLE_PRIORITY_H_ */
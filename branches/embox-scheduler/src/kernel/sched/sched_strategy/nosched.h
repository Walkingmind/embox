/*
 * @file
 *
 * @date Mar 21, 2013
 * @author: Anton Bondarev
 */

#ifndef NOSCHED_H_
#define NOSCHED_H_


struct runq {

};

struct sched_strategy_data {
};


//TODO problem with single task
struct thread;
int thread_set_priority(struct thread *t, unsigned int new_priority) {
	return 0;
}

#endif /* NOSCHED_H_ */

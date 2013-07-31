/**
 * @file
 *
 * @date Jul 31, 2013
 * @author: Anton Bondarev
 */

#ifndef SMP_AFFINITY_H_
#define SMP_AFFINITY_H_


#define AFFINITY_DEFINE int affinity

struct thread;

extern int sched_affinity_check(struct thread *t);
extern void sched_affinity_init(struct thread *t);
extern void sched_affinity_set(struct thread *t, int mask);
extern int sched_affinity_get(struct thread *t);

#endif /* SMP_AFFINITY_H_ */

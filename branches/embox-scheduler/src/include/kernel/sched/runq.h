/**
 * @file
 *
 * @date Jul 29, 2013
 * @author: Anton Bondarev
 */

#ifndef RUNQ_H_
#define RUNQ_H_

extern void runq_queue_init(runq_queue_t *queue);
extern void runq_queue_insert(runq_queue_t *queue, struct thread *thread);
extern void runq_queue_remove(runq_queue_t *queue, struct thread *thread);
extern struct thread *runq_queue_extract(runq_queue_t *queue);

#endif /* RUNQ_H_ */

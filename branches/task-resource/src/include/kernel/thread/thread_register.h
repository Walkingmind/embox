/**
 * @file
 * @brief
 *
 * @date 28.02.14
 * @author Ilia Vaprol
 */

#ifndef THREAD_REGISTER_H_
#define THREAD_REGISTER_H_

struct task;
struct thread;

/** insert a created task into the task */
extern void thread_register(struct task *, struct thread *);

extern void thread_unregister(struct task *, struct thread *);

#endif /* THREAD_REGISTER_H_ */

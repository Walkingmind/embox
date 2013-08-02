/**
 * @file
 *
 * @date Aug 2, 2013
 * @author: Anton Bondarev
 */

#include <kernel/thread.h>
#include <kernel/task.h>


int task_add_thread(struct task * task, struct thread *t) {
	if((NULL == task) || (NULL == t)) {
		return -EINVAL;
	}

	/* insert new t to the list */
	dlist_head_init(&t->thread_link);
	dlist_add_next(&t->thread_link, &task->main_thread->thread_link);

	t->task = task;

	if(task->priority != 0) {
		/* we initialize thread priority for default task priority and now we must
		 * rescheduler thread
		 */
		thread_set_priority(t, thread_priority_get(t));
	}

	return ENOERR;
}


int task_remove_thread(struct task * task, struct thread *thread) {
	if((NULL == task) || (NULL == thread)) {
		return -EINVAL;
	}
#if 0
	if(NULL == task->main_thread) {
		return -EINVAL;
	}

	if(task->main_thread == thread) {
		return -EBUSY;
	}

	if(dlist_empty(&task->main_thread->thread_link)) {
		return -EBUSY;
	}
#endif

	dlist_del(&thread->thread_link);

	return ENOERR;
}



/**
 * @file
 * @brief Thread management API implementation.
 *
 * @date 22.04.10
 * @author Dmitry Avdyukhin
 *          - Initial implementation
 * @author Alina Kramar
 *          - Thread control block memory allocation
 *          - Move state management code into the scheduler
 *          - Suspend/resume logic
 * @author Eldar Abusalimov
 *          - Reviewing and simplifying threads API
 *          - Stack allocation
 * @author Anton Kozlov
 *          - Tasks binding
 *
 * @see tests/kernel/thread/core_test.c
 */

#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <time.h>

#include <embox/unit.h>

#include <kernel/thread.h>
#include <kernel/task.h>
#include <kernel/sched.h>
#include <kernel/thread/state.h>
#include <kernel/thread/wait_data.h>

#include <kernel/panic.h>

#include <hal/context.h>

EMBOX_UNIT_INIT(thread_core_init);

DLIST_DEFINE(__thread_list);

static int id_counter;

extern void thread_init(struct thread *t, unsigned int flags,
		void *(*run)(void *), void *arg);

static void thread_delete(struct thread *t);

extern struct thread *thread_alloc(void);
extern void thread_free(struct thread *t);

/**
 * Wrapper for thread start routine.
 */
static void __attribute__((noreturn)) thread_trampoline(void) {
	struct thread *current = thread_self();
	void *res;

	assert(!critical_allows(CRITICAL_SCHED_LOCK));

	sched_unlock_noswitch();
	/* we must make ipl_enable() because thread_trampoline start executing in
	 * sched_switch function? but in it we have off interrupts
	 */
	ipl_enable();

	assert(!critical_inside(CRITICAL_SCHED_LOCK));

	res = current->run(current->run_arg);
	thread_exit(res);
}

int thread_create(struct thread **p_thread, unsigned int flags,
		void *(*run)(void *), void *arg) {
	struct thread *t;
	int save_ptr;
	int res = ENOERR;

	/* check mutually exclusive flags */
	if ((flags & THREAD_FLAG_PRIORITY_LOWER)
			&& (flags & THREAD_FLAG_PRIORITY_HIGHER)) {
		return -EINVAL;
	}

	/* check one more mutually exclusive flags */
	if ((flags & THREAD_FLAG_SUSPENDED) && (flags & THREAD_FLAG_DETACHED)) {
		return -EINVAL;
	}

	/* check whether we need to return thread structure pointer */
	save_ptr = (flags & THREAD_FLAG_SUSPENDED)
			|| !(flags & THREAD_FLAG_DETACHED);

	/* if we need thread handler we check place for result */
	if (save_ptr && !p_thread) {
		return -EINVAL;
	}

	/* check correct executive function */
	if (!run) {
		return -EINVAL;
	}

	/* below we will work with thread's instances and therefore we need to
	 * lock scheduler (disable scheduling) to our structures is not be
	 * corrupted
	 */
	sched_lock(); /* lock scheduling */
		/*allocate memory */
		if (!(t = thread_alloc())) {
			res = -ENOMEM;
			goto out;
		}
		/* initialize internal thread structure */
		thread_init(t, flags, run, arg);


		/* link with task if it need */
		if(!(flags & THREAD_FLAG_TASK_THREAD)) {
			task_add_thread(task_self(), t);
		}

		if (!(flags & THREAD_FLAG_SUSPENDED)) {
			thread_launch(t);
		}

		if (flags & THREAD_FLAG_DETACHED) {
			thread_detach(t);
		}

out:
	sched_unlock();

	if (save_ptr) {
		*p_thread = t; /* save result pointer */
	}

	return res;
}

/*
 * extern void thread_init(struct thread *t, unsigned int flags,
 * void *(*run)(void *), void *arg)
 */
void thread_init(struct thread *t, unsigned int flags,
		void *(*run)(void *), void *arg) {
	__thread_priority_t priority;

	assert(t);
	assert(run);
	assert(t->stack);
	assert(t->stack_sz);

	t->id = id_counter++;

	dlist_head_init(&t->thread_link);
	dlist_add_next(&t->thread_link, &__thread_list);

	dlist_init(&t->thread_task_link); /* default unlink value */

	t->state = thread_state_init();

	/* set executive function and arguments pointer */
	t->run = run;
	t->run_arg = arg;

	/* calculate current thread priority. It can be change later with
	 * thread_set_priority () function
	 */
	if (flags & THREAD_FLAG_PRIORITY_INHERIT) {
		priority = thread_priority_get(thread_self());
	} else {
		priority = THREAD_PRIORITY_DEFAULT;
	}

	if ((flags & THREAD_FLAG_PRIORITY_LOWER)
			&& (priority > THREAD_PRIORITY_MIN)) {
		priority--;
	} else if ((flags & THREAD_FLAG_PRIORITY_HIGHER)
			&& (priority < THREAD_PRIORITY_HIGH)) {
		priority++;
	}

	/* setup thread priority. Now we have not started thread yet therefore we
	 * just set both base and scheduling priority in default value.
	 */
	thread_priority_set(t, priority);

	t->joined = NULL; /* there are not any joined thread */

	/* cpu context init */
	context_init(&t->context, true); /* setup default value of CPU registers */
	context_set_entry(&t->context, thread_trampoline); /* set entry (IP register */
	/* setup stack pointer to the top of allocated memory
	 * The structure of kernel thread stack follow:
	 * +++++++++++++++ top
	 *                  |
	 *                  v
	 * the thread structure
	 * xxxxxxx
	 * the end
	 * +++++++++++++++ bottom (t->stack - allocated memory for the stack)
	 */
	context_set_stack(&t->context, (char *) t->stack + t->stack_sz);

	sched_strategy_init(&t->sched);

	t->affinity = THREAD_AFFINITY_NONE;

	wait_data_init(&t->wait_data);
}

void __attribute__((noreturn)) thread_exit(void *ret) {
	struct thread *current = thread_self();
	struct task *task = task_self();

	assert(critical_allows(CRITICAL_SCHED_LOCK));

	sched_lock();
	{
		/* We can free only not main threads */
		if(task->main_thread == current) {
			/* We are last thread. Unlock scheduler and exit task. */
			sched_unlock();
			task_exit(ret);
		} else {
			/* Finish scheduling of the thread */
			sched_finish(current);

			if (thread_state_dead(current->state)) {
				/* Thread is detached. Should be deleted by itself. */
				thread_delete(current);
			} else {
				/* Thread is attached. Joined thread delete it.    */
				current->run_ret = ret;

				if (current->joined) {
					sched_thread_notify(current->joined, ENOERR);
				}
			}
		}
	}
	sched_unlock();

	/* NOTREACHED */
	panic("Returning from thread_exit()");
}

int thread_join(struct thread *t, void **p_ret) {
	struct thread *current = thread_self();
	void *join_ret;

	assert(t);

	if (t == current) {
		return -EDEADLK;
	}

	sched_lock();
	{
		if (!thread_state_exited(t->state)) {
			/* Target thread is not exited. Waiting for his exiting. */
			assert(!t->joined);
			t->joined = current;

			sched_prepare_wait(NULL, NULL);
			sched_wait_locked(SCHED_TIMEOUT_INFINITE);
			sched_cleanup_wait();
		}

		join_ret = t->run_ret;
		t->state = thread_state_do_detach(t->state);
		thread_delete(t);

		if (p_ret) {
			*p_ret = join_ret;
		}
	}
	sched_unlock();

	return 0;
}

int thread_detach(struct thread *t) {
	assert(t);

	sched_lock();
	{
		t->state = thread_state_do_detach(t->state);

		if (thread_state_dead(t->state)) {
			/* The target thread has finished, free it here. */
			thread_delete(t);
		}
	}
	sched_unlock();

	return 0;
}

int thread_launch(struct thread *t) {
	assert(t);

	sched_lock();
	{
		if (thread_state_started(t->state)) {
			sched_unlock();
			return -EINVAL;
		}

		if (thread_state_exited(t->state)) {
			sched_unlock();
			return -ESRCH;
		}

		/* running time */
		t->running_time = 0;
		t->last_sync = clock();

		sched_start(t);
	}
	sched_unlock();

	return 0;
}

int thread_terminate(struct thread *t) {
	assert(t);

	sched_lock();
	{
		if (!thread_state_exited(t->state)) {
			sched_finish(t);
		}

		if (!thread_state_detached(t->state)) {
			t->state = thread_state_do_detach(t->state);
		}

		thread_delete(t);
	}
	sched_unlock();

	return 0;
}

void thread_yield(void) {
	sched_post_switch();
}

int thread_set_priority(struct thread *t, thread_priority_t new_priority) {
	assert(t);

	if ((new_priority < THREAD_PRIORITY_MIN)
			|| (new_priority > THREAD_PRIORITY_MAX)) {
		return -EINVAL;
	}

	thread_priority_set(t, new_priority);

	return 0;
}

thread_priority_t thread_get_priority(struct thread *t) {
	assert(t);

	return thread_priority_get(t);
}


clock_t thread_get_running_time(struct thread *thread) {
	clock_t new_clock;

	sched_lock();
	{
		if (thread_state_oncpu(thread->state)) {
			/* Recalculate time of the thread. */
			new_clock = clock();
			thread->running_time += new_clock - thread->last_sync;
			thread->last_sync = new_clock;
		}
	}
	sched_unlock();

	return thread->running_time;
}


static void thread_delete(struct thread *t) {
	static struct thread *zombie = NULL;

	struct thread *current = thread_self();

	assert(t);
	assert(thread_state_dead(t->state));
	assert(t != zombie);
	assert(zombie == current);

	if (zombie != NULL) {
		thread_free(zombie);
		zombie = NULL;
	}

	task_remove_thread(t->task, t);
	dlist_del(&t->thread_link);

	if (t == current) {
		zombie = t;
	} else {
		thread_free(t);
	}
}


struct thread *thread_lookup(thread_id_t id) {
	struct thread *t, *tmp;

	thread_foreach(t, tmp) {
		if (t->id == id) {
			return t;
		}
	}

	return NULL;
}



extern int sched_init(struct thread *idle, struct thread *current);
extern struct thread *thread_idle_init(void);
extern struct thread *thread_boot_init(void);

static int thread_core_init(void) {
	struct thread *idle;
	struct thread *current;

	id_counter = 0; /* start enumeration */

	idle = thread_idle_init(); /* idle thread always has ID=0 */

	current = thread_boot_init(); /* 'init' thread ID=1 */

	return sched_init(idle, current);
}

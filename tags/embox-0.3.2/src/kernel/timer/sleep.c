/**
 * @file
 * @brief Multi-thread sleep
 *
 * @date 05.07.11
 * @author Ilia Vaprol
 * @author Fedor Burdun
 */

#include <errno.h>
#include <types.h>
#include <time.h>

#include <kernel/timer.h>
#include <kernel/thread/sched.h>
#include <kernel/thread/event.h>

static void restore_thread(sys_timer_t *timer, void *param) {
	sched_wake((struct event *) param);
}

/* system library function */
int usleep(useconds_t usec) {
	int ret = 0;

	if(0 == usec) {
		sched_yield();
		return ret;
	}

	sched_lock();
	{
		struct event wait_event;
		struct sys_timer tmr; /* we allocate timer structure on the stack */

		event_init(&wait_event, NULL);
		if (0 != timer_init(&tmr, TIMER_ONESHOT, usec, &restore_thread, &wait_event)) {
			ret = -EBUSY;
			goto out_unlock;
		}

		sched_sleep_locked(&wait_event);

		timer_close(&tmr);
	}
	out_unlock: sched_unlock();

	return ret;
}

int sleep(unsigned int seconds) {
	return usleep(seconds * 1000);
}
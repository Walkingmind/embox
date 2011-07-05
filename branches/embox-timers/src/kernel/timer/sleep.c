/**
 * @file
 * @brief Multi-thread sleep
 *
 * @date 05.07.11
 * @author Ilia Vaprol
 */

#include <types.h>
#include <kernel/timer.h>
#include <kernel/thread/sched.h>
#include <kernel/thread/event.h>

static void restore_thread(sys_tmr_ptr timer, void *param) {
	sched_wake((struct event *) param);
	close_timer(&timer);
}

/*system library function */
int usleep(useconds_t usec) {
	struct event wait_event;

	event_init(&wait_event, NULL);

	sched_lock();

	if (set_timer(NULL, usec, &restore_thread, &wait_event)) {
		return 1;
	}
	sched_sleep_locked(&wait_event);

	sched_unlock();
	return 0;
}

int sleep(uint32_t seconds) {
	return usleep(seconds * TIMER_FREQUENCY);
}

/**
 * @file
 * @brief Timer handling.
 *
 * @date 30.06.11
 * @author Andrey Baboshin
 * @author Ilia Vaprol
 */

#include <types.h>
#include <unistd.h>
#include <kernel/irq.h>
#include <hal/clock.h>
#include <kernel/timer.h>
#include <time.h>
#include <util/array.h>
#include <string.h>
#include <embox/unit.h>
#include <lib/list.h>
#include <hal/arch.h>
#include <kernel/thread/event.h>
#include <kernel/thread/sched.h>
#include <assert.h>

EMBOX_UNIT_INIT(timer_init);

#define TIMER_FREQUENCY 1000

typedef struct sys_tmr {
	struct list_head *next, *prev;
	uint32_t   id;
	uint32_t   load;
	uint32_t   cnt;
	TIMER_FUNC handle;
	struct event event_wait;
} sys_tmr_t;

static volatile uint32_t cnt_ms_sleep; /**< for sleep function */
static volatile uint32_t cnt_sys_time; /**< quantity ms after start system */

static sys_tmr_t sys_timers[_SC_TIMER_MAX];

static LIST_HEAD(free_sys_timers_list);
static LIST_HEAD(sys_timers_list);

uint32_t cnt_system_time(void) {
	return cnt_sys_time;
}

static sys_tmr_t * get_timer_by_id(uint32_t id) {
	struct list_head *p;

	list_for_each(p, &sys_timers_list) {
		if (id == ((sys_tmr_t *) p)->id) {
			return (sys_tmr_t *) p;
		}
	}
	return (sys_tmr_t *) 0;
}

static int timer_id_is_busy(uint32_t id) {
	sys_tmr_t *timer;

	timer = get_timer_by_id(id);
	if (timer != (sys_tmr_t *) 0) {
		return 1;
	}
	return 0;
}

static uint32_t get_free_timer_id(void) {
	uint32_t id;
	for (id = 1; id < _SC_TIMER_MAX; id++) {
		if (!get_timer_by_id(id)) {
			return id;
		}
	}
	return (uint32_t)-1;
}

int set_timer(uint32_t id, uint32_t ticks, TIMER_FUNC handle) {
	sys_tmr_t *new_timer;
	if (list_empty(&free_sys_timers_list) ||
	    timer_id_is_busy(id) || !handle) {
		return 0;
	}
	new_timer = (sys_tmr_t *) free_sys_timers_list.next;
	new_timer->cnt    = new_timer->load = ticks;
	new_timer->id     = id;
	new_timer->handle = handle;
	event_init(&new_timer->event_wait, NULL);
	list_move_tail((struct list_head *) new_timer, &sys_timers_list);
	return id;
}

void close_timer(uint32_t id) {
	struct list_head *p;
	list_for_each(p, &sys_timers_list) {
		if (id == ((sys_tmr_t *) p)->id) {
			list_move_tail(p, &free_sys_timers_list);
			break;
		}
	}
}

/**
 * For each timer in the timers array do the following: if the timer is enable
 * and the counter of this timer is the zero then its initial value is assigned
 * to the counter and the function is executed.
 */
static void inc_sys_timers(void) {
	struct list_head *tmp, *tmp2;
	sys_tmr_t *tmr;

	list_for_each_safe(tmp, tmp2, &sys_timers_list) {
		tmr = (sys_tmr_t *) tmp;
		if (0 == tmr->cnt--) {
			if (tmr->handle) {
				tmr->handle(tmr->id);
			}
			tmr->cnt = tmr->load;
		}
	}
}

/**
 * Handling of the clock tick.
 */
void clock_tick_handler(int irq_num, void *dev_id) {
	cnt_ms_sleep++;
	cnt_sys_time++;
	inc_sys_timers();
}

/**
 * Initialization of the timer subsystem.
 *
 * @return 0 if success
 */
int timer_init(void) {
	size_t i;
	cnt_sys_time = 0;
	for (i = 0; i < ARRAY_SIZE(sys_timers); i++) {
		list_add((struct list_head *) &sys_timers[i], &free_sys_timers_list);
	}
	clock_init();
	clock_setup(TIMER_FREQUENCY);
	return 0;
}

static void restore_thread(uint32_t id)
{
	struct event *e;
	sys_tmr_t *timer;

	printf("Timer id: %d\n", id);
	timer = get_timer_by_id(id);
	assert(timer);
	e = &timer->event_wait;
	close_timer(id);
	sched_wake(e);
//	sched_wake(&get_timer_by_id(id)->event_wait);
}

/*system library function */
int usleep(useconds_t usec) {
	uint32_t id;

	sched_lock();

	id = get_free_timer_id();
	if ((id == (uint32_t) -1) || !set_timer(id, usec, &restore_thread)) {
		return 1;
	}
	sched_sleep_locked(&get_timer_by_id(id)->event_wait);

	sched_unlock();

	return 0;
}

uint32_t sleep(uint32_t seconds) {
	return usleep(seconds * TIMER_FREQUENCY);
}

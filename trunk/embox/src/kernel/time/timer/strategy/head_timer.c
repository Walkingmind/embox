/**
 * @file
 * @brief
 *
 * @date 22.07.10
 * @author Andrey Baboshin
 * @author Ilia Vaprol
 * @author Fedor Burdun
 */

#include <lib/list.h>
#include <kernel/time/timer.h>


static DLIST_DEFINE(sys_timers_list); /* list head to timers */

void timer_strat_start(struct sys_timer *tmr) {
	struct sys_timer *it_tmr, *tmp;

	dlist_head_init(&tmr->lnk);
	timer_set_started(tmr);

	tmr->cnt = tmr->load;

	/* find first element that its time bigger than inserting @new_time */
	dlist_foreach_entry(it_tmr, tmp, &sys_timers_list,lnk) {
		if (it_tmr->cnt >= tmr->cnt) {
			/* decrease value of next timer after inserting */
			it_tmr->cnt -= tmr->cnt;

			dlist_add_prev(&tmr->lnk, &it_tmr->lnk);

			return;
		}
		tmr->cnt -= it_tmr->cnt;

	}

	/* add the latest timer to end of list */
	dlist_add_prev(&tmr->lnk, &sys_timers_list);
}

void timer_strat_stop(struct sys_timer *ptimer) {
	struct sys_timer *next_tmr;

	timer_set_stopped(ptimer);

	if(ptimer->lnk.next != &sys_timers_list) {
		next_tmr = (struct sys_timer *)ptimer->lnk.next;
		next_tmr->cnt += ptimer->cnt;
	}

	dlist_del(&ptimer->lnk);
}

static inline bool timers_need_schedule(void) {
	if(dlist_empty(&sys_timers_list)) {
		return false;
	}

	if(0 == --((sys_timer_t*)sys_timers_list.next)->cnt) {
		return true;
	} else {
		return false;
	}
}

static inline void timers_schedule(void) {
	struct sys_timer *timer,*tmp;
	uint32_t nxt_cnt = 0; /* we schedule first timer */

	dlist_foreach_entry(timer, tmp, &sys_timers_list, lnk) {
		nxt_cnt = tmp->cnt;
		timer->handle(timer, timer->param);

		timer_strat_stop(timer);
		if(timer_is_periodic(timer)) {
			timer_strat_start(timer);
		}
		if (0 != nxt_cnt) {
			return;
		}
	}
}

/**
 * For each timer in the timers array do the following: if the timer is enable
 * and the counter of this timer is the zero then its initial value is assigned
 * to the counter and the function is executed.
 */
void timer_strat_sched(void) {
	if(timers_need_schedule()) {
		timers_schedule();
	}
}

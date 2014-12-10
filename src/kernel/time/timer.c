/**
 * @file
 * @brief Link layer between timers and clock sources.
 *
 * @date 09.07.2012
 * @author Alexander Kalmuk
 */

#include <embox/unit.h>
#include <kernel/softirq.h>
#include <kernel/task.h>
#include <module/embox/kernel/time/slowdown.h>
#include <kernel/time/timer.h>
#include <kernel/time/clock_source.h>

#define SLOWDOWN_FACTOR OPTION_MODULE_GET(embox__kernel__time__slowdown, NUMBER, factor)

EMBOX_UNIT_INIT(init);

extern struct clock_source *cs_jiffies;

/**
 * Handling of the clock tick.
 */
void clock_tick_handler(int irq_num, void *dev_id) {
	struct clock_source *cs = (struct clock_source *) dev_id;

	assert(cs);
	if (++cs->jiffies_cnt == SLOWDOWN_FACTOR) {
		cs->jiffies_cnt = 0;
		cs->jiffies++;

		if (cs_jiffies->event_device && irq_num == cs_jiffies->event_device->irq_nr) {
			//task_self()->per_cpu++;
			softirq_raise(SOFTIRQ_NR_TIMER);
		} 
	}
}

static void soft_clock_handler(unsigned int softirq_nr, void *data) {
	timer_strat_sched();
}

static int init(void) {
	softirq_install(SOFTIRQ_NR_TIMER, soft_clock_handler,NULL);
	return 0;
}

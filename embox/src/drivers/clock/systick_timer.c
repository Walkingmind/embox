/**
 * @file
 * @brief Core clocking device in Cortex-M3 
 *
 * @date 23.03.12
 * @author Anton Kozlov
 */

#include <hal/clock.h>
#include <hal/reg.h>
#include <kernel/irq.h>
#include <kernel/clock_source.h>
#include <types.h>
#include <hal/interrupt.h>

#define SYSTICK_IRQ 15

#define SYSTICK_BASE 0xe000e010

#define SYSTICK_CTRL SYSTICK_BASE

#define SYSTICK_CALIB ((int) SYSTICK_BASE + 0x0c)

#define SYSTICK_RELOAD (SYSTICK_BASE + 0x04)
#define SYSTICK_VAL (SYSTICK_BASE + 0x08)

#define SYSTICK_ENABLE 0x01
#define SYSTICK_TICKINT (0x01 << 1)
#define SYSTICK_CLOCKINIT (0x01 << 2)

#define SCB_SHP_BASE ((unsigned int *) 0xe000ed18)
#define SCB_SHP_PERIF_N 8 

void clock_handler(void) {
	clock_tick_handler(SYSTICK_IRQ, NULL);
}

static int this_init(void) {
	return 0;
}

static int this_config(enum device_config cfg, void *param) {
	int ticks_per_10ms = REG_LOAD(SYSTICK_CALIB) & 0xffffff;

	REG_STORE(SYSTICK_CTRL, 0);

	REG_STORE(SYSTICK_RELOAD, ticks_per_10ms /10 - 1);

	REG_STORE(SYSTICK_VAL, 0);	

	REG_STORE(SCB_SHP_BASE + 2, 0xf0 << (3 * SCB_SHP_PERIF_N));

	REG_STORE(SYSTICK_CTRL, SYSTICK_ENABLE | SYSTICK_TICKINT | 
			SYSTICK_CLOCKINIT);

	return 0;
}

static struct time_event_device this_event = {
	.init = this_init,
	.jiffies = 0, 
	.config = this_config ,
	.resolution = 10,
};


static struct time_counter_device this_counter = {
	.read = NULL,
	.resolution = 1000000,
};

static struct clock_source this_clock_source = {
	.name = "system_tick", 
	.event_device = &this_event, 
	.counter_device = &this_counter,
	.read = clock_source_read,
};

CLOCK_SOURCE(&this_clock_source);


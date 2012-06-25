/**
 * @file
 * @brief System timer
 *
 * @date 14.07.10
 * @author Anton Kozlov
 */

#include <hal/clock.h>
#include <hal/reg.h>
#include <kernel/irq.h>
#include <kernel/clock_source.h>
#include <types.h>
#include <hal/interrupt.h>
#include <drivers/at91sam7s256.h>

#include <system.h>

#define AT91_PIT_COUNTER_RES (SYS_CLOCK / 16)
#define AT91_PIT_EVENT_RES 1000

irq_return_t clock_handler(int irq_num, void *dev_id) {
	if (REG_LOAD(AT91C_PITC_PISR)) {
		REG_LOAD(AT91C_PITC_PIVR);
		clock_tick_handler(irq_num, dev_id);
	}
	return IRQ_HANDLED;
}

static char init_flag = 0;

static int at91_pitc_init(void) {
	if (init_flag) {
		return 0;
	}
		
	init_flag = 1;

	REG_STORE(AT91C_PMC_PCER, AT91C_ID_SYS);
	return irq_attach((irq_nr_t) AT91C_ID_SYS,
		(irq_handler_t) &clock_handler, 0, NULL, "at91 PIT");
}

static int at91_pitc_config(enum device_config cfg, void *param);

static struct time_event_device at91_pitc_event = {
	.init = at91_pitc_init,
	.jiffies = 0, 
	.config = at91_pitc_config,
	.resolution = AT91_PIT_EVENT_RES,
};


static cycle_t at91_pitc_read(void) {
	return 0; //REG_LOAD(AT91C_PITC_PIVR);
}

static struct time_counter_device at91_pitc_counter = {
	.read = at91_pitc_read,
	.resolution = AT91_PIT_COUNTER_RES,
};

static struct clock_source at91_pitc_clock_source = {
	.name = "at91_pitc", 
	.event_device = &at91_pitc_event, 
	.counter_device = &at91_pitc_counter,
	.read = clock_source_read,
};

static int at91_pitc_config(enum device_config cfg, void *param) {
	REG_LOAD(AT91C_PITC_PIVR);
	REG_STORE(AT91C_PITC_PIMR, AT91C_PITC_PITEN | AT91C_PITC_PITIEN |
	    (at91_pitc_counter.resolution / at91_pitc_event.resolution));
	return 0;
}

CLOCK_SOURCE(&at91_pitc_clock_source);


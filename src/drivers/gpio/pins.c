/**
 * @file
 * @brief Pins managment system
 *
 * @date 26.11.10
 * @author Anton Kozlov
 */

#include <drivers/pins.h>
#include <hal/pins.h>
#include <kernel/printk.h>
#include "omap3_gpio.h"

/**
 * Assuming each pin have a single strictly determined function
 * (very strange if it doesn't, using simply scheme)
 */

#define N_PINS 8 * (sizeof(int))

struct handler_item_t {
	int mask;
	pin_handler_t handler;
};

static struct handler_item_t handlers[N_PINS];

static int n_handler = 0;

irq_return_t irq_pin_handler(unsigned int irq_nr, void *data) {
	int i;
	int current = pin_get_input(~0);
	int changed = pin_get_input_changed();

	for (i = 0; i < n_handler; i++) {
		if (changed & handlers[i].mask) {
			handlers[i].handler(handlers[i].mask & current, handlers[i].mask);
		}
	}

	return IRQ_HANDLED;
}

void pin_set_input_monitor(int mask, pin_handler_t pin_handler) {
	handlers[n_handler].handler = pin_handler;
	handlers[n_handler].mask = mask;
	n_handler++;
	pin_config_input(mask);
	pin_set_input_interrupt(mask);
}

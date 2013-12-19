/**
 * @file
 * @brief AT91 pio pin driver
 *
 * @date 26.11.2010
 * @author Anton Kozlov
 */

#include <embox/unit.h>
#include <drivers/at91sam7s256.h>
#include <hal/reg.h>
#include <drivers/pins.h>
#include <hal/pins.h>
#include <kernel/irq.h>

EMBOX_UNIT_INIT(at91_pin_init);

static int at91_pin_init(void) {
	REG_STORE(AT91C_PMC_PCER, 1L << AT91C_ID_PIOA);
	irq_attach(AT91C_ID_PIOA, (irq_handler_t) &irq_pin_handler,
			1, NULL, "AT91 PIO pins");
	pin_get_input_changed();
	return 0;
}

static void pin_disable_perf(int mask) {
	REG_STORE(AT91C_PIOA_PER, (uint32_t) mask);
}

void pin_config_input(int mask) {
	pin_disable_perf(mask);
	REG_STORE(AT91C_PIOA_ODR, (uint32_t) mask);
}

void pin_config_output(int mask) {
	pin_disable_perf(mask);
	REG_STORE(AT91C_PIOA_OER, (uint32_t) mask);
}

int pin_get_input(void) {
	return (int) REG_LOAD(AT91C_PIOA_PDSR);
}

void pin_set_output(int mask) {
	REG_STORE(AT91C_PIOA_SODR, mask);
	REG_STORE(AT91C_PIOA_CODR, (~mask));
}

void pin_set_input_interrupt(int mask) {
	REG_STORE(AT91C_PIOA_IER, mask);
}

int pin_get_input_changed(void) {
	return (int) REG_LOAD(AT91C_PIOA_ISR);
}
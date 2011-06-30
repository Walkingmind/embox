/**
 * @file
 * @brief Init Atmel AVR ATmega8 PDIP.
 *
 * @date 16.10.10
 * @author Anton Kozlov
 */

#include <embox/unit.h>
#include <string.h>
#include <hal/reg.h>
#include <unistd.h>
#include <kernel/timer.h>
#include <drivers/at91sam7s256.h>
#include <drivers/twi.h>
#include <drivers/nxt_buttons.h>
#include <drivers/nxt_avr.h>
#include <drivers/nxt_sensor.h>
#include <kernel/measure.h>

EMBOX_UNIT_INIT(init);

const char avr_brainwash_string[] =
  "\xCC" "Let's samba nxt arm in arm, (c)LEGO System A/S";

to_avr_t data_to_avr;
from_avr_t data_from_avr;
static int read_write = 0;
static bool avr_line_locked = false;

static int avr_send_data(to_avr_t *data_to_avr) {
	int res = 0;

#ifdef CONFIG_MEASURE
	measure_start();
#endif
	avr_line_locked = true;
	twi_send(NXT_AVR_ADDRESS, (uint8_t *) data_to_avr, sizeof(to_avr_t));
	avr_line_locked = false;

#ifdef CONFIG_MEASURE
	avr_send_process(measure_stop());
#endif
	return res;
}

static int avr_get_data(from_avr_t *data_from_avr) {
	int res = 0;

#ifdef CONFIG_MEASURE
	measure_start();
#endif

	avr_line_locked = true;
	res = twi_receive(NXT_AVR_ADDRESS, (uint8_t *) data_from_avr,
		sizeof(from_avr_t));
	avr_line_locked = false;
#ifdef CONFIG_MEASURE
	avr_get_process(measure_stop());
#endif
	return res;
}

static uint32_t avr_handler(void) {
	if (avr_line_locked) {
	}

	if (read_write++ & 1) {
		avr_send_data(&data_to_avr);
	} else {
		avr_get_data(&data_from_avr);
		buttons_updated((buttons_t) data_from_avr.buttons_val);
		sensors_updated(data_from_avr.adc_value);
	}

	return 0;
}

static int init(void) {
	int result = 0;

	twi_init();
	twi_write(NXT_AVR_ADDRESS, (const uint8_t *) avr_brainwash_string,
					strlen(avr_brainwash_string));

	data_to_avr.power = 0;
	data_to_avr.pwm_frequency = 0;
	data_to_avr.output_mode = 0;
	data_to_avr.input_power = 0;

	sensors_init();

	set_timer(0, 1, (TIMER_FUNC) avr_handler);

	return result;
}

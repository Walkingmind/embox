/**
 * @file
 * @brief Color sensor test
 *
 * @date 05.11.10
 * @author Anton Kozlov
 */

#include <types.h>
#include <embox/test.h>
#include <unistd.h>
#include <drivers/nxt/buttons.h>
#include <drivers/pins.h>

#include <drivers/nxt/sensor.h>
#include <drivers/nxt/avr.h>

EMBOX_TEST(sensor_test);

#define TOUCH_PORT (&sensors[0])

sensor_val_t sval = 10;

void sensor_handler(sensor_t *sensor, sensor_val_t val) {
	sval = val;
}

static int sensor_test(void) {
	nxt_sensor_conf_pass(TOUCH_PORT, (sensor_hnd_t) sensor_handler);

	//pin_config_output((1 << TOUCH_PORT->n0p) | (1 << TOUCH_PORT->n1p));
	//pin_set_output((1 << TOUCH_PORT->n0p | (1 << TOUCH_PORT->n1p)));
	//pin_clear_output((1 << DIGIB0) | (1 << DIGIB1));
	uint8_t power_val = 0x01;
	data_to_avr.input_power = power_val;

	while (true) {
		int butt_state = nxt_buttons_pressed();
		if (butt_state & NXT_BT_ENTER) {
			TRACE("|%d", sval);
		}
		if (butt_state & NXT_BT_DOWN) {
			break;
		}
		if (butt_state & NXT_BT_LEFT) {
			power_val <<=1;
			if (power_val == 0) {
				power_val = 1;
			}
			data_to_avr.input_power = power_val;
		}
		usleep(500);
	}

	return 0;
}

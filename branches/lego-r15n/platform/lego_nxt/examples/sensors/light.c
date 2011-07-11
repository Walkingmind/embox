/**
 * @file
 * @brief Color sensor test
 *
 * @date 05.11.10
 * @author Anton Kozlov
 */

#include <types.h>
#include <embox/example.h>
#include <unistd.h>
#include <drivers/nxt/buttons.h>
#include <drivers/pins.h>

#include <drivers/nxt/sensor.h>
#include <drivers/nxt/avr.h>

EMBOX_EXAMPLE(sensor_example);

#define LIGHT_PORT NXT_SENSOR_1

sensor_val_t sval = 10;

void sensor_handler(sensor_t *sensor, sensor_val_t val) {
	sval = val;
}

static int sensor_example(void) {
	nxt_sensor_conf_pass(LIGHT_PORT, (sensor_hnd_t) sensor_handler);

	while (true) {
		int butt_state = nxt_buttons_pressed();
		if (butt_state & NXT_BT_ENTER) {
			printf("|%d", sval);
		}
		if (butt_state & NXT_BT_DOWN) {
			break;
		}
		usleep(500);
	}

	return 0;
}

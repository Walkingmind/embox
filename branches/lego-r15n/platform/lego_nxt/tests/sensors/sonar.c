/**
 * @file
 * @brief Sonar test
 *
 * @date 22.12.10
 * @author Anton Kozlov
 */

#include <drivers/soft_i2c.h>
#include <drivers/nxt/buttons.h>
#include <drivers/nxt/sonar_sensor.h>
#include <embox/test.h>
#include <drivers/at91sam7s256.h>
#include <unistd.h>

EMBOX_TEST(sonar_test);

#define PORT ((sensor_t *) (&sensors[1]))


static int sonar_test(void) {
	int buts;
	nxt_sonar_init(PORT);

	while (!(( buts = nxt_buttons_pressed()) & NXT_BT_DOWN)) {
		TRACE("%d\n", nxt_sensor_get_val(PORT));

		usleep(1000);
	}
	return 0;
}

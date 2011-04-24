/**
 * @file
 * @brief nxt box around test
 * @details during the test robot travels clockwise around a rectangular box
 *
 * @date 17.01.11
 * @author Alexander Batyukov
 */
#include <types.h>
#include <embox/test.h>
#include <unistd.h>
#include <drivers/nxt_buttons.h>
#include <drivers/nxt_sonar_sensor.h>
#include <util/math.h>

#include <drivers/nxt_motor.h>

EMBOX_TEST(box_around_test);

#define SONAR_PORT (&sensors[1])
#define MOTOR0 (&motors[0])
#define MOTOR1 (&motors[1])

#define ROBOT_WIDTH 15

#define MOTOR_POWER -100

static int sonar_treshold = 50;

/* TODO: mb move this stuff to library */


static void rotate_start(int motor_power0, int motor_power1) {
	motor_set_power(MOTOR0, motor_power0);
	motor_set_power(MOTOR1, motor_power1);
}

static void move_start(void) {
	motor_set_power(MOTOR0, MOTOR_POWER);
	motor_set_power(MOTOR1, MOTOR_POWER);
}

static void move_stop(void) {
	motor_set_power(MOTOR0, 0);
	motor_set_power(MOTOR1, 0);
}

static int box_around_test(void) {
	int mp0, mp1;

	sonar_sensor_init (SONAR_PORT);

	motor_start(MOTOR0, 0, 360, NULL);
	motor_start(MOTOR1, 0, 360, NULL);

	sonar_treshold = sonar_sensor_get_val(SONAR_PORT);

	printf ("distance is %d\n", sonar_treshold);

	mp0 = MOTOR_POWER * sonar_treshold / (sonar_treshold + ROBOT_WIDTH);
	mp1 = MOTOR_POWER;

	while (!nxt_buttons_was_pressed()) {
		while (abs(sonar_sensor_get_val(SONAR_PORT) - sonar_treshold) < 3) {
			move_start();
		}
		move_stop();

		while (abs(sonar_sensor_get_val(SONAR_PORT) - sonar_treshold) >= 3) {
			rotate_start(mp0, mp1);
		}

		move_stop();
	}

	return 0;
}

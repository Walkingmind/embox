/**
 * @file
 * @brief Angle test
 *
 * @date 14.05.11
 * @author Alexandr Kalmuk
 */

#include <drivers/soft_i2c.h>
#include <drivers/nxt/angle_sensor.h>
#include <embox/cmd.h>
#include <unistd.h>
#include <drivers/nxt/motor.h>

EMBOX_CMD(pen_angle);

#define MOTOR_POWER 100

#define PORT NXT_SENSOR_1
#define MOTOR0 NXT_MOTOR_A
#define MOTOR1 NXT_MOTOR_B


static sensor_val_t sval = 0;

static int pen_angle(int argc, char **argv) {
	int motor_pov = 100;

	nxt_angle_sensor_init(PORT);

	nxt_motor_set_power(MOTOR0, motor_pov);
	nxt_motor_set_power(MOTOR1, -motor_pov);

	while (true) {
		sval = nxt_sensor_active_get_val(PORT, NXT_ANGLE_2X_ANGLE_COMM);
		if (sval >= 9 && sval <= 11) {
			motor_pov *= (-1);
			nxt_motor_set_power(MOTOR0, motor_pov);
			nxt_motor_set_power(MOTOR1, -motor_pov);
			while (sval >= 9 && sval <= 11) {
				sval = nxt_sensor_active_get_val(PORT, NXT_ANGLE_2X_ANGLE_COMM);
			}
		}
	}
	return 0;
}

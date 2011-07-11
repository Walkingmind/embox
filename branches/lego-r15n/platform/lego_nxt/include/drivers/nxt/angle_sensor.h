/**
 * @file angle_sensor.h
 * @brief NXT angle sensor interface
 *
 * @date 30.04.11
 * @author Anton Kozlov
 */

#ifndef NXT_ANGLE_H_
#define NXT_ANGLE_H_

#include <drivers/nxt/sensor.h>

/* commands to be given as 'commands'
 * to nxt_sensor_active_get_val */
#define NXT_ANGLE_2X_ANGLE_COMM 0x42
#define NXT_ANGLE_1_ANGLE_ADD_COMM 0x43
#define NXT_ANGLE_RPM_HIGH_COMM 0x48
#define NXT_ANGLE_RPM_LOW_COMM 0x49

/**
 * Dynamically defines @link sensor @link as angle sensor
 * @param sensor Sensor to be defined
 */
extern void nxt_angle_sensor_init(sensor_t *sensor);

/**
 * Gets Rotates Per Minute from angle sensor
 * @param sensor Sensor to be accessed
 * @return Rotates Per Minute value
 */
extern uint16_t nxt_angle_get_rpm(sensor_t *sensor);

#endif /* NXT_SONAR_H_ */

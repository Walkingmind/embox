/**
 * @file
 * @brief Touch sensor interface of nxt
 *
 * @date 02.12.2010
 * @author Anton Kozlov 
 */


#ifndef NXT_TOUCH_SENSOR_H_
#define NXT_TOUCH_SENSOR_H_

#include <drivers/nxt_sensor.h>

typedef void (*touch_hnd_t)(sensor_t sensor);

extern void touch_sensor_init (sensor_t sensor, touch_hnd_t handler);

#endif /*NXT_SENSOR_H_*/


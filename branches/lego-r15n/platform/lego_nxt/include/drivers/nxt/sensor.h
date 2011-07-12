/**
 * @file
 * @brief Input interface of nxt
 *
 * @date 02.12.10
 * @author Anton Kozlov
 */

#ifndef NXT_SENSOR_H_
#define NXT_SENSOR_H_

#include <drivers/nxt/avr.h>
#include <drivers/soft_i2c.h>

#define SENSOR_NOT_CONF 42

/**
 * Sensor class type. Describes general interface for sensor
 */
typedef enum {
	NXT_SENSOR_NONE,   //!< Not used
	NXT_SENSOR_PASSIVE,//!< Passive (touch, light,...)
	NXT_SENSOR_ACTIVE, //!< Active (sonar, angle,...)
} sensor_type_t;

/**
 * Sensor struct type
 */
typedef struct {
	uint8_t id;
	sensor_type_t type;
	uint8_t def_comm;
	i2c_port_t i2c_port;
} sensor_t;

#define NXT_N_SENSORS NXT_AVR_N_INPUTS

extern sensor_t sensors[NXT_N_SENSORS];

#define NXT_SENSOR_1 (&sensors[0])
#define NXT_SENSOR_2 (&sensors[1])
#define NXT_SENSOR_3 (&sensors[2])
#define NXT_SENSOR_4 (&sensors[3])

/**
 * Sensor value type. Returns as sensor measuring
 */
typedef uint16_t sensor_val_t;

/**
 * Sensor value changed handler. Called when sensor reads new value. Used only with passive sensors
 * @param sensor Sensor, which value changed
 * @param sensor_val Value of @link sensor @link
 */
typedef void (*sensor_hnd_t)(sensor_t *sensor, sensor_val_t sensor_val);

/**
 * Configure sensor as passive and sets handler
 * @param sensor Sensor to be configured
 * @param handler @link sensor_hnd_t @link or NULL as sensor value changed handler
 */
extern void nxt_sensor_conf_pass(sensor_t *sensor, sensor_hnd_t handler);

/**
 * Configure sensor as active
 * @param sensor
 */
extern void nxt_sensor_conf_active(sensor_t *sensor);

/**
 * Gets current measuring value from sensor
 * @param sensor Sensor to be used
 * @return Sensor measuring value
 */
extern sensor_val_t nxt_sensor_get_val(sensor_t *sensor);

/**
 * Gets additional measuring value from sensor
 * @param sensor Sensor to be used
 * @param command Special id of value. Special for each sensor
 * @return
 */
extern sensor_val_t nxt_sensor_active_get_val(sensor_t *sensor, uint8_t command);


#endif /* NXT_SENSOR_H_ */

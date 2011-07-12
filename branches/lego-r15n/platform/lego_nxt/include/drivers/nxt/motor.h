/**
 * @file
 * @brief Motor driver interface
 *
 * @date 02.12.10
 * @author Anton Kozlov
 */

#ifndef NXT_MOTOR_H_
#define NXT_MOTOR_H_

#include <types.h>
#include <drivers/nxt/avr.h>
#include <drivers/pins.h>

/**
 * Total number of motors avaible in system
 */
#define NXT_N_MOTORS NXT_AVR_N_OUTPUTS

/**
 * Tacholimit handler function type. Tacholimit handler of motor
 * (@link motor_t.tacho_hnd) is called after
 * @link motor_t.tacho_limit @link went to zero
 */
typedef void (*tacholimit_hnd_t)(void);

typedef struct {
	uint8_t          id;
	uint32_t         m_0, m_1;
	uint32_t         tacho_limit;
	tacholimit_hnd_t limit_hnd;
	uint32_t         tacho_count;
	pin_handler_t    pin_handler;
} nxt_motor_t;


extern nxt_motor_t nxt_motors[NXT_N_MOTORS];

#define NXT_MOTOR_A (&nxt_motors[0])
#define NXT_MOTOR_B (&nxt_motors[1])
#define NXT_MOTOR_C (&nxt_motors[2])


/**
 * Inits all motor preferences
 * @param motor Motor
 * @param limit Count of tacho ticks before handler call
 * @param lim_handler Handler called when @link limit @endlink ticks passed
 */
extern void nxt_motor_set_tacho(nxt_motor_t *motor, uint32_t limit,
			tacholimit_hnd_t lim_handler);
/**
 * Set power motor
 * @param motor Motor
 * @param power for motor:
 *		0    means stop
 *		-100 means full counterclockwise
 *		100	 measn full clockwise
 * */
extern void nxt_motor_set_power(nxt_motor_t *motor, int8_t power);

/**
 * Gets motor tacho count i.e. number of motor tacho ticks since last
 * tacho limit cycle (since last tacho handler call)
 * @param motor
 * @return
 */
extern uint32_t nxt_motor_get_tacho_count(nxt_motor_t *motor);

#endif /* NXT_MOTOR_H_ */

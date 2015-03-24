/**
 * @file
 * @brief IO interface of NXT AVR co-processor.
 *
 * @date 05.11.10
 * @author Anton Kozlov
 */

#ifndef NXT_AVR_H_
#define NXT_AVR_H_

#include <stdint.h>

#define NXT_AVR_ADDRESS 1
#define NXT_AVR_N_OUTPUTS 4
#define NXT_AVR_N_INPUTS  4

typedef struct {
	uint8_t power;
	uint8_t pwm_frequency;
	int8_t  output_percent[NXT_AVR_N_OUTPUTS];
	uint8_t output_mode;
	uint8_t input_power;
} __attribute__((packed)) to_avr_t;

typedef struct {
	uint16_t adc_value[NXT_AVR_N_INPUTS];
	uint16_t buttons_val;
	uint16_t extra;
	uint8_t  csum;
} __attribute__((packed)) from_avr_t;

#endif /* NXT_AVR_H_ */

/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    10.11.2014
 */

#ifndef LIBLEDDRV_LL_H_
#define LIBLEDDRV_LL_H_

#include "libleddrv.h"

extern void leddrv_ll_init(void);

extern void leddrv_ll_update(unsigned char leds_state[LEDDRV_LED_N]);

extern int leddrv_ll_error(int n);

#endif /* LIBLEDDRV_LL_H_ */

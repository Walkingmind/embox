/**
 * @file
 *
 * @date 24.10.10
 * @author Anton Kozlov
 */

#ifndef NXT_BUTTONS_H_
#define NXT_BUTTONS_H_

#include <types.h>

#define NXT_BT_ENTER 1
#define NXT_BT_LEFT 2
#define NXT_BT_RIGHT 4
#define NXT_BT_DOWN 8

typedef uint16_t nxt_buttons_mask_t;

/* Buttons pressed at now */
extern nxt_buttons_mask_t nxt_buttons_pushed(void);

/* Buttons was pressed since last call */
extern nxt_buttons_mask_t nxt_buttons_pressed(void);

#endif /* NXT_BUTTONS_H_ */

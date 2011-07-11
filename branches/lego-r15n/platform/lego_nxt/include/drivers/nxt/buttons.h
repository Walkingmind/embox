/**
 * @file buttons.h
 * @brief interface for on-brick buttons of nxt
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

/**
 * Buttons mask. Represents several buttons in time. E.g.
 * simultanious pressing BT_ENTER and BT_DOWN gives '9' value
 * (equals '1 | 8')
 */
typedef uint16_t nxt_buttons_mask_t;

/**
 * Gives buttons mask of currently pushed down buttons
 * @return mask of currently pushed buttons
 */
extern nxt_buttons_mask_t nxt_buttons_pushed(void);

/**
 * Gives buttons mask of pressed buttons since last call of
 * @link nxt_buttons_pressed @link
 * @return mask of pressed buttons since last call
 */
extern nxt_buttons_mask_t nxt_buttons_pressed(void);

#endif /* NXT_BUTTONS_H_ */

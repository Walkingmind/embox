/**
 * @file
 * @brief avr init test
 *
 * @date 16.10.10
 * @author Anton Kozlov
 */

#include <embox/unit.h>
#include <drivers/at91sam7s256.h>
#include <string.h>
#include <hal/reg.h>
#include <drivers/twi.h>
#include <unistd.h>
#include <kernel/timer.h>
#include <drivers/nxt_buttons.h>

EMBOX_UNIT_INIT(init);

void nxt_lcd_set_all_pixels_on(__u32 on);

const char avr_brainwash_string[] =
  "\xCC" "Let's samba nxt arm in arm, (c)LEGO System A/S";

static to_avr data_avr;
static from_avr data_from_avr;

#define DEL 20
static int old_state = 0;
static int state_count = DEL;
static int read_write = 0;

static int buttons_state = 0;
static int buttons_accum_state = 0;

/* Buttons pressed at now */
uint32_t nxt_buttons_are_pressed(void) {
	return buttons_state;
}
/* Buttons was pressed since last call */
uint32_t nxt_buttons_was_pressed(void) {
	uint32_t ret = buttons_accum_state;
	buttons_accum_state = 0;
	return ret;
}

static int translate_buttons(uint32_t buttons_val) {
	int ret = 0;
	if (buttons_val > 1500) {
		ret |= BT_ENTER;
		buttons_val -= 0x7ff;
	}

	if (buttons_val > 720) {
		ret |= BT_DOWN;
	} else if (buttons_val > 270) {
		ret |= BT_RIGHT;
	} else if (buttons_val > 60) {
		ret |= BT_LEFT;
	}

	return ret;
}

static uint32_t avr_handler(void) {
	int new_state = 0;
	if (read_write++ & 1) {
		twi_send(NXT_AVR_ADDRESS, (const uint8_t *) &data_avr, sizeof(data_avr));
	} else {
		twi_receive(NXT_AVR_ADDRESS, (uint8_t *) &data_from_avr, sizeof(data_from_avr));
		new_state = translate_buttons(data_from_avr.buttons_val);
		if (new_state == old_state) {
			if (!state_count) {
				if (new_state) { //button pressed
					//nxt_lcd_set_all_pixels_on(1);
					//switch_bank();
					buttons_state = new_state;
					buttons_accum_state |= new_state;
				}
			} else { 
				state_count--;
			}
		} else { 
			if (!state_count) { //button just released
				//nxt_lcd_set_all_pixels_on(0);
			}
			old_state = new_state;
			state_count = DEL;
		}
	}
	return 0;
}

static int init(void) {
	int result = 0;

	twi_init();
	twi_write(NXT_AVR_ADDRESS, (const uint8_t *) avr_brainwash_string, strlen(avr_brainwash_string));

	data_avr.power = 0;
	data_avr.pwm_frequency = 0;
	data_avr.output_mode = 0;
	data_avr.input_power = 0;
	
	set_timer(0, 1, (TIMER_FUNC) avr_handler);

	return result;
}

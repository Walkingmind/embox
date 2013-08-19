/**
 * @file
 * @brief Diag LCD output
 *
 * @date 7.06.10
 * @author Anton Kozlov
 */

#include <stdbool.h>
#include <drivers/nxt/lcd.h>
#include <drivers/diag.h>

static int nxt_lcd_diag_init(void *obj) {
	lcd_init();
	display_clear_screen();
	return 0;
}

static void nxt_lcd_diag_putc(void *obj, char ch) {
	display_char(ch);
}

DIAG_OPS_DECLARE(
		.init = nxt_lcd_diag_init,
		.putc = nxt_lcd_diag_putc,
);

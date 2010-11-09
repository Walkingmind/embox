/**
 * @file
 * @brief TODO
 *
 * @date 7.06.2010
 * @author Anton Kozlov 
 */

#include <types.h>

#include <kernel/diag.h>

void diag_init(void) {
	lcd_init();
}

char diag_getc(void) {
	/*getc cant be implemented */
	return '!';
}

void diag_putc(char ch) {
	display_char(ch);
}

int diag_has_symbol(void) {
	/* as no symbol can be obtained... */
#define DEBUG_GETC
	/*should be disabled in release for consistency */
#ifdef DEBUG_GETC
	return true;
#else 
	return false;
#endif
}

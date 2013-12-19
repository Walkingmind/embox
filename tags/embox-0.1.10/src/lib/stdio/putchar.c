/**
 * @file
 * @brief TODO
 *
 * @date 14.02.2010
 * @author Eldar Abusalimov
 */

#include <stdio.h>
#include <kernel/diag.h>
#include <drivers/vconsole.h>

#ifdef CONFIG_TTY_CONSOLE_COUNT
int putchar(int c) {
	static char prev = 0;

	if (c == '\n' && prev != '\r') {
		vconsole_putchar( cur_console, '\r');
	}
	vconsole_putchar( cur_console, (char) c);

	return (prev = c);
}
#else
int putchar(int c) {
	static char prev = 0;

	if (c == '\n' && prev != '\r') {
		diag_putc('\r');
	}
	diag_putc((char) c);

	return (prev = c);
}
#endif

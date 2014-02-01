/**
 * @file
 * @brief
 *
 * @date 10.11.10
 * @author Anton Bondarev
 */

#include <stdarg.h>
#include <stdio.h>
#include <prom/prom_printf.h>
#include <drivers/diag.h>

extern int __print(void(*printchar_handler)(char **str, int c), char **out,
		const char *format, va_list args);

static void printchar(char **str, int c) {
	if (str) {
		**str = c;
		++(*str);
	} else {
		static int prev = 0;
		if (c == '\n' && prev != '\r') {
			diag_putc('\r');
		}
		diag_putc((char) c);
		prev = c;
	}
}

int prom_printf(const char *format, ...) {
	int ret;
	va_list args;

	va_start(args, format);
	ret = prom_vprintf(format, args);
	va_end(args);

	return ret;
}

int prom_vprintf(const char *format, va_list args) {
	return __print(printchar, 0, format, args);
}

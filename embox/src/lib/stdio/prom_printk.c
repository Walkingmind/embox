/**
 * @file
 *
 * @brief
 *
 * @date 10.11.2010
 * @author Anton Bondarev
 */

#include <stdio.h>
#include <stdarg.h>
#include <types.h>

static void printchar(char **str, int c) {
	if (str) {
		**str = c;
		++(*str);
	} else {
		putchar(c);
	}
}


#include "print_impl.h"

int vprintf(const char *format, va_list args) {
	return print(0, format, args);
}

int vsprintf(char *out, const char *format, va_list args) {
	return print(&out, format, args);
}

int prom_printf(const char *format, ...) {
	int ret;
	va_list args;

	va_start(args, format);
	ret = print(0, format, args);
	va_end(args);

	return ret;
}


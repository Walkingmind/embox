/**
 * @file
 * @brief
 *
 * @date 10.11.10
 * @author Anton Bondarev
 */

#include <assert.h>
#include <drivers/iodev.h>
#include <stdarg.h>
#include <stdio.h>

#include "printf_impl.h"

static void iodev_printchar(struct printchar_handler_data *d, int c) {
	iodev_putc(c);
}

int printk(const char *format, ...) {
	int ret;
	va_list args;

	assert(format != NULL);

	va_start(args, format);
	ret = __print(iodev_printchar, NULL, format, args);
	va_end(args);

	return ret;
}

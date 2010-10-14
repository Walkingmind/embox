/*
 Copyright 2001, 2002 Georges Menie (www.menie.org)
 stdarg version contributed by Christian Ettinger

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 putchar is the only external dependency for this file,
 if you have a working putchar, leave it commented out.
 If not, uncomment the define below and
 replace outbyte(c) by your own function call.

 #define putchar(c) outbyte(c)
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

#define PAD_RIGHT 1
#define PAD_ZERO 2

static int prints(char **out, const char *string, int width, int pad) {
	/*TODO: optimizations needed to be enabled in gcc (-O2) to make register qualifier work*/
	/*register*/int pc = 0, padchar = ' ';

	if (width > 0) {
		/*register*/int len = 0;
		/*register*/
		const char *ptr;
		for (ptr = string; *ptr; ++ptr)
			++len;
		if (len >= width)
			width = 0;
		else
			width -= len;
		if (pad & PAD_ZERO)
			padchar = '0';
	}
	if (!(pad & PAD_RIGHT)) {
		for (; width > 0; --width) {
			printchar(out, padchar);
			++pc;
		}
	}
	for (; *string; ++string) {
		printchar(out, *string);
		++pc;
	}
	for (; width > 0; --width) {
		printchar(out, padchar);
		++pc;
	}

	return pc;
}

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12

static int printi(char **out, int i, int b, int sg, int width, int pad,
		int letbase) {
	char print_buf[PRINT_BUF_LEN];
	/*register*/
	char *s;
	/*register*/
	int t, neg = 0, pc = 0;
	/*register*/
	unsigned int u = i;

	if (i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return prints(out, print_buf, width, pad);
	}

	if (sg && b == 10 && i < 0) {
		neg = 1;
		u = -i;
	}

	s = print_buf + PRINT_BUF_LEN - 1;
	*s = '\0';

	while (u) {
		t = u % b;
		if (t >= 10)
			t += letbase - '0' - 10;
		*--s = t + '0';
		u /= b;
	}

	if (neg) {
		if (width && (pad & PAD_ZERO)) {
			printchar(out, '-');
			++pc;
			--width;
		} else {
			*--s = '-';
		}
	}

	return pc + prints(out, s, width, pad);
}

#define PRINTB_BUF_LEN 64

static int printb(char **out, int i, int width, int dot) {
	char print_buf[PRINTB_BUF_LEN];
	/*register*/
	char *s;
	/*register*/
	unsigned int u = i;
	/*register*/
	int k;
	/*register*/
	int dc = 0;

	s = print_buf + PRINTB_BUF_LEN - 1;
	*s = '\0';

	for (k = 0; k < width;) {
		*--s = ((u & 1) ? '1' : '0');
		u >>= 1;
		k++;

		if (dot && !(k & 0x03)) {
			*--s = ' ';
			dc++;
		}
	}
	if (*s == ' ') {
		++s;
		dc--;
	}
	return prints(out, s, width + dc, 0);
}

static int print(char **out, const char *format, va_list args) {
	/*register*/int width, pad;
	/*register*/
	int pc = 0;
	char scr[2];

	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			width = pad = 0;
			if (*format == '\0')
				break;
			if (*format == '%')
				goto out_print;
			if (*format == '-') {
				++format;
				pad = PAD_RIGHT;
			}
			while (*format == '0') {
				++format;
				pad |= PAD_ZERO;
			}
			for (; *format >= '0' && *format <= '9'; ++format) {
				width *= 10;
				width += *format - '0';
			}
			if (*format == 'l') {
				//TODO:
				++format;
			}
			switch (*format) {
			case 's': {
				char *s = (char *) va_arg( args, int );
				pc += prints(out, s ? s : "(null)", width, pad);
			}
				continue;
			case 'd':
				pc += printi(out, va_arg( args, int ), 10, 1, width, pad, 'a');
				continue;
			case 'x':
				pc += printi(out, va_arg( args, int ), 16, 0, width, pad, 'a');
				continue;
			case 'X':
				pc += printi(out, va_arg( args, int ), 16, 0, width, pad, 'A');
				continue;
			case 'u':
				pc += printi(out, va_arg( args, int ), 10, 0, width, pad, 'a');
				continue;
			case 'b':
				pc += printb(out, va_arg( args, int ), width, 0);
				continue;
			case 'B':
				pc += printb(out, va_arg( args, int ), width, 1);
				continue;
			case 'c':
				/* char are converted to int then pushed on the stack */
				scr[0] = (char) va_arg( args, int );
				scr[1] = '\0';
				pc += prints(out, scr, width, pad);
				continue;
			case 'p':
				/*TODO: printf haven't realized pointer variable operations*/
				continue;
			case 'f':
				/*TODO: printf haven't realized float variable operations*/
				continue;
			}
		} else {
			out_print: printchar(out, *format);
			++pc;
		}
	}
	if (out) {
		**out = '\0';
	}
	return pc;
}

int vprintf(const char *format, va_list args) {
	return print(0, format, args);
}

int vsprintf(char *out, const char *format, va_list args) {
	return print(&out, format, args);
}

int printf(const char *format, ...) {
	int ret;
	va_list args;

	va_start(args, format);
	ret = print(0, format, args);
	va_end(args);

	return ret;
}

int sprintf(char *out, const char *format, ...) {
	int ret;
	va_list args;

	va_start(args, format);
	ret = vsprintf(out, format, args);
	va_end(args);

	return ret;
}

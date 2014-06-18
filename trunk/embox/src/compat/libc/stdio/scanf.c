/**
 * @file
 * @brief Simple scanf implementation.
 *
 * @date 10.02.09
 * @author Alexandr Batyukov
 *          - Initial implementation
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <fs/file_operation.h>

FILE *file;

/*TODO: throw out.*/
/**
 * convert digit character to integer
 * @param digit character for converting
 * @param base for converting
 * @return converted symbol
 * @return -1 if error
 */
int ch_to_digit(char ch, int base) {
	ch = toupper(ch);
	switch (base) {
	case 16: {
		if (ch >= '0' && ch <= '9') {
			return (ch - '0');
		} else if (ch >= 'A' && ch <= 'F') {
			return (ch - 'A' + 0x0A);
		}
		return -1;
	}
	case 10: {
		if (ch >= '0' && ch <= '9') {
			return (ch - '0');
		}
		return -1;
	}
	case 8: {
		if (ch >= '0' && ch <= '7') {
			return (ch - '0');
		}
		return -1;
	}
	default:
		return -1;
	}
	return -1;
}

static void unscanchar(char **str, int ch) {
	/*	extern int ungetchar();*/
	if ((unsigned int) str >= 2) {
#if 1
		(*str) --;
		**str = ch;

		/*int *p;
		 p = *str - 4;
		 *p = ch;
		 *str = p;*/
#endif
	} else if ((int) str == 1) {
		ungetc(ch, file);
	} else {
		ungetchar(ch);
	}
}

static int scanchar(char **str) {
	extern int getchar(void);
	int ch;
	if ((unsigned int)str >= 2) {
		ch = **str;
		(*str)++;
		return ch;

	} else if ((int)str == 1) {
		return getc(file);
	} else {
		if ('\n' == (ch = getchar())) {
			return EOF;
		}
		return ch;
	}
}

static bool is_space(int ch) {
	if ((ch == ' ') || (ch == '\t') || (ch == '\n'))
		return true;
	return false;
}

static int trim_leading(char **str) {
	int ch;

	do {
		ch = scanchar(str);
		/*when break*/
		if (ch == EOF)
			break;
	} while (is_space(ch));

	unscanchar(str, ch);
	return ch;
}

static int scan_int(char **in, int base, int widht, int *res) {
	int neg = 0;
	int dst = 0;
	int ch;
	int i;
	int not_empty = 0;

	if (EOF == (ch = trim_leading(in))) {
		return EOF;
	}

	if ((ch == '-') || (ch == '+')) {
		neg = (ch == '-');
		scanchar(in);
	} else {
		dst = 0;
	}

	for (i = 0; (ch = (int) scanchar(in)) != EOF; i++) {
		if (!(base == 10 ? isdigit(ch) : isxdigit(ch)) || (0 == widht)) {
			unscanchar(in, ch);
			/*end conversion*/
			break;
		}
		not_empty = 1;
		dst = base * dst + ch_to_digit(ch, base);
//		ch = scanchar(in);
	}

	if (!not_empty) {
		return -1;
	}

	if (neg)
		dst = -dst;
	*res = dst;
	return 0;
}
#if 0
static double scan_double(char **in, int base, int width) {
	int neg = 0;
	double dst = 0;
	int ch;
	int i;

	trim_leading(in);

	for (i = 0; (ch = scanchar(in)) != EOF; i++) {
		if (i == 0 && (ch == '-' || ch == '+')) {
			neg = (ch == '-');
			continue;
		}

		if (!isdigit(ch)) {
			ungetchar(ch);
			break;
		}
		/*for different bases*/
		if (base >10)
		dst = dst * base + (ch - '0' - 7);
		else
		dst = dst * base + (ch - '0');
	}

	if (neg)
	dst = -dst;
	return dst;
}
#endif

#define OPS_LEN_MIN           0x00000040 /* s_char (d, i); u_char (u, o, x, X); s_char* (n) */
#define OPS_LEN_SHORT         0x00000080 /* short (d, i); u_short (u, o, x, X); short* (n) */
#define OPS_LEN_LONG          0x00000100 /* long (d, i); u_long (u, o, x, X); wint_t (c); wchar_t(s); long* (n) */
#define OPS_LEN_LONGLONG      0x00000200 /* llong (d, i); u_llong (u, o, x, X); llong* (n) */
#define OPS_LEN_MAX           0x00000400 /* intmax_t (d, i); uintmax_t (u, o, x, X); intmax_t* (n) */
#define OPS_LEN_SIZE          0x00000800 /* size_t (d, i, u, o, x, X); size_t* (n) */
#define OPS_LEN_PTRDIFF       0x00001000 /* ptrdiff_t (d, i, u, o, x, X); ptrdiff_t* (n) */
#define OPS_LEN_LONGFP        0x00002000 /* long double (f, F, e, E, g, G, a, A) */

static int scan(char **in, const char *fmt, va_list args) {
	int widht;
	int converted = 0;
	int ops_len;

	while (*fmt != '\0') {
		if (*fmt == '%') {
			fmt++;
			widht = 80;

			if (*fmt == '\0')
				break;

			if (isdigit((int) *fmt))
				widht = 0;

			while (isdigit((int) *fmt)) {

				widht = widht * 10 + (*fmt++ - '0');
			}

			ops_len = 0;
			switch (*fmt) {
			case 'h': ops_len = *++fmt != 'h' ? OPS_LEN_SHORT : (++fmt, OPS_LEN_MIN); break;
			case 'l': ops_len = *++fmt != 'l' ? OPS_LEN_LONG : (++fmt, OPS_LEN_LONGLONG); break;
			case 'j': ops_len = OPS_LEN_MAX; ++fmt; break;
			case 'z': ops_len = OPS_LEN_SIZE; ++fmt; break;
			case 't': ops_len = OPS_LEN_PTRDIFF; ++fmt; break;
			case 'L': ops_len = OPS_LEN_LONGFP; ++fmt; break;
			}
			if (*fmt == '\0')
				break;

			switch (*fmt) {
			case 's': {
				char *dst = va_arg(args, char*);
				int ch;
#if 0
				trim_leading(in);
#endif
				while (EOF != (ch = scanchar(in)) && widht--)
					*dst++ = (char) ch;
				*dst = '\0';

				++converted;
			}
				break;
			case 'c': {
				int dst;

#if 0
				trim_leading(in);
#endif
				dst = scanchar(in);
				*va_arg(args, char*) = dst;
				++converted;

			}
				break;
			case 'u': {
				int dst;
				if (0 != scan_int(in, 10, widht, &dst)) {
					goto out;
				}

				switch (ops_len) {
				default: /* FIXME */
					*va_arg(args, unsigned int*) = dst;
					break;
				case OPS_LEN_MIN:
					*va_arg(args, unsigned char*) = dst;
					break;
				case OPS_LEN_SHORT:
					*va_arg(args, unsigned short*) = dst;
					break;
				}
				
				++converted;
			}
				break;
			case 'f': /* TODO float scanf haven't realized */
			case 'd': {
				int dst;
				if (0 != scan_int(in, 10, widht, &dst)) {
					goto out;
				}

				switch (ops_len) {
				default: /* FIXME */
					memcpy(va_arg(args, int*), &dst, sizeof(dst));
					break;
				case OPS_LEN_MIN:
					*va_arg(args, char*) = dst;
					break;
				case OPS_LEN_SHORT:
					*va_arg(args, short*) = dst;
					break;
				}
				
				++converted;
			}
				break;
#if 0
			case 'D': {
					double dst;
					dst = scan_double(in,10,widht);
					*va_arg(args, int*) = dst;
					++converted;
				}
				break;
#endif
			case 'o': {
				int dst;
				if (0 != scan_int(in, 8, widht, &dst)) {
					goto out;
				}

				*va_arg(args, int*) = dst;

				++converted;
			}
				break;
#if 0
			case 'O': {
				double dst;
				dst = scan_double(in,8,widht);
				va_arg(args, int) = dst;
				++converted;
			}
				break;
#endif
			case 'x': {
				int dst;
				if (0 != scan_int(in, 16, widht, &dst)) {
					goto out;
				}
				*va_arg(args, int*) = dst;

				++converted;
			}
				break;
#if 0
			case 'X': {
				double dst;
				dst = scan_double(in, 16, widht);
				va_arg(args, int) = dst;
				++converted;
			}
				break;
#endif
			}
			fmt++;
		} else {
			if (*fmt++ != *(*in)++) {
				return converted;
			}
		}
	}

out:
	return converted;
}

int scanf(const char *format, ...) {
	va_list args;
	int rv;

	va_start(args, format);
	rv = scan(0, format, args);
	va_end(args);

	return rv;
}

int fscanf(FILE *stream, const char *format, ...) {
	va_list args;
	int rv;

	file = stream;

	va_start(args, format);
	rv = scan((char **)1, format, args);
	va_end(args);

	return rv;
}
int sscanf(const char *out, const char *format, ...) {
	va_list args;
	int rv;

	va_start(args, format);
	rv = scan((/*FIXME*/char**)&out, format, args);
	va_end (args);

	return rv;
}

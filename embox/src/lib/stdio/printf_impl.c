/**
 * @file
 * @brief
 *
 * @date 19.11.10
 * @author Anton Bondarev
 * @author Ilia Vaprol
 */

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * Format specifiers
 */
#define OPS_FLAG_LEFT_ALIGN   0x00000001 /* left alignment */
#define OPS_FLAG_WITH_SIGN    0x00000002 /* print sign */
#define OPS_FLAG_EXTRA_SPACE  0x00000004 /* add extra space before digit */
#define OPS_FLAG_WITH_SPEC    0x00000008 /* print a prefix for non-decimal systems */
#define OPS_FLAG_ZERO_PAD     0x00000010 /* padding with zeroes */
#define OPS_PREC_IS_GIVEN     0x00000020 /* precision is specified */
#define OPS_LEN_MIN           0x00000040 /* s_char (d, i); u_char (u, o, x, X); s_char* (n) */
#define OPS_LEN_SHORT         0x00000080 /* short (d, i); u_short (u, o, x, X); short* (n) */
#define OPS_LEN_LONG          0x00000100 /* long (d, i); u_long (u, o, x, X); wint_t (c); wchar_t(s); long* (n) */
#define OPS_LEN_LONGLONG      0x00000200 /* llong (d, i); u_llong (u, o, x, X); llong* (n) */
#define OPS_LEN_MAX           0x00000400 /* intmax_t (d, i); uintmax_t (u, o, x, X); intmax_t* (n) */
#define OPS_LEN_SIZE          0x00000800 /* size_t (d, i, u, o, x, X); size_t* (n) */
#define OPS_LEN_PTRDIFF       0x00001000 /* ptrdiff_t (d, i, u, o, x, X); ptrdiff_t* (n) */
#define OPS_LEN_LONGFP        0x00002000 /* long double (f, F, e, E, g, G, a, A) */
#define OPS_SPEC_UPPER_CASE   0x00004000 /* specifier is tall */
#define OPS_SPEC_IS_SIGNED    0x00008000 /* specifier is signed */
#define OPS_SPEC_WITH_EXP     0x00010000 /* use scientific notation */
//#define OPS_SPEC_IS_SHORTENED 0x00010000 /* specifier has shortened form */

/**
 * Options for print_s
 */
#define PRINT_S_NULL_STR "(null)" /* default value of NULL */

/**
 * Options for print_i
 */
#define PRINT_I_BUFF_SZ 23 /* size of buffer for long long int (64bit) -- that's enough for oct, dec and hex base systems */

/**
 * Options for print_f
 */
#define PRINT_F_BUFF_SZ        65 /* size of buffer for long double -- FIXME this may not be enough */
//#define PRINT_F_PREC_SHORTENED 4 /* shortened precision for real numbers */
#define PRINT_F_PREC_DEFAULT   6 /* default precision for real numbers */

struct printchar_handler_data;

static int print_s(void (*printchar_handler)(struct printchar_handler_data *d, int c),
		struct printchar_handler_data *printchar_data,
		const char *str, int width, int max_len, unsigned int ops) {
	int pc, len, space_count;

	assert(printchar_handler != NULL);
	assert(str != NULL);
	assert(width >= 0);
	assert(max_len >= 0);

	pc = 0;
	len = strlen(str);
	max_len = max_len ? max_len : len;
	len = min(max_len, len);
	space_count = width > len ? width - len : 0;

	if (!(ops & OPS_FLAG_LEFT_ALIGN)) {
		pc += space_count;
		for (; space_count; --space_count) printchar_handler(printchar_data, ' ');
	}

	pc += len;
	while (len--) printchar_handler(printchar_data, *str++);

	pc += space_count;
	while (space_count--) printchar_handler(printchar_data, ' ');

	return pc;
}

static int print_i(void (*printchar_handler)(struct printchar_handler_data *d, int c),
		struct printchar_handler_data *printchar_data, unsigned long long int u,
		int width, int min_len, unsigned int ops, int base) {
	char buff[PRINT_I_BUFF_SZ], *str, *end, *prefix;
	int pc, ch, len, prefix_len, zero_count, space_count, letbase;

	assert(printchar_handler != NULL);
	assert(width >= 0);
	assert(min_len >= 0);

	str = end = &buff[0] + sizeof buff / sizeof buff[0] - 1;
	*end = '\0';
	prefix = (ops & OPS_SPEC_IS_SIGNED) && ((long long int)u < 0) ? u = -u, "-"
			: (ops & OPS_SPEC_IS_SIGNED) && (ops & OPS_FLAG_WITH_SIGN) ? "+"
			: (ops & OPS_SPEC_IS_SIGNED) && (ops & OPS_FLAG_EXTRA_SPACE) ? " "
			: (base == 8) && (ops & OPS_FLAG_WITH_SPEC) ? "0"
			: (base == 16) && (ops & OPS_FLAG_WITH_SPEC)
				? ops & OPS_SPEC_UPPER_CASE ? "0X" : "0x"
			: "";
	pc = 0;
	prefix_len = strlen(prefix);
	letbase = ops & OPS_SPEC_UPPER_CASE ? 'A' : 'a';

	do {
		ch = u % base;
		if (ch >= 10) ch += letbase - 10 - '0';
		*--str = ch + '0';
		u /= base;
	} while (u);

	len = end - str;
	zero_count = (len < min_len ? min_len : (ops & OPS_FLAG_ZERO_PAD)
			&& !(ops & OPS_FLAG_LEFT_ALIGN) ? width : 0) - len - prefix_len;
	zero_count = max(zero_count, 0);
	space_count = width - len - prefix_len - zero_count;
	space_count = max(space_count, 0);

	if (!(ops & OPS_FLAG_LEFT_ALIGN)) {
		pc += space_count;
		for (; space_count; --space_count) printchar_handler(printchar_data, ' ');
	}

	pc += prefix_len;
	while (prefix_len--) printchar_handler(printchar_data, *prefix++);

	pc += zero_count;
	while (zero_count--) printchar_handler(printchar_data, '0');

	pc += len;
	while (len--) printchar_handler(printchar_data, *str++);

	pc += space_count;
	while (space_count--) printchar_handler(printchar_data, ' ');

	return pc;
}

static int print_f(void (*printchar_handler)(struct printchar_handler_data *d, int c),
		struct printchar_handler_data *printchar_data, double r, int width,
		int precision, unsigned int ops, int base) {
	char buff[PRINT_F_BUFF_SZ], *str, *end, *prefix/*, *postfix*/;
	double ip, fp/*, ep*/;
	int pc, i, ch, len, prefix_len/*, postfix_len*/, pad_count, letbase;

	assert(printchar_handler != NULL);
	assert(width >= 0);
	assert(precision >= 0);

	str = end = &buff[0] + sizeof buff / sizeof buff[0] - 1;
	*end = '\0';
	prefix = signbit(r) ? (r = -r, base == 16)
				? ops & OPS_SPEC_UPPER_CASE ? "-0X" : "-0x"
				: "-"
			: ops & OPS_FLAG_WITH_SIGN ? base == 16
				? ops & OPS_SPEC_UPPER_CASE ? "+0X" : "+0x"
				: "+"
			: ops & OPS_FLAG_EXTRA_SPACE ? base == 16
				? ops & OPS_SPEC_UPPER_CASE ? " 0X" : " 0x"
				: " "
			: base == 16 ? ops & OPS_SPEC_UPPER_CASE ? "0X" : "0x"
			: "";
	i = pc = 0;
	prefix_len = strlen(prefix);
	letbase = ops & OPS_SPEC_UPPER_CASE ? 'A' : 'a';
	precision = ops & OPS_PREC_IS_GIVEN ? precision : PRINT_F_PREC_DEFAULT;

	fp = modf(r, &ip);
    for (; (i < precision) && (fmod(fp, 1.0) != 0.0); ++i) fp *= base;
	fp = round(fp);
	ip = precision ? (fp != pow((double)base, (double)i) ? ip : ip + 1.0) : round(r);
	fp = fp != pow((double)base, (double)i) ? fp : 0.0;

	for (; i; --i) {
		ch = (int)(fmod(fp, (double)base) * base);
		if (ch >= 10) ch += letbase - 10 - '0';
		*--str = ch + '0';
		modf(fp / base, &fp);
	}

	if (precision || (ops & OPS_FLAG_WITH_SPEC)) {
		*--str = '.';
	}

	do {
		ch = (int)(fmod(ip, (double)base) * base);
		if (ch >= 10) ch += letbase - 10 - '0';
		*--str = ch + '0';
		modf(ip / base, &ip);
	} while (ip != 0.0);

	len = end - str;
	pad_count = prefix_len + len < width ? width - prefix_len - len : 0;

	if (!(ops & (OPS_FLAG_ZERO_PAD | OPS_FLAG_LEFT_ALIGN))) {
		pc += pad_count;
		while (pad_count--) printchar_handler(printchar_data, ' ');
	}

	pc += prefix_len;
	while (prefix_len--) printchar_handler(printchar_data, *prefix++);

	if (ops & OPS_FLAG_ZERO_PAD) {
		pc += pad_count;
		while (pad_count--) printchar_handler(printchar_data, '0');
	}

	pc += len;
	while (len--) printchar_handler(printchar_data, *str++);

	if (ops & OPS_FLAG_LEFT_ALIGN) {
		pc += pad_count;
		while (pad_count--) printchar_handler(printchar_data, ' ');
	}

	return pc;
}

int __print(void (*printchar_handler)(struct printchar_handler_data *d, int c),
		struct printchar_handler_data *printchar_data,
		const char *format, va_list args) {
	int pc, width, precision;
	unsigned int ops;
	union {
		void *vp;
		char ca[2];
		char *cp;
		unsigned long long int ulli;
		long double ld;
	} tmp;

	assert(printchar_handler != NULL);
	assert(format != NULL);

	pc = 0;

	for (; *format; ++format) {
		/**
		 * %[flags][width][.precision][length]specifier
		 */

		/* check first symbol */
		if (*format != '%') {
single_print:
			printchar_handler(printchar_data, *format);
			++pc;
			continue;
		}
		
		ops = 0;

		/* get flags */
		while (*++format) {
			switch (*format) {
			default: goto after_flags;
			case '-': ops |= OPS_FLAG_LEFT_ALIGN; break;
			case '+': ops |= OPS_FLAG_WITH_SIGN; break;
			case ' ': ops |= OPS_FLAG_EXTRA_SPACE; break;
			case '#': ops |= OPS_FLAG_WITH_SPEC; break;
			case '0': ops |= OPS_FLAG_ZERO_PAD; break;
			}
		}
after_flags:

		/* get width */
		if (*format == '*') { width = va_arg(args, int); ++format; }
		else { width = atoi(format); while (isdigit(*format)) ++format; }
		width = max(width, 0);

		/* get precision */
		ops |= *format == '.' ? OPS_PREC_IS_GIVEN : 0;
		if ((*format == '.') && (*++format == '*')) { precision = va_arg(args, int); ++format; }
		else { precision = atoi(format); while (isdigit(*format)) ++format; }
		precision = precision >= 0 ? precision : (ops &= ~OPS_PREC_IS_GIVEN, 0);

		/* get length */
		switch (*format) {
		case 'h': ops |= *++format != 'h' ? OPS_LEN_MIN : (++format, OPS_LEN_SHORT); break;
		case 'l': ops |= *++format != 'l' ? OPS_LEN_LONG : (++format, OPS_LEN_LONGLONG); break;
		case 'j': ops |= OPS_LEN_MAX; ++format; break;
		case 'z': ops |= OPS_LEN_SIZE; ++format; break;
		case 't': ops |= OPS_LEN_PTRDIFF; ++format; break;
		case 'L': ops |= OPS_LEN_LONGFP; ++format; break;
		}

		/* handle specifier */
		ops |= isupper(*format) ? OPS_SPEC_UPPER_CASE : 0;
		switch (*format) {
		case '%': goto single_print;
		case 'd':
		case 'i':
			tmp.ulli = ops & OPS_LEN_MIN ? (signed char)va_arg(args, int)
					: ops & OPS_LEN_SHORT ? (short int)va_arg(args, int)
					: ops & OPS_LEN_LONG ? va_arg(args, long int)
					: ops & OPS_LEN_LONGLONG ? va_arg(args, long long int)
					: ops & OPS_LEN_MAX ? va_arg(args, intmax_t)
					: ops & OPS_LEN_SIZE ? va_arg(args, ssize_t)
					: ops & OPS_LEN_PTRDIFF ? va_arg(args, ptrdiff_t)
					: va_arg(args, int);
			pc += print_i(printchar_handler, printchar_data, tmp.ulli, width,
					precision, ops | OPS_SPEC_IS_SIGNED, 10);
			break;
		case 'u':
		case 'o':
		case 'x':
		case 'X':
			tmp.ulli = ops & OPS_LEN_MIN ? (unsigned char)va_arg(args, unsigned int)
					: ops & OPS_LEN_SHORT ? (unsigned short int)va_arg(args, unsigned int)
					: ops & OPS_LEN_LONG ? va_arg(args, unsigned long int)
					: ops & OPS_LEN_LONGLONG ? va_arg(args, unsigned long long int)
					: ops & OPS_LEN_MAX ? va_arg(args, uintmax_t)
					: ops & OPS_LEN_SIZE ? va_arg(args, size_t)
					: ops & OPS_LEN_PTRDIFF ? va_arg(args, ptrdiff_t)
					: va_arg(args, unsigned int);
			pc += print_i(printchar_handler, printchar_data, tmp.ulli, width,
					precision, ops,
					*format == 'u' ? 10 : (*format == 'o' ? 8 : 16));
			break;
		case 'f':
		case 'F':
		case 'e':
		case 'E':
//		case 'g':
//		case 'G':
//		case 'a': // TODO
//		case 'A':
			/* TODO handle (ops & OPS_LEN_LONGFP) for long double */
			if (ops & OPS_LEN_LONGFP) goto single_print; /* TODO long double support */
			tmp.ld = ops & OPS_LEN_LONGFP ? va_arg(args, long double)
					: va_arg(args, double);
			pc += print_f(printchar_handler, printchar_data, (double)tmp.ld,
					width, precision,
					ops | (tolower(*format) == 'e' ? OPS_SPEC_WITH_EXP : 0), 10);
			break;
		case 'c':
			/* TODO handle (ops & OPS_LEN_LONG) for wint_t */
			tmp.ca[0] = (char)va_arg(args, int);
			tmp.ca[1] = '\0';
			pc += print_s(printchar_handler, printchar_data, &tmp.ca[0],
					width, precision, ops);
			break;
		case 's':
			/* TODO handle (ops & OPS_LEN_LONG) for wchar_t* */
			tmp.cp = va_arg(args, char *);
			pc += print_s(printchar_handler, printchar_data,
					tmp.cp ? tmp.cp : PRINT_S_NULL_STR, width, precision, ops);
			break;
		case 'p':
			tmp.vp = va_arg(args, void *);
			pc += print_i(printchar_handler, printchar_data, (size_t)tmp.vp,
					width, sizeof tmp.vp * 2 + 2,
					ops | (OPS_FLAG_WITH_SPEC | OPS_FLAG_ZERO_PAD), 16);
			break;
		case 'n':
			if (ops & OPS_LEN_MIN) *va_arg(args, signed char *) = (signed char)pc;
			else if (ops & OPS_LEN_SHORT) *va_arg(args, short int *) = (short int)pc;
			else if (ops & OPS_LEN_LONG) *va_arg(args, long int *) = (long int)pc;
			else if (ops & OPS_LEN_LONGLONG) *va_arg(args, long long int *) = (long long int)pc;
			else if (ops & OPS_LEN_MAX) *va_arg(args, intmax_t *) = (intmax_t)pc;
			else if (ops & OPS_LEN_SIZE) *va_arg(args, size_t *) = (size_t)pc;
			else if (ops & OPS_LEN_PTRDIFF) *va_arg(args, ptrdiff_t *) = (ptrdiff_t)pc;
			else *va_arg(args, int *) = pc;
			break;
		}
	}

	return pc;
}

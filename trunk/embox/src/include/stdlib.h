/**
 * @file
 * @brief ISO C99 Standard: 7.20 General utilities.
 * @details Contains declarations for many standard functions.
 *
 * @date 20.11.09
 * @author Nikolay Korotky
 *          - Initial implementation
 * @author Eldar Abusalimov
 *          - Extracting minimal used subset
 *          - Docs
 */

#ifndef STDLIB_H_
#define STDLIB_H_

#include <stddef.h>
#include <sys/wait.h>

/**
 * Converts the initial part of the string in @a nptr to a long integer value
 * according to the given @a base, which must be between 2 and 36 inclusive,
 * or be the special value 0.
 *
 * The remainder of the string is converted to a @code long int @endcode value
 * in the obvious manner, stopping at the first character which is not a valid
 * digit in the given @a base.
 *
 * @param nptr
 *   The string to parse. It may begin with an arbitrary amount of white space
 *   (determined by #isspace()) followed by a single optional '+' or '-' sign.
 *   The string is interpreted until the first invalid character is
 *   encountered.
 * @param endptr
 *   If @a endptr is not @c NULL, the address of the first invalid character is
 *   stored in @c *endptr.
 * @param base
 *   The base of interpreted number.
 *   If @a base is zero or 16, the string may include a @c 0x prefix, and the
 *   number will be read in base 16 (hex).
 *   Otherwise, a zero base is taken as 10 (decimal) unless the next character
 *   is @c '0', in which case it is taken as 8 (octal).
 * @return
 *   The parsed number bounded to @code [LONG_MIN..LONG_MAX] @endcode or zero
 *   if there were no valid characters representing a number in the given
 *   @a base.
 */
extern long int strtol(const char *nptr, char **endptr, int base);
extern unsigned long int strtoul(const char *nptr, char **endptr, int base);

extern double strtod(const char *nptr, char **endptr);

/** Allocate and free dynamic memory */
extern void *calloc(size_t nmemb, size_t size);
extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *realloc(void *ptr, size_t size);

#endif /* STDLIB_H_ */

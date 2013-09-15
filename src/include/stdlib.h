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

#include <defines/size_t.h>
#include <defines/wchar_t.h>

/* In addition, the following symbolic names and macros shall be defined as in
 * <sys/wait.h> , for use in decoding the return value from system():
 */
#include <sys/wait.h>

typedef struct ldiv {
   long int quot;
   long int rem;
} ldiv_t;

typedef struct div {
   int quot;
   int rem;
} div_t;

#include <sys/cdefs.h>
__BEGIN_DECLS

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

/**
 * Convert integer to string.
 * Converts an integer value to a null-terminated string using the specified base and stores the result in the array given by buf parameter.
 * If num < 0, the resulting string is preceded with '-' (regardless of base). No prefix is used to explicitly specify the base.
 * @param num Number to convert.
 * @param buf Character array to store the result. This should be long enough to contain any possible value.
 * @param base Base for the conversion. 1 < base < 37.
 * @return Pointer to buf.
 */
extern char *itoa( int num, char *buf, unsigned short int base );

/* Allocate and free dynamic memory */
extern void *calloc(size_t nmemb, size_t size);
extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *realloc(void *ptr, size_t size);
extern void *memalign(size_t boundary, size_t size);


extern void qsort(void *base, size_t nmemb, size_t size,
		int(*compar)(const void *, const void *));

extern void *bsearch(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));

/** Find the smallest element, greater or equals to specified. */
extern void *lower_bound(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));

/** Find the smallest element, strictly greater than specified. */
extern void *upper_bound(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));


extern int rand(void);
extern int rand_r(unsigned int *seedp);
extern void srand(unsigned int seed);

extern long int random(void);
extern void srandom(unsigned int seed);
extern char *initstate(unsigned int seed, char *state, size_t n);
extern char *setstate(char *state);

/* glibc extention */
#include <stdint.h>
struct random_data
  {
    int32_t *fptr;		/* Front pointer.  */
    int32_t *rptr;		/* Rear pointer.  */
    int32_t *state;		/* Array of state values.  */
    int rand_type;		/* Type of random number generator.  */
    int rand_deg;		/* Degree of random number generator.  */
    int rand_sep;		/* Distance between front and rear.  */
    int32_t *end_ptr;		/* Pointer behind state table.  */
  };

extern int random_r(struct random_data *buf, int32_t *result);
extern int srandom_r(unsigned int seed, struct random_data *buf);
extern int initstate_r(unsigned int seed, char *statebuf,
                       size_t statelen, struct random_data *buf);
extern int setstate_r(char *statebuf, struct random_data *buf);

extern ldiv_t ldiv(long num, long denom);
extern div_t div(int num, int denom);

//FIXME atof atoi and so on
extern double atof(const char *nptr);
extern int atoi(const char *nptr);
extern long atol(const char *nptr);
extern long long atoll(const char *nptr);
extern long long atoq(const char *nptr);
extern double strtod(const char *nptr, char **endptr);
extern float strtof(const char *nptr, char **endptr);
extern long double strtold(const char *nptr, char **endptr);
extern void abort(void);

#define EXIT_FAILURE 0
#define EXIT_SUCCESS 1
extern void exit(int status);

/**
 * Returns the absolute value of an argument. If the argument is not negative,
 * the argument is returned. If the argument is negative, the negation of the
 * argument is returned.
 *
 * @param x the argument whose absolute value is to be determined
 *
 * @return the absolute value of the argument
 */
static inline int abs(int x) { return x < 0 ? -x : x; } // TODO move from here
static inline long labs(long x) { return x < 0 ? -x : x; }


extern char * getenv(const char *name);
extern int putenv(char *string);
extern int setenv(const char *envname, const char *envval, int overwrite);
extern int unsetenv(const char *name);
extern int clearenv(void);
extern int system(const char *command);

static inline int mkstemp(char *path_template) { return -1; }
static inline int mbtowc(wchar_t *pwc, const char *s, size_t n) { return 0; }
static inline int wctomb(char *s, wchar_t wchar) { return 0; }

__END_DECLS

#endif /* STDLIB_H_ */

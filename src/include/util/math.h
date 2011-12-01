/**
 * @file
 * @brief Basic numeric operations
 *
 * @date 04.06.10
 * @author Eldar Abusalimov
 */

#ifndef UTIL_MATH_H_
#define UTIL_MATH_H_

#include __impl_x(util/math_impl.h)

/**
 * Returns the absolute value of an argument. If the argument is not negative,
 * the argument is returned. If the argument is negative, the negation of the
 * argument is returned.
 *
 * @param x the argument whose absolute value is to be determined
 *
 * @return the absolute value of the argument
 */
#define abs(x) __abs(x)

/**
 * Returns the greater of two values.
 *
 * @param a an argument
 * @param b another argument
 *
 * @return the larger of @c a and @c b
 */
#define min(a, b) __min(a, b)

/**
 * Returns the smaller of two values.
 *
 * @param a an argument
 * @param b another argument
 *
 * @return the smaller of @c a and @c b
 */
#define max(a, b) __max(a, b)

/**
 * Limits value to the specified boundary.
 *
 * @param val value to be clamped
 * @param lo lower bound
 * @param hi upper bound
 *
 * @return clamped value
 * @retval @c lo if @c val is less than @c lo
 * @retval @c hi if @c val is greater than @c hi
 * @retval @c val otherwise
 */
#define clamp(val, lo, hi) __clamp(val, lo, hi)

/**
 * First 1 in val
 * @param val Value
 * @return Number of first 1 in Value
 */
static inline int blog2(int val);

extern double floor(double x);
extern float floorf(float x);
extern long double floorl(long double x);

extern double pow(double x, double y);
extern float powf(float x, float y);
extern long double powl(long double x, long double y);

#endif /* UTIL_MATH_H_ */

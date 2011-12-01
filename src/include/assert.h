/**
 * @file
 * @brief ISO C99 Standard: 7.2 Diagnostics.
 * @details Provides #assert() macro definition
 *          which is used in debugging purposes.
 *
 * @date 25.11.09
 * @author Eldar Abusalimov
 */

#ifndef ASSERT_H_
#define ASSERT_H_

#include __impl_x(lib/assert_impl.h)

/**
 * If @a condition expression evaluates to @c 0 (@c false), then
 * @link #panic() @endlink function is called with the message containing the
 * expression, source code filename, and line number as its argument.
 *
 * If the identifier NDEBUG ("no debug") is defined with
 * @code #define NDEBUG @endcode then the macro @c assert does nothing.
 *
 * @param condition
 *   The expression being asserted.
 * @param message
 *   Optional message in @c printf format.
 */
#define assert(condition, message...) \
	  __assert(condition, #condition, message)

/* Hide assert internals from CDT macro expansion and code formatter. */
#ifdef __CDT_PARSER__
# undef assert
/* Actually assert is a macro, but it is hidden from Eclipse CDT macro
 * expansion. Check assert_impl.h for the details. */
extern void assert(int condition, ...);
#endif /* __CDT_PARSER__ */

#endif /* ASSERT_H_ */

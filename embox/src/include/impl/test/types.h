/**
 * @file
 * @brief Type declarations shared between test framework and each test suite.
 *
 * @date 11.06.2010
 * @author Eldar Abusalimov
 */

#ifndef IMPL_TEST_TYPES_H_
#define IMPL_TEST_TYPES_H_

#include <util/location.h>

/**
 * Each test case implements this interface.
 *
 * @return the test result
 * @retval 0 on success
 * @retval nonzero on failure
 */
typedef int(*test_run_t)(void);

struct __test_private;
struct test_case;

struct test {
	/** @c NULL terminated array of pointers to test cases. */
	const struct test_case **test_cases;
	/** The corresponding mod. */
	const struct mod *mod;
	/** One-line human readable description of the whole test suite. */
	const char *description;
	/** Internal data managed by framework. */
	struct __test_private *private;
};

struct test_case {
	/** The test itself. */
	test_run_t run;
	/** One-line human readable description of the test case. */
	const char *description;
	/** Location of the test case function definition within the file. */
	struct location location;
};

struct __test_private {
	int result;
};

#endif /* IMPL_TEST_TYPES_H_ */

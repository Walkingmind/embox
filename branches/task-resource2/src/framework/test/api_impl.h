/**
 * @file
 * @brief Test foreach iteration macro and inline versions of some methods from
 *        test registry.
 *
 * @date 11.06.10
 * @author Eldar Abusalimov
 */

#ifndef FRAMEWORK_TEST_API_IMPL_H_
#define FRAMEWORK_TEST_API_IMPL_H_

#include <stddef.h>

#include <util/array.h>
#include <framework/mod/api.h>

#include "types.h"

#define __test_foreach(test_ptr) \
	array_spread_foreach_ptr(test_ptr, __test_registry)

ARRAY_SPREAD_DECLARE(const struct test_suite, __test_registry);

static inline const char *test_name(const struct test_suite *test) {
	return NULL != test ? test->mod->name : NULL;
}

static inline const char *test_package(const struct test_suite *test) {
	return NULL != test ? test->mod->package->name : NULL;
}

#endif /* FRAMEWORK_TEST_API_IMPL_H_ */

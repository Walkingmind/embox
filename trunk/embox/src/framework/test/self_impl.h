/**
 * @file
 * @brief Hidden implementations of test registration macros.
 *
 * @date 12.06.2010
 * @author Eldar Abusalimov
 */

#ifndef FRAMEWORK_TEST_SELF_IMPL_H_
#define FRAMEWORK_TEST_SELF_IMPL_H_

#include <stddef.h>

#include <util/array.h>
#include <util/macro.h>
#include <util/location.h>
#include <framework/mod/self.h>

#include "types.h"

#define __EMBOX_TEST_SUITE(description) \
	__EMBOX_TEST_SUITE_NM("" description, MACRO_GUARD(__test_suite), \
			MACRO_GUARD(__test_private))

#define __EMBOX_TEST_SUITE_NM(_description, test_suite_nm, test_private_nm) \
	extern const struct test_suite __test_registry[];                   \
	extern const struct mod_ops __test_mod_ops;                   \
	ARRAY_SPREAD_DEF_TERMINATED(static const  struct test_case *, \
			__TEST_CASES_ARRAY, NULL);                            \
	static struct __test_private test_private_nm;                 \
	ARRAY_SPREAD_ADD_NAMED(__test_registry, test_suite_nm, {      \
			.private = &test_private_nm,                          \
			.test_cases = __TEST_CASES_ARRAY,                     \
			.mod = &mod_self,                                     \
			.description = _description,                          \
		});                                                       \
	MOD_SELF_BIND(test_suite_nm, &__test_mod_ops)

#define __TEST_CASE(description) \
	__TEST_CASE_NM("" description, MACRO_GUARD(__test_case), \
			MACRO_GUARD(__test_case_run))

#define __TEST_CASE_NM(_description, test_case_nm, run_nm) \
	static int run_nm(void);                             \
	static const struct test_case test_case_nm = {       \
		.run = run_nm,                                   \
		.location = LOCATION_INIT,                       \
		.description = _description,                     \
	};                                                   \
	extern const struct test_case *__TEST_CASES_ARRAY[]; \
	ARRAY_SPREAD_ADD(__TEST_CASES_ARRAY, &test_case_nm); \
	static int run_nm(void)

#define __TEST_CASES_ARRAY \
	MACRO_CONCAT(__test_cases__,__EMBUILD_MOD__)

/* This is implemented on top of test suite and test case. */
#define __EMBOX_TEST(_run) \
	__EMBOX_TEST_SUITE("generic test suite"); \
	__TEST_CASE_NM("generic test case", MACRO_GUARD(__test_case), _run)

#endif /* FRAMEWORK_TEST_SELF_IMPL_H_ */

/**
 * @file
 * @brief Common array utilities and diffuse arrays.
 * @details
 *     <b>Diffuse array</b> is statically allocated array, which is initialized
 * (populated) in multiple compilation units. In other words you can define the
 * array itself in one unit and add elements to it in another unit. Except for
 * the way of definition and initialization, diffuse array is usual array, so
 * it can be declared and used at run time in regular manner.
 *
 *     Just alike for usual arrays there are two general approaches for
 * iterating over (or determining size of) diffuse array.
 *  - At compile time using the array name. See #ARRAY_DIFFUSE_SIZE().
 *  - At run time for those array which has a special element at the end of
 * array so-called terminator element (e.g. @c NULL). See
 * #ARRAY_DIFFUSE_DEF_TERMINATED().
 *
 *     Considering current use cases and some implementation issues, diffuse
 * arrays are always allocated in read-only data section as if you have defined
 * a regular array with @c const modifier (although you might not have to). To
 * prevent confusion and to take advantage of compiler type checking always
 * include @c const modifier when defining diffuse array with
 * #ARRAY_DIFFUSE_DEF() and its derivatives or when declaring it using
 * @c extern.
 *
 * @date 13.06.2010
 * @author Eldar Abusalimov
 */

#ifndef UTIL_ARRAY_H_
#define UTIL_ARRAY_H_

#include <impl/util/array.h>

/**
 * Defines a new diffuse array.
 *
 * @param element_type
 *   The type of array elements with optional modifiers.
 *   To control the scope of array definition the standard visibility modifiers
 *   may be used. Thus, without any modifier the array is defined in the global
 *   scope and could be referenced inside other compilation units.
 *   @c static modifier forces the array to be defined in the file scope
 *   and prevents any global symbol to be emitted to the resulting object.
 *   Static diffuse array cannot be referenced outside the definition file, but
 *   it remains accessible from other compilation units for elements addition
 *   using #ARRAY_DIFFUSE_ADD() macro and its @link #ARRAY_DIFFUSE_ADD_NAMED
 *   named derivative @endlink.
 *   Do not forget to specify @c const modifier explicitly (see general docs).
 * @param name
 *   The array name which is used to refer the array itself and to populate it
 *   using #ARRAY_DIFFUSE_ADD().
 *
 * @note
 *   This command should be used in the file scope, outside of any block.
 * @note
 *   The @a element_type must include @c const modifier (see general docs).
 */
#define ARRAY_DIFFUSE_DEF(element_type, name) \
		__ARRAY_DIFFUSE_DEF(element_type, name)

/**
 * Defines a new diffuse array ended up by the specified @a terminator element.
 *
 * @param element_type
 *   The type of array elements with optional modifiers.
 * @param name
 *   The array name which is used to refer the array itself and to populate it
 *   using #ARRAY_DIFFUSE_ADD().
 * @param terminator
 *   An element indicating the array end (e.g. @c NULL pointer).
 *
 * @note
 *   This command should be used in the file scope, outside of any block.
 * @note
 *   The @a element_type must include @c const modifier (see general docs).
 *
 * @see ARRAY_DIFFUSE_DEF()
 *   More detailed explanation of macro arguments.
 */
#define ARRAY_DIFFUSE_DEF_TERMINATED(element_type, name, terminator) \
		__ARRAY_DIFFUSE_DEF_TERMINATED(element_type, name, terminator)

/**
 * Adds elements to the specified diffuse array.
 *
 * @param array_name
 *   The name of the diffuse array to which to add elements.
 * @param ...
 *   The elements to add.
 *
 * @note
 *   This command should be used in the file scope, outside of any block.
 */
#define ARRAY_DIFFUSE_ADD(array_name, ...) \
		__ARRAY_DIFFUSE_ADD(array_name, __VA_ARGS__)

/**
 * Does the same as #ARRAY_DIFFUSE_ADD() but also puts a pointer to head of the
 * added sub-array into a variable with the specified name.
 *
 * @param array_name
 *   The name of the diffuse array to which to add elements.
 * @param ptr_name
 *   The variable name used to refer to the added sub-array.
 * @param ...
 *   The elements to add.
 *
 * @note
 *   This command should be used in the file scope, outside of any block.
 */
#define ARRAY_DIFFUSE_ADD_NAMED(array_name, ptr_name, ...) \
		__ARRAY_DIFFUSE_ADD_NAMED(array_name, ptr_name, __VA_ARGS__)

/**
 * Gets the length of the specified diffuse array.
 *
 * @param array_name
 *   The array to check size for (must be a literal symbol).
 * @return
 *   Actual number of array elements including terminator element (if any).
 */
#define ARRAY_DIFFUSE_SIZE(array_name) \
		__ARRAY_DIFFUSE_SIZE(array_name)

/**
 * Gets the length of the specified diffuse array without taking into an
 * account a terminator element (if any).
 *
 * @param array_name
 *   The array to check size for (must be a literal symbol).
 * @return
 *   Number of array elements except terminating (if any). If the target array
 *   is not terminated then the result is the same as of #ARRAY_DIFFUSE_SIZE().
 */
#define ARRAY_DIFFUSE_SIZE_IGNORE_TERMINATING(array_name) \
		__ARRAY_DIFFUSE_SIZE_IGNORE_TERMINATING(array_name)

/**
 * Gets the length of the specified array.
 * The macro can be used only if the array length is known at the compile-time.
 *
 * @param array
 *   The array to check size for.
 * @return
 *   Number of array elements.
 *
 * @note
 *   The array must be statically defined/declared, otherwise an incorrect
 *   result is returned without any error or warning.
 */
#define ARRAY_SIZE(array) \
		__ARRAY_SIZE(array)

#define array_foreach(element, array, size) \
		__array_foreach(element, array, size)

#define array_terminated_foreach(element, array, terminator) \
		__array_terminated_foreach(element, array, terminator)

#define array_static_foreach(element, array) \
		__array_static_foreach(element, array)

#define array_diffuse_foreach(element, array) \
		__array_diffuse_foreach(element, array)

#define array_cond_foreach(element, array, condition) \
		__array_cond_foreach(element, array, condition)

#define array_foreach_ptr(element, array, size) \
		__array_foreach_ptr(element, array, size)

#define array_static_foreach_ptr(element, array) \
		__array_static_foreach_ptr(element, array)

#define array_diffuse_foreach_ptr(element, array) \
		__array_diffuse_foreach_ptr(element, array)

#define array_cond_foreach_ptr(element, array, condition) \
		__array_cond_foreach_ptr(element, array, condition)

#endif /* UTIL_ARRAY_H_ */

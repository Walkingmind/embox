/**
 * @file
 * @brief EMBuild-side binding interface.
 *
 * @date 12.06.10
 * @author Eldar Abusalimov
 */

#ifndef FRAMEWORK_MOD_EMBUILD_H_
#define FRAMEWORK_MOD_EMBUILD_H_

#include __impl_x(framework/mod/embuild_impl.h)

/**
 * Defines a new mod. For the new mod the @link #mod corresponding @endlink
 * structure is allocated. Also two section-driven arrays are defined for the
 * mod#provides and mod#requires lists.
 *
 * @param mod_package_nm
 *   The package variable name used in #MOD_PACKAGE_DEF().
 * @param mod_nm
 *   The last fragment of module name (without package).
 *
 * @note
 *   The variable name is computed as mod_package_nm##__##mod_nm and used to:
 *    - define dependencies with #MOD_DEP_DEF(),
 *    - refer the mod inside those compilation units that bind mod-specific
 *      @link #mod_info information @endlink using #MOD_INFO_BIND() or define
 *      members with #MOD_MEMBER_BIND().
 *   For the code generated by EMBuild this argument is the same as provided
 *   by the @c __EMBUILD_MOD__ macro for each mod at compilation time.
 */
#define MOD_DEF(mod_package_nm, mod_nm) \
	  __MOD_DEF(mod_package_nm ## __ ## mod_nm, mod_package_nm, #mod_nm)

/**
 * Cmd-specific definitions.
 *
 * @param mod_nm
 * @param name
 *   A string with command name.
 * @param brief
 *   A one-line string containing brief description.
 * @param details
 *   A string with detailed description.
 */
#define MOD_CMD_DEF(mod_nm, name, brief, details) \
	  __MOD_CMD_DEF(mod_nm, name, brief, details)

/**
 * App-specific definitions.
 * @param mod_nm
 */
#define MOD_APP_DEF(mod_nm) \
	  __MOD_APP_DEF(mod_nm)

/**
 * Defines a new dependency between two specified modules.
 *
 * @param mod_nm
 *   Symbol name of the module which depends on @a dep_nm.
 * @param dep_nm
 *   Symbol name of the module on which @a mod_nm depends.
 */
#define MOD_DEP_DEF(mod_nm, dep_nm) \
	  __MOD_DEP_DEF(mod_nm, dep_nm)

#define MOD_CONTENTS_DEF(mod_nm, content_nm) \
	  __MOD_CONTENTS_DEF(mod_nm, content_nm)
/**
 * Defines new after-loading dependency of modules
 * @param mod_nm
 *   Symbol name of the module after which @a dep_nm
 *   should be loaded
 * @param dep_nm
 *   Symbol name of the module that should be loaded
 *   after @a mod_nm
 */
#define MOD_AFTER_DEP_DEF(mod_nm, dep_nm) \
	  __MOD_AFTER_DEP_DEF(mod_nm, dep_nm)

/**
 * Defines a new package.
 *
 * @param package_nm
 *   Variable name to use.
 * @param name
 *   A string containing the package name.
 */
#define MOD_PACKAGE_DEF(package_nm, name) \
	  __MOD_PACKAGE_DEF(package_nm, name)

#endif /* FRAMEWORK_MOD_EMBUILD_H_ */
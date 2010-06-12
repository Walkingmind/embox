/**
 * @file
 * @brief EMBOX dependency injection framework.
 *
 * @date 22.02.2010
 * @author Eldar Abusalimov
 */

#ifndef EMBOX_MOD_H_
#define EMBOX_MOD_H_

#include <stdbool.h>
#include <stddef.h>

#include <impl/embox/mod.h>

/**
 * Pointer to the #mod structure defined with #MOD_DEF() macro.
 *
 * @param s_mod the mod variable name used at definition time.
 */
#define MOD_PTR(s_mod) \
		__MOD_PTR(s_mod)

/**
 * Pointer to the #mod_tag structure defined with #MOD_TAG_DEF() macro.
 *
 * @param s_tag the mod_tag variable name used at definition time.
 */
#define MOD_TAG_PTR(s_tag) \
		__MOD_TAG_PTR(s_tag)

/**
 * Defines a new mod. For the new mod the @link #mod corresponding @endlink
 * structure is allocated. Also two section-driven arrays are defined for the
 * mod#provides and mod#requires lists.
 *
 * @param s_mod the variable name used later to access the mod structure
 *        with #MOD_PTR(), to define dependencies with #MOD_DEP_DEF(), or to
 *        bind mod-specific @link #mod_info information @endlink using
 *        #MOD_INFO_DEF() macro and its derivatives. For the code generated by
 *        EMBuild this argument must be the same as provided by the
 *        __EMBUILD_MOD__ macro for each mod at compilation time
 * @param s_mod_package the package variable name used in #MOD_PACKAGE_DEF()
 * @param mod_name a string containing the mod name. The name of the current
 *        mod (referenced by __EMBUILD_MOD__) can accessed at compilation time
 *        using #MOD_SELF_NAME macro
 */
#define MOD_DEF(s_mod, s_mod_package, mod_name) \
		__MOD_DEF(s_mod, s_mod_package, mod_name)

/**
 * Defines a new tag by allocating the @link #mod_tag corresponding @endlink
 * structure and a section-driven array for the list of the tagged mods.
 *
 * @param s_tag the variable name used later to access the tag structure
 *        with #MOD_TAG_PTR() and to bind the tag with a particular mod using
 *        #MOD_INFO_TAGGED_DEF() macro
 * @param tag_name a string containing the tag name
 */
#define MOD_TAG_DEF(s_tag, tag_name) \
		__MOD_TAG_DEF(s_tag, tag_name)

/**
 * Associates data and operations with the mod specified by @c s_mod argument.
 *
 * @param s_mod symbol name of the module
 * @param mod_data pointer to the module specific data (if any)
 * @param mod_ops pointer to the #mod_ops structure (if any)
 */
#define MOD_INFO_DEF(s_mod, mod_data, mod_ops) \
		__MOD_INFO_DEF(s_mod, mod_data, mod_ops)

/**
 * Does the same as #MOD_INFO_DEF() and also tags the current mod with the
 * specified tag.
 *
 * @param s_mod symbol name of the module
 * @param mod_data pointer to the module specific data (if any)
 * @param mod_ops pointer to the #mod_ops structure (if any)
 * @param s_tag symbol name of the tag defined with #MOD_TAG_DEF() macro
 */
#define MOD_INFO_TAGGED_DEF(s_mod, mod_data, mod_ops, s_tag) \
		__MOD_INFO_TAGGED_DEF(s_mod, mod_data, mod_ops, s_tag)

/**
 * Defines a new dependency between two specified modules.
 *
 * @param s_mod symbol name of the module which depends on @c s_dep
 * @param s_dep symbol name of the module on which @c s_mod depends
 */
#define MOD_DEP_DEF(s_mod, s_dep) \
		__MOD_DEP_DEF(s_mod, s_dep)

/**
 * Defines a new package.
 *
 * @param s_package the variable name
 * @param package_name a string containing the package name
 */
#define MOD_PACKAGE_DEF(s_package, package_name) \
		__MOD_PACKAGE_DEF(s_package, package_name)

/**
 * Pointer to the #mod structure of the module associated with current
 * compilation unit.
 *
 * @see MOD_PTR()
 */
#define MOD_SELF_PTR  __MOD_SELF_PTR

/**
 * String containing the name of the current module.
 */
#define MOD_SELF_NAME __MOD_SELF_NAME

/**
 * Associates the specified mod data and operations with the current mod.
 *
 * @param _mod_data pointer to the module specific data (if any)
 * @param _mod_ops pointer to the #mod_ops structure (if any)
 *
 * @see MOD_INFO_DEF()
 */
#define MOD_SELF_INFO_DEF(_mod_data, _mod_ops) \
		__MOD_SELF_INFO_DEF(_mod_data, _mod_ops)

/**
 * Defines the mod interface as #MOD_SELF_INFO_DEF() does and also tags the
 * current mod with the specified tag.
 *
 * @param _mod_data pointer to the module specific data (if any)
 * @param _mod_ops pointer to the #mod_ops structure (if any)
 * @param s_tag symbol name of the tag defined with #MOD_TAG_DEF() macro
 *
 * @see MOD_INFO_TAGGED_DEF()
 */
#define MOD_SELF_INFO_TAGGED_DEF(_mod_data, _mod_ops, s_tag) \
		__MOD_SELF_INFO_TAGGED_DEF(_mod_data, _mod_ops, s_tag)

/**
 * Defines a new dependency between the current module and the one specified by
 * @c s_dep argument.
 *
 * @param s_dep symbol name of the module on which the current one depends
 *
 * @see MOD_DEP_DEF()
 */
#define MOD_SELF_DEP_DEF(s_dep) \
		__MOD_SELF_DEP_DEF(s_dep)

/*
 * Here go various structure and type definitions and public methods
 * prototypes.
 */

struct mod;
struct mod_package;
struct mod_ops;
struct mod_info;
struct mod_tag;
struct mod_private;

/**
 * Performs an operation with the module. The semantics of the operation is
 * module-specific. If the module has no operation assigned (#mod_ops structure
 * contains @c NULL pointer fields), the meaning is that module operation
 * always succeeds (as if the corresponding function returns 0).
 *
 * @param self pointer to the #mod struct.
 * @return error code
 * @retval 0 if operation succeeds
 * @retval nonzero on error
 */
typedef int (*mod_op_t)(struct mod *self);

/**
 * The main mod operation. The semantics of the operation is module-specific.
 * Mods framework does not use this method nor its return value. Please note
 * that framework also does not track the current state of the mod or its
 * dependencies, so the mod should check its state by itself.
 *
 * The caller should use #mod_invoke() function instead of directly accessing
 * the corresponding field of the #mod_ops structure.
 *
 * @param self pointer to the #mod struct.
 * @param data optional argument
 * @return operation result
 */
typedef int (*mod_invoke_t)(struct mod *self, void *data);

/**
 * TODO Module info emitted by EMBuild dependency injection model generator.
 */
struct mod {
	/** Internal data needed by dependency resolver. */
	struct mod_private *private;
	/** (optional) Interface with mods framework and others. */
	struct mod_info *info;
	/** Module package assigned by EMBuild. */
	struct mod_package *package;
	/** Module name assigned by EMBuild. */
	const char *name;
	/** Null-terminated array containing dependency info. */
	struct mod **requires, **provides;
};

/**
 * Mods framework manages each mod through a special interface so-called
 * @c mod_info.
 */
struct mod_info {
	/** (optional) Module specific data. */
	void *data;
	/** (optional) Available operations. */
	struct mod_ops *ops;
	/** (optional) Mod tag. */
	struct mod_tag *tag;
};

/**
 * Each mod can have an optional tag. Tag is used to group similar mods, e.g.
 * which are managed by the same framework. Tag has no special meaning for the
 * mods framework.
 */
struct mod_tag {
	/** (optional) Tag name. */
	const char *name;
	/** Null-terminated array of tagged mods. */
	struct mod **mods;
};

struct mod_package {
	const char *name;
};

/**
 * Module operations.
 * @note Do not call these functions directly!
 */
struct mod_ops {
	/** (optional) Module state change operation. */
	mod_op_t enable, disable;
	/** (optional) Module main method. */
	mod_invoke_t invoke;
};

struct mod_private {
	unsigned int flags;
};

/**
 * Used to iterate over various mod lists.
 */
struct mod_iterator {
	struct mod **p_mod;
};
/**
 * The special package which may be used for pseudo-mods defined by other
 * frameworks.
 */
__MOD_PACKAGE_DECL(generic);

/**
 * Enables the specified mod resolving its dependencies. This implies that all
 * the mods on which the given one depends will also be enabled.
 * If the mod has already been enabled then nothing special is done and this
 * function returns zero.
 *
 * @param mod the mod to enable
 * @return operation result
 * @retval 0 if the mod has been successfully enabled
 * @retval -EINVAL if the argument is @c NULL
 * @retval -EINTR if an error has occurred while enabling the mod or one of
 *         its dependencies
 */
extern int mod_enable(const struct mod *mod);

/**
 * Disables the specified mod resolving its dependencies. This implies that all
 * the mods which depend on the given one will also be disabled.
 * If the mod has not been enabled yet then nothing special is done and this
 * function returns zero.
 *
 * @param mod the mod to disable
 * @return operation result
 * @retval 0 if the mod has been successfully disabled
 * @retval -EINVAL if the argument is @c NULL
 * @retval -EINTR if an error has occurred while disabling the mod or one of
 *         its dependencies
 */
extern int mod_disable(const struct mod *mod);

/**
 * The weak version of #mod_enable().
 * Enables the specified mod if and only if all the mods on which the given one
 * depends are also enabled. If the mod has already been enabled then nothing
 * special is done and the function returns zero.
 *
 * @param mod the mod to enable
 * @return operation result
 * @retval 0 if the mod has been successfully enabled
 * @retval -EINVAL if the argument is @c NULL
 * @retval -EBUSY if the mod cannot be enabled at the moment because of
 *         unsatisfied dependencies
 * @retval -EINTR if an error has occurred while enabling the mod
 */
extern int mod_enable_nodep(const struct mod *mod);

/**
 * The weak version of #mod_disable().
 * Disables the specified mod if and only if all the mods which depend on the
 * given one are also disabled. If the mod has not been enabled yet then
 * nothing special is done and the function returns zero.
 *
 * @param mod the mod to disable
 * @return operation result
 * @retval 0 if the mod has been successfully disabled
 * @retval -EINVAL if the argument is @c NULL
 * @retval -EBUSY if the mod cannot be disabled at the moment because of
 *         unsatisfied dependencies
 * @retval -EINTR if an error has occurred while disabling the mod
 */
extern int mod_disable_nodep(const struct mod *mod);

/**
 * Invokes the module if it has provided the corresponding operation.
 * Please note that framework does not track the current state of the mod or
 * its dependencies, this means that the mod will be invoked even if it is not
 * enabled now.
 *
 * @param mod the mod on which to call @link mod_ops#invoke @endlink method
 * @param data optional argument to pass to the @c invoke method
 * @return invocation result
 * @retval -EINVAL if the @c mod argument is @c NULL
 * @retval -ENOTSUP if the mod does not support invoke method
 */
extern int mod_invoke(const struct mod *mod, void *data);

/**
 * Tells whether the specified mod is enabled or not.
 *
 * @param mod the mod to check
 * @return the running status of the mod
 * @retval true if the mod is enabled
 * @retval false if argument is @c NULL or mod is disabled
 */
extern bool mod_is_running(const struct mod *mod);

/**
 * Gets the data associated with the specified mod (if any).
 *
 * @param mod the mod which's data to get
 * @return the mod data
 */
extern void *mod_data(const struct mod *mod);

/**
 * Gets the list of mods on which the specified one depends.
 *
 * @param mod the target mod
 * @param iterator pointer to the #mod_iterator structure instance
 * @return iterator over the list of mod dependencies
 * @retval the value passed as the @c iterator argument
 * @retval NULL if one or more arguments is @c NULL
 */
extern struct mod_iterator *mod_requires(const struct mod *mod,
		struct mod_iterator *iterator);

/**
 * Gets the list of mods which depend on the specified one.
 *
 * @param mod the target mod
 * @param iterator pointer to the #mod_iterator structure instance
 * @return iterator over the list of requested mods
 * @retval the value passed as the @c iterator argument
 * @retval NULL if one or more arguments is @c NULL
 */
extern struct mod_iterator *mod_provides(const struct mod *mod,
		struct mod_iterator *iterator);

/**
 * Gets the list of mods which are tagged by the specified tag.
 *
 * @param tag the target tag
 * @param iterator pointer to the #mod_iterator structure instance
 * @return iterator over the list of tagged mods
 * @retval the value passed as the @c iterator argument
 * @retval NULL if one or more arguments is @c NULL
 */
extern struct mod_iterator *mod_tagged(const struct mod_tag *tag,
		struct mod_iterator *iterator);

/**
 * Retrieves the next mod in the iteration (if any).
 *
 * @param iterator the iterator over the list of mods
 * @return the next element in the iteration
 * @retval the next #mod instance if such exists
 * @retval NULL if argument is @c NULL or iteration has no more elements
 */
extern struct mod *mod_iterator_next(struct mod_iterator *iterator);

/**
 * Tells whether the iteration has more elements.
 *
 * @param iterator the iterator over the list of mods
 * @return the check result
 * @retval true if the iterator has more elements
 * @retval false if argument is @c NULL or iteration has no more elements
 */
extern bool mod_iterator_has_next(struct mod_iterator *iterator);

#if 0
/* TODO there is no way to implement these functions at now. -- Eldar */

/**
 * Sets the mod-specific data.
 *
 * @param mod the mod which's data to get
 * @param data the data to associate with the mod
 */
extern void mod_data_set(const struct mod *mod, void *data);

/**
 * Gets the #mod_ops of the specified mod.
 *
 * @param mod the mod which's ops to get
 * @return the mod operations structure
 */
extern struct mod_ops *mod_ops_get(const struct mod *mod);

/**
 * Sets the mod-specific data.
 *
 * @param mod the mod which's data to get
 * @param ops the data to associate with the mod
 */
extern void mod_ops_set(const struct mod *mod, struct mod_ops *ops);
#endif

#endif /* EMBOX_MOD_H_ */

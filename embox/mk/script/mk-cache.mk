# $Id$
#
#   Date: Jan 25, 2012
# Author: Eldar Abusalimov
#

.PHONY : all
all :
	@#

include mk/script/check-make-flags.mk

ifndef CACHE_INCLUDES
$(error CACHE_INCLUDES is not defined, nothing to cache)
endif
CACHE_REQUIRES ?=

# Flatten.
override CACHE_INCLUDES := $(CACHE_INCLUDES)
override CACHE_REQUIRES := $(CACHE_REQUIRES)

#
# Define a rule to generate a file with Make dependencies.
#

ifdef CACHE_DEP_TARGET

override CACHE_DEP_TARGET := $(CACHE_DEP_TARGET)

CACHE_DEP_FILE ?= $(CACHE_DEP_TARGET).d
override CACHE_DEP_FILE   := $(CACHE_DEP_FILE)

.PHONY : $(CACHE_DEP_FILE)
all : $(CACHE_DEP_FILE)

# The 'MAKEFILE_LIST' inside the recipe will be expanded after including
# all needed Makefiles, so its value will be valid.
$(CACHE_DEP_FILE) :
	@printf '$(CACHE_DEP_TARGET):' > $@
	@for dep in $(MAKEFILE_LIST); \
		do printf ' \\\n\t%s' "$$dep" >> $@; done
	@printf '\n' >> $@
	@for dep in $(MAKEFILE_LIST); \
		do printf '\n%s:\n' "$$dep" >> $@; done

endif

include mk/core/common.mk

# Forces certain variables to be dumped unconditionally, even if some of them
# has been already defined before including scripts listed in 'CACHE_INCLUDES'
# (i.e., as part of 'CACHE_REQUIRES').
# Usually, volatiles are different counters and lists. Moreover, they _are_
# assumed to be a list, that is whitespaces in their values are considered
# insingnificant.
# The current implementation also restricts volatile variable to be simple.
__cache_volatile :=

# Variables listed here are only initialized to an empty string.
# Usually, transients are temporary variables.
__cache_transient :=

__cache_preinclude_variables :=
__cache_postinclude_variables :=

# Remove ourselves from the list of used scripts.
MAKEFILE_LIST :=

# Include scripts which should not be cached...
$(foreach __cache_include,$(CACHE_REQUIRES), \
	$(eval include $(filter-out $(MAKEFILE_LIST),$(__cache_include))))

# Save volatile state.
$(foreach v,__cache_volatile $(filter $(__cache_volatile),$(.VARIABLES)), \
	${eval __cache_volatile_variable_$$v := $$(value $$v)})

# Collect variables...
__cache_preinclude_variables := $(.VARIABLES)
$(foreach __cache_include,$(CACHE_INCLUDES), \
	$(eval include $(filter-out $(MAKEFILE_LIST),$(__cache_include))))
__cache_postinclude_variables := $(.VARIABLES)

MAKEFILE_LIST := $(sort $(MAKEFILE_LIST))

__cache_volatile := $(strip $(__cache_volatile))
__cache_transient := $(strip $(__cache_transient))

#
# Now define some internally used functions.
#

# Yeah, 'filter-out' is evil because some variables contain percent sign.
# But nobody cares...
__cache_new_variables := \
	$(filter-out \
		$(__cache_preinclude_variables), \
		$(__cache_postinclude_variables))

# No args.
__cache_print_new_variable_definitions = \
	$(foreach 1,$(call __cache_sort,$(filter-out \
			$(__cache_volatile) $(__cache_transient), \
			$(__cache_new_variables))), \
		$(__cache_print_variable_definition))

# No args.
__cache_print_transient_variable_definitions = \
	$(call __cache_print_variable_definition,__cache_transient) \
	$(foreach 1,$(call __cache_sort,$(filter \
			$(__cache_transient), \
			$(__cache_new_variables))), \
		$(info $(__cache_escape_variable_name) \
			$(if $(findstring simple,$(flavor $1)),:)= ))
# No args.
__cache_print_volatile_variable_definitions = \
	$(foreach 1,__cache_volatile \
			$(call __cache_sort,$(filter \
				$(__cache_volatile), \
				$(.VARIABLES))), \
		$(__cache_print_volatile_variable_definition))

# Arg 1: variable name.
# TODO insert accumulation check.
__cache_print_volatile_variable_definition = \
	$(if $(findstring u,$(flavor $1)), \
		$(error Volatile variable '$1' is $(flavor $1), must be simple)) \
	$(if $(or $(findstring undefined,$(flavor __cache_volatile_variable_$1)), \
			$(word $(words x $(__cache_volatile_variable_$1)),$($1))), \
		$(info $(__cache_escape_variable_name) \
			$(if $(findstring undefined, \
					$(flavor __cache_volatile_variable_$1)),:=,+=) \
			$(patsubst %,\$(\n)$(\t)%, \
				$(wordlist \
					$(words x $(value __cache_volatile_variable_$1)), \
					$(words $($1)), \
						$(subst $(\h),$$(\h),$(subst $$,$$$$,$($1)))))))

# Arg 1: list of variables.
__cache_sort = \
	$(foreach v, \
		$(sort $(join $(patsubst [%],%_,$(subst _,,$(1:%=[%]))),$1)) \
		,$(subst [$v]$(firstword $(subst _,_ ,$v)),,[$v]$v))
#	$(sort $1)# Uncomment for simple lexicographical sort.
#	$1# Or for no sort at all.

# Arg 1: variable name.
__cache_print_variable_definition = \
	$(info $(__cache_construct_$(if \
		$(findstring $(\h),$(subst $(\n),$(\h),$(value $1))) \
			,verbose,regular)_$(flavor $1)_variable))

#
# __cache_construct_xxx
#

__cache_construct_regular_simple_variable = \
	$(__cache_escape_variable_name) := \
		$(if $(__cache_variable_has_leading_ws),$$(\0))$(subst $$,$$$$,$($1))

__cache_construct_regular_recursive_variable = \
	$(if $(__cache_variable_has_leading_ws) \
		,$(__cache_construct_verbose_recursive_variable),$(__cache_escape_variable_name) \
			= $(value $1))

__cache_construct_verbose_recursive_variable = \
	define $(__cache_escape_variable_name)$(\n)$(value $1)$(\n)endef

__cache_construct_verbose_simple_variable = \
	$(__cache_construct_verbose_recursive_variable)$(\n)$(__cache_escape_variable_name) \
		:= $$(value $(__cache_escape_variable_name))

__cache_construct_regular_undefined_variable = $(__cache_error_undefined)
__cache_construct_verbose_undefined_variable = $(__cache_error_undefined)

__cache_error_undefined = \
	$(error Undefined variable '$1' listed in '.VARIABLES')

__cache_escape_variable_name = \
	$(subst $(=),$$(=),$(subst $(:),$$(:),$(subst $(\h),$$(\h),$(subst $$,$$$$,$1))))
__cache_variable_has_leading_ws = \
	$(subst x$(firstword $(value $1)),,$(firstword x$(value $1)))

__cache_print_requires_inclusions = \
	$(foreach mk, \
		mk/core/common.mk $(filter-out mk/core/common.mk,$(CACHE_REQUIRES)), \
		$(info include $$(filter-out $$(MAKEFILE_LIST),$(mk))))

__cache_print_list_comment = \
	$(info $(\h) $1:) \
	$(foreach mk,$(or $($1),<nothing>),$(info $(\h)   $(mk)))

#
# And, finally, print everything out.
#

$(info # Generated by GNU Make $(MAKE_VERSION) on $(shell date).)
$(info )
$(call __cache_print_list_comment,CACHE_REQUIRES)
$(call __cache_print_list_comment,CACHE_INCLUDES)
$(call __cache_print_list_comment,MAKEFILE_LIST)
$(info )
ifdef CACHE_DEP_TARGET
$(info ifneq ($$(word 2,$$(filter $(CACHE_DEP_TARGET),$$(MAKEFILE_LIST))),))
$(info $$(error Multiple inclusion of '$(CACHE_DEP_TARGET)'))
$(info endif)
$(info )
endif
$(__cache_print_requires_inclusions)
$(info )
$(info # Transient variables.)
$(__cache_print_transient_variable_definitions)
$(info )
$(info # Volatiles variables.)
$(__cache_print_volatile_variable_definitions)
$(info )
$(info # New variables.)
$(__cache_print_new_variable_definitions)
$(info )


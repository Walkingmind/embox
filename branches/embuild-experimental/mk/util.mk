# $Id$
#
# Some useful stuff lives here.
#
# Author: Eldar Abusalimov
#

ifndef _util_mk_
_util_mk_ := 1

include gmsl.mk

empty:=#

define \n


endef
\n := $(\n)

escape = $(call assert_called,escape,$0)$(call dollar_encode,$1)

dollar_encode = $(call assert_called,dollar_encode,$0)$(subst $$,$$$$,$1)
dollar_decode = $(call assert_called,dollar_decode,$0)$(subst $$$$,$$,$1)

##
# The last word of the MAKEFILE_LIST variable.
# Actual only until another makefile is included.
self_makefile = $(abspath $(lastword $(MAKEFILE_LIST)))

##
# Expands to empty string for the first time, and to 'true' for subsequent
# invocations. Should be used before any include directives.
#
# Thus, the typical usage of this function is:
#
#    ifndef $(already_included)
#      ...
#    endif #$(already_included)
#
already_included = \
  $(or $(call get,included,$(self_makefile)), \
       $(call set,included,$(self_makefile),true))

called = $()$(call seq,$1,$2)

##
# Can be used to check whether the variable is expanded using call or not.
#
# For example:
#   func = $(call assert_called,func,$0) Use input args, e.g. $1, $2 or $3
#   $(call func,foo,bar,baz) expands to "Use input args, e.g. foo, bar or baz"
#   but plain $(func) expansion produces an assertion failure.
#
# Usage: $(call assert_called,var_name,$0)
#
ifeq (0,1)
assert_called = $(strip \
  $(call __assert_called,assert_called,$0) \
  $(call __assert_called,$1,$2) \
)

__assert_called = $(call assert \
  ,$(call seq,$1,$2),$1 must be call'ed$(if $1, (last call'ed variable is $2)))
else
assert_called :=
assert:=
endif

args_nr = $(foreach __args_nr_i,1,$(__args_nr))
__args_nr = \
  $(if $(filter-out undefined,$(origin $(__args_nr_i))), \
    $(foreach __args_nr_i,$(call inc,$(__args_nr_i)),$(__args_nr)), \
    $(__args_nr_i) \
  )

sequence = $(if $(call lt,$1,$2) \
  ,$(call __sequence_inc,$1,$2),$(call __sequence_dec,$2,$1))
__sequence_inc = $1$(if $(call lt,$1,$2),$(call $0, $(call inc,$1),$2))
__sequence_dec = $(if $(call lt,$1,$2),$(call $0,$(call inc,$1) ,$2))$1

expand_once   = $(call expand_once_0,$1)
__expand_once_def_all = \
  $(foreach x,$(call sequence,0,9),$(eval $(value __expand_once_def_x)))
define __expand_once_def_x
  expand_once_$x = $(foreach total_args,$x,$(__expand_once))
endef

$(__expand_once_def_all)

# Do not call. Pass number of args through total_args variable.
__expand_once = $(strip \
  $(call assert_called,expand_once_$(total_args),$0) \
  $(call assert,$(call eq,$(words $1),1),Invalid name of variable being expanded) \
  $(if $(filter undefined,$(origin $(__expansion_name))),$(eval \
       $(value __expansion_name) := $$(call $(__expansion_args)) \
  )) \
)$($(__expansion_name))
# XXX may be encode $(value __expansion_name) inside eval ? -- Eldar
 
__expansion_arg_nrs = $(call sequence,1,$(call inc,$(total_args)))
__expansion_escape_arg = $(call dollar_encode,$($(arg_nr)))

__expansion_args = $(call split,_$$$$$$_,$(call merge,$(true:%=,), \
  $(foreach arg_nr,$(__expansion_arg_nrs), \
    $(call merge,_$$$$$$_,$(__expansion_escape_arg)) \
  ) \
))

__expansion_name = __expansion_of_$1_$$__$(strip $(call merge \
  ,_$$$$$$_, \
  $(foreach arg_nr,$(__expansion_arg_nrs) \
    ,$(call merge,_$$_,$(__expansion_escape_arg))) \
))


# ----------------------------------------------------------------------------
# Function:  put
# Arguments: 1: Name of associative array
#            2: The key value to associate
#            3: The value associated with the key
# Returns:   None
# ----------------------------------------------------------------------------
map_put = $(strip \
  $(call assert_called,map_put,$0) \
  $(__map_args_check) \
  $(call var_assign_simple,$(__map_entry),$3) \
)

# ----------------------------------------------------------------------------
# Function:  get
# Arguments: 1: Name of associative array
#            2: The key to retrieve
# Returns:   The value stored in the array for that key
# ----------------------------------------------------------------------------
map_get = $(strip \
  $(call assert_called,map_get,$0) \
  $(__map_args_check) \
  $(if $(filter-out undefined,$(origin $(__map_entry))),$($(__map_entry))) \
)

# ----------------------------------------------------------------------------
# Function:  XXX
# Arguments: 1: Name of associative array
#            2: The key value to remove
# Returns:   None
# ----------------------------------------------------------------------------
map_remove = $(strip \
  $(call assert_called,map_remove,$0) \
  $(__map_args_check) \
  $(call var_undefine,$(__map_entry),$3) \
)

# ----------------------------------------------------------------------------
# Function:  keys
# Arguments: 1: Name of associative array
# Returns:   Returns a list of all defined keys in the array
# ----------------------------------------------------------------------------
map_keys = $(sort \
  $(call assert_called,keys,$0) \
  $(call assert,$(strip $1),Must specify map name) \
  $(patsubst $(call __map_entry,$1,%),%, \
    $(filter $(call __map_entry,$1,%),$(.VARIABLES)) \
)

# ----------------------------------------------------------------------------
# Function:  defined
# Arguments: 1: Name of associative array
#            2: The key to test
# Returns:   Returns true if the key is defined (i.e. not empty)
# ----------------------------------------------------------------------------
map_defined = $(__gmsl_tr2)$(call assert_no_dollar,$0,$1$2)$(call sne,$(call get,$1,$2),)

__map_args_check = \
  $(call assert,$(and $(strip $1),$(strip $2)),Must specify map and key names)
  
__map_entry = \
  $(__map_entry_prefix)$(call dollar_encode,$1)_$$_$(call dollar_encode,$2)
__map_entry_prefix := __map_entry_


##
# r-patsubst stands for recursive patsubst.
# This function has the same syntax as patsubst, excepting that you should use
# $(call ...) to invoke it.
# Unlike regular patsubst this one performs pattern replacement until at least
# one of the words in target expression matches the pattern.
#
# For example:
#   $(call r-patsubst,%/,%,foo/ bar/// baz) produces "foo bar baz"
#   whilst $(patsubst %/,%,foo/ bar/// baz) is just  "foo bar// baz"
#
# Usage: $(call r-patsubst,pattern,replacement,text)
#
r-patsubst = $(if $(filter $1,$3),$(call $0,$1,$2,$(3:$1=$2)),$3)

##
# Extended version of wildcard that understands double asterisk pattern (**).
#
# Usage: $(call r-wildcard,pattern)
#
# NOTE: does not handle properly more than one ** tokens.
#
r-wildcard = $(strip $(call __r-wildcard,$1,$(wildcard $1)))

__r-wildcard = \
  $(if $(and $(findstring **,$1),$2), \
    $(call $0,$(subst **,**/*,$1),$(wildcard $(subst **,**/*,$1))) \
  ) $2

# Directory/file versions of wildcard.
# Both of them are based on the fact that wildcard expansion of the expression
# containing the trailing slash drops the slash for files but leaves it for
# directories.

##
# Directory-only wildcard. This version of wildcard filters out any files
# leaving only directories.
#
# Usage: $(call d-wildcard,pattern)
#
d-wildcard = $(patsubst %/,%,$(filter %/,$(wildcard $(1:%=%/))))

##
# File-only wildcard. This version of wildcard leaves only files in the
# expansion result.
#
# Usage: $(call f-wildcard,pattern)
#
f-wildcard = $(patsubst %/,%,$(filter-out %/,$(wildcard $(1:%=%/))))

# Make-style error and warning strings.

# The most general way to get error/warning string.
# First argument should contain the location to print (directory and file).
error_str_file   = $1:1: error: 
warning_str_file = $1:1: warning: 

# Print location using the first argument as directory
# and 'Makefile' as file within the directory.
error_str_dir    = $(call error_str_file,$1/Makefile)
warning_str_dir  = $(call warning_str_file,$1/Makefile)

# Generates error/warning string in $(dir)/Makefile.
error_str        = $(call error_str_dir,$(dir))
warning_str      = $(call warning_str_dir,$(dir))

# Just for better output readability.
define N


endef

endif # _util_mk_

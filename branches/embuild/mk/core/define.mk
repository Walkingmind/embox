# $Id$

#
# Copyright 2008-2011, Mathematics and Mechanics faculty
#                   of Saint-Petersburg State University. All rights reserved.
# Copyright 2008-2011, Lanit-Tercom Inc. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

#
# Make functional language extensions:
#  - Syntactic:
#    - Function definition with inline comments
#    - Defining multiline verbose functions
#    - Using tabs for function code indentation
#  - Semantic:
#    - 'lambda' and 'with' for defining anonymous inner functions
#
#   Date: Jun 28, 2011
# Author: Eldar Abusalimov
#

ifndef __core_def_mk
__core_def_mk := 1

##
# Example of typical usage scenario is the following:
#
##
#   include mk/core/def.mk
#
#   define foo
#   	$(call bar,
#   		# Zzz...
#   		baz
#   	)
#   endef
#   $(call def,foo)
#

include mk/core/common.mk
include mk/core/string.mk

include mk/util/list.mk
include mk/util/var/assign.mk

##
# Performs both syntactiacal and semantical transformations of a function
# defined with a given name.
#
# Params:
#   1. Name of the function being defined.
# Return:
#   Nothing.
def = $(warning def: $1)$(strip \
  $(foreach __def_var,$1, \
    $(call var_assign_recursive_ml,$(__def_var),$ \
      $(call __def,$(value $(__def_var))))) \
)

# Params:
#   1. Code of a function being defined.
# Return:
#   Processed code ready to replace the original value of the function.
__def = \
  $(call __def_builtin,$ \
    $(call __def_brace,$ \
      $(call __def_strip,$ \
        $(subst $$,$$$$,$1))))

# Params:
#   1. Code with dollars escaped.
# Return:
#   The code with comments, newlines and indentation discarded.
#   Dollars remain escaped.
__def_strip = \
  $(call __def_strip_unescape,$ \
    $(call list_scan,__def_strip_fold,_$$n,$ \
      $(call __def_strip_escape,$ \
       $1)))

# Params:
#   1. Code with dollars escaped.
# Return:
#   The code with whitespaces and some other control chars replaced with
#   special markers (for instance, \n -> _$$n).
__def_strip_escape = \
  $(subst \ _$$h ,$(\h),$ \
   $(subst  $(\h), _$$h ,$ \
    $(subst  $(\n), _$$n ,$ \
     $(subst  $(\t), _$$t ,$ \
      $(subst  $(\s), _$$s ,$ \
       $1)))))

# Code convolution function.
# Params:
#   1. Previous token or empty inside a comment.
#   2. Current token.
# Return:
#   Token to append to the resulting text.
__def_strip_fold = \
  $(and $(subst _$$h,,$2), \
        $(if $(findstring _$$n,$1),$ \
             $(subst _$$s,_$$n,$(subst _$$t,_$$n,$2)),$ \
             $(or $(findstring _$$n,$2), \
                  $(if $1,$2))) \
   )

# Params:
#   1. Code with control characters inserted by '__def_strip_escape'.
# Return:
#   The code with restored whitespaces (space and tabs).
#   Newlines are discarded.
__def_strip_unescape = \
  $(subst  _$$s,$(\s),$ \
   $(subst  _$$t,$(\t),$ \
    $(subst  _$$n,,$      \
     $(subst $(\s),,$      \
      $1))))

#
# Starting at this point the rest functions will be written using new syntax
# that we have just defined.
# But since '__def_brace' and '__def_builtin' functions have not been
# implemented yet, we need to define stubs conforming to their interfaces.
#

# See '__def_brace_real'.
__def_brace = \
  $(subst $$$$,$$,$1)

# See: '__def_builtin_real'.
__def_builtin = \
  $1

#
# Now we can use $(call def,...).
#

# Expands value of the argument treating it as a code.
# Params:
#   1. Make code to be expanded.
# Return:
#   Expansion result.
# Note:
#   As a side effect all escaped dollars become unescaped.
define __def_expand
	# It is essential to use simple variable definition here to allow
	# redifinitions inside the expansion.
	#
	# The reason of this limitation is a bug in expansion engine of
	# GNU Make which affects all recent versions that implement 'eval'
	# function (any of 3.8x).
	#
	# The simplest case that reproduces this bug is expanding recursive
	# variable 'foo' defined as follows:
	#
	#   foo = $(eval foo =)
	#
	# In that case steps that Make performs to expand string $(foo) are:
	#   1. Start expanding a reference to a recursive variable 'foo':
	#        $(foo)
	#   2. Get its value and start parsing it:
	#        $(eval foo =)
	#   3. Find an invocation of builtin function 'eval' and run it:
	#        foo =
	#   4. Redefine the variable 'foo' which is being expanded right now.
	#      Redefinition of an already defined variable also involves
	#      freeing a memory occupied by an old value.
	#   5. Return from builtin function handler back to string expansion
	#      code (see step 2).
	#   6. At this point the string being parsed refers to a memory block
	#      that has been freed in step 4.
	#
	# Symptoms that one can observe may vary depending on the actual value
	# of an expanding variable. These may include:
	#   - 'missing separator' error,
	#   - 'unterminated variable reference' and 'unterminated call to function'
	#      errors,
	#   - garbage in results in case if expansion succeeds.
	# The latter is clearly seen when running Make under Valgrind with
	# --free-fill flag.
	#
	# A possible workaround is to use simple variable assignments, like:
	#
	#   foo := $(eval foo =)
	#
	# Here expansion of the value being assigned occurs immediately before
	# actually assigning it and no redefinitions of recursive variables is
	# performed.
	#
	# The most significant drawback is that we can't use 'define' directive
	# in version 3.81 and lower because such variable would be defined
	# recursive. This forces us to escape newlines and comment hashes
	# properly.
	${eval \
		# Use immediate expansion to allow recursive invocations of 'def' and
		# reuse '__def_tmp__' variable (e.g. in '__def_fn_args').
		__def_tmp__ := \
			$$(\empty)# To preserve whitepaces at the line start.
			$(subst $(\h),\$(\h),# To avoid interpreting hashes as comments.
				# TODO actually there is no newlines in our use cases. -- Eldar
				$(subst $(\n),$$(\n),# To place everything on a single line.
					$1
				)
			)
	}
	$(__def_tmp__)
endef
$(call def,__def_expand)

# Substitutes all unescaped occurrences of ${...} expansion to $(...).
# This does not affect pure {...} groups or escaped $${...}.
# Params:
#   1. Dollar-escaped value.
# Return:
#   The unescaped result of brace substitution.
define __def_brace_real
	# Expand hooks.
	$(call __def_expand,
		# Replace true ${...} expansion occurrences to a hook call:
		#   ${call __def_brace_hook,...}
		# which will echo its argument surrounded by $(...)
		$(subst $$$${,$${call __def_brace_hook$(\comma),
			# Isolate doubled dollars (in terms of the original value)
			# from the succeeding text.
			#   $${...}  -> $($)$($){...}
			#   $$${...} -> $($)$($)${...}
			$(subst $$$$$$$$,$$($$$$)$$($$$$),
				# First of all, replace commas with references to \comma.
				# This is needed to get properly handling of cases like
				#   $(call foo,${xxx bar,baz})
				# that would otherwise result in an error:
				#   unterminated call to function `xxx': missing `}'
				$(subst $(\comma),$$(\comma),
					$1
				)
			)
		)
	)
endef
$(call def,__def_brace_real)

# Surrounds the argument with '$(' and ')'.
__def_brace_hook = \
  $$($1)

# Brace-to-paren substitution logic is now ready.
__def_brace = \
  $(call __def_brace_real,$1)

#
# Here goes builtin functions transformation stuff.
#
# This part of logic is probably the most tricky and complicated.
# The processing is performed in two phases: inner and outer. Each phase
# involves some code transformation (namely installation of so-called hooks)
# with subsequent expansion of the code which invokes the installed hooks.
#
# Inner phase is focused on structural checks of code. Depending on what it
# does recognize (variable expansion, substitution reference, function
# call, etc.) it installs necessary hooks for the outer phase.
#
# Outer phase manages a so-called expansion stack which is used to track how
# the expansion is actually performed by make. It also helps to collect
# arguments passed to functions occurred in the code. Unlike inner the outer
# phase performs high-level code checks and transformations which include
# checking number of arguments passed to a certain function, defining extended
# builtin functions and so on.
#
# In order to prevent execution of the code being processed all dollar signs
# are quadruplicated ($ -> $$$$). After both expansions have been performed
# dollars are automatically restored to the initial state ($$$$ -> $$ -> $).
#

# The real work is done here.
# 1. Text
define __def_builtin_real
	$(call __def_expand,$(call __def_inner_unescape,
		$(call __def_expand,$(call __def_inner_install_hooks,
			# Escape dollars twice.
			$(subst $$,$$$$$$$$,
				$$(__def_root__ $1)
			)
		))
	))
endef
$(call def,__def_builtin_real)

define __def_inner_escape
	$(subst $(\paren_open),_$$[,$(subst $(\paren_close),_$$],
		$(subst :,_$$l,$(subst _$$q,=,
			$(subst $(\s),_$$s,$(subst $(\t),_$$t,
				$1
			))
		))
	))
endef
$(call def,__def_inner_escape)

define __def_inner_unescape
	$(subst _$$[,$(\paren_open),$(subst _$$],$(\paren_close),
		$(subst _$$l,:,$(subst _$$q,=,
			$(subst _$$s,$(\s),$(subst _$$t,$(\t),
				$1
			))
		))
	))
endef
$(call def,__def_inner_unescape)

define __def_inner_install_hooks
	$(subst $$$$$$$$$(\paren_open),
			$$$(\paren_open)call __def_inner_hook$(\comma),
		# Doubly escaped double dollars. I am a rich man. $)
		$(subst $$$$$$$$$$$$$$$$,
			# The hell below is '$($$)$($$)' with dollars and parens escaped.
			$$$$_$$$$[$$$$$$$$_$$$$]
			$$$$_$$$$[$$$$$$$$_$$$$],
			$(subst $(\comma),_$$$$c,
				$1
			)
		)
	)
endef
$(call def,__def_inner_install_hooks)

define __def_inner_hook
	$(call __def_inner_escape,
		$(or \
			$(foreach first,$(firstword $1),
				# Guaranteed non empty value inside $(...).
				$(__def_inner_handle)
			),
			# Empty variable name or nothing except whitespaces.
			$$(call __def_outer_hook_warning,
				$$$$($1),
				Empty variable name
			)
		)
	)
endef
$(call def,__def_inner_hook)

#
# Params:
#   1. Non-empty value being handled.
#   'first': The first word of the value.
#
# Return:
#   Resulting handled value with (possibly) outer hooks installed if the value
#   is syntactically correct, or empty otherwise.
#
# Invariants:
#   Everything that has been already handled before is mangled so that
#   there is no whitespaces, escaped commas, colons or equal signs in such
#   handled fragments.
#
#   For example, if we are going to handle the outermost expansion of
#     $(foo bar$(one:%r=%z),baz$(two bob,alice))
#   then the actual value being handled would have a form of
#     $(foo bar???,baz???)
#
#   This avoids handling values more than once and prevents interference with
#   the processing of the current values. Referring to the example above, the
#   value will have only two words (unlike three words in the original
#   expansion), only one comma (as opposed to two commas) and no equal sign or
#   colon.
define __def_inner_handle
	$(or \

		# First try to treat it as a variable expansion with a substitution
		# reference.
		$(__def_inner_handle_substitution_reference),

		# Check that there is no commas in function or variable name.
		$(if $(findstring _$$c,$(first)),
			# Invalid name. Emit a warning hook.
			#   $(foo,bar) $(foo, bar) $(foo,) $(,foo) $(,)
			$$(call __def_outer_hook_warning,
				$$$$($(subst _$$c,$(\comma),$1)),
				Unexpected '$$(\comma)' in variable or function name
			)
		),

		# No commas in the first word. Assuming that it is the only word inside
		# the value being expanded and there is no whitespaces around it
		# we try to handle it as a regular variable expansion.
		#   $(foo)
		$(call singleword,$$$$($1)),

		# Falling in here means that there are some whitespaces inside
		# the expansion parens, either between chars or around them...

		# Check if the first char is not a whitespace.
		$(if $(filter-out x$(first),$(firstword x$1)),
			# There are some, name is bad:
			#   $( foo) $( foo bar)
			$$(call __def_outer_hook_warning,
				$$$$($(subst _$$c,$(\comma),$1)),
				Unexpected leading whitespace in variable or function name
			)
		),

		# No leading whitespaces: valid function call.
		$(__def_inner_handle_function)
	)
endef
$(call def,__def_inner_handle)

# Params:
#   The same as to '__def_inner_handle'
# Return:
#   The value inside expansion parens if it is a valid substitution reference,
#   or empty otherwise.
define __def_inner_handle_substitution_reference
	$(and \

		# If there is a colon in the first word...
		$(findstring :,$(first)),

		# ...and there is an equal sign after the colon...
		$(findstring =,$(call nofirstword,$(subst :,: ,$1))),

		# ...then it seems to be a substitution reference. Substitutions
		# are not our friends. Stop handle here and output the value as is.
		$$$$($1)
	)
endef
$(call def,__def_inner_handle_substitution_reference)

# Params:
#   The same as to '__def_inner_handle'
# Return:
#   Resulting value with necessary outer hooks installed in case that it is
#   a valid function call, or empty otherwise.
define __def_inner_handle_function
	$$(call __def_outer_hook_push,$(first))

	$(if $(call singleword,$1),
		# The one and only word with trailing whitespace is a function call
		# with a single empty argument.
		# $(foo )
		$$(call __def_outer_hook_func,$$(call __def_outer_hook_arg)),
	
		# One non-empty argument or more than one argument.
		#   $(foo bar) $(foo ,) $(foo bar,) $(foo ,bar) ...
		$$(call __def_outer_hook_func
			# Unescape any escaped commas and install argument hooks
			# after each of them.
			$(subst _$$c,
				# Real commas are needed to get actual arguments placed
				# into the corresponding variables ($1,$2,...), and
				# hooks help to get the list of theese variables.
				$(\comma)$$(call __def_outer_hook_arg),
				# Escaped comma before the actual arguments.
				_$$c
				# The actual arguments form the rest of the value being
				# handled. An exact structure of whitespaces between
				# the function name and the first argument is not
				# meaningful and thus it is not preserved.
				$(subst $(\paren_open),
					_$$[$$_$$[call __def_outer_hook_push$(\comma)__paren___$$],
					$(subst $(\paren_close),
						$$_$$[call __def_outer_hook_pop$(\comma)__paren___$$]_$$],
						$(call nofirstword,$1)
					)
				)
			)
		)
	)

	$$(call __def_outer_hook_pop,$(first))

endef
$(call def,__def_inner_handle_function)
#
# The main structure used by the outer expansion phase is an expansion stack.
# The stack holds an information about how native make expansion engine
# handles a value prepared by inner phase.
# Each element of the stack corresponds to a function call.
#

# The stack element is represented by a single word in form:
#   foo,1,2 bar,1 __def_root__,1
# where 'foo' and 'bar' are names of the corresponding functions,
# and comma separated numbers refer to function arguments that have already
# been processed.
__def_outer_stack     :=# Initially empty.

# Top of the stack is separated from the rest elements. The only difference is
# that the funсtion name and numbers are separated using spaces:
#   boo 1 2 3
__def_outer_stack_top :=# Empty too.

# In debugging purposes.
__def_outer_stack_depth = \
  $(if $(__def_outer_stack_top),$(\t))$(__def_outer_stack:%=>$(\t))

# Issues a warning with the specified message including the call stack.
# Params:
#   1. Code fragment which caused the warning.
#   2. The message.
# Return:
#   The first argument.
define __def_outer_hook_warning
	$1
	$(warning $2: $1)
	$(warning Expansion stack:)
	$(strip $(foreach e,
			$(subst $(\s),$(\comma),$(__def_outer_stack_top)) \
			$(__def_outer_stack),
		$(warning \
			$(\t)arg $(lastword $(subst $(\comma), ,$e)) \
				of '$(firstword $(subst $(\comma), ,$e))'
		)
	))
endef
$(call def,__def_outer_hook_warning)

# Pushes the specified name onto the top of the expansion stack saving the
# previous value of the top into the stack.
# Params:
#   1. Value to push.
# Return:
#   Nothing.
__def_outer_hook_push  = \
  $(warning $(__def_outer_stack_depth)push [$1])$ \
  ${eval $(value __def_outer_hook_push_mk)}

define __def_outer_hook_push_mk
  # Save the current value of the top into the stack.
  __def_outer_stack := \
    $(subst $(\s),$(\comma),$(__def_outer_stack_top)) \
    $(__def_outer_stack)
  # Put new function name onto the top.
  __def_outer_stack_top := $1
endef

# Removes an element from the top and restores the previous element.
# Return:
#   Nothing.
__def_outer_hook_pop   = \
  ${eval $(value __def_outer_hook_pop_mk)}$ \
  $(warning $(__def_outer_stack_depth)pop  [$1])

define __def_outer_hook_pop_mk
  # Restore the top from the stack.
  __def_outer_stack_top := \
    $(subst $(\comma),$(\s),$(firstword $(__def_outer_stack)))
  # And remove from the stack.
  __def_outer_stack := \
    $(call nofirstword,$(__def_outer_stack))
endef

# Increments the number of arguments of the function call being handled now.
# Return:
#   Nothing.
__def_outer_hook_arg = \
  $(warning $(__def_outer_stack_depth)arg$(words $(__def_outer_stack_top)))$ \
  ${eval $(value __def_outer_hook_arg_mk)}

define __def_outer_hook_arg_mk
  # Append the next argument number to the stack top.
  __def_outer_stack_top += \
    $(words $(__def_outer_stack_top))
endef

define __def_outer_hook_func
	$(warning \
		$(__def_outer_stack_depth)func [$(__def_fn_name)]
		(
			$(foreach a,$(__def_fn_args_list),
				[$($a)]
			)
		)
	)
	$(foreach 0,__def_func_'$(__def_fn_name)',
		$(if $(value $0),
			$($0),
			$$($(__def_fn_name) $(__def_fn_args))
		)
	)
endef
$(call def,__def_outer_hook_func)

__def_func_'__def_root__' = \
  $(__def_fn_args)

# Gets the name of a function being handled.
# Example:
#   For $(foo bar,baz) it would return 'foo'.
# Note:
#   You may simply expand this macro without 'call'ing it.
__def_fn_name = \
  $(firstword $(__def_outer_stack_top))

# Gets a list of variable names of all arguments of a function being handled.
# This macro is useful for counting and iterating over the formal arguments.
# Example:
#   For $(foo bar,baz) it would return '1 2'.
# Note:
#   You may simply expand this macro without 'call'ing it.
__def_fn_args_list = \
  $(call nofirstword,$(__def_outer_stack_top))

# '__def_fn_args' and its derivatives construct an actual arguments passing
# code in a 'call'-like syntax.
# Note:
#   You must not 'call' theese macros in order to preserve argument values of
#   the current function call.

# $(f foo,bar,baz) -> 'foo,bar,baz'.
__def_fn_args      = $(foreach args_filter,id         ,$(__def_fn_args_expand))

# $(f foo,bar,baz) -> 'foo'.
__def_fn_firstarg  = $(foreach args_filter,firstword  ,$(__def_fn_args_expand))

# $(f foo,bar,baz) -> 'baz'.
__def_fn_lastarg   = $(foreach args_filter,lastword   ,$(__def_fn_args_expand))

# $(f foo,bar,baz) -> 'bar,baz'.
__def_fn_nofirstarg= $(foreach args_filter,nofirstword,$(__def_fn_args_expand))

# $(f foo,bar,baz) -> 'foo,bar'.
__def_fn_nolastarg = $(foreach args_filter,nolastword ,$(__def_fn_args_expand))

# Comma-separated list of expanded arguments. Intended for internal usage only.
# Context:
#   'args_filter': name of a filtering function to apply to the list of args.
# Example:
#   For $(func foo,bar,baz) it would return 'foo,bar,baz'.
# Note:
#   You must not 'call' this macro in order to preserve the current context.
define __def_fn_args_expand
	# Can't use '__def_expand' because of the need to access local arguments.
	# But everything we have told about there concerns to the code below too.
	${eval \
		__def_tmp__ := \
			# For $(func foo,bar,baz) it would be '$(1),$(2),$(3)'
			# which in turn expands to the sought-for.
			$(subst $(\s),$(\comma),$(patsubst %,$$(%),
				$(call $(args_filter),$(__def_fn_args_list))
			))
	}
	$(__def_tmp__)
endef
$(call def,__def_fn_args_expand)

# Gets the name of a function which is upper in the expansion stack than the
# current one by the specified depth (if any).
# Params:
#   1. (Optional) depth, '1' by default which mean direct caller.
# Return:
#   Function name or empty if the argument is bigger than actual stack depth.
# Example:
#   In case of handling the innermost function of $(foo $(bar $(baz ...))),
#   namely 'baz', its direct caller is 'bar' and a caller at depth 2 is 'foo'.
define __def_fn_caller
	$(firstword $(subst $(\comma),$(\s),
		$(word $(or $(if $(filter __def_fn_caller,$0),$(value 1)),1),
			$(filter-out __paren__% __def_root__%,$(__def_outer_stack))
		)
	))
endef
$(call def,__def_fn_caller)

# Auxiliary procedure for function allocation.
# Useful if your builtin needs to define auxiliary function/variable.
define __def_builtin_alloc
	__builtin$(words $(__def_builtin_cnt))$(__def_var)
	${eval \
		__def_builtin_cnt += x
	}
endef
$(call def,__def_builtin_alloc)
__def_builtin_cnt :=# Initially empty.

# Now builtins definition core framework is up. Enable it here.
__def_builtin = \
  $(call __def_builtin_real,$1)

#
# Extension: 'lambda' builtin function.
#
# '$(lambda body)'
#
define __def_func_'lambda'
	$(foreach aux,$(__def_builtin_alloc),
		# Define external function.
		$(call var_assign_recursive_sl,$(aux),$(__def_fn_args))
		# The value being returned.
		$(aux)
	)
endef
$(call def,__def_func_'lambda')

# Stub for case of $(lambda) or $(call lambda,...).
lambda = $(warning lambda: illegal invocation)

#
# Extension: 'with' builtin function.
#
# '$(with args...,body)'
#
define __def_func_'with'
	$(foreach aux,$(__def_builtin_alloc),
		$(call var_assign_recursive_sl,$(aux),$(__def_fn_lastarg))
		$$(call $(aux)
			$(if $(call nolastword,$(__def_fn_args_list)),
				$(\comma)$(__def_fn_nolastarg)
			)
		)
	)
endef
$(call def,__def_func_'with')

# Stub for case of $(lambda) or $(call lambda,...).
with = $(warning with: illegal invocation)

endif # __core_def_mk

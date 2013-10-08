ifndef __mk_ugly_mk
__mk_ugly_mk := 1

#
# Headers.
#

# By header get module
#
define __header_mod_name 
	$(strip	
		$(subst /,.,
			$(patsubst $(abspath $(SRCGEN_DIR))/include/module/%.h,
					%,
					$(abspath $1))))
endef


__header_mod = $(call map-get,$(build_model),moduleInstanceByName,$1)

__header_gen = $(with $(__header_mod_name), \
  $(subst $(\n),\n,$(call __header_template,$(call __header_mod,$1),$1)))

# 1. ModuleInstance of most specified module in hierarchy 
# 2. Target generated mod name
define __header_template
/* Autogenerated file. Do not edit. */ $(\n)
$(for modName <- $2,
	$(\n)
	$(\h)ifndef __MOD_HEADER__$(subst .,__,$(modName)) $(\n)
	$(\h)define __MOD_HEADER__$(subst .,__,$(modName)) $(\n)
	$(for optionInstance <- $(get 1->options),
		optionId <- $(subst .,__,$(invoke optionInstance->option>getId)),
		$(\n)
		$(\h)ifndef $(optionId)$(\n)
		$(\h)define $(optionId) $(invoke optionInstance->value>toString)$(\n)
		$(\h)endif$(\n))
	
	$(foreach impl,$(get 1->type) $(get 1->type>allSuperTypes),
		$(\n)// module: $(get impl->qualifiedName)$(\n)
		$(or $(foreach header,$(strip $(patsubst $(abspath $(SRC_DIR))/%,%,
				 $(abspath $(call module_get_headers,$(impl))))) \
		      ,$(\h)include <../$(header)>$(\n)),
		     // no headers to include$(\n)))



	$(\n)$(\h)endif /* __MOD_HEADER__$(subst .,__,$(modName)) */$(\n)
)
endef


module_get_headers = \
	$(filter %.h,$(module_get_files))
module_get_files = \
	$(foreach s,$(get 1->sources),$(get s->fileFullName))


# Performs topological sort of library modules.
# Anonymous function performs sorting, 
#	1 arg: Black, visited, sorted vertexes, consists of topological sorted vertexes.
#	2 arg: Grey vertexes, considering on this step.
#	3 arg: White vertexes, have not reach those.
# On each step:
#	If there is no grey or white vertexes
#		 print out $1. Exit.
#	Else 	 
#		If there is grey vertexes,
#			take first. 
#			If one has white vertexes as depends,
#				move them in front of grey vertexes. 
#			Else 
#				If one has grey vertexes as depends, 
#					move it to end of grey vertexes list.
#				Else move one in front of black vertexes. 
#		Else 
#			move first of white vertexes to grey vertexes.
#
#	Take next step.			
#
define filter_static_modules 
	$(with ,,$(strip $(foreach m,$1,$(if $(get $(get m->type).isStatic),$m))),
		$(if $(or $2,$3),
			$(if $2,
				$(if $(filter $(get $(firstword $2).depends),$3),
					$(call $0,$1,$(filter $(get $(firstword $2).depends),$3) $2,
						$(filter-out $(get $(firstword $2).depends),$3)),
					$(if $(filter $(get $(firstword $2).depends),$2),
						$(call $0,$1,$(wordlist 2,$(words $2),$2) $(firstword $2),$3),
						$(call $0,$(firstword $2) $1,$(wordlist 2,$(words $2),$2),$3))),
				$(call $0,$1,$(firstword $3),$(wordlist 2,$(words $3),$3))),
			$1))
endef
			
$(def_all)

endif # __mk_ugly_mk

ifndef __mk_ugly_mk
__mk_ugly_mk := 1

include mk/conf/roots.mk
include mk/conf/runlevel.mk

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
	$(foreach impl,$(get $(get 1->type).allSuperTypes),
		$(\n)// impl: $(get $(get 1->type).qualifiedName)$(\n)
		$(foreach header,$(strip $(patsubst $(abspath $(SRC_DIR))/%,%,
				 $(abspath $(call module_get_headers,$1)))) \
		      ,$(\h)include <../$(header)>$(\n)$(\n)))

	$(for moduleInstance <- $1,
		optionInstance <- $(get moduleInstance->options),
		option <- $(get optionInstance->option),
		optionId <- $(invoke option->getId),
		optionValue <- $(get optionInstance->value),
		$(\n)$(\n)$(\h)define $(subst .,__,$(optionId)) $(invoke optionValue->toString))

	$(\n)$(\h)endif /* __MOD_HEADER__$(subst .,__,$(modName)) */$(\n)
)
endef


#
# Image.
#

SRC_TO_OBJ = \
	$(call filter-patsubst, \
		$(abspath $(ROOT_DIR))%.c $(abspath $(ROOT_DIR))%.S,$(OBJ_DIR)%.o, \
		$(filter-out %.lds.S,$(abspath $1)))

LIB_FILE = \
	$(foreach 1,$1,$(LIB_DIR)/$(get $(get $1.type).qualifiedName).a)

moduleInst_get_files = $(call module_get_files,$(get 1->type))

module_get_files = \
	$(foreach s,$(get 1->sources),$(get s->fileFullName))
module_get_sources = \
	$(filter %.c %.S,$(moduleInst_get_files))
module_get_headers = \
	$(filter %.h,$(moduleInst_get_files))
module_get_objects = \
	$(call SRC_TO_OBJ,$(module_get_sources))

define filter_abstract_modules
	$(strip 
		$(for \
			m <- $1,
			s <- $(get m->type) $(get $(get m->type).allSuperTypes),
				$(if $(get s->isAbstract),
					$(get s->qualifiedName))))
endef 

filter_static_modules = \
	$(strip $(foreach m,$1,$(if $(get $(get m->type).isStatic),$m)))

ROOTFS_LABEL := mybuild.lang.InitFS

define module_get_rootfs 
	$(for fileMember <- $(get $(get 1->type).sourcesMembers),
		annot <- $(get fileMember->annotations),
		annotType <- $(get annot->type),
		$(if $(eq $(ROOTFS_LABEL),$(get $(get annot->type).qualifiedName)),
			$(for fileName <- $(get fileMember->files),
				$(get fileName->fileFullName))))
endef

LABEL-IncludePath := mybuild.lang.IncludePath
LABEL-DefineMacro := mybuild.lang.DefineMacro

# 1. Module.
define define_mod_obj_rules
	${eval 
		$(for mod<-$(get $1.type),
			$(for \
				srcMember<-$(get mod->sourcesMembers),
				annot <- $(get srcMember->annotations),
				annotType <- $(get annot->type),
				annotName <- $(get annotType->qualifiedName),
				annotBind <- $(get annot->bindings),
				opt <- $(get annotBind->option),
				optName <- $(get opt->name),
				optValue <- $(get $(get annotBind->value).value),
				src<-$(get srcMember->files),
				obj<-$(call SRC_TO_OBJ,$(get src->fileFullName)),
				$(if $(and \
						$(eq $(annotName),$(LABEL-IncludePath)),
						$(eq $(optName),value)),
				$(obj) : override CCFLAGS += -I'$(optValue)'$(\n)) 
				$(if $(and \
						$(eq $(annotName),$(LABEL-DefineMacro)),
						$(eq $(optName),value)),
				$(obj) : override CCFLAGS += -D'$(optValue)'$(\n))) 
			$(for \
				src<-$(get mod->sources),
				obj<-$(call SRC_TO_OBJ,$(get src->fileFullName)),
				$(obj) : override CPPFLAGS += \
					-D__EMBUILD_MOD__='$(subst .,__,$(get mod->qualifiedName))'\
					-include $(SRCGEN_DIR)/include/module/$(subst .,/,$(get mod->qualifiedName)).h$(\n)))}
endef

# 1. Library module.
define define_lib_rules
	${eval \
		$(call LIB_FILE,$1) : $(call module_get_objects,$1)$(\n)
			$(\t)$(AR) $(ARFLAGS) $$@ $$(^:%= \$$(\n)	%)
	}
endef


#
# Generated dependencies graph.
#

mod_package = $(basename $(mod))
mod_name = $(patsubst .%,%,$(suffix $(mod)))

# The same as DEPS-$(mod), at least for now.
mod_requires = $(DEPS-$(mod))
# This is very inefficient algorithm but it does work.
mod_provides = $(filter-out $(mod),$(foreach m,$(MODS_BUILD), \
  $(if $(filter $(mod),$(call MOD_DEPS_DAG,$(m))),$(m)) \
))

c_mod = $(call c_escape,$(mod))
c_dep = $(call c_escape,$(dep))
c_package = $(call c_escape,$(package))

c_escape = $(subst .,__,$(1))

c_str_escape = \
  "$(subst $(\n),\n,$(subst $(\t),\t,$(subst ",\",$1)))"

eol-trim = $(if $(findstring $(\s)\n,$1),$(call $0,$(subst $(\s)\n,\n,$1)),$1)

cond_flags = NYI
#cond_flags =   $(if $(strip $(CFLAGS-$2) $(CPPFLAGS-$2)), \
    $1 $(strip $(CFLAGS-$2) $(CPPFLAGS-$2)) \
  ) \

package_def = \
  $(\n)$(\n)/* Package: $(package) */ \
  $(\n)MOD_PACKAGE_DEF($(c_package), "$(package)");

generate_package_defs = /* Package definitions. */\
  $(foreach package,$(sort generic $(basename $(for m <- $(MODS_BUILD), \
        $(get $(get m->type).qualifiedName)))), \
    $(package_def) \
  )$(\n)

# 1. Name of the annotation property.
define mod_cmd_annotation_value
	$(for string <-
			$(for m <- $(value m),
				a <- $(get m->annotations),
				aType <- $(get a->type),
				binding <-
					$(if $(filter mybuild.lang.Cmd,$(get aType->qualifiedName)),
						$(get a->bindings)),
				option <- $(get binding->option),
				$(if $(filter $1,$(get option->name)),
					$(get binding->value))),
		$(get string->value))
endef

mod_def = \
  $(\n)$(\n)/* Mod: $(mod) */ \
  $(\n)MOD_DEF($(c_mod), $(call c_escape,$(mod_package)), "$(mod_name)", \
  $(call c_str_escape,$(call mod_cmd_annotation_value,help)), \
  $(call c_str_escape,$(call mod_cmd_annotation_value,man)));


generate_mod_defs = $(\n)/* Mod definitions. */\
  $(for instance <- $(MODS_BUILD) $(LIBS_BUILD), \
  	m <- $(get instance->type), \
        mod <- $(get m->qualifiedName), \
    $(mod_def) \
  ) \
  $(foreach runlevel,0 1 2 3, \
    $(foreach mod,$(addprefix generic.runlevel$(runlevel)_,init fini), \
      $(mod_def) \
    ) \
  )$(\n)
    

LABEL-Runlevel := mybuild.lang.Runlevel

generate_mod_deps = $(\n)/* Mod deps. */\
  $(for instance <- $(MODS_BUILD) $(LIBS_BUILD), \
  	m <- $(get instance->type), \
        mod <- $(get m->qualifiedName), \
	$(for obj_dep <- $(get instance->depends), \
          dep <- $(get $(get obj_dep->type).qualifiedName), \
	      $(\n)MOD_DEP_DEF($(c_mod), $(c_dep)); \
	   )\
	$(for obj_dep <- $(get instance->afterDepends), \
          dep <- $(get $(get obj_dep->type).qualifiedName), \
	      $(\n)MOD_AFTER_DEP_DEF($(c_mod), $(c_dep)); \
	   )\
   $(with $(for include <- $(get instance->includeMember), \
		annotation <- $(get include->annotations), \
		annotationType <- $(get annotation->type), \
		annotationName <- $(get annotationType->qualifiedName), \
		binding <- $(get annotation->bindings), \
		option <- $(get binding->option), \
		value <- $(get binding->value), \
		valueRaw <- $(get value->value), \
		$(if $(and $(eq $(annotationName),$(LABEL-Runlevel)), \
			$(eq $(get option->name),value)), \
			$(valueRaw)\
		)), \
	$(for valueRaw <- $(or $1,2),\
	  $(\n)MOD_DEP_DEF(generic__runlevel$(valueRaw)_init, $(c_mod)); \
	  $(\n)MOD_DEP_DEF($(c_mod), generic__runlevel$(valueRaw)_fini); \
     ) \
    ) \
  )$(\n)

$(def_all)

endif # __mk_ugly_mk

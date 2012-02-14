# $Id$
#
# Dependency Injection model generator. 
#
# Author: Eldar Abusalimov
#

ifndef _codegen_di_mk_
_codegen_di_mk_ := 1

#include $(MK_DIR)/embuild.mk

DEPSINJECT_SRC = $(CODEGEN_DIR)/depsinject.c
DEPSINJECT_OBJ = $(OBJ_DIR)/depsinject.o

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
  \n\t\t"$(subst $(\n),\\\\n"\n\t\t",$(subst $(\t),\\t,$(subst ",\",$1)))"

eol-trim = $(if $(findstring $(\s)\n,$1),$(call $0,$(subst $(\s)\n,\n,$1)),$1)

cond_flags = NYI
#cond_flags =   $(if $(strip $(CFLAGS-$2) $(CPPFLAGS-$2)), \
    $1 $(strip $(CFLAGS-$2) $(CPPFLAGS-$2)) \
  ) \

package_def = \
  \n\n/* Package: $(package) */ \
  \nMOD_PACKAGE_DEF($(c_package), "$(package)");

generate_package_defs = $(call eol-trim,\n/* Package definitions. */\
  $(foreach package,$(sort generic $(basename $(for m <- $(MODS_BUILD), \
        $(get m->qualified_name)))), \
    $(package_def) \
  ) \
)\n

mod_def = \
  \n\n/* Mod: $(mod) */ \
  \nMOD_DEF($(c_mod), $(call c_escape,$(mod_package)), "$(mod_name)", \
    $(call c_str_escape,$(value BRIEF-$(mod))), \
    $(call c_str_escape,$(value DETAILS-$(mod))));

generate_mod_defs = $(call eol-trim,\n/* Mod definitions. */\
  $(for m <- $(MODS_BUILD), \
        mod <- $(get m->qualified_name), \
    $(mod_def) \
  ) \
  $(foreach runlevel,0 1 2 3, \
    $(foreach mod,$(addprefix generic.runlevel$(runlevel)_,init fini), \
      $(mod_def) \
    ) \
  ) \
)\n

generate_mod_deps = $(strip \n/* Mod deps. */\
  $(for m <- $(MODS_BUILD), \
        mod <- $(get m->qualified_name), \
    $(for link <- $(get m->depends_refs), \
          d <- $(get link->dst), \
          dep <- $(get d->qualified_name), \
      \nMOD_DEP_DEF($(c_mod), $(c_dep)); \
    ) \
    $(for link <- $(get m->super_module_ref), \
          d <- $(get link->dst), \
          mod <- $(get d->qualified_name), \
          dep <- $(get m->qualified_name), \
      \nMOD_DEP_DEF($(c_mod), $(c_dep)); \
    ) \
    $(if $(value RUNLEVEL-$(mod)), \
      \nMOD_DEP_DEF(generic__runlevel$(RUNLEVEL-$(mod))_init, $(c_mod)); \
      \nMOD_DEP_DEF($(c_mod), generic__runlevel$(RUNLEVEL-$(mod))_fini); \
    ) \
  ) \
)\n

generate_header := \
  /* Auto-generated EMBuild Dependency Injection model file. Do not edit. */\n

generate_includes := \n\#include <framework/mod/embuild.h>\n

__printf_escape = "$(subst ",\",$1)"
$(DEPSINJECT_SRC) : $(MK_DIR)/codegen-di.mk $(AUTOCONF_DIR)/mods.mk
	@$(PRINTF) $(call __printf_escape,$(generate_header)) > $@
	@$(PRINTF) $(call __printf_escape,$(generate_includes)) >> $@
	@$(PRINTF) $(call __printf_escape,$(generate_package_defs)) >> $@
	@$(PRINTF) $(call __printf_escape,$(generate_mod_defs)) >> $@
	@$(PRINTF) $(call __printf_escape,$(generate_mod_deps)) >> $@

$(DEPSINJECT_OBJ) : $(AUTOCONF_DIR)/config.h
$(DEPSINJECT_OBJ) : $(DEPSINJECT_SRC)
	$(CC) $(CFLAGS) $(CPPFLAGS) -std=gnu99 -D__EMBUILD__ -o $@ -c $<

-include $(DEPSINJECT_OBJ:.o=.d)

endif

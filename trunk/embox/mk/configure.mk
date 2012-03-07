# $Id$
#
# Author: Eldar Abusalimov
#

HOSTCC  = gcc
#SVN_REV = $(shell svn info $(ROOT_DIR) | grep Rev: | awk '{print $$4}')
HOSTCPP = $(HOSTCC) -E

HOSTCC_MAJOR := \
  $(shell $(HOSTCC) -v 2>&1 | grep "gcc version" | cut -d' ' -f3  | cut -d'.' -f1)

build_conf   := $(CONF_DIR)/build.conf
options_conf := $(CONF_DIR)/options.conf
mods_conf    := $(CONF_DIR)/mods.conf
lds_conf     := $(CONF_DIR)/lds.conf

build_mk     := $(AUTOCONF_DIR)/build.mk
mods_mk      := $(AUTOCONF_DIR)/mods.mk
config_h     := $(AUTOCONF_DIR)/config.h
config_lds_h := $(AUTOCONF_DIR)/config.lds.h

CONF_FILES     := $(build_conf) $(options_conf) $(mods_conf) $(lds_conf)
AUTOCONF_FILES := $(build_mk) $(mods_mk) $(config_h) $(config_lds_h)

ifeq (1,1)

config_resource_set := $(call config_link_with_myfile_model,$(__config_resource_set),$(__myfile_resource_set))
mybuild_model := $(call new,Mybuild,$(__myfile_resource_set) $(config_resource_set))
build_model := $(call Mybuild-createBuild,$(mybuild_model))

$(warning Modules are $($(build_model).modules))
endif

MODS_ENABLE :=
-include $(build_mk) $(mods_mk)

include mk/conf/roots.mk
include mk/conf/runlevel.mk

$(if $(filter-out $(words $(MODS_ENABLE)),$(words $(sort $(MODS_ENABLE)))),\
	$(error Multiple mod inclusion: $(sort $(foreach m,$(MODS_ENABLE),$(if $(word 2,$(filter $m,$(MODS_ENABLE))),$m)))))

__MODS_ENABLE_OBJ := \
	$(foreach m,$(MODS_ENABLE),$(or $(strip $(call find_mod,$m)), \
		$(error Can't resolve module $m named in configs)))

__MODS_ENABLE_OBJ := \
	$(call module_closure,$(__MODS_ENABLE_OBJ))

_MODS_ENABLE_OBJ := $(strip $(foreach m,$(MODS_ENABLE),$(foreach n,$(__MODS_ENABLE_OBJ),$(if $(call eq,$(basename $n),$m),$n))))
MODS_ENABLE_OBJ := $(_MODS_ENABLE_OBJ) $(filter-out $(_MODS_ENABLE_OBJ),$(__MODS_ENABLE_OBJ))

TARGET ?= embox$(if $(value PLATFORM),-$(PLATFORM))
TARGET := $(TARGET)$(if $(value LOCALVERSION),-$(LOCALVERSION))

.PHONY: check_config check_conf_dir
check_config: check_conf_dir $(CONF_FILES)
ifndef ARCH
	@echo 'Error: ARCH undefined'
	exit 1
endif

check_conf_dir:
	@test -d $(CONF_DIR) $(CONF_FILES:%=-a -f %) \
		||(echo 'Error: conf directory or files do not exist' \
		&& echo 'Usage: "make PROJECT=<project> PROFILE=<profile> config"' \
		&& echo '    See templates dir for possible projects and profiles' \
		&& exit 1)

$(build_mk)     : DEFS := __BUILD_MK__
$(mods_mk)      : DEFS := __MODS_MK__
$(config_h)     : DEFS := __CONFIG_H__
$(config_lds_h) : DEFS := __CONFIG_LDS_H__

$(AUTOCONF_DIR)/start_script.inc: $(CONF_DIR)/start_script.inc
	@cp -f $< $@

ifeq ($(HOSTCC_MAJOR),4)
HOSTCC_CPPFLAGS := -iquote $(CONF_DIR)
else
HOSTCC_CPPFLAGS := -I $(CONF_DIR) -I-
endif

$(build_mk) $(mods_mk) : 
	$(HOSTCPP) -P -undef -nostdinc $(HOSTCC_CPPFLAGS) $(DEFS:%=-D%) \
	-MMD -MT $@ -MF $@.d mk/confmacro.S \
		| sed 's/$$N/\n/g' > $@

$(config_h) $(config_lds_h) :
	$(HOSTCPP) -P -undef -nostdinc $(HOSTCC_CPPFLAGS) $(DEFS:%=-D%) \
	-MMD -MT $@ -MF $@.d mk/confmacro.S \
		| sed -e 's/$$N/\n/g' -e 's/$$define/#define/g' > $@
#ifeq ($(SVN_REV),)
#	@echo "svn cmd not found"
#else
#	@echo "#define CONFIG_SVN_REV $(SVN_REV)" >> $@
#endif

$(AUTOCONF_FILES) : mk/configure.mk \
  | check_conf_dir mkdir # these goals shouldn't force target to be updated

-include $(AUTOCONF_FILES:%=%.d)

CROSS_COMPILE ?=

mkdir:
	@test -d $(AUTOCONF_DIR) || mkdir -p $(AUTOCONF_DIR)

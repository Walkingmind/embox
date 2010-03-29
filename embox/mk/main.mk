# $Id$
#
# EMBOX main Makefile
#

# The first target is "all"
all:

ifeq ($(MAKE_VERSION),3.80)
define ERROR
Unsupported GNU Make version.
Unfortunatelly EMBuild does not work properly with GNU Make $(MAKE_VERSION)
This is a known issue. Please use GNU Make version 3.81
endef
$(error $(ERROR))
endif

ifndef ROOT_DIR
$(error ROOT_DIR undefined)
endif

MK_DIR         := $(ROOT_DIR)/mk
SCRIPTS_DIR    := $(ROOT_DIR)/scripts
PROJECTS_DIR  := $(ROOT_DIR)/templates
THIRDPARTY_DIR := $(ROOT_DIR)/third-party
PLATFORM_DIR   := $(ROOT_DIR)/platform
SRC_DIR        := $(ROOT_DIR)/src

CONF_DIR       := $(ROOT_DIR)/conf

BASE_CONF_DIR  := $(ROOT_DIR)/conf
PATCH_CONF_DIR := $(ROOT_DIR)/conf/$(PATCH_NAME)

BACKUP_DIR     := $(ROOT_DIR)/conf/backup~

ifeq ($(BUILD_TYPE),patch)
BUILD_DIR      := $(ROOT_DIR)/build/patch_$(PATCH_NAME)
else
ifeq ($(BUILD_TYPE),base)
BUILD_DIR      := $(ROOT_DIR)/build/base
else
BUILD_DIR      := $(ROOT_DIR)/build
endif
endif

ifdef SINGLE_TARGET
# ? - m.b. it's a mistake=)
BUILD_TYPE     := single_target
BUILD_DIR      := $(ROOT_DIR)/build
endif

BIN_DIR        := $(BUILD_DIR)/bin
OBJ_DIR        := $(BUILD_DIR)/obj
LIB_DIR        := $(OBJ_DIR)
DOT_DIR        := $(BUILD_DIR)/dot
DOCS_DIR       := $(BUILD_DIR)/docs
CODEGEN_DIR    := $(BUILD_DIR)/codegen
AUTOCONF_DIR   := $(CODEGEN_DIR)

RM     := rm -f
CP     := cp
EDIT   := emacs
PRINTF := printf

TEMPLATES = $(notdir $(wildcard $(TEMPLATES_DIR)/*))

include $(MK_DIR)/util.mk

makegoals := $(MAKECMDGOALS)
ifeq ($(makegoals),)
makegoals := all
endif

ifdef BUILD_TYPE
# Need to include it prior to walking the source tree
# (particularly because of ARCH definition).
include $(MK_DIR)/configure.mk
endif

ifneq ($(wildcard $(AUTOCONF_DIR)/build.mk),)
include $(MK_DIR)/image.mk
include $(MK_DIR)/codegen-dot.mk
endif

__get_subdirs = $(sort $(notdir $(call d-wildcard,$(1:%=%/*))))
build_patch_targets := $(patsubst %,%.target,$(filter-out $(notdir $(BACKUP_DIR)), \
  $(call __get_subdirs, $(CONF_DIR))))
ifndef $(SINGLE_TARGET)
build_targets = build_base_target $(build_patch_targets)
else
build_targets = $(SINGLE_TARGET)
endif
.PHONY: all build prepare docs dot clean config xconfig menuconfig
.PHONY: $(build_patch_targets) build_base_target build_targets

all: build_base_target 
all: $(build_patch_targets)
	@echo 'Build complete'

$(build_patch_targets):
	$(MAKE) BUILD_TYPE=patch PATCH_NAME=$(basename $@) build

build_base_target:	
	$(MAKE) BUILD_TYPE=base build

build: check_config prepare image
	@echo '$(PATCH_NAME) build complete'

prepare:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LIB_DIR)
	@mkdir -p $(AUTOCONF_DIR)
 
docs:
	@mkdir -p $(DOCS_DIR) && doxygen

dot: $(GRAPH_PS)
	@echo 'Dot complete'

clean: _clean
	@echo 'Clean complete'

distclean: _distclean
	@echo 'Distclean complete'

_clean:
	@$(RM) -rv $(BUILD_DIR)
#	@$(RM) -r $(BIN_DIR) $(OBJ_DIR) $(DOCS_DIR) $(AUTOCONF_DIR)
#	@$(RM) $(OBJS_ALL)
#	@$(RM) $(OBJS_ALL:.o=.d)
#	@$(RM) .config.old
#	@$(SCRIPTS_DIR)/ConfigBuilder/Misc/checksum.py \
#		-o $(OD_TOOL) -d $(BIN_DIR) -t $(TARGET) --build=$(BUILD) --clean

_distclean: _clean
	@$(RM) -rv $(BACKUP_DIR)
	@$(RM) -rv $(CONF_DIR)


config: _clean
ifndef PROFILE
	@echo 'Error: PROFILE undefined'
	@echo 'Usage: "make PROJECT=<project> PROFILE=<profile> config"'
	@echo '    See templates dir for possible projects and profiles'
	exit 1
endif
ifndef PROJECT
	@echo 'Error: PROJECT undefined'
	@echo 'Usage: "make PROJECT=<project> PROFILE=<profile> config"'
	@echo '    See templates dir for possible projects and profiles'
	exit 1
endif
	@test -d $(PROJECTS_DIR)/$(PROJECT) \
		|| (echo 'Error: project $(PROJECT) does not exist' \
			&& exit 1)
	@test -d $(PROJECTS_DIR)/$(PROJECT)/$(PROFILE) \
		|| (echo 'Error: profile $(PROFILE) does not exist in project $(PROJECT)' \
			&& exit 1)
	@if [ -d $(CONF_DIR) ];           \
	then                              \
		if [ -d $(BACKUP_DIR) ];      \
		then                          \
			$(RM) -r $(BACKUP_DIR)/*; \
		else                          \
			mkdir -p $(BACKUP_DIR);   \
		fi;                           \
		$(if $(filter-out $(BACKUP_DIR),$(wildcard $(CONF_DIR)/*)), \
			mv -fv -t $(BACKUP_DIR) \
				$(filter-out $(BACKUP_DIR),$(wildcard $(CONF_DIR)/*));, \
			rm -r $(BACKUP_DIR); \
		)                             \
	else                              \
		mkdir -p $(CONF_DIR);         \
	fi;
ifeq (0,1)
# That's an old variant of config creating system.
# It will be removed soon.
# Just not to search long if smth goes wrong %)
	@$(foreach dir,$(call __get_subdirs,$(PROJECTS_DIR)/$(PROJECT)/$(PROFILE)), \
	  mkdir -p $(CONF_DIR)/$(dir); \
	  cp -fv -t $(CONF_DIR)/$(dir) \
	     $(wildcard $(PROJECTS_DIR)/$(PROJECT)/$(PROFILE)/*); \
	  $(if $(wildcard $(PROJECTS_DIR)/$(PROJECT)/$(PROFILE)/$(dir)/*), \
	    cp -fv -t $(CONF_DIR)/$(dir) \
	       $(wildcard $(PROJECTS_DIR)/$(PROJECT)/$(PROFILE)/$(dir)/*); \
	  ) \
	)
else
# That's a new variant. 
# We just copy from templates dir to conf dir
	@cp -fv -R -t $(CONF_DIR) \
	  $(wildcard $(PROJECTS_DIR)/$(PROJECT)/$(PROFILE)/*);
endif
	@echo 'Config complete'

menuconfig:
	make PROFILE=`dialog \
		--stdout --backtitle "Configuration template selection" \
		--radiolist "Select template to load:" 10 40 3 \
		$(patsubst %,% "" off,$(TEMPLATES))` \
	config
	@$(EDIT) -nw $(CONF_DIR)/*.conf

xconfig:
	make PROFILE=`Xdialog \
		--stdout --backtitle "Configuration template selection" \
		--radiolist "Select template to load:" 20 40 3 \
		$(patsubst %,% "" off,$(TEMPLATES))` \
	config
	@$(EDIT) $(CONF_DIR)/*.conf

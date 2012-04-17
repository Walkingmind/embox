# $Id$
#
# Loads my- and config-files, links them together, and infers the build model.
#
#   Date: Feb 9, 2012
# Author: Eldar Abusalimov
# Author: Anton Kozlov
#

MYFILES_PATH := mk/ src/ platform/ third-party/
MYFILES := \
	$(shell find $(MYFILES_PATH) -depth \
		\( -name Mybuild -o -name \*.my \) -print)

CONFIGFILES_PATH := $(CONF_DIR)
CONFIGFILES := $(wildcard $(CONFIGFILES_PATH)/*.config)

ifeq ($(strip $(CONFIGFILES)),)
$(error No config files were found in '$(CONFIGFILES_PATH)')
endif

ifneq ($(word 2,$(CONFIGFILES)),)
$(error Handling multiplie config files is not implemented: '$(CONFIGFILES)')
endif

#
# Directories where to put generated scripts.
#
ifndef CACHE_DIR
$(error CACHE_DIR is not defined, \
	do not include this script directly, use mk/load.mk instead)
endif

export MYBUILD_CACHE_DIR       := $(CACHE_DIR)/mybuild
export MYBUILD_FILES_CACHE_DIR := $(MYBUILD_CACHE_DIR)/files

#
# Generated artifacts.
#

# My-files.
myfiles_mk := \
	$(patsubst $(abspath ./%),$(MYBUILD_FILES_CACHE_DIR)/%.mk, \
		$(abspath $(MYFILES)))
$(myfiles_mk) : recipe_tag      := MYFILE
$(myfiles_mk) : MAKEFILES       := $(mk_mybuild_myfile)
$(myfiles_mk) : PERSIST_OBJECTS  = $$(call new,MyFileResource,$<)

# Config-files.
configfiles_mk := \
	$(patsubst $(abspath ./%),$(MYBUILD_FILES_CACHE_DIR)/%.mk, \
		$(abspath $(CONFIGFILES)))
$(configfiles_mk) : recipe_tag      := CONFIGFILE
$(configfiles_mk) : MAKEFILES       := $(mk_mybuild_configfile)
$(configfiles_mk) : PERSIST_OBJECTS  = $$(call new,ConfigFileResource,$<)

# Defaults, must be overridden with target-specific variables.
$(myfiles_mk) $(configfiles_mk) : export PERSIST_OBJECTS ?=
$(myfiles_mk) $(configfiles_mk) : export MAKEFILES ?=

$(myfiles_mk) $(configfiles_mk) : $$(MAKEFILES)
$(myfiles_mk) $(configfiles_mk) : mk/load-mybuild.inc.mk
$(myfiles_mk) $(configfiles_mk) : mk/script/mk-persist.mk
$(myfiles_mk) $(configfiles_mk) : | $$(@D)/.

$(myfiles_mk) $(configfiles_mk) : $(MYBUILD_FILES_CACHE_DIR)/%.mk : %
	@echo ' $(recipe_tag) $<'
	@SCOPE=`echo '$<' | sum | cut -f 1 -d ' '`; \
	$(MAKE) -f mk/script/mk-persist.mk ALLOC_SCOPE="p$$SCOPE" > $@ && \
	echo '$$(lastword $$(MAKEFILE_LIST)) := '".obj1p$$SCOPE" >> $@

#
# Linking files together.
#

# My-files.
export myfiles_model_mk := $(MYBUILD_CACHE_DIR)/myfiles-model.mk
myfiles_mk_cached_list_mk := $(MYBUILD_CACHE_DIR)/myfiles-list.mk

$(myfiles_model_mk) : MAKEFILES := $(mk_mybuild_myfile) $(myfiles_mk)
$(myfiles_model_mk) :
	@echo ' MYLINK: $(words $(myfiles_mk)) files $(__myfiles_model_stats)'
	@$(MAKE) -f mk/script/mk-persist.mk \
		PERSIST_OBJECTS='$$(call myfile_create_resource_set_from_files,$(myfiles_mk))' \
		PERSIST_REALLOC='my' \
		PERSIST_VARIABLE='__myfile_resource_set' \
		ALLOC_SCOPE='z' > $@
	@$(PRINTF) 'myfiles_mk_cached := %b' '$(myfiles_mk:%=\\\n\t%)' \
		> $(myfiles_mk_cached_list_mk)
load_mybuild_files += $(myfiles_model_mk)

# Config-files are linked agains linked model of my-files.
export configfiles_model_mk := $(MYBUILD_CACHE_DIR)/configfiles-model.mk

$(configfiles_model_mk) : MAKEFILES := $(mk_mybuild_configfile) $(configfiles_mk) $(myfiles_model_mk)
$(configfiles_model_mk) :
	@echo ' CONFIGLINK'
	@$(MAKE) -f mk/script/mk-persist.mk \
		PERSIST_OBJECTS='$$(call config_create_resource_set_from_files,$(configfiles_mk))' \
		PERSIST_REALLOC='cfg' \
		PERSIST_VARIABLE='__config_resource_set' \
		ALLOC_SCOPE='y' > $@
load_mybuild_files += $(configfiles_model_mk)

export load_mybuild_files := $(load_mybuild_files)

$(load_mybuild_files) : export MAKEFILES ?=

$(load_mybuild_files) : $$(MAKEFILES)
$(load_mybuild_files) : mk/load-mybuild.inc.mk
$(load_mybuild_files) : mk/script/mk-persist.mk
$(load_mybuild_files) : | $$(@D)/.

#
# Added/removed myfiles detection.
#

-include $(myfiles_mk_cached_list_mk)
myfiles_mk_cached ?=

export myfiles_mk_added := \
	$(filter-out $(myfiles_mk_cached),$(myfiles_mk))
export myfiles_mk_removed := \
	$(filter-out $(myfiles_mk),$(myfiles_mk_cached))

ifneq ($(or $(myfiles_mk_added),$(myfiles_mk_removed)),)
.PHONY : $(myfiles_model_mk)
ifneq ($(filter-out recursive,$(flavor myfiles_mk_cached)),)
$(myfiles_model_mk) : __myfiles_model_stats := ($(if \
		$(myfiles_mk_added),$(words $(myfiles_mk_added)) added)$(and \
		$(myfiles_mk_added),$(myfiles_mk_removed),$(if ,,, ))$(if \
		$(myfiles_mk_removed),$(words $(myfiles_mk_removed)) removed))
endif
endif

$(myfiles_model_mk) : __myfiles_model_stats ?=


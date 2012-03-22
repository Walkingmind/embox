# $Id$
#
# Third stage: loads conf-files.
#
#   Date: Feb 9, 2012
# Author: Eldar Abusalimov
# Author: Anton Kozlov
# 		- Generate config related stuff 
#

export CONFIGFILES_CACHE_DIR := $(MYBUILD_CACHE_DIR)/config

CONFIG_PATH := conf
CONFIG_GENERATED_PATH := build/base/codegen

HOSTCPP = gcc -E

HOSTCC_CPPFLAGS := -I$(CONFIG_PATH)

CONFIG_GENERATED := $(CONFIG_GENERATED_PATH)/genConf.config

$(CONFIG_GENERATED) : 
	mkdir -p $(@D)
	$(HOSTCPP) -P -undef -nostdinc $(HOSTCC_CPPFLAGS) \
		-MMD -MT $@ -MF $@.d -D__MODS_CONF__ mk/confmacro2.S | \
		awk -f mk/confmacro2.awk > $@

-include $(CONFIG_GENERATED:%=%.d)

#CONFIGFILES := \
#	$(shell find $(CONFIG_PATH) -depth \
#		-name \*.config -print) \
#	$(CONFIG_GENERATED)
#CONFIGFILES := $(firstword $(CONFIGFILES))

CONFIGFILES := $(CONFIG_GENERATED)

export configfiles_mk := \
	$(patsubst $(abspath ./%),$(CONFIGFILES_CACHE_DIR)/%.mk, \
		$(abspath $(CONFIGFILES)))

configfiles_linked_mk := $(CONFIGFILES_CACHE_DIR)/config_files_linked.mk

$(MAKECMDGOALS) : $(configfiles_linked_mk) 
	@$(MAKE) -f mk/main.mk MAKEFILES='$(all_mk_files) $(mybuild_model_mk) $<' $@

.DELETE_ON_ERROR:

.PHONY : $(configfiles_linked_mk) 

$(configfiles_mk) : $(CONFIGFILES)

$(configfiles_mk) : mk/load3.mk
$(configfiles_mk) : mk/script/mk-persist.mk
$(configfiles_mk) : $(CONFIGFILES_CACHE_DIR)/%.mk : %
	@echo ' CONFIGFILE $<'
	@SCOPE=`echo '$<' | sum | cut -f 1 -d ' '`; \
	mkdir -p $(@D) && \
	$(MAKE) -f mk/script/mk-persist.mk MAKEFILES='$(mk_mybuild_configfile)' \
		PERSIST_OBJECTS='$$(call new,ConfigFileResource,$<)' \
		ALLOC_SCOPE="r$$SCOPE" > $@ && \
	echo '$$(lastword $$(MAKEFILE_LIST)) := '".obj1r$$SCOPE" >> $@

$(configfiles_linked_mk) : $(configfiles_mk)
	@mkdir -p $(@D) && \
		$(MAKE) -f mk/script/mk-persist.mk \
		MAKEFILES='$(mk_mybuild) $(configfiles_mk) $(mybuild_model_mk)' \
		PERSIST_OBJECTS='$$(call config_create_resource_set_from_files,$$(configfiles_mk))' \
		PERSIST_REALLOC='cfg' \
		ALLOC_SCOPE='c' > $@
	@echo '__config_resource_set := .cfg1c' >> $@

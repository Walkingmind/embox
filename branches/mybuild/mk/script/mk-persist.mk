# $Id$
#
#   Date: Feb 9, 2012
# Author: Eldar Abusalimov
#

.PHONY : all
all :
	@#

include mk/script/check-make-flags.mk

ifndef PERSIST_OBJECTS
$(error PERSIST_OBJECTS is not defined, nothing to serialize)
endif

# All incoming variables must be flattened on order to prevent
# expanding them once again.
override PERSIST_OBJECTS := $(PERSIST_OBJECTS)

$(info # Generated by GNU Make $(MAKE_VERSION). Do not edit.)
$(info )
$(info $(\h) PERSIST_OBJECTS:)
$(foreach o,$(or $(PERSIST_OBJECTS),<nothing>),$(info $(\h)   $o))
$(info )

ifdef PERSIST_REALLOC

override PERSIST_REALLOC := $(PERSIST_REALLOC)
__persist_id_provider = \
	$(foreach id,.$(PERSIST_REALLOC)$(call alloc,$(PERSIST_REALLOC)),$(eval \
		__persist_realloced += $(id))$(id))

$(info $(call object_graph_print,$(PERSIST_OBJECTS),__persist_id_provider))

$(info # Seal these objects (prevent further serialization).)
$(foreach id,$(value __persist_realloced),\
	$(info $(id).__serial_id__ := $(id)))
$(info )

else

$(info $(call object_graph_print,$(PERSIST_OBJECTS)))

endif # PERSIST_REALLOC

ifdef PERSIST_VARIABLE

override PERSIST_VARIABLE := $(PERSIST_VARIABLE)

$(info # List of objects requested to be serialized explicitly.)
$(info $(PERSIST_VARIABLE) := \
	$(foreach o,$(PERSIST_OBJECTS),\$(\n)$(\t)$($o.__serial_id__)))
$(info )

endif # PERSIST_VARIABLE

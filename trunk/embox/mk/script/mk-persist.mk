# $Id$
#
#   Date: Feb 9, 2012
# Author: Eldar Abusalimov
#

.PHONY : all
all :
	@#

ifndef PERSIST_OBJECTS
$(error PERSIST_OBJECTS is not defined, nothing to serialize)
endif

ifndef mk_core_obj
$(error mk_core_obj is not defined, use the loader to run this script)
endif

include $(filter-out $(MAKEFILE_LIST),$(mk_core_obj))

# All incoming variables must be flattened on order to prevent
# expanding them once again.
override PERSIST_OBJECTS := $(PERSIST_OBJECTS)

$(info # Generated by GNU Make $(MAKE_VERSION) on $(shell date).)
$(info )
$(info $(\h) PERSIST_OBJECTS:)
$(foreach o,$(or $(PERSIST_OBJECTS),<nothing>),$(info $(\h)   $o))
$(info )

ifdef PERSIST_REALLOC

override PERSIST_REALLOC := $(PERSIST_REALLOC)
__persist_id_provider = .$(PERSIST_REALLOC)$(call alloc,$(PERSIST_REALLOC))

$(info $(call object_graph_print,$(PERSIST_OBJECTS),__persist_id_provider))

else

$(info $(call object_graph_print,$(PERSIST_OBJECTS)))

endif

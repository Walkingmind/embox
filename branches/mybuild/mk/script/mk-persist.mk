# $Id: $
#
#   Date: Feb 9, 2012
# Author: Eldar Abusalimov
#

ifndef PERSIST_OBJECTS
$(error PERSIST_OBJECTS is not defined, nothing to serialize)
endif

ifndef mk_core_obj
$(error mk_core_obj is not defined, use the loader to run this script)
endef

include $(mk_core_obj)

__PERSIST_OBJECTS := $(PERSIST_OBJECTS)

$(info # Generated by GNU Make $(MAKE_VERSION) on $(shell date).)
$(info )
$(info $(\h) PERSIST_OBJECTS:)
$(foreach o,$(or $(__PERSIST_OBJECTS),<nothing>),$(info $(\h)   $o))
$(info )
$(info $(call object_graph_print,$(__PERSIST_OBJECTS)))
$(info )

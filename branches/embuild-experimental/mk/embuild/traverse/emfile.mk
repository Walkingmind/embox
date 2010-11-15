# $Id: $
#
# Traverser sandbox for em-files.
#
#   Date: Nov 13, 2010
# Author: Eldar Abusalimov
#

__embuild_traverse_emfile_needs := \
  __EMBUILD_TRAVERSE_EMFILE_ROOT \
  __EMBUILD_TRAVERSE_EMFILE

__embuild_traverse_emfile_needs_undefined := $(strip \
  $(foreach var,$(__embuild_traverse_emfile_needs), \
    $(if $(filter undefined,$(flavor $(var))),$(var)) \
  ) \
)

ifneq ($(__embuild_traverse_emfile_needs_undefined),)
define error_msg
Traverser em-file sandbox needs the following variables to be defined:
  $(__embuild_traverse_emfile_needs_undefined)
endef
$(error $(error_msg))
endif

__embuild_traverse_emfile_variables :=
__embuild_traverse_emfile_variables := $(.VARIABLES)

# Go!
include $(__EMBUILD_TRAVERSE_EMFILE_ROOT)/$(__EMBUILD_TRAVERSE_EMFILE)

__embuild_traverse_emfile_variables := \
  $(filter-out $(__embuild_traverse_emfile_variables),$(.VARIABLES))

# Now we are free to include some other files.
include embuild/traverse/entity.mk

__embuild_traverse_emfile_entity_variables := \
  $(filter $(__embuild_traverse_entity_types:%=%-%), \
           $(__embuild_traverse_emfile_variables))
__embuild_traverse_emfile_entity_targets := \
  $(__embuild_traverse_emfile_entity_variables:%=__embuild_traverse_emfile_%)

.PHONY: all
.PHONY: $(__embuild_traverse_emfile_entity_targets)
all: $(__embuild_traverse_emfile_entity_targets)

__embuild_traverse_emfile_%: \
  export __EMBUILD_TRAVERSE_ENTITY_FILE = $(__EMBUILD_TRAVERSE_EMFILE)

__embuild_traverse_emfile_%: \
  export __EMBUILD_TRAVERSE_ENTITY = $(value $*)

__embuild_traverse_emfile_module-%: \
  export __EMBUILD_TRAVERSE_ENTITY_TYPE = module

#$(__embuild_traverse_entity_types:%=__embuild_traverse_emfile_%-%):
__embuild_traverse_emfile_module-%:
	$(MAKE) -f mk/embuild/traverse/entity.mk \
		__EMBUILD_TRAVERSE_ENTITY_NAME=$(dir $(__EMBUILD_TRAVERSE_EMFILE))/$*



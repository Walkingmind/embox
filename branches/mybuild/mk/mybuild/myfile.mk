# $Id: myfile-model.mk 4454 2011-12-19 15:55:06Z drakon.mega $
#
# MyFile facade.
#
#   Date: Dec 20, 2011
# Author: Eldar Abusalimov
#

ifndef __mybuild_myfile_mk
__mybuild_myfile_mk := $(lastword $(MAKEFILE_LIST))

include $(addprefix $(__mybuild_myfile_mk)), \
			-model-old.mk -parser.mk)

$(def_all)

endif # __mybuild_myfile_mk


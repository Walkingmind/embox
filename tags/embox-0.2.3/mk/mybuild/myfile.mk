# Generated by GOLD Parser Builder using MyBuild program template.

# Parser for 'MyFile' grammar (version 0.1): MyBuild file.
# Author: Eldar Abusalimov

#
# Every parser is defined in its own namespace specified by 'gold_grammar'
# variable. Its value is primarily used to refer the grammar when calling
# 'gold_parse'.
#
gold_grammar := myfile

ifeq ($(call singleword,$(gold_grammar)),)
$(error 'gold_grammar' is empty or not a single word, \
	you have to define it properly in order to continue)
endif

gold_grammar := $(call trim,$(gold_grammar))

ifndef __gold_grammar_$(gold_grammar)_mk
__gold_grammar_$(gold_grammar)_mk := $(lastword $(MAKEFILE_LIST))

include mk/gold/engine.mk

#
# Include tables file and constructors for symbols and rules.
#
include $(addprefix \
			$(dir $(__gold_grammar_$(gold_grammar)_mk))$(gold_grammar)-, \
			tables.mk symbols.mk rules.mk)

$(def_all)

gold_grammar :=# Undefine.

endif # __gold_grammar_$(gold_grammar)_mk


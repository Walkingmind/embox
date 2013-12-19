##LANGUAGE 'GNU Make'
##ENGINE-NAME 'MyBuild'
##TEMPLATE-NAME 'Main script'
##AUTHOR 'Eldar Abusalimov'
##FILE-EXTENSION 'mk'
##NOTES
This template generates the facade script which defines the name of your parser
and includes necessary files. This is the main file from user's point of view.

By default the parser will be named by the filename without an extension. Also
this name will be used to include the rest scripts. For example, given the name
of output file is 'mygrammar.mk', then the parser gets name 'mygrammar',
and the following files will be also included:
'mygrammar-tables.mk', 'mygrammar-rules.mk' and 'mygrammar-symbols.mk'.
##END-NOTES
##DELIMITER ','
##ID-SEPARATOR '_'
# Generated by GOLD Parser Builder using MyBuild program template.

##PARAMETERS
# Parser for '%Name%' grammar (version %Version%): %About%.
# Author: %Author%
##END-PARAMETERS

#
# Every parser is defined in its own namespace specified by 'gold_grammar'
# variable. Its value is primarily used to refer the grammar when calling
# 'gold_parse'.
#
# TODO Override this variable to define everything in a different namespace.
# Defaults to the basename of the definition script. Must be a single word.
gold_grammar := %OutputFileBase%

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
# TODO By default it is assumed that you'll place grammar-related files
# in the same directory with this one and name them
# with '-tables', '-symbols' and '-rules' suffixes.
# Fix the following 'include' directives to override the default behavior.
include $(basename $(__gold_grammar_$(gold_grammar)_mk))-tables.mk

# Productions and symbols are not mandatory.
-include $(addprefix $(basename $(__gold_grammar_$(gold_grammar)_mk)), \
			-symbols.mk -rules.mk)

$(def_all)

gold_grammar :=# Undefine.

endif # __gold_grammar_$(gold_grammar)_mk

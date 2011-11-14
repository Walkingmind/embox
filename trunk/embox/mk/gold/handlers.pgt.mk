##TEMPLATE-NAME 'Make - MyBuild engine (application stub)'
##LANGUAGE 'GNU Make'
##ENGINE-NAME 'MyBuild'
##AUTHOR 'Eldar Abusalimov' 
##FILE-EXTENSION 'mk'
##NOTES
This template generates handler function stubs for symbols and rules.

Handlers are used to convert each node of a parse tree into
an application-specific representation.
##END-NOTES
##DELIMITER ','
##ID-SEPARATOR '_'
##PARAMETERS
# Application for '%Name%' grammar (version %Version%).
#    %About%
# Author: %Author%
##END-PARAMETERS

#
# All API functions and internals of the parser are defined in their own
# namespace which defaults to the basename of the definition script.
#
# This name is primarily used to refer the grammar when calling
# 'gold_parse_file' and 'gold_parse_stream' functions.
#

# Override this variable to define everything in a different namespace.
# Must be a single word.
gold_prefix := $(basename $(notdir $(lastword $(MAKEFILE_LIST))))

ifeq ($(call singleword,$(gold_prefix)),)
$(error 'gold_prefix' is empty or not a single word, \
	you have to define it properly in order to continue)
endif

gold_prefix := $(call trim,$(gold_prefix))

ifndef __gold_grammar_$(gold_prefix)_mk
__gold_grammar_$(gold_prefix)_mk := 1

# By default it is assumed that you'll place tables file in the same directory
# with this one and name it with '-tables' prefix.

# Fix the following line to override default behavior.
include $(dir $(lastword $(MAKEFILE_LIST)))$(gold_prefix)-tables.mk

#
# Symbols.
#
# Each symbol is converted by the corresponding handler (if any has been
# defined). Handler is a function with the following signature:
#
# Params:
#   For terminals:
#     1. List of decimal char codes representing the token.
#     2. Location of the first character of this token: 'line:column'.
#   For nonterminals:
#     1. The result of applying one of rule handlers (it may be used
#        to extract common symbol value postprocessing from its rules).
#
# Return:
#   Converted value. The value is then passed to a rule containing that symbol
#   in its RHS or returned to user in case of the Start Symbol.
#

##SYMBOLS
# Symbol: %Description%
#define $(gold_prefix)_create-%ID%
#	$(gold_default_create)# TODO Auto-generated stub! Uncomment to override.
#endef

##END-SYMBOLS

#
# For each regular terminal we also define a constant with a human-readable
# description. Due to current limitations of template generator a definition
# is generated for all existing symbols, although variables for nonterminals
# are never actually used.
#

##SYMBOLS
define $(gold_prefix)_name_of-%ID%
	%Description% 
endef
$(gold_prefix)_name_of-%ID% := \
	$(call trim,$(value $(gold_prefix)_name_of-%ID%))

##END-SYMBOLS


#
# Rules.
#
# As for symbols each rule can have a handler that is used to create an
# application-specific representation if the rule data.
# The signature of handlers is the following:
#
# Params:
#  ... Each argument contains a value of the corresponding symbol
#      in the rule's RHS.
#
# Return:
#   Converted value that is passed to a symbol handler corresponding to
#   the rule's LHS (if any has been defined).
#

##RULES
# Rule: %Description%
#define $(gold_prefix)_produce-%ID%
#	$(gold_default_produce)# TODO Auto-generated stub! Uncomment to override.
#endef

##END-RULES

$(def_all)

gold_prefix :=# Undefine.

endif # __gold_grammar_$(gold_prefix)_mk


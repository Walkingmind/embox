##TEMPLATE-NAME 'Make MyBuild'
##LANGUAGE 'GNU Make'
##ENGINE-NAME 'MyBuild'
##AUTHOR 'Eldar Abusalimov' 
##FILE-EXTENSION 'mk'
##NOTES
This template outputs the tables using extended syntax of Make functional language.
##END-NOTES
##DELIMITER ','
##ID-SEPARATOR '_'
##ID-SYMBOL-PREFIX 'Symbol'
##ID-RULE-PREFIX 'Rule'
##PARAMETERS

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
#   1. For terminals it is a list of decimal char codes representing the token.
#      For nonterminals - the result of applying one of rule handlers (it may
#      be used to extract common symbol value postprocessing from its rules).
#
# Return:
#   Converted value. The value is then passed to a rule containing that symbol
#   in its RHS or returned to user in case of the Start Symbol.
#

##SYMBOLS
# Symbol: %Description%
define $(gold_prefix)_%ID%
	# TODO Auto-generated token handler stub! Returns empty by default.
endef

##END-SYMBOLS

#
# Rules.
#

##RULES
# Rule: %Description%
define $(gold_prefix)_%ID%
	# TODO Auto-generated rule handler stub! Returns empty by default.
endef

##END-RULES

$(def_all)

gold_prefix :=# Undefine.

endif # __gold_grammar_$(gold_prefix)_mk


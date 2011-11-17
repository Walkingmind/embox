##TEMPLATE-NAME 'Make - MyBuild engine (Symbols)'
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
# Symbols.
#
# Each symbol is converted by the corresponding constructor (if any has been
# defined). Constructor is a function named '$(gold_grammar)_create-<ID>'
# (where ID is a unique symbol identifier) with the following signature:
#
# Params:
#   1. For terminals: a list of decimal char codes representing the token.
#      For nonterminals: the result of production.
#   2. Start location in form 'line:column'.
#
# Return:
#   Converted value. The value is then passed to a rule containing that symbol
#   in its RHS or returned to user in case of the Start Symbol.
#
# If constructor for some symbol is not defined then the default behavior
# is used:
#   For terminals:
#     Decodes an input by replacing all printable characters with their values
#     and the rest ones with spaces.
#   For nonterminals:
#     Outputs the result of production as is, without modifying it.
#
# Constructor may also use a special 'gold_default_create' function to get
# the default value.
#

#
# Symbol contructors.
#
# TODO You can safely remove any constructor if the default behavior is ok.
#

##SYMBOLS
# Symbol: %Description%
define $(gold_grammar)_create-%ID%
	$(gold_default_create)# TODO Auto-generated stub!
endef

##END-SYMBOLS

#
# Optimized contructors for constant terminals (i.e. keywords and punctuation).
#
# TODO Uncomment (and fix if needed) the lines corresponding to terminals
# which are known to be immutable. This eliminates the need to convert them
# from an input each time when a new token arrives.
#

##SYMBOLS
#$(gold_grammar)_create-%ID.Padded% := %ID%
##END-SYMBOLS

#
# For each regular terminal we also define a constant with a human-readable
# description used for error reporting.
#
# TODO Due to current limitations of template generator a definition
# is generated for all existing symbols, although variables for nonterminals
# are never actually used.
#

##SYMBOLS
$(gold_grammar)_name_of-%ID.Padded% := %Description%
##END-SYMBOLS


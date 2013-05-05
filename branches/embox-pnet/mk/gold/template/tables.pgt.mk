##LANGUAGE 'GNU Make'
##ENGINE-NAME 'Mybuild'
##TEMPLATE-NAME 'Parser tables'
##AUTHOR 'Eldar Abusalimov'
##FILE-EXTENSION 'mk'
##NOTES
This template outputs all necessary tables for the parser.
In general you have to name this file the same as base name of the main script
with '-tables' suffix.

You should not modify the generated file.
##END-NOTES
##ID-SEPARATOR '_'
# Generated by GOLD Parser Builder using Mybuild program template. Do not edit!

##PARAMETERS
# Grammar info:
#   Name            : %Name%
#   Version         : %Version%
#   Author          : %Author%
#   About           : %About%
#   Case Sensitive  : %CaseSensitive%
#   Start Symbol    : %StartSymbol%
##END-PARAMETERS

ifndef gold_grammar
$(error 'gold_grammar' is not defined. \
	Do not include $(notdir $(lastword $(MAKEFILE_LIST))) directly!)
endif # gold_grammar

# Contains all necessary tables.
define __gold_$(gold_grammar)_parser
	$(gold-parser \
##SYMBOL-TABLE
		# Symbols.
		# 	$(gold-symbol <ID>,
		# 		<Type>,
		# 		<Function name>
		# 	),
		$(gold-symbol-table \
##SYMBOLS
			$(gold-symbol %Index%,%Kind%,%ID%),
##END-SYMBOLS
		),# Total %Count% symbol(s).
##END-SYMBOL-TABLE

##RULE-TABLE
		# Rules.
		# 	$(gold-rule <ID>,
		# 		<LHS nonterminal ID>,
		# 		<RHS total symbols>,
		# 		<Function name>
		# 	),
		$(gold-rule-table \
##RULES
			$(gold-rule %Index%,%NonterminalIndex%,%SymbolCount%,%ID%),
##END-RULES
		),# Total %Count% rule(s).
##END-RULE-TABLE

##CHAR-SET-TABLE
		# Charsets.
		# 	$(gold-charset <ID>,
		# 		<List of chars>
		# 	),
		$(gold-charset-table \
##CHAR-SETS
##RANGE-CHARS '.'
##DELIMITER ';'
			$(gold-charset %Index%,%Chars.RangeList%),
##END-CHAR-SETS
		),# Total %Count% charset(s).
##END-CHAR-SET-TABLE

##DFA-TABLE
		# DFA states.
		# 	$(gold-dfa-state <ID>,
		# 		<Accept symbol ID or -1>,
		# 		$(gold-dfa-edge <Charset ID>,
		# 			<Target state ID>
		# 		),
		# 		...
		# 	),
		$(gold-dfa-table $(def-id \
				%InitialState%# Initial state ID.
##DFA-STATES
			),$(gold-dfa-state %Index%,%AcceptIndex%,
##DFA-EDGES
				$(gold-dfa-edge %CharSetIndex%,%Target%),
##END-DFA-EDGES
##END-DFA-STATES
			)
		),# Total %Count% DFA state(s).
##END-DFA-TABLE

##LALR-TABLE
		# LALR states.
		# 	$(gold-lalr-state <ID>,
		# 		$(gold-lalr-action <Symbol ID>,
		# 			<Action>,
		# 			<Value>
		# 		),
		# 		...
		# 	),
		$(gold-lalr-table $(def-id \
				%InitialState%# Initial state ID.
##LALR-STATES
			),$(gold-lalr-state %Index%,
##LALR-ACTIONS
				$(gold-lalr-action %SymbolIndex%,%Action%,%Value%),
##END-LALR-ACTIONS
##END-LALR-STATES
			)
		)# Total %Count% LALR state(s).
##END-LALR-TABLE

	)
endef # __gold_$(gold_grammar)_parser

$(def_all)


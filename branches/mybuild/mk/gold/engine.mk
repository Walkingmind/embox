# $Id$

#
# Copyright 2011, Mathematics and Mechanics faculty
#                   of Saint-Petersburg State University. All rights reserved.
# Copyright 2011, Lanit-Tercom Inc. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#

#
# Builtins and runtime support for parsers generated by GOLD.
#
#   Date: Oct 26, 2011
# Author: Eldar Abusalimov
#

ifndef __gold_engine_mk
__gold_engine_mk := 1

##
# Technology overview.
#
# This is an engine for GOLD Parsing System, and its design is largely implied
# by concepts of GOLD itself.
#
# Parsing is performed in three main stages:
#   - Lexical analysis using DFA scanned,
#   - Syntactic analysis with LALR parser, and
#   - Parse tree interpretation.
#
# The first two stages are common for all GOLD parser engines, a general
# overview of them is available at http://www.goldparser.org/.
# Instead of providing stream-like API, where each token/action is retrieved by
# a corresponding calls inside a parse loop, this implementation uses another
# approach. First, we iterate through the whole list of input characters
# constructing a list of recognized terminals. Then, the resulting list is
# trasformed into a parse tree, again just by iterating over the tokens.
#
# The only stage that involves calling of a user code is the third phase, where
# the parse tree is interpreted by invoking user-defined functions for each
# node of the tree.
# Nodes are tranformed from a leaves upwards to the root: the result of
# calling a handler for some node is passed as an argument to a handler of its
# parent node. Finally, the result of transforming the root is returned to the
# client.
#

include mk/core/common.mk
include mk/core/string.mk
include mk/core/define.mk

include mk/util/var/assign.mk
include mk/util/var/info.mk

##
# Function: gold_parse
# Parses the given file with a grammar specified by its prefix.
#
# Params:
#   1. The name used for definitions in your grammar files.
#   2. Input file name.
# Return:
#   Result of interpreting parse tree with user-defined handlers
#   or empty on error.
# Note:
#   The grammar must be previously loaded.
define gold_parse
	$(if $(not $(singleword $1)),
		$(error Invalid grammar name: '$1')
	)

	$(if $(call var_undefined,__gold_$1_parser),
		$(error Grammar '$1' does not seem to be loaded)
	)

	$(foreach gold_grammar,$1,$(foreach g,__g_$(gold_grammar),
		$(foreach gold_file,$2,
			$(__gold_parse)
		)
	))
endef

# Params:
#   1. List of decimal char codes.
# Context:
#   g. Prefix.
# Return:
#   Result of interpreting parse tree using user-defined handlers.
define __gold_parse
	$(call __gold_expand,
		$(call __gold_analyze,
			$(call __gold_lex,
				$(call __gold_read_file,$(gold_file))
			)
		)
	)
endef

# Params:
#   1. File name.
# Return:
#   List of decimal char codes.
__gold_read_file = \
	$(shell od -v -A n -t uC $1)

# Parser private namespace for builtins context. The same as $g in runtime.
__gold_ns = $(call builtin_tag,gold-parser)

define builtin_tag-gold-parser
	$(or \
		$(filter-patsubst __gold_%_parser,__g_%,$(__def_var)),
		$(call builtin_error,
			Bad variable name: '$(__def_var)'
		)
	)
endef

# Params: ignored
define builtin_func-gold-parser
	${eval \
		__def_ignore += $(__gold_ns)%
	}
endef

#
# Symbols.
#
#	$(gold-symbol-table \
#		$(gold-symbol  0,3,# (EOF)
#			Symbol_Eof),
#		# ...
#	),
#
# Symbols are easy: each one is represented by a simple variable:
#
#	$g_symbol$(id) := $(type) $(handler)
#
# where:
#      'id' is an index of the symbol,
#    'type' defines a kind of the symbol:
#            0: Normal Nonterminal
#            1: Normal Terminal
#            2: Whitespace Terminal
#            3: End of File
#            4: Start of a block quote (Not supported)
#            5: End of a block quote (Not supported)
#            6: Line Comment Terminal (Not supported)
#            7: Error Terminal
# 'handler' is a name of a function used to instantiate terminal tokens
#           from the list of character codes, and
#       'g' refers to a namespace of a parser.
#

# Params:
#   1. Id.
#   2. Symbol type (see above).
#   3. Instantiation function.
define builtin_func-gold-symbol
	$(assert $(if $(eq 0,$1),$(eq 3,$2),ok),
		EOF terminal is assumed to have Id 0)
	$(assert $(if $(eq 1,$1),$(eq 7,$2),ok),
		Error terminal is assumed to have Id 1)
	$(assert $(if $(eq 2,$1),$(eq 2,$2),ok),
		Whitespace terminal is assumed to have Id 2)

	$(if $(filter 4 5 6,$2),
		$(call builtin_error,
			Comment terminals are not supported, \
				incorporate them into whitespace terminal
		)
	)

	$(call var_assign_simple,$(__gold_ns)_symbol$1,
		$2 $3
	)
endef

# 1. Id.
__gold_symbol_type = \
	$(firstword $($g_symbol$1))
# 1. Id.
__gold_symbol_fn = \
	$(secondword $($g_symbol$1))

builtin_func-gold-symbol-table :=# Noop.

#
# Rules.
#
#	$(gold-rule-table \
#		$(gold-rule 0,9,1,# <Program> ::= <Expression>
#			Rule_Program),
#		# ...
#	),
#
# For each rule we define a simple variable in parser's namespace:
#
#	$g_rule$(id) := $(nonterminal_id) $(number_of_symbols) $(handler)
#
# where:
#      'id' is an index of the rule,
# 'nonterminal_id'    points to a symbol produced by the rule (LHS),
# 'number_of_symbols' number of symbols in RHS,
# 'handler' is a name of a function called when the parser completes reading
#           all of the rule's symbols, and
#       'g' refers to a namespace of a parser.
#
# Also there are few auxiliary variables defined in a common namespace and
# shared by all parsers:
#
#	__gold_seq$(n)-1 := <sequence of numbers from 1 to N minus one>
#	__gold_n$(n)+1  := <literal value of N plus one>
#
# where 'n' gets all possible values of number of symbols for each defined
# rule (except for zero). These values are used later in LALR reduce handler.
#
#	__gold_hook_rule_n$(n) = <proxy function>
#	__gold_args$(n) = <Space separated arguments from $1 to $(N)>
#
# The latters are used by in last parsing phase to redirect expansion hooks
# and echo a certain number of arguments correspondingly.
#

# Params:
#   1. Id
#   2. Nonterminal
#   3. Number of symbols in right-hand side
#   4. Instantiation function.
define builtin_func-gold-rule
	$(and \
		$(filter-out 0,$3),
		$(call var_undefined,__gold_seq$3),

		# Each __gold_seqN-1 contains N-1 whitespace separated 'x's
		# __gold_seq3-1 = 1 2
		$(call var_assign_simple,__gold_seq$3-1,
			$(with $3,,
				$(if $(word $1,$2 x),
					$2,
					$(call $0,$1,$2 $(words $2 x))
				)
			)
		)
		# .. and __gold_nN+1 is value of N+1.
		# __gold_n3+1 = 4
		$(call var_assign_simple,__gold_n$3+1,
			$(words $(__gold_seq$3-1) x x)
		)

		$(call var_assign_recursive_sl,__gold_args$3,
			$(with $(__gold_seq$3-1) $(words $(__gold_seq$3-1) x),
				$(patsubst %,$$%,$(words-to 9,$1))
				$(if $(word 10,$1), $(patsubst %,$$(%),$(words-from 10,$1)))
			)
		)

		# Proxy function to the real hook handler.
		# Used by __gold_expand.
		$(call var_assign_recursive_sl,
			# Params:
			#   1..N: RHS Symbols.
			#   N+1:  Their locations.
			#   N+2:  Rule Id.
			__gold_hook_rule_n$3,
			$$(foreach r,$$($(words $(__gold_seq$3-1) x x x)),
				$$(__gold_hook_rule)
			)
		)
	)

	$(call var_assign_simple,$(__gold_ns)_rule$1,
		$2 $3 $4
	)
endef

__gold_n0+1 := 1

# Params:
#   1:  Rule Id.
__gold_hook_rule_n0 = $(foreach r,$2,$(__gold_hook_rule))

# Echoes no args.
__gold_args0 :=

# 1. Id.
__gold_rule_nonterminal_id = \
	$(firstword $($g_rule$1))
# 1. Id.
__gold_rule_symbols_nr = \
	$(secondword $($g_rule$1))
# 1. Id.
__gold_rule_fn = \
	$(word 3,$($g_rule$1))

builtin_func-gold-rule-table :=# Noop

#
# Charsets.
#
#	$(gold-charset-table \
#		$(gold-charset 0,# &#9;&#10;&#11;&#12;&#13; &#160; #
#			9.13;32;160),
#		# ...
#	),
#
# Charsets are used during DFA scanning to match an incoming character.
# Each charset is a matcher function which takes a char code and tells whether
# the char is included in the given charset.
#
#	$g_cs$(id) = ...
#
# where:
#      'id' is a unique index of the charset, and
#       'g' refers to a namespace of a parser.
#

# Params:
#   1. Id
# ... Char codes
define builtin_func-gold-charset
	$(call var_assign_recursive_sl,
		$(__gold_ns)_cs$1,# =

		$(with \
			# Sort chars by their usage frequency.
			$(filter \
				# Construct the list of chars.
				$(foreach c,$(subst ;, ,$2),
					$(if $(findstring .,$c),
						# Range of chars.
						$(foreach e,$(subst .,,$(suffix $c)),
							# Be careful with zero as the lower bound.
							$(if $(findstring .0.,.$c),
								0 $(wordlist 1,$e,$(__gold_cs_seq)),
								$(wordlist $(basename $c),$e,$(__gold_cs_seq))
							)
						),
						# Plain char.
						$c
					)
				),
				$(__gold_cs_freq_sort)
			),

			$$(findstring |$$1|,|$(subst $(\s),|,$1)|)
		)
	)
endef

# Char sequence: [1 .. 255].
__gold_cs_seq := \
        1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 \
   16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31 \
   32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47 \
   48  49  50  51  52  53  54  55  56  57  58  59  60  61  62  63 \
   64  65  66  67  68  69  70  71  72  73  74  75  76  77  78  79 \
   80  81  82  83  84  85  86  87  88  89  90  91  92  93  94  95 \
   96  97  98  99 100 101 102 103 104 105 106 107 108 109 110 111 \
  112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 \
  128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 \
  144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 \
  160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 \
  176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 \
  192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 \
  208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 \
  224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 \
  240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255
__gold_cs_seq := $(strip $(__gold_cs_seq))

# Chars sorted by usage frequency (got from C source file of 1.5MB size).
# Only the first half of the ASCII table is actually counted (0-127).
# Sorting chars in a charset gives a little gain in matching speed because of
# the way 'findstring' is implemented in GNU Make.
__gold_cs_freq_sort := \
       32 116 101  95 115 105 114 110  99  97  40  41 111 117 100 \
   10 108 112  59  34 109 103 102 118  42  44  98 107 104  48 121 \
   61 120 123 125  49 113 119  45  62  38  58  50  69  54  46  37 \
   84  52  60  51  76  80 122  82  92  73  78  65  43  33  83  85 \
   67  79  68  56  91  93  77 124  70  53  71  63 106  72  86  75 \
   55  66  47  87  88  89  57  81 126  90  74  94  35  39  64  36 \
    1   2   3   4   5   6   7   8   9  11  12  13  14  15  16  17 \
   18  19  20  21  22  23  24  25  26  27  28  29  30  31  96 127 \
  128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 \
  144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 \
  160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 \
  176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 \
  192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 \
  208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 \
  224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 \
  240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 \
    0
__gold_cs_freq_sort := $(strip $(__gold_cs_freq_sort))

builtin_func-gold-charset-table :=# Noop

#
# DFA lexer.
#
#	$(gold-dfa-table 0,
#		$(gold-dfa-state 0,-1,
#			$(gold-dfa-edge 0,1),
#			# ...
#		),
#		# ...
#	),
#
# Each DFA state is represented by a function which tries to match an input
# characher by applying charset matchers of its edges one by one. If matching
# fails the ID of accepted symbol (if any) is returned.
#
#	$g_dfa$(id) = ...
#
# where:
#      'id' is the state identifier, and
#       'g' refers to a namespace of a parser.
#
# The main function of the DFA scanner itself is '__gold_lex' which takes
# a list of decimal char codes and returns result of tokenization.
#

# Params:
#   1. Charset
#   2. Target state
define builtin_func-gold-dfa-edge
	# Emit a call to charset matcher.
	$$(if $$($(__gold_ns)_cs$1),$2),
endef

# Params:
#   1. Id
#   2. Accept symbol or -1
#   ... Edges
define builtin_func-gold-dfa-state
	$(call var_assign_recursive_sl,
		# Params:
		#   1. Char code.
		# Return:
		#   Plain number: Next state Id;
		#   '/' Number: Accepted symbol Id (including error);
		$(__gold_ns)_dfa$1,# =

		$$(or \
			$(foreach a,$(words-from 3,$(builtin_args_list)),
				$($a)
			)# <- Ends up with a comma.
			/$(subst -1,1,$2)
		)
	)
endef

# Params:
#   1. Initial state
#   ... States (unused)
define builtin_func-gold-dfa-table
	# Remember the initial state.
	$(call var_assign_simple,$(__gold_ns)_dfa_ground,$1)

	# Handles the case when erroneous char occurs in the ground
	# just after accepting some token.
	$(call var_assign_simple,$(__gold_ns)_dfa/1,/1/)
endef

# The lexer itself.
#
# Params:
#   1. Input string as a list of decimal char codes.
# Context:
#   g. Prefix.
# Return:
#   List of tokens in form 'char1.char2...charN./symbolID'.
define __gold_lex
	${eval \
		# Initialize the state.
		__gold_state__ := $($g_dfa_ground)
		$(\n)

		# And reset location counters.
		$(__gold_location_reset_mk)
	}

	$(filter-out %/2,# Omit whitespaces.
			$(subst ./,/,$(subst . ,.,

		$(__gold_location)/# Position of the first token.

		$(foreach 1,$1,$(foreach a,$($g_dfa$(__gold_state__)),
			# 1: char code
			# a:
			#   advance:       'State'
			#   accept/error:  '/Symbol'
			#   pending error: '/1/'

			$(if $(findstring /,$a),
				# Got a token or error.
				$(foreach l,$(__gold_location),

					${eval \
						# Make a move from ground.
						__gold_state__  := $($g_dfa$($g_dfa_ground))
						$(\n)
						$(__gold_location_advance_mk)
					}

					$(__gold_dfa_handle[$(findstring /1/,$(__gold_state__)$a/)])
				),

				${eval \
					# Advance the state.
					__gold_state__  := $a
					$(\n)
					$(__gold_location_advance_mk)
				}
				$1.
			)

		))

		# We still may be in some state, so land to the ground.
		$(foreach a,$(call $g_dfa$(__gold_state__),),
			$(foreach l,$(__gold_location),# Position of the pending token.
				$(if $(findstring $a,/1),/)/$(__gold_location)$(a:%/=%) \
				$l//$l/0# EOF token at the end.
			)
		)
	)))
endef

__gold_state__ :=

# No error.
# Params:
#   1. Char code.
# Context:
#   a. '/' Accepted symbol Id.
#   l. Location.
define __gold_dfa_handle[]
	# Accept a token and open a new one.
	/$l$a $l/$1.
endef

# The char caused an error.
define __gold_dfa_handle[/1/]
	$(if $(findstring /1/1/,$(__gold_state__)$a/),
		# The char causes errors both in the current state and on the ground.
		# Error token will be closed on the next iteration.
		$(if $(a:/1/=),/)$1.,# "\ %

		$(if $(findstring /1/,$a/),
			# Error in the current state.
			$(if $(a:/1/=),/$1)/$l/1 $l/$1.,# " LF

			# Error on the ground.
			# Accept the current token and open an empty one.
			/$l$a $l//$1.# WS %
		)
	)
endef

# Current location in form 'line:col'.
define __gold_location
	$(__gold_line_nr__):$(words $(__gold_column__))
endef

# Sets location to the file start.
define __gold_location_reset_mk
  __gold_line__    := x
  __gold_line_nr__ := 1
  __gold_column__  := x
endef
# No code, so make it simple.
__gold_location_reset_mk := $(value __gold_location_reset_mk)

# Params:
#   1. Char code.
define __gold_location_advance_mk
	$(if $(findstring [$1],[10]),
		# Line feed.
		__gold_line__    += x$(\n)
		__gold_line_nr__ := $(words $(__gold_line__) x)$(\n)
		__gold_column__  := x

		,#else
		__gold_column__  += x

	)
endef

__gold_line__    :=
__gold_line_nr__ :=
__gold_column__  :=

#
# LALR parser.
#
#	$(gold-lalr-table 0,
#		$(gold-lalr-state 0,
#			$(gold-lalr-action 4,1,1),
#			# ...
#		),
#		# ...
#	)

# Params:
#   1. Symbol
#   2. Action:
#       1: Shift
#       2: Reduce
#       3: Goto
#       4: Accept
#   3. Value:
#       Rule Id for Reduce action
#       Target state in case of Shift or Goto
define builtin_func-gold-lalr-action
	$(or \
		$(and $(eq 1,$2),$1/+/$3),
		$(and $(eq 2,$2),$1/-/$3),
		$(and $(eq 3,$2),:$1/$3),
		$(and $(eq 4,$2),$1/),
	)
endef

# Params:
#   1. Id
#   ... Actions
define builtin_func-gold-lalr-state
	$(with \
		$1,
		$(foreach a,$(nofirstword $(builtin_args_list)),
			$($a)
		),

		# Goto action is only used to advance the state after a reduction is
		# performed. We can use such knowledge to decrease a total size of
		# state lookup table.
		# So goto action does not contribute to the general transition table of
		# the particular state. Instead of doing that we'll put it into
		# a special goto table of the state.
		$(call var_assign_simple,
			# List of elements in form 'Symbol/Value'
			$(__gold_ns)_goto.$1,# :=

			$(filter-patsubst :%,%,$2)
		)

		$(call var_assign_simple,
			# List of elements in form:
			#   'Symbol/+/State' for shift
			#   'Symbol/-/Rule'  for reduce
			#   'Symbol/'        for accept
			$(__gold_ns)_lalr.$1,# :=

			$(filter-out :%,$2)
		)
	)
endef

# Params:
#   1. Initial state
#   ... States (unused)
define builtin_func-gold-lalr-table
	$(call var_assign_simple,$(__gold_ns)_lalr_ground,$1)
	$(call var_assign_simple,$(__gold_ns)_lalr,)# Cyclic error until EOF.
endef

# Params:
#   1. List of tokens returned by lexer.
# Context:
#   g. Prefix.
# Return:
#   Parse tree.
define __gold_analyze
	${eval \
		__gold_state__ := .$($g_lalr_ground)
		$(\n)
		__gold_stack__ :=# Empty.
	}

	$(and $(foreach t,$1,
		# t: Token.
		$(__gold_parse_token)
	),)

	$(assert $(not $(__gold_state__)),
		Parsing must end up with either Accept or Error)

	$(__gold_stack__)
endef

# Context:
#   t. Token.
#   g. Prefix.
# Return:
#   Nothing.
define __gold_parse_token
	$(if $(foreach a,/$(filter $(notdir $t)/%,$($g_lalr$(__gold_state__))),
		# a: An action in one of the following forms:
		#     shift:  '/Token/+/State'
		#     reduce: '/Token/-/Rule'
		#     accept: '/Token/'
		#     error:  '/'
		$(__gold_lalr_handle[$(findstring +,$a)$(findstring -,$a)])

	),$(call __gold_parse_token))
endef

# Shift (hot).
#   a. Action: '/Token/+/State'
#   t. Token: 'Start/Chars/End/Type'
# Return:
#   Nothing.
define __gold_lalr_handle[+]
	${eval \
		# Push the current token onto the stack.
		__gold_stack__ += \
			$$(call $(lambda $1/[$2,$1,$4]),$(subst /,$(\comma),$t))
			$(__gold_state__)
		$(\n)
		# Move to a new state.
		__gold_state__ := .$(notdir $a)
	}
endef

# Reduce (hot).
#   a. Action: '/Token/-/Rule'
#   t. Token.
#   g. Prefix.
# Return:
#   Non-empty always.
define __gold_lalr_handle[-]
	${eval $(foreach r,$(notdir $a),$(foreach n,$(word 2,$($g_rule$r)),
		# r: Rule Id.
		# n: N of symbols.

		$(if $(findstring $n,0),
			# Just append a reduction.
			__gold_stack__ += \
				$(firstword $(subst /, ,$t))/(0,,$r)$(__gold_state__)

			,# else
			$(foreach d,$(words $(__gold_stack__)),
				# d: Current stack depth.

				# Pop N symbols.
				__gold_tmp__ := \
					$$(wordlist $d,2147483647,# stack[depth-$n+1 .. depth]
							$(__gold_seq$n-1) $$(__gold_stack__))
				$(\n)

				# Replace the current state by one saved in the first
				# reduced symbol.
				__gold_state__ := \
					$$(suffix $$(firstword $$(__gold_tmp__)))
				$(\n)

				# Replace them with a reduction.
				__gold_stack__ := \
					$$(wordlist $(__gold_n$n+1),$d,# stack[1 .. depth-$n]
							x $(__gold_seq$n-1) $$(__gold_stack__)) \
					$$(dir $$(firstword $$(__gold_tmp__)))# Start of reduction.
					($n,# Arg 0: N of symbols.
						$$(subst $$(\s),$$(\comma),
							$$(notdir $$(basename $$(__gold_tmp__)))
						),# 1..N: Symbols.
						$$(subst / ,.,
								$$(dir $$(__gold_tmp__)) ),# N+1: Locations.
						$r# N+2: Rule Id.
					)
					$$(__gold_state__)
			)
		)
		$(\n)

		# Go to a new state.
		__gold_state__ := \
			.$$(notdir $$(filter $(firstword $($g_rule$r))/%,
				$$($g_goto$$(__gold_state__))
			))
	))}

	x# Need to repeat handling of the token in a new state.
endef

# Accept or error (cold).
#   a. Action:
#       Accept: '/Token/'
#       Error:  '/'
#   t. Token
#   g. Prefix.
# Return:
#   Nothing.
define __gold_lalr_handle[]
	$(if $(eq /,$a),
		# Error.
		$(__gold_lalr_error),
		# Accept.
		$(__gold_lalr_accept)
	)
endef

# Accepting is just removing the suffix.
#   t. Token, assumed to be EOF.
#   g. Prefix.
define __gold_lalr_accept
	$(assert $(eq 0,$(notdir $t)),
		Only EOF may cause Accept action)
	$(assert $(singleword $(__gold_stack__)),
		Only a single symbol may be accepted as a root of the parse tree)
	$(assert $(eq .0,$(suffix $(__gold_stack__))),
		Accept may occur only in the ground state)
	$(assert $(__gold_state__),
		Accept can't occur after an error or another accept)

	${eval \
		__gold_stack__ := $$(notdir $$(basename $$(__gold_stack__)))
		$(\n)

		# Reset the state. This indicates that parsing is done.
		__gold_state__ :=
	}
endef

#   t. Token:
#       DFA error:  'Start/Chars/Bogus/End/1'
#       LALR error: 'Start/Chars/End/Type'
#   g. Prefix.
define __gold_lalr_error
	$(if $(__gold_state__),
		${eval \
			__gold_stack__ := $(if $(t:%/1=),$$(call \
					$(lambda {lalr,$4,$2,$1,$3,$(__gold_state__:.%=%)}),
				$(subst /,$(\comma),$t)))
			$(\n)
			__gold_state__ :=
		}
	)

	$(if $(filter %/1,$t),
		${eval \
			__gold_stack__ := $$(__gold_stack__)$$(call \
					$(lambda {dfa,$2,$3,$1,$4}),
				$(subst /,$(\comma),$t))
		}
	)
endef

__gold_state__ :=
__gold_stack__ :=
__gold_tmp__   :=

#
# Parse tree interpretation.
#

# Params:
#   1. Parse tree.
# Return:
#   Result of tree expansion.
define __gold_expand
	$(eval \
		# Transform tree into a code.
		__gold_tmp__ := \
			$(subst {,$${call __gold_hook_error_,
				$(subst [,$$$[call __gold_hook_token$(\comma),
					$(subst $[,$$$[call __gold_hook_rule_n,
						$(subst ],$],
							$(subst ., ,
								$1
							)
						)
					)
				)
			)
	)
	$(__gold_tmp__)
endef

# 1. Parsed chars
# 2. Bogus chars
# 3. Start position
# 4. End position
define __gold_hook_error_dfa
	$(call gold_report_at,$4,
		Lexical error: Unrecognized character$(if $(word 2,$2),s) \
		$(subst $(\s),$(\comma)$(\s),$(foreach c,$2,
			'$(if $(eq 0,$c),NULL,$(word $c,$(ascii_table)))'
		))
	)
endef

# 1. Symbol Id
# 2. Chars
# 3. Start position
# 4. End position
# 5. LALR State
define __gold_hook_error_lalr
	$(call gold_report_at,$4,
		Syntax error: Unexpected $(__gold_symbol_name) token$(\comma) \
		expected $(with $(filter-out /%,$(subst /, /,$($g_lalr.$5))),
			$(foreach s,$(nolastword $1),
				$(call __gold_symbol_name,$s),
			)
			$(if $(not $(singleword $1)),
				$(\s)or$(\s)
			)
			$(call __gold_symbol_name,$(lastword $1))
		)
	)
endef

# Params:
#   1. Id.
# Context:
#   g. Prefix.
define __gold_symbol_name
	$(foreach fn,$(__gold_symbol_fn),
		$(call \
			$(or $(call var_defined,$(gold_grammar)_name_of-$(fn)),
					__gold_default_symbol_name)
		)
	)
endef

# Context:
#   fn. Symbol function name.
__gold_default_symbol_name = \
	$(fn)

# Params:
#   1. Chars.
#   2. Location.
#   3. Symbol Id.
define __gold_hook_token
	$(foreach __gold_location__,$3,
		$(__gold_invoke_create_fn)
	)
endef

# Calls symbols creation function (if any, otherwise a default one is called).
# Params:
#   1. Chars/Production.
#   2. One word location in form 'line:col'.
#   3. Symbol Id.
# Context:
#   '__gold_location__': The same as arg 2.
define __gold_invoke_create_fn
	$(foreach __gold_symbol_id,$3,
		$(foreach 0,
			$(or \
				$(call var_defined,
						$(gold_grammar)_create-$(call __gold_symbol_fn,$3)),
				gold_default_create
			),
			$($0)
		)
	)
endef

# Params:
#   1. Data.
define gold_default_create
	$(__gold_default_create[
			$(firstword $(value $g_symbol$(value __gold_symbol_id)))
		])
endef

# Bad symbol.
define __gold_default_create[]
	$(error \
		'gold_default_create' function \
		must be called within regular terminal/nonterminal creation functions
	)
endef

# Create terminal.
#   1. Char codes.
define __gold_default_create[1]
	$(foreach str,
		$(subst $(\s),,$(foreach c,$(subst $(\s)0$(\s),256,$1),
			$(word $c,$(__gold_ascii_table))
		)),
		$(if $(findstring $$,$(str)),
			$(expand $(str)),
			$(str)
		)
	)
endef

# Create nonterminal.
#   1. Result of production.
__gold_default_create[0] = \
	$1

__gold_ascii_table_special := \
            \SOH    \STX    \ETX    \EOT    \ENQ    \ACK    \BEL    \
    \BS    $$(\t)  $$(\n)   \VT     \FF  $$(\empty) \SO     \SI     \
    \DLE    \DC1    \DC2    \DC3    \DC4    \NAK    \SYN    \ETB    \
    \CAN    \EM     \SUB    \ESC    \FS     \GS     \RS     \US     \
   $$(\s)
__gold_ascii_table_special := \
	$(__gold_ascii_table_special:\%=$$(__gold_ascii_char_special))

__gold_ascii_char_special = \
	$(warning Converting special characher into a space)$(\s)

__gold_ascii_table := \
  $(__gold_ascii_table_special) \
  $(call words-from,33,$(ascii_table:$$=$$$$)) \
  $$(__gold_ascii_char_special)# <- NULL as 256'th char.

# Called by '__gold_hook_rule_nN' proxy.
# Context:
#   r. Rule Id
# Params:
#   ... Symbols,
#   N+1 Location vector.
define __gold_hook_rule
	$(foreach __gold_location__,
		$(firstword $($(__gold_n$(call __gold_rule_symbols_nr,$r)+1))),
		$(call __gold_invoke_create_fn,
			$(foreach __gold_rule_id,$r,
				$(foreach 0,
					$(or \
						$(call var_defined,
							$(gold_grammar)_produce-$(call __gold_rule_fn,$r)),
						gold_default_produce
					),
					$($0)# No call to preserve expansion context.
				)
			),
			$(__gold_location__),
			$(call __gold_rule_nonterminal_id,$r)
		)
	)
endef

# Params:
#   1. Data.
define gold_default_produce
	$(if $(value __gold_rule_id),
		# Echo everything.
		$(__gold_args$(call __gold_rule_symbols_nr,$(__gold_rule_id))),
		$(error \
			'gold_default_produce' function \
			must be called within rule production functions
		)
	)
endef

#
# Error/warning/info reporting.
#

# 1. Message.
define gold_report
	$(call gold_report_at,$(__gold_location__),$1)
endef

# 1. Location.
# 2. Message.
define gold_report_at
	$(info $(gold_file):$1: $2)
endef

# 1. Message.
define gold_report_info
	$(call gold_report,info: $1)
endef

# 1. Location.
# 2. Message.
define gold_report_info_at
	$(call gold_report_at,$1,info: $2)
endef

# 1. Message.
define gold_report_warning
	$(call gold_report,warning: $1)
endef

# 1. Location.
# 2. Message.
define gold_report_warning_at
	$(call gold_report_at,$1,warning: $2)
endef

# 1. Message.
define gold_report_error
	$(call gold_report,error: $1)
endef

# 1. Location.
# 2. Message.
define gold_report_error_at
	$(call gold_report_at,$1,error: $2)
endef

$(def_all)

endif # __gold_engine_mk

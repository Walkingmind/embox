# $Id: $
#
# Builtins and runtime support for parsers generated by GOLD.
#
#   Date: Oct 26, 2011
# Author: Eldar Abusalimov
#

ifndef __embuild_gold_mk
__embuild_gold_mk := 1

include mk/core/common.mk
include mk/core/string.mk
include mk/core/define.mk

include mk/util/var/assign.mk

ascii_table = \
       SOH STX ETX EOT ENQ ACK BEL BS  TAB LF  VT  FF  CR  SO  SI  \
   DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US  \
   SP  !   "   \#  $   %   &   '   (   )   *   +   ,   —   .   /   \
   0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?   \
   @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   \
   P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _   \
   `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o   \
   p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~   DEL
ascii_table := $(strip $(value ascii_table))

__gold_prefix = $(call builtin_tag,gold-parser)

# Retrieves user-defined 'gold_prefix'
define builtin_tag_gold-parser
	$(or \
		$(filter-patsubst %parser,%,$(__def_var)),
		$(call builtin_error,
			Bad variable name: '$(__def_var)'
		)
	)
endef

# Params: ignored
define builtin_func_gold-parser
	${eval \
		__def_ignore += $(__gold_prefix)%
	}

	$$(foreach g,$(__gold_prefix),
		$$(call __gold_expand,
			$$(call $(__gold_prefix)_do_lalr,
				 $$($(__gold_prefix)_do_dfa)
			)
		)
	)
endef

#
# Symbols.
#
#	$(gold-symbol-table \
#		# Args: Id,Type,Name
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
define builtin_func_gold-symbol
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

	$(call var_assign_simple,$(__gold_prefix)_symbol$1,
		$2 $3
	)
endef

builtin_func_gold-symbol-table =# Noop.

#
# Rules.
#
#	$(gold-rule-table \
#		# Args: Id,Nonterminal,SymbolsNr,Name
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
#	__gold_xs$(n)-1 := <list of N minus one 'x's>
#	__gold_n$(n)+1  := <literal value of N plus one>
#
# where 'n' gets all possible values of number of symbols for each defined
# rule (except for zero). These values are used later in LALR reduce handler.
#
#	__gold_rule_hook_n$(n) = <proxy function>
#
# The latters are used by in last parsing phase to redirect expansion hooks.
#

# 1. Id
# 2. Nonterminal
# 3. Number of symbols in right-hand side
# 4. Instantiation function.
define builtin_func_gold-rule
	$(and \
		$(filter-out 0,$3),
		$(call var_undefined,__gold_xs$3),

		# Each __gold_xsN-1 contains N-1 whitespace separated 'x's
		# __gold_xs3-1 = x x
		$(call var_assign_simple,__gold_xs$3-1,
			$(with $3,,
				$(if $(word $1,x $2),
					$2,
					$(call $0,$1,x $2)
				)
			)
		)
		# .. and __gold_nN+1 is value of N+1.
		# __gold_n3+1 = 4
		$(call var_assign_simple,__gold_n$3+1,
			$(words $(__gold_xs$3-1) x x)
		)
		
		# Proxy function to the real hook handler.
		# Used by __gold_expand.
		$(call var_assign_recursive_sl,__gold_rule_hook_n$3,
			$$(foreach r,$$($(__gold_n$3+1)),
				$$(__gold_rule_hook)
			)
		)
	)

	$(call var_assign_simple,$(__gold_prefix)_rule$1,
		$2 $3 $4
	)
endef

__gold_rule_hook_n0 = $(foreach r,$1,$(__gold_rule_hook))

builtin_func_gold-rule-table =# Noop

builtin_func_gold-charset-table =# Noop

# 1. Id
# ... Char codes
define builtin_func_gold-charset
	$(call var_assign_recursive_sl,$(__gold_prefix)_cs$1,
		$$(findstring |$$1|,
			|
			$(subst $(\s),|,
				$(filter \
					$(foreach a,$(nofirstword $(builtin_args_list)),
						$($a)
					),
					$(__gold_cs_freq_sort)
				)
			)
			|
		)
	)
endef

# Chars sorted by usage frequency (got from C source file of 1.5MB size).
# Only the first half of the ASCII table is actually counted (0-127).
__gold_cs_freq_sort := \
      32  116 101 95  115 105 114 110 99  97  40  41  111 117 100 \
  10  108 112 59  34  109 103 102 118 42  44  98  107 104 48  121 \
  61  120 123 125 49  113 119 45  62  38  58  50  69  54  46  37  \
  84  52  60  51  76  80  122 82  92  73  78  65  43  33  83  85  \
  67  79  68  56  91  93  77  124 70  53  71  63  106 72  86  75  \
  55  66  47  87  88  89  57  81  126 90  74  94  35  39  64  36  \
  1   2   3   4   5   6   7   8   9   11  12  13  14  15  16  17  \
  18  19  20  21  22  23  24  25  26  27  28  29  30  31  96  127 \
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

define __gold_dfa_accept
	$(info DFA accept symbol $2 ($(word 2,$(__golden_symbol$2))): \
		[$(foreach c,$1,$(word $c,$(ascii_table)))])
endef

# 1. Initial state
# ... States (unused)
define builtin_func_gold-dfa-table
	$(call var_assign_recursive_sl,
		# Params:
		#   1. Input string as a list of decimal char codes.
		# Context:
		#   g. Prefix.
		# Return:
		#   List of tokens in form 'char1.char2...charN./symbolID'.
		$(__gold_prefix)_do_dfa,# =

		$$(foreach s,$1,
			$$(__gold_lex)
		)
	)
	$(call var_assign_simple,$(__gold_prefix)_dfa,)# Cyclic error until EOF
endef

# Params:
#   1. Input string as a list of decimal char codes.
# Context:
#   s. Initial state.
#   g. Prefix.
# Return:
#   List of tokens in form 'char1.char2...charN./symbolID'.
define __gold_lex
	${eval \
		__gold_state__ := $s# Ground.
	}

	$(subst . ,.,$(foreach 1,$1,
		${eval \
			# Advance the state.
			__gold_state__ := $($g_dfa$(__gold_state__))
		}

		$(if $(findstring /,$(__gold_state__)),
			# Got a token, emit it as is (with slash) appending a space.
			$(__gold_state__) \

			${eval \
				# Make a move from ground.
				__gold_state__ := $($g_dfa$s)
			}
		)
		$1.

	) )# <- a space after the last char.

	# We still may be in some state, so land to the ground.
	# Assume EOF symbol is 0 and Error is 1.
	$(or $(call $g_dfa$(__gold_state__),),/1) /0
endef

# 1. Id
# 2. Accept symbol or -1
# ... Edges
define builtin_func_gold-dfa-state
	$(call var_assign_recursive_sl,
		# Params:
		#   1. Char code.
		# Return:
		#   Plain number: Next state Id;
		#   '/' Number: Accepted symbol Id;
		#   Empty on error.
		$(__gold_prefix)_dfa$1,# =

		$$(or \
			$(foreach a,$(words-from 3,$(builtin_args_list)),
				$($a)
			)
			$(if $(findstring $2,-1),,/$2)
		)
	)
endef

# 1. Charset
# 2. Target state
define builtin_func_gold-dfa-edge
	$$(if $$($(__gold_prefix)_cs$1),$2),
endef

# 1. Initial state
# ... States (unused)
define builtin_func_gold-lalr-table
	$(call var_assign_recursive_sl,
		# Params:
		#   1. List of tokens returned by lexer.
		# Context:
		#   g. Prefix.
		# Return:
		$(__gold_prefix)_do_lalr,# =

		$$(foreach s,$1,
			$$(__gold_parse)
		)
	)
endef

# Params:
#   1. List of tokens returned by lexer.
# Context:
#   s. Initial state.
#   g. Prefix.
# Return:
#   Parse tree.
define __gold_parse
	${eval \
		__gold_state__ := .$s# Ground.
		$(\n)
		__gold_stack__ :=# Empty.
	}

	$(and $(foreach t,$(filter-out %/2,$1),# Omit whitespaces.
		# t: Token.
		$(__gold_parse_token)
	),)

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
		#     accept: '/Token'
		#     error:  '/'
		$(__gold_lalr_handle$(findstring +,$a)$(findstring -,$a))

	),$(call __gold_parse_token))
endef

# Shift (hot).
#   a. Action: '/Token/+/State'
#   t. Token
# Return:
#   Nothing.
define __gold_lalr_handle+
	${eval \
		# Push the current token onto the stack.
		__gold_stack__ += [$t]$(__gold_state__)
		$(\n)
		# Move to a new state.
		__gold_state__ := .$(notdir $a)
	}
endef

# Reduce (hot).
#   a. Action: '/Token/-/Rule'
#   t. Token
#   g. Prefix.
# Return:
#   Non-empty.
define __gold_lalr_handle-
	${eval $(foreach r,$(notdir $a),$(foreach n,$(word 2,$($g_rule$r)),
		# r: Rule Id.
		# n: N of symbols.

		$(if $(findstring $n,0),
			# Just append a reduction.
			__gold_stack__ += \
				($r)$(__gold_state__)

			,# else
			$(foreach d,$(words $(__gold_stack__)),
				# d: Current stack depth.

				# Pop N symbols.
				__gold_tmp__ := \
					$$(wordlist $d,2147483647,# stack[depth-$n+1 .. depth]
							$(__gold_xs$n-1) $$(__gold_stack__))
				$(\n)

				# Replace the current state by one saved in the first
				# reduced symbol.
				__gold_state__ := \
					$$(suffix $$(firstword $$(__gold_tmp__)))
				$(\n)

				# Replace them with a reduction.
				__gold_stack__ := \
					$$(wordlist $(__gold_n$n+1),$d,# stack[1 .. depth-$n]
							x $(__gold_xs$n-1) $$(__gold_stack__)) \
					($n,$$(subst $$(\s),$$(\comma),
							$$(basename $$(__gold_tmp__))),$r)
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
define __gold_lalr_handle
	$(info )
	$(info accept/error: $a : [$t])
	$(info __gold_parse_token: __gold_stack__ = $(__gold_stack__))
	$(info __gold_parse_token: __gold_state__ = $(__gold_state__))
#	$(error )
endef

# 1. Id
# ... Actions
define builtin_func_gold-lalr-state
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
			$(__gold_prefix)_goto.$1,# :=

			$(filter-patsubst :%,%,$2)
		)

		$(call var_assign_simple,
			# List of elements in form:
			#   'Symbol/+/State' for shift
			#   'Symbol/-/Rule'  for reduce
			#   'Symbol/'        for accept
			$(__gold_prefix)_lalr.$1,# :=

			$(filter-out :%,$2)
		)
	)
endef

# 1. Symbol
# 2. Action:
#     1: Shift
#     2: Reduce
#     3: Goto
#     4: Accept
# 3. Value:
#     Rule Id for Reduce action
#     Target state in case of Shift or Goto
define builtin_func_gold-lalr-action
	$(or \
		$(and $(eq 1,$2),$1/+/$3),
		$(and $(eq 2,$2),$1/-/$3),
		$(and $(eq 3,$2),:$1/$3),
		$(and $(eq 4,$2),$1/),
	)
endef

# Params:
#   1. Parse tree.
# Return:
#   Result of tree expansion.
define __gold_expand
	${eval \
		# Transform tree into a code.
		__gold_tmp__ := \
			$(subst [,$$$(\p[)call __gold_token_hook$(\comma),
				$(subst $(\p[),$$$(\p[)call __gold_rule_hook_n,
					$(subst ],$(\p]),
						$(subst ., ,$(subst /,$(\comma),$(subst ./,/,
							$1
						)))
					)
				)
			)
	}
	$(__gold_tmp__)
endef

# 1. Chars
# 2. Symbol Id
define __gold_token_hook
	$(with \
		$(subst $(\s),,$(foreach c,$1,
			$(if $(eq 0,$c),
				<0>,
				$(word $c,$(ascii_table))
			)
		)),
		$2,

		$(info $(word 2,$($g_symbol$2)): $1)
		$1
	)
endef

# Context:
#   r. Rule Id
# Params:
#   ... Symbols
define __gold_rule_hook
	$(with \
		$(word 3,$($g_rule$r)) {
			$(subst $(\n),$(\n)$(\t),
				$(if $(not $(eq 0,$(word 2,$($g_rule$1)))),
					$(foreach a,$(wordlist 1,$(word 2,$($g_rule$r)),1 2 3 4 5 6 7 8 9),
						$(\n)$a: $($a)
					)
				)
			) $(\n)
		},
#		$(info $1)
		$1
	)
endef

$(def_all)

define __gold_example_parser
	$(gold-parser \

		$(gold-symbol-table \
			# Args: Id,Type,Name
			$(gold-symbol  0,3,# (EOF)
				Symbol_Eof),
			# ...
		),

		$(gold-rule-table \
			# Args: Id,Nonterminal,SymbolsNr,Name
			$(gold-rule 0,9,1,# <Program> ::= <Expression>
				Rule_Program),
			# ...
		),

		$(gold-charset-table \
			# Args: Id,Chars...
			$(gold-charset 0,# &#9;&#10;&#11;&#12;&#13; &#160; #
				9,10,11,12,13,32,160),
			# ...
		),

		$(gold-dfa-table 0,# <- Initial state
			$(gold-dfa-state 0,-1,
				$(gold-dfa-edge 0,1),
				# ...
			),
			# ...
		),

		$(gold-lalr-table 0,# <- Initial state
			$(gold-lalr-state 0,
				$(gold-lalr-action 4,1,1),# Shift to State 1
				# ...
			),
			# ...
		)

	)
endef
__gold_example_parser :=

$(def_all)

endif # __embuild_gold_mk



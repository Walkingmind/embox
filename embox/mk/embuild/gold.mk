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

# Chars sorted by usage frequency (got from C source file of 1.5MB size).
# Only the first half of the ASCII table is actually counted (0-127).
sorted_charset := \
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
sorted_charset := $(strip $(sorted_charset))

#__gold_prefix = $(call builtin_tag,gold-parser)
__gold_prefix := __golden

define builtin_tag_gold-parser
#	$(or \
#		$(call filter-patsubst,%parser,%,$(__def_var)),
#		$(call builtin_error,
#			Bad variable name: '$(__def_var)'
#		)
#	)
	__golden# TODO for devel only
endef

define builtin_func_gold-parser
	$(info $(__gold_prefix)%)
	${eval \
		__def_ignore += $(__gold_prefix)%
	}
endef

__gold_prefix_symbol = $(__gold_prefix)_symbol

builtin_func_gold-symbol-table =# Noop

# 1. Id
# 2. Symbol type:
#     0: Normal Nonterminal
#     1: Normal Terminal
#     2: Whitespace Terminal
#     3: End of File
#     4: Start of a block quote
#     5: End of a block quote
#     6: Line Comment Terminal
#     7: Error Terminal
# 3. Instantiation function
define builtin_func_gold-symbol
	$(call var_assign_simple,$(__gold_prefix_symbol)$1,
		$2 $3
	)
endef

builtin_func_gold-rule-table =# Noop

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
	)

	$(call var_assign_simple,$(__gold_prefix)_rule$1,
		$2 $3 $4
	)
endef

__gold_prefix_charset = $(__gold_prefix)_charset

builtin_func_gold-charset-table =# Noop

# 1. Id
# ... Char codes
define builtin_func_gold-charset
	$(call var_assign_recursive_sl,$(__gold_prefix_charset)$1,
		$$(findstring |$$1|,
			|
			$(subst $(\s),|,
				$(filter \
					$(foreach a,$(nofirstword $(builtin_args_list)),
						$($a)
					),
					$(sorted_charset)
				)
			)
			|
		)
	)
endef

__gold_prefix_dfa     = $(__gold_prefix)_dfa

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
		# Return:
		#   List of tokens in form 'char1.char2...charN./symbolID'.
		$(__gold_prefix)_dfa_table,# =

		$${eval \
			__gold_dfa_state__ := $1# Ground.
		}
		$$(subst .$(\s),.,
			$$(foreach 1,$$1,
				$${eval \
					# Advance the state.
					__gold_dfa_state__ := \
						$$($(__gold_prefix_dfa)$$(__gold_dfa_state__))
				}

				$$(if $$(findstring /,$$(__gold_dfa_state__)),
					# Got a token, emit it as is (with slash).
					$$(__gold_dfa_state__)$(\s)

					$${eval \
						# Make a move from ground.
						__gold_dfa_state__ := $$($(__gold_prefix_dfa)$1)
					}
				)
				$$1.

			)$(\s)
			# We still may be in some state, so land to the ground.
			# Assume EOF symbol is 0 and Error is 1.
			$$(or $$(call $(__gold_prefix_dfa)$$(__gold_dfa_state__),),/1) /0
		)
	)
	$(call var_assign_simple,$(__gold_prefix_dfa),)# Cyclic error until EOF
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
		$(__gold_prefix_dfa)$1,# =

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
	$$(if $$($(__gold_prefix_charset)$1),$2),
endef

# 1. Initial state
# ... States (unused)
define builtin_func_gold-lalr-table
	$(call var_assign_recursive_sl,
		# Params:
		#   1. List of tokens returned by lexer.
		# Return:
		$(__gold_prefix)_lalr_table,# =

		$${eval \
			__gold_lalr_state__ := .$1# Ground.
			$$(\n)
			__gold_lalr_stack__ :=# Empty.
		}
		
		$$(and $$(foreach t,$$1,
			$$(__gold_parse_token)
		),)
		
		$$(basename $$(__gold_lalr_stack__))
	)
endef

# Params:
#   t. Token.
# Return:
define __gold_parse_token
	$(info )
	$(info __gold_parse_token: __gold_lalr_stack__ = $(__gold_lalr_stack__))
	$(info __gold_parse_token: __gold_lalr_state__ = $(__gold_lalr_state__))
	$(info __gold_parse_token: token:  [$t])

	$(if $(foreach a,
		# shift:  '/Token/+/State'
		# reduce: '/Token/-/Rule'
		# accept: '/Token'
		# error:  '/'
		/$(filter $(notdir $t)/%,$($(__gold_prefix)_lalr$(__gold_lalr_state__))),
		$(info __gold_parse_token: action: [$a])

		$(__gold_lalr_handle$(findstring +,$a)$(findstring -,$a))

	),$(call __gold_parse_token))
endef

# Shift (hot).
#   a. Action: '/Token/+/State'
#   t. Token
define __gold_lalr_handle+
	$(info __gold_parse_token: shift)

	${eval \
		# Push the current token onto the stack.
		__gold_lalr_stack__ += [$t]$(__gold_lalr_state__)
		$(\n)
		# Move to a new state.
		__gold_lalr_state__ := .$(notdir $a)
	}
endef

# Reduce (hot).
#   a. Action: '/Token/-/Rule'
#   t. Token
define __gold_lalr_handle-
	$(info __gold_parse_token: reduce)
	${eval \
			$(foreach r,$(notdir $a),# r: Rule Id.
			$(foreach n,$(word 2,$($(__gold_prefix)_rule$r)),# n: N of symbols.
			
		$(if $(findstring $n,0),
			# Just append a reduction.
			__gold_lalr_stack__ += \
				($r)$(__gold_lalr_state__)

			,# else
			$(foreach d,$(words $(__gold_lalr_stack__)),# Current stack depth.
				# Pop N symbols.
				__gold_tmp__ := \
					$$(wordlist $d,2147483647,# stack[depth-$n+1 .. depth]
							$(__gold_xs$n-1) $$(__gold_lalr_stack__))
				$(\n)
				# Replace the current state by one saved in the first
				# reduced symbol.
				__gold_lalr_state__ := \
					$$(suffix $$(firstword $$(__gold_tmp__)))
				$(\n)
				# Replace them with a reduction.
				__gold_lalr_stack__ := \
					$$(wordlist $(__gold_n$n+1),$d,# stack[1 .. depth-$n]
							x $(__gold_xs$n-1) $$(__gold_lalr_stack__)) \
					($$(subst $$(\s),$$(\comma),$$(basename $$(__gold_tmp__))),
							$r)$$(__gold_lalr_state__)
			)
		)
		$(\n)
		# Go to a new state.
		__gold_lalr_state__ := \
			.$$(notdir $$(filter $(firstword $($(__gold_prefix)_rule$r))/%,
				$$($(__gold_prefix)_goto$$(__gold_lalr_state__))
			))
	))}
	x# Need to repeat handling of the token in a new state.
endef

# Accept or error (cold).
define __gold_lalr_handle
	$(info accept/error)
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



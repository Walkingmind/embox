# Generated by GOLD Parser Builder using MyBuild program template.

# Symbol constructors for 'MyFile' grammar.

#
# Each symbol is converted by the corresponding constructor (if any has been
# defined). Constructor is a function named '$(gold_grammar)_create-<ID>'
# (where ID is a unique symbol identifier) with the following signature:
#
# Params:
#   1. For terminals: a list of decimal char codes representing the token.
#      For nonterminals: the result of production.
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

# Symbol: BooleanLiteral
define $(gold_grammar)_create-BooleanLiteral
	$(if $(filter true,$(gold_default_create)),1)
endef

# Symbol: Identifier
define $(gold_grammar)_create-Identifier
	$(gold_default_create:^%=%)
endef

# Symbol: NumberLiteral
define $(gold_grammar)_create-NumberLiteral
	$(or \
		$(filter-out 0x%,$(gold_default_create)),
		$(call gold_report_warning,
				NYI: Hex literals)
	)
endef

# Symbol: StringLiteral
define $(gold_grammar)_create-StringLiteral
	$(subst \\ ,\,# Unescape '\' sequences.
		$(subst \',',
			$(if $(eq ",$(call gold_default_create,$(firstword $1))),
				# Regular "..." string.
				$(subst \",",$(subst \t,$(\t),$(subst \n,$(\n),$(subst \r,,
					$(subst \\,\\ ,
						$(call gold_default_create,
							# Remove '"' at the ends.
							$(wordlist 3,$(words $1),x $1)
						)
					)
				)))),
				# Verbatim '''...''' string.
				$(subst \\,\\ ,
					$(call gold_default_create,
						# Remove ''' at the ends.
						$(wordlist 7,$(words $1),x x x $1)
					)
				)
			)
		)
	)
endef

#
# Optimized contructors for constant terminals (i.e. keywords and punctuation).
#

$(gold_grammar)_create-Comma            := ,
$(gold_grammar)_create-Dot              := .
$(gold_grammar)_create-DotTimes         := .*
$(gold_grammar)_create-Colon            := :
$(gold_grammar)_create-LBrace           := {
$(gold_grammar)_create-RBrace           := }
$(gold_grammar)_create-Eq               := =
$(gold_grammar)_create-abstract         := abstract
$(gold_grammar)_create-boolean          := boolean
$(gold_grammar)_create-depends          := depends
$(gold_grammar)_create-extends          := extends
$(gold_grammar)_create-feature          := feature
$(gold_grammar)_create-flags            := flags
$(gold_grammar)_create-import           := import
$(gold_grammar)_create-interface        := interface
$(gold_grammar)_create-make             := make
$(gold_grammar)_create-module           := module
$(gold_grammar)_create-number           := number
$(gold_grammar)_create-object           := object
$(gold_grammar)_create-option           := option
$(gold_grammar)_create-package          := package
$(gold_grammar)_create-provides         := provides
$(gold_grammar)_create-requires         := requires
$(gold_grammar)_create-source           := source
$(gold_grammar)_create-static           := static
$(gold_grammar)_create-string           := string

#
# For each regular terminal we also define a constant with a human-readable
# description used for error reporting.
#

$(gold_grammar)_name_of-Comma           := ','
$(gold_grammar)_name_of-Dot             := '.'
$(gold_grammar)_name_of-DotTimes        := '.*'
$(gold_grammar)_name_of-Colon           := ':'
$(gold_grammar)_name_of-LBrace          := '{'
$(gold_grammar)_name_of-RBrace          := '}'
$(gold_grammar)_name_of-Eq              := '='
$(gold_grammar)_name_of-abstract        := abstract
$(gold_grammar)_name_of-boolean         := boolean
$(gold_grammar)_name_of-BooleanLiteral  := Boolean Literal
$(gold_grammar)_name_of-depends         := depends
$(gold_grammar)_name_of-extends         := extends
$(gold_grammar)_name_of-feature         := feature
$(gold_grammar)_name_of-flags           := flags
$(gold_grammar)_name_of-Identifier      := Identifier
$(gold_grammar)_name_of-import          := import
$(gold_grammar)_name_of-interface       := interface
$(gold_grammar)_name_of-make            := make
$(gold_grammar)_name_of-module          := module
$(gold_grammar)_name_of-number          := number
$(gold_grammar)_name_of-NumberLiteral   := Number Literal
$(gold_grammar)_name_of-object          := object
$(gold_grammar)_name_of-option          := option
$(gold_grammar)_name_of-package         := package
$(gold_grammar)_name_of-provides        := provides
$(gold_grammar)_name_of-requires        := requires
$(gold_grammar)_name_of-source          := source
$(gold_grammar)_name_of-static          := static
$(gold_grammar)_name_of-string          := string
$(gold_grammar)_name_of-StringLiteral   := String Literal


# Application for 'MyFile' grammar (version 0.1).
#    MyBuild file
# Author: Eldar Abusalimov

#
# Rules.
#
# As for symbols each rule can have a constructor that is used to produce an
# application-specific representation of the rule data.
# The signature of production function is the following:
#
# Params:
#  1..N: Each argument contains a value of the corresponding symbol
#        in the rule's RHS.
#  N+1:  Location vector with 'line:column' words each of which is a start of
#        the corresponding symbol.
#
# Return:
#   Converted value that is passed to a symbol handler corresponding to
#   the rule's LHS (if any has been defined).
#
# If production function is not defined then the rule is produced by
# concatenating the RHS through a space. To reuse this default value one can
# call 'gold_default_produce' function.
#

# Rule: <Model> ::= <PackageDecl> <ImportDecls> <ModuleDecls>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-Model
	$(\h) Generated from $(gold_file). Do not edit!$(\n)$(\n)
	$(if $1,$1$(\n))
	$(if $2,$2$(\n))
	$(if $3,
		$(if $(findstring $$_APIS,$3),$$_APIS :=$(\n))
		$(if $(findstring $$_MODS,$3),$$_MODS :=$(\n))
		$(\n)$3$(\n)
	)
endef

# Rule: <PackageDecl> ::= package <QualifiedName> ';'
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-PackageDecl_package_Semi
	$$_PACKAGE := $2$(\n)
endef

# Rule: <PackageDecl> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-PackageDecl
	$(call gold_report,$3,
		Warning: using default package
	)
endef

# Rule: <ImportDecls> ::= <ImportDecl> <ImportDecls>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-ImportDecls
	$(call gold_report,$3,
		Imports are not yet implemented!
	)
endef

# Rule: <ModuleDecls> ::= <ModuleDecl> <ModuleDecls>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-ModuleDecls
	$1$2
endef

# Rule: <ModuleDecl> ::= <ModuleModifiers> module Identifier <SuperModules> '{' <ModuleBodyDecls> '}'
# Args: 1..7 - Symbols; 7+1 - Location vector.
define $(gold_grammar)_produce-ModuleDecl_module_Identifier_LBrace_RBrace
	m := $3$(\n)
	$$_$(if $(filter abstract,$1),APIS,MODS) += $$m$(\n)
	$4
	$6$(\n)
endef

# Rule: <SuperModules> ::= extends <ModuleRefList>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-SuperModules_extends
	$$_PROVIDES-$$m += $2$(\n)
endef

# Rule: <SuperModules> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-SuperModules
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleBodyDecls> ::= <ModuleBodyDecl> <ModuleBodyDecls>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-ModuleBodyDecls
	$1$2
endef

# Rule: <CcflagsDecl> ::= ccfags StringLiteral ';'
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-CcflagsDecl_ccfags_StringLiteral_Semi
	$$_CFLAGS-$$m += $2$(\n)
endef

# Rule: <DependenciesDecl> ::= depends <ModuleRefList> ';'
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-DependenciesDecl_depends_Semi
	$$_DEPS-$$m += $2$(\n)
endef

# Rule: <SourcesDecl> ::= source <FileOrTargetList> ';'
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-SourcesDecl_source_Semi
	$$_SRCS-$$m += $2$(\n)
endef

# Rule: <ObjectsDecl> ::= object <FileOrTargetList> ';'
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-ObjectsDecl_object_Semi
	$(call gold_report,$4,
		Objects are not yet implemented!
	)
endef

# Rule: <FileOrTarget> ::= <Filename>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-FileOrTarget
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FileOrTarget> ::= <Filename> ':' <FilenameList> '{' StringLiteral '}'
# Args: 1..6 - Symbols; 6+1 - Location vector.
define $(gold_grammar)_produce-FileOrTarget_Colon_LBrace_StringLiteral_RBrace
	$(call gold_report,$4,
		Auto-generated files are not yet implemented!
	)
endef

# Rule: <FileOrTargetList> ::= <FileOrTarget> ',' <FileOrTargetList>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-FileOrTargetList_Comma
	$1 $3
endef

# Rule: <Filename> ::= StringLiteral
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-Filename_StringLiteral
	$(or \
		$(singleword $1),
		$(call gold_report,$2,
			File name must be a single word
		)
	)
endef

# Rule: <FilenameList> ::= <Filename> ',' <FilenameList>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-FilenameList_Comma
	$1 $3
endef

# Rule: <ModuleRefList> ::= <ModuleRef> ',' <ModuleRefList>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-ModuleRefList_Comma
	$1 $3
endef

# Rule: <QualifiedName> ::= Identifier '.' <QualifiedName>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-QualifiedName_Identifier_Dot
	$1.$3
endef

# Rule: <QualifiedNameWithWildcard> ::= <QualifiedName> '.*'
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-QualifiedNameWithWildcard_DotTimes
	$1.*
endef


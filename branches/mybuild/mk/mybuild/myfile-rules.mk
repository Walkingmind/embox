# Generated by GOLD Parser Builder using Mybuild program template.

# Rule productions for 'MyFile' grammar.

#
# As for symbols each rule can have a constructor that is used to produce an
# application-specific representation of the rule data.
# Production functions are named '$(gold_grammar)_produce-<ID>' and have the
# following signature:
#
# Params:
#   1..N: Each argument contains a value of the corresponding symbol in the RHS
#         of the rule production.
#
# Return:
#   The value to pass as an argument to a rule containing the production
#   of this rule in its RHS, or to return to user in case of the Start Symbol.
#
# If production function is not defined then the rule is produced by
# concatenating the RHS through spaces. To reuse this default value one can
# call 'gold_default_produce' function.
#

# Rule: <MyFile> ::= <Package> <Imports> <Entities>
# Args: 1..3 - Symbols in the RHS.
define $(gold_grammar)_produce-MyFile
	$(for root <- $(new MyFileContentRoot),
		$(set root->name,$1)
		$(set root->imports,$2)
		$(set root->types,$3)
		$(root))
endef

# Rule: <Package> ::= package <QualifiedName>
# Args: 1..2 - Symbols in the RHS.
$(gold_grammar)_produce-Package_package  = $2

# Rule: <Package> ::= 
# Args: 1..0 - Symbols in the RHS.
define $(gold_grammar)_produce-Package
	$(call gold_report_warning,
			Using default package)
endef

# Rule: <Import> ::= import <QualifiedNameWithWildcard>
# Args: 1..2 - Symbols in the RHS.
$(gold_grammar)_produce-Import_import = $2

# Rule: <AnnotatedType> ::= <AnnotationSpecifiers> <Type>
# Args: 1..2 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotatedType
		$2
endef

# Rule: <Annotation> ::= annotation Identifier '{' <AnnotationMembers> '}'
# Args: 1..5 - Symbols in the RHS.
define $(gold_grammar)_produce-Annotation_annotation_Identifier_LBrace_RBrace
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotatedAnnotationMember> ::= <AnnotationSpecifiers> <Option>
# Args: 1..2 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotatedAnnotationMember
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotationSpecifiers> ::= <AnnotationSpecifier> <AnnotationSpecifiers>
# Args: 1..2 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotationSpecifiers
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotationSpecifiers> ::= 
# Args: 1..0 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotationSpecifiers2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotationSpecifier> ::= '@' <Reference> <AnnotationInitializer>
# Args: 1..3 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotationSpecifier_At
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotationInitializer> ::= '(' <AnnotationParametersList> ')'
# Args: 1..3 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotationInitializer_LParan_RParan
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotationInitializer> ::= '(' <Value> ')'
# Args: 1..3 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotationInitializer_LParan_RParan2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotationInitializer> ::= 
# Args: 1..0 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotationInitializer
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotationParametersList> ::= <AnnotationParameter> ',' <AnnotationParametersList>
# Args: 1..3 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotationParametersList_Comma
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotationParametersList> ::= <AnnotationParameter>
# Args: 1..1 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotationParametersList
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotationParameter> ::= <SimpleReference> '=' <Value>
# Args: 1..3 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotationParameter_Eq
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Interface> ::= interface Identifier <SuperInterfaces> '{' <Features> '}'
# Args: 1..6 - Symbols in the RHS.
define $(gold_grammar)_produce-Interface_interface_Identifier_LBrace_RBrace
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <SuperInterfaces> ::= extends <ReferenceList>
# Args: 1..2 - Symbols in the RHS.
define $(gold_grammar)_produce-SuperInterfaces_extends
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <SuperInterfaces> ::= 
# Args: 1..0 - Symbols in the RHS.
define $(gold_grammar)_produce-SuperInterfaces
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Features> ::= <AnnotatedFeature> <Features>
# Args: 1..2 - Symbols in the RHS.
define $(gold_grammar)_produce-Features
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Features> ::= 
# Args: 1..0 - Symbols in the RHS.
define $(gold_grammar)_produce-Features2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <AnnotatedFeature> ::= <AnnotationSpecifiers> <Feature>
# Args: 1..2 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotatedFeature
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Feature> ::= feature Identifier <SuperFeatures>
# Args: 1..3 - Symbols in the RHS.
define $(gold_grammar)_produce-Feature_feature_Identifier
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <SuperFeatures> ::= extends <ReferenceList>
# Args: 1..2 - Symbols in the RHS.
define $(gold_grammar)_produce-SuperFeatures_extends
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <SuperFeatures> ::= 
# Args: 1..0 - Symbols in the RHS.
define $(gold_grammar)_produce-SuperFeatures
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Module> ::= <ModuleModifiers> module Identifier <SuperModule> '{' <ModuleMembers> '}'
# Args: 1..7 - Symbols in the RHS.
define $(gold_grammar)_produce-Module_module_Identifier_LBrace_RBrace
	$(foreach module,$(new MyModule),
		$(set module->name,$3)
		$(set module->origin,$(call gold_location_of,3))

		$(set module->isStatic,$(filter static,$1))
		$(set module->isAbstract,$(filter abstract,$1))

		$(set module->superType_link,$4)

		$(silent-foreach attr, \
				sources \
				flags \
				options \
				depends_links,
				$(set module->$(attr),
					$(filter-patsubst $(attr)/%,%,$6)))

		$(module)
	)
endef

# Rule: <ModuleModifiers> ::= <ModuleModifier> <ModuleModifiers>
# Args: 1..2 - Symbols in the RHS.
define $(gold_grammar)_produce-ModuleModifiers
	$(if $(filter $1,$2),
		$(call gold_report_error,
				Duplicate module modifier '$1'),
		$1 \
	)
	$2
endef

# Rule: <SuperModule> ::= extends <Reference>
# Args: 1..2 - Symbols in the RHS.
$(gold_grammar)_produce-SuperModule_extends = $2

# Rule: <AnnotatedModuleMember> ::= <AnnotationSpecifiers> <ModuleMember>
# Args: 1..2 - Symbols in the RHS.
define $(gold_grammar)_produce-AnnotatedModuleMember
		$2
endef

# Rule: <ModuleMember> ::= depends <ReferenceList>
$(gold_grammar)_produce-ModuleMember_depends = $(addprefix $1_links/,$2)

# Rule: <ModuleMember> ::= provides <ReferenceList>
$(gold_grammar)_produce-ModuleMember_provides = $(addprefix $1_links/,$2)

# Rule: <ModuleMember> ::= requires <ReferenceList>
$(gold_grammar)_produce-ModuleMember_requires = $(addprefix $1_links/,$2)

# Rule: <ModuleMember> ::= source <FilenameList>
$(gold_grammar)_produce-ModuleMember_source = $(addprefix $1s/,$2)
# Rule: <ModuleMember> ::= object <FilenameList>
$(gold_grammar)_produce-ModuleMember_object = $(addprefix $1s/,$2)

# Rule: <ModuleMember> ::= option <Option>
# Args: 1..2 - Symbols in the RHS.
$(gold_grammar)_produce-ModuleMember_option = $(addprefix $1s/,$2)

# Rule: <Option> ::= <OptionType> Identifier <OptionDefaultValue>
# Args: 1..3 - Symbols in the RHS.
define $(gold_grammar)_produce-Option_Identifier
    $(for opt <- $(new My$1Option),
		$(set opt->name,$2)
		$(set opt->defaultValue,$3)
		
		$(opt))
endef

# Rule: <OptionType> ::= string
# Args: 1..1 - Symbols in the RHS.
$(gold_grammar)_produce-OptionType_string = String

# Rule: <OptionType> ::= number
# Args: 1..1 - Symbols in the RHS.
$(gold_grammar)_produce-OptionType_number = Number

# Rule: <OptionType> ::= boolean
# Args: 1..1 - Symbols in the RHS.
$(gold_grammar)_produce-OptionType_boolean = Boolean

# Rule: <OptionDefaultValue> ::= '=' <Value>
# Args: 1..2 - Symbols in the RHS.
$(gold_grammar)_produce-OptionDefaultValue_Eq = $2

# Rule: <Value> ::= StringLiteral
# Args: 1..1 - Symbols in the RHS.
$(gold_grammar)_produce-Value_StringLiteral = $(new MyStringOptionValue,$1)

# Rule: <Value> ::= NumberLiteral
# Args: 1..1 - Symbols in the RHS.
$(gold_grammar)_produce-Value_NumberLiteral = $(new MyNumberOptionValue,$1)

# Rule: <Value> ::= BooleanLiteral
# Args: 1..1 - Symbols in the RHS.
define $(gold_grammar)_produce-Value_BooleanLiteral
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Reference> ::= <QualifiedName>
# Args: 1..1 - Symbols in the RHS.
$(gold_grammar)_produce-Reference = $(new ELink,$1,$(gold_location)) 

# Rule: <SimpleReference> ::= Identifier
# Args: 1..1 - Symbols in the RHS.
$(gold_grammar)_produce-SimpleReference_Identifier = $(new ELink,$1,$(gold_location)) 

# Rule: <Filename> ::= StringLiteral
# Args: 1..1 - Symbols in the RHS.
define $(gold_grammar)_produce-Filename_StringLiteral
	$(for file <- $(new MyFile),
		$(set file->fileName,$1)
				$(file))
endef

# Rule: <ReferenceList> ::= <Reference> ',' <ReferenceList>
# Args: 1..3 - Symbols in the RHS.
$(gold_grammar)_produce-ReferenceList_Comma = $1 $3

# Rule: <FilenameList> ::= <Filename> ',' <FilenameList>
# Args: 1..3 - Symbols in the RHS.
$(gold_grammar)_produce-FilenameList_Comma = $1 $3

# <QualifiedName> ::= Identifier '.' <QualifiedName>
$(gold_grammar)_produce-QualifiedName_Identifier_Dot         = $1.$3
# <QualifiedNameWithWildcard> ::= <QualifiedName> '.*'
$(gold_grammar)_produce-QualifiedNameWithWildcard_DotTimes   = $1.*



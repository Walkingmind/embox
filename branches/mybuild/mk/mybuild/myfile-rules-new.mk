# Generated by GOLD Parser Builder using MyBuild program template.

# Rule productions for 'MyFile' grammar.

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

# Rule: <Model> ::= <Package> <Imports> <Entities>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-Model
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Package> ::= package <QualifiedName>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-Package_package
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Package> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-Package
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Imports> ::= <Import> <Imports>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-Imports
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Imports> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-Imports2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Import> ::= import <ImportFeature> <QualifiedNameWithWildcard>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-Import_import
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ImportFeature> ::= feature
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-ImportFeature_feature
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ImportFeature> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-ImportFeature
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Entities> ::= <Entity> <Entities>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-Entities
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Entities> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-Entities2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Entity> ::= <Module>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-Entity
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Entity> ::= <Interface>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-Entity2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Interface> ::= interface Identifier <SuperInterfaces> '{' <InterfaceAttributes> '}'
# Args: 1..6 - Symbols; 6+1 - Location vector.
define $(gold_grammar)_produce-Interface_interface_Identifier_LBrace_RBrace
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <SuperInterfaces> ::= extends <InterfaceRefList>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-SuperInterfaces_extends
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <SuperInterfaces> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-SuperInterfaces
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <InterfaceAttributes> ::= <InterfaceAttribute> <InterfaceAttributes>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-InterfaceAttributes
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <InterfaceAttributes> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-InterfaceAttributes2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <InterfaceAttribute> ::= <Feature>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-InterfaceAttribute
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Feature> ::= feature Identifier <SuperFeatures>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-Feature_feature_Identifier
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <SuperFeatures> ::= extends <FeatureRefList>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-SuperFeatures_extends
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <SuperFeatures> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-SuperFeatures
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Module> ::= <ModuleModifiers> module Identifier <SuperModule> '{' <ModuleAttributes> '}'
# Args: 1..7 - Symbols; 7+1 - Location vector.
define $(gold_grammar)_produce-Module_module_Identifier_LBrace_RBrace
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleModifiers> ::= <ModuleModifier> <ModuleModifiers>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-ModuleModifiers
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleModifiers> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-ModuleModifiers2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleModifier> ::= static
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-ModuleModifier_static
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleModifier> ::= abstract
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-ModuleModifier_abstract
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <SuperModule> ::= extends <ModuleRef>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-SuperModule_extends
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <SuperModule> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-SuperModule
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleAttributes> ::= <ModuleAttribute> <ModuleAttributes>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-ModuleAttributes
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleAttributes> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-ModuleAttributes2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleAttribute> ::= <Depends>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-ModuleAttribute
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleAttribute> ::= <FeatureAttribute>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-ModuleAttribute2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleAttribute> ::= <FilenameAttribute>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-ModuleAttribute3
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleAttribute> ::= <MakeAttribute>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-ModuleAttribute4
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleAttribute> ::= <Option>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-ModuleAttribute5
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Depends> ::= depends <ModuleRefList>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-Depends_depends
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FeatureAttribute> ::= <FeatureAttributeNature> <FeatureRefList>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-FeatureAttribute
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FeatureAttributeNature> ::= provides
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-FeatureAttributeNature_provides
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FeatureAttributeNature> ::= requires
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-FeatureAttributeNature_requires
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FilenameAttribute> ::= <FilenameAttributeNature> <FilenameList>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-FilenameAttribute
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FilenameAttributeNature> ::= source
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-FilenameAttributeNature_source
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FilenameAttributeNature> ::= object
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-FilenameAttributeNature_object
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Option> ::= option Identifier ':' <OptionTypeWithAssignment>
# Args: 1..4 - Symbols; 4+1 - Location vector.
define $(gold_grammar)_produce-Option_option_Identifier_Colon
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <OptionTypeWithAssignment> ::= string <StringOptionAssignment>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-OptionTypeWithAssignment_string
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <OptionTypeWithAssignment> ::= number <NumberOptionAssignment>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-OptionTypeWithAssignment_number
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <OptionTypeWithAssignment> ::= boolean <BooleanOptionAssignment>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-OptionTypeWithAssignment_boolean
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <StringOptionAssignment> ::= '=' StringLiteral
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-StringOptionAssignment_Eq_StringLiteral
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <StringOptionAssignment> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-StringOptionAssignment
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <NumberOptionAssignment> ::= '=' NumberLiteral
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-NumberOptionAssignment_Eq_NumberLiteral
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <NumberOptionAssignment> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-NumberOptionAssignment
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <BooleanOptionAssignment> ::= '=' BooleanLiteral
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-BooleanOptionAssignment_Eq_BooleanLiteral
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <BooleanOptionAssignment> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-BooleanOptionAssignment
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <MakeAttribute> ::= make <Make>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-MakeAttribute_make
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Make> ::= <MakeFlags>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-Make
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Make> ::= <MakeRule>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-Make2
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <MakeFlags> ::= flags <StringList>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-MakeFlags_flags
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <MakeRule> ::= <Filename> <Prerequisites> <Recipes>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-MakeRule
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Prerequisites> ::= ':' <FilenameList>
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-Prerequisites_Colon
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Prerequisites> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-Prerequisites
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Recipes> ::= '{' <StringList> '}'
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-Recipes_LBrace_RBrace
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Recipes> ::= 
# Args: 1..0 - Symbols; 0+1 - Location vector.
define $(gold_grammar)_produce-Recipes
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <InterfaceRef> ::= <QualifiedName>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-InterfaceRef
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FeatureRef> ::= <QualifiedNameWithWildcard>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-FeatureRef
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleRef> ::= <QualifiedName>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-ModuleRef
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <Filename> ::= StringLiteral
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-Filename_StringLiteral
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <String> ::= StringLiteral
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-String_StringLiteral
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <InterfaceRefList> ::= <InterfaceRef> ',' <InterfaceRefList>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-InterfaceRefList_Comma
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <InterfaceRefList> ::= <InterfaceRef>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-InterfaceRefList
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FeatureRefList> ::= <FeatureRef> ',' <FeatureRefList>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-FeatureRefList_Comma
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FeatureRefList> ::= <FeatureRef>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-FeatureRefList
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleRefList> ::= <ModuleRef> ',' <ModuleRefList>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-ModuleRefList_Comma
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <ModuleRefList> ::= <ModuleRef>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-ModuleRefList
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FilenameList> ::= <Filename> ',' <FilenameList>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-FilenameList_Comma
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <FilenameList> ::= <Filename>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-FilenameList
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <StringList> ::= <String> ',' <StringList>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-StringList_Comma
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <StringList> ::= <String>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-StringList
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <QualifiedName> ::= Identifier '.' <QualifiedName>
# Args: 1..3 - Symbols; 3+1 - Location vector.
define $(gold_grammar)_produce-QualifiedName_Identifier_Dot
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <QualifiedName> ::= Identifier
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-QualifiedName_Identifier
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <QualifiedNameWithWildcard> ::= <QualifiedName> '.*'
# Args: 1..2 - Symbols; 2+1 - Location vector.
define $(gold_grammar)_produce-QualifiedNameWithWildcard_DotTimes
	$(gold_default_produce)# TODO Auto-generated stub!
endef

# Rule: <QualifiedNameWithWildcard> ::= <QualifiedName>
# Args: 1..1 - Symbols; 1+1 - Location vector.
define $(gold_grammar)_produce-QualifiedNameWithWildcard
	$(gold_default_produce)# TODO Auto-generated stub!
endef



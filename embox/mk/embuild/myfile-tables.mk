# This file is auto-generated by GOLD Parser Builder using MyBuild program
# template. Do not edit!

ifndef gold_prefix
$(error 'gold_prefix' is not defined. \
	Do not include $(notdir $(lastword $(MAKEFILE_LIST))) directly!)
endif # gold_prefix

ifdef __gold_$(gold_prefix)_parse
$(error Multiple inclusion of tables file for '$(gold_prefix)' parser. \
	Do not include $(notdir $(lastword $(MAKEFILE_LIST))) directly!)
endif # __gold_$(gold_prefix)_parse

#
# Params:
#   1. Stream of decimal char codes representing an input.
# Return:
#   Result of interpreting parse tree with user-defined handlers.
#   TODO error handling.
#
# Note:
#   This function is auto-generated by GOLD Parser Builder using MyBuild
#   program template. Do not edit!
define __gold_$(gold_prefix)_parse
	# Grammar info:
	#   Name            : MyFile
	#   Version         : 0.1
	#   Author          : Eldar Abusalimov
	#   About           : MyBuild file
	#   Case Sensitive  : True
	#   Start Symbol    : 23
	$(gold-parser \

		$(gold-symbol-table \
			# Args: Id,Type,Name
			$(gold-symbol  0,3,# (EOF)
				Symbol_EOF),
			$(gold-symbol  1,7,# (Error)
				Symbol_Error),
			$(gold-symbol  2,2,# (Whitespace)
				Symbol_Whitespace),
			$(gold-symbol  3,1,# ','
				Symbol_Comma),
			$(gold-symbol  4,1,# '.'
				Symbol_Dot),
			$(gold-symbol  5,1,# '.*'
				Symbol_DotTimes),
			$(gold-symbol  6,1,# ';'
				Symbol_Semi),
			$(gold-symbol  7,1,# '{'
				Symbol_LBrace),
			$(gold-symbol  8,1,# '}'
				Symbol_RBrace),
			$(gold-symbol  9,1,# abstract
				Symbol_abstract),
			$(gold-symbol 10,1,# depends
				Symbol_depends),
			$(gold-symbol 11,1,# extends
				Symbol_extends),
			$(gold-symbol 12,1,# file
				Symbol_file),
			$(gold-symbol 13,1,# Identifier
				Symbol_Identifier),
			$(gold-symbol 14,1,# import
				Symbol_import),
			$(gold-symbol 15,1,# module
				Symbol_module),
			$(gold-symbol 16,1,# package
				Symbol_package),
			$(gold-symbol 17,1,# source
				Symbol_source),
			$(gold-symbol 18,1,# static
				Symbol_static),
			$(gold-symbol 19,1,# StringLiteral
				Symbol_StringLiteral),
			$(gold-symbol 20,0,# <DependencyDecl>
				Symbol_DependencyDecl),
			$(gold-symbol 21,0,# <ImportDecl>
				Symbol_ImportDecl),
			$(gold-symbol 22,0,# <ImportDecls>
				Symbol_ImportDecls),
			$(gold-symbol 23,0,# <Model>
				Symbol_Model),
			$(gold-symbol 24,0,# <ModuleBodyDecl>
				Symbol_ModuleBodyDecl),
			$(gold-symbol 25,0,# <ModuleBodyDecls>
				Symbol_ModuleBodyDecls),
			$(gold-symbol 26,0,# <ModuleDecl>
				Symbol_ModuleDecl),
			$(gold-symbol 27,0,# <ModuleDecls>
				Symbol_ModuleDecls),
			$(gold-symbol 28,0,# <ModuleModifier>
				Symbol_ModuleModifier),
			$(gold-symbol 29,0,# <ModuleModifiers>
				Symbol_ModuleModifiers),
			$(gold-symbol 30,0,# <PackageDecl>
				Symbol_PackageDecl),
			$(gold-symbol 31,0,# <QualifiedName>
				Symbol_QualifiedName),
			$(gold-symbol 32,0,# <QualifiedNameWithWildcard>
				Symbol_QualifiedNameWithWildcard),
			$(gold-symbol 33,0,# <SourceBody>
				Symbol_SourceBody),
			$(gold-symbol 34,0,# <SourceDecl>
				Symbol_SourceDecl),
			$(gold-symbol 35,0,# <SourceStatement>
				Symbol_SourceStatement),
			$(gold-symbol 36,0,# <SourceStatements>
				Symbol_SourceStatements),
			$(gold-symbol 37,0,# <SuperModules>
				Symbol_SuperModules),
			$(gold-symbol 38,0,# <SuperModulesList>
				Symbol_SuperModulesList) 
		),# Total 39 symbol(s).

		$(gold-rule-table \
			# Args: Id,Nonterminal,SymbolsNr,Name
			$(gold-rule  0,31,3,# <QualifiedName> ::= Identifier '.' <QualifiedName>
				Rule_QualifiedName_Identifier_Dot),
			$(gold-rule  1,31,1,# <QualifiedName> ::= Identifier
				Rule_QualifiedName_Identifier),
			$(gold-rule  2,32,2,# <QualifiedNameWithWildcard> ::= <QualifiedName> '.*'
				Rule_QualifiedNameWithWildcard_DotTimes),
			$(gold-rule  3,32,1,# <QualifiedNameWithWildcard> ::= <QualifiedName>
				Rule_QualifiedNameWithWildcard),
			$(gold-rule  4,23,3,# <Model> ::= <PackageDecl> <ImportDecls> <ModuleDecls>
				Rule_Model),
			$(gold-rule  5,30,3,# <PackageDecl> ::= package <QualifiedName> ';'
				Rule_PackageDecl_package_Semi),
			$(gold-rule  6,30,0,# <PackageDecl> ::= 
				Rule_PackageDecl),
			$(gold-rule  7,22,2,# <ImportDecls> ::= <ImportDecl> <ImportDecls>
				Rule_ImportDecls),
			$(gold-rule  8,22,0,# <ImportDecls> ::= 
				Rule_ImportDecls2),
			$(gold-rule  9,21,3,# <ImportDecl> ::= import <QualifiedNameWithWildcard> ';'
				Rule_ImportDecl_import_Semi),
			$(gold-rule 10,27,2,# <ModuleDecls> ::= <ModuleDecl> <ModuleDecls>
				Rule_ModuleDecls),
			$(gold-rule 11,27,0,# <ModuleDecls> ::= 
				Rule_ModuleDecls2),
			$(gold-rule 12,26,7,# <ModuleDecl> ::= <ModuleModifiers> module Identifier <SuperModules> '{' <ModuleBodyDecls> '}'
				Rule_ModuleDecl_module_Identifier_LBrace_RBrace),
			$(gold-rule 13,29,2,# <ModuleModifiers> ::= <ModuleModifier> <ModuleModifiers>
				Rule_ModuleModifiers),
			$(gold-rule 14,29,0,# <ModuleModifiers> ::= 
				Rule_ModuleModifiers2),
			$(gold-rule 15,28,1,# <ModuleModifier> ::= static
				Rule_ModuleModifier_static),
			$(gold-rule 16,28,1,# <ModuleModifier> ::= abstract
				Rule_ModuleModifier_abstract),
			$(gold-rule 17,37,2,# <SuperModules> ::= extends <SuperModulesList>
				Rule_SuperModules_extends),
			$(gold-rule 18,37,0,# <SuperModules> ::= 
				Rule_SuperModules),
			$(gold-rule 19,38,3,# <SuperModulesList> ::= <QualifiedName> ',' <SuperModulesList>
				Rule_SuperModulesList_Comma),
			$(gold-rule 20,38,1,# <SuperModulesList> ::= <QualifiedName>
				Rule_SuperModulesList),
			$(gold-rule 21,25,2,# <ModuleBodyDecls> ::= <ModuleBodyDecl> <ModuleBodyDecls>
				Rule_ModuleBodyDecls),
			$(gold-rule 22,25,0,# <ModuleBodyDecls> ::= 
				Rule_ModuleBodyDecls2),
			$(gold-rule 23,24,1,# <ModuleBodyDecl> ::= <SourceDecl>
				Rule_ModuleBodyDecl),
			$(gold-rule 24,24,1,# <ModuleBodyDecl> ::= <DependencyDecl>
				Rule_ModuleBodyDecl2),
			$(gold-rule 25,34,2,# <SourceDecl> ::= source <SourceBody>
				Rule_SourceDecl_source),
			$(gold-rule 26,33,3,# <SourceBody> ::= '{' <SourceStatements> '}'
				Rule_SourceBody_LBrace_RBrace),
			$(gold-rule 27,33,1,# <SourceBody> ::= <SourceStatement>
				Rule_SourceBody),
			$(gold-rule 28,36,2,# <SourceStatements> ::= <SourceStatement> <SourceStatements>
				Rule_SourceStatements),
			$(gold-rule 29,36,0,# <SourceStatements> ::= 
				Rule_SourceStatements2),
			$(gold-rule 30,35,3,# <SourceStatement> ::= file StringLiteral ';'
				Rule_SourceStatement_file_StringLiteral_Semi),
			$(gold-rule 31,20,1,# <DependencyDecl> ::= depends
				Rule_DependencyDecl_depends) 
		),# Total 32 rule(s).

		$(gold-charset-table \
			# Args: Id,Chars...
			$(gold-charset 0,# &#9;&#10;&#11;&#12;&#13; &#160; #
				9,10,11,12,13,32,160),
			$(gold-charset 1,# , #
				44),
			$(gold-charset 2,# ; #
				59),
			$(gold-charset 3,# { #
				123),
			$(gold-charset 4,# } #
				125),
			$(gold-charset 5,# ABCDEFGHIJKLMNOPQRSTUVWXYZ_bcghjklnoqrtuvwxyz #
				65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,98,99,103,104,106,107,108,110,111,113,114,116,117,118,119,120,121,122),
			$(gold-charset 6,# &quot; #
				34),
			$(gold-charset 7,# . #
				46),
			$(gold-charset 8,# / #
				47),
			$(gold-charset 9,# a #
				97),
			$(gold-charset 10,# d #
				100),
			$(gold-charset 11,# e #
				101),
			$(gold-charset 12,# f #
				102),
			$(gold-charset 13,# i #
				105),
			$(gold-charset 14,# m #
				109),
			$(gold-charset 15,# p #
				112),
			$(gold-charset 16,# s #
				115),
			$(gold-charset 17,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 18,# &#9; !#$%&amp;'()*+,-./0123456789:;&lt;=&gt;?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~&#160; #
				9,32,33,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,160),
			$(gold-charset 19,# \ #
				92),
			$(gold-charset 20,#  !&quot;#$%&amp;'()*+,-./0123456789:;&lt;=&gt;?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~&#160; #
				32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,160),
			$(gold-charset 21,# * #
				42),
			$(gold-charset 22,# &#9;&#10;&#11;&#12;&#13; #
				9,10,11,12,13),
			$(gold-charset 23,# !&quot;#$%&amp;'()+,-./0123456789:;&lt;=&gt;?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ #
				33,34,35,36,37,38,39,40,41,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126),
			$(gold-charset 24,#  &#160; #
				32,160),
			$(gold-charset 25,# !&quot;#$%&amp;'()+,-.0123456789:;&lt;=&gt;?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~ #
				33,34,35,36,37,38,39,40,41,43,44,45,46,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126),
			$(gold-charset 26,# &#9;&#11;&#12; !&quot;#$%&amp;'()*+,-./0123456789:;&lt;=&gt;?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~&#160; #
				9,11,12,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,160),
			$(gold-charset 27,# &#13; #
				13),
			$(gold-charset 28,# &#10; #
				10),
			$(gold-charset 29,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_acdefghijklmnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 30,# b #
				98),
			$(gold-charset 31,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrtuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,116,117,118,119,120,121,122),
			$(gold-charset 32,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrsuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,117,118,119,120,121,122),
			$(gold-charset 33,# t #
				116),
			$(gold-charset 34,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,115,116,117,118,119,120,121,122),
			$(gold-charset 35,# r #
				114),
			$(gold-charset 36,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_bcdefghijklmnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 37,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abdefghijklmnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 38,# c #
				99),
			$(gold-charset 39,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdfghijklmnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 40,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnoqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 41,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 42,# n #
				110),
			$(gold-charset 43,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcefghijklmnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 44,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,121,122),
			$(gold-charset 45,# x #
				120),
			$(gold-charset 46,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghjklmnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 47,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijkmnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,109,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 48,# l #
				108),
			$(gold-charset 49,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 50,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnpqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,110,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 51,# o #
				111),
			$(gold-charset 52,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,118,119,120,121,122),
			$(gold-charset 53,# u #
				117),
			$(gold-charset 54,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijlmnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 55,# k #
				107),
			$(gold-charset 56,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefhijklmnopqrstuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122),
			$(gold-charset 57,# g #
				103),
			$(gold-charset 58,# 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnpqrsuvwxyz #
				48,49,50,51,52,53,54,55,56,57,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,95,97,98,99,100,101,102,103,104,105,106,107,108,109,110,112,113,114,115,117,118,119,120,121,122)
		),# Total 59 charset(s).

		$(gold-dfa-table 0,# <- Initial state
			$(gold-dfa-state 0,-1,
				$(gold-dfa-edge 0,1),
				$(gold-dfa-edge 1,2),
				$(gold-dfa-edge 2,3),
				$(gold-dfa-edge 3,4),
				$(gold-dfa-edge 4,5),
				$(gold-dfa-edge 5,6),
				$(gold-dfa-edge 6,8),
				$(gold-dfa-edge 7,13),
				$(gold-dfa-edge 8,15),
				$(gold-dfa-edge 9,28),
				$(gold-dfa-edge 10,36),
				$(gold-dfa-edge 11,43),
				$(gold-dfa-edge 12,50),
				$(gold-dfa-edge 13,54),
				$(gold-dfa-edge 14,60),
				$(gold-dfa-edge 15,66),
				$(gold-dfa-edge 16,73),
			),# Total 17 edge(s).
			$(gold-dfa-state 1,2,
				$(gold-dfa-edge 0,1),
			),# Total 1 edge(s).
			$(gold-dfa-state 2,3,
			),# Total 0 edge(s).
			$(gold-dfa-state 3,6,
			),# Total 0 edge(s).
			$(gold-dfa-state 4,7,
			),# Total 0 edge(s).
			$(gold-dfa-state 5,8,
			),# Total 0 edge(s).
			$(gold-dfa-state 6,13,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
			$(gold-dfa-state 7,13,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
			$(gold-dfa-state 8,-1,
				$(gold-dfa-edge 18,9),
				$(gold-dfa-edge 19,10),
				$(gold-dfa-edge 6,12),
			),# Total 3 edge(s).
			$(gold-dfa-state 9,-1,
				$(gold-dfa-edge 18,9),
				$(gold-dfa-edge 19,10),
				$(gold-dfa-edge 6,12),
			),# Total 3 edge(s).
			$(gold-dfa-state 10,-1,
				$(gold-dfa-edge 20,11),
			),# Total 1 edge(s).
			$(gold-dfa-state 11,-1,
				$(gold-dfa-edge 18,9),
				$(gold-dfa-edge 19,10),
				$(gold-dfa-edge 6,12),
			),# Total 3 edge(s).
			$(gold-dfa-state 12,19,
			),# Total 0 edge(s).
			$(gold-dfa-state 13,4,
				$(gold-dfa-edge 21,14),
			),# Total 1 edge(s).
			$(gold-dfa-state 14,5,
			),# Total 0 edge(s).
			$(gold-dfa-state 15,-1,
				$(gold-dfa-edge 21,16),
				$(gold-dfa-edge 8,24),
			),# Total 2 edge(s).
			$(gold-dfa-state 16,-1,
				$(gold-dfa-edge 22,17),
				$(gold-dfa-edge 23,18),
				$(gold-dfa-edge 24,19),
				$(gold-dfa-edge 21,20),
			),# Total 4 edge(s).
			$(gold-dfa-state 17,-1,
				$(gold-dfa-edge 22,17),
				$(gold-dfa-edge 23,18),
				$(gold-dfa-edge 24,19),
				$(gold-dfa-edge 21,20),
			),# Total 4 edge(s).
			$(gold-dfa-state 18,-1,
				$(gold-dfa-edge 22,17),
				$(gold-dfa-edge 23,18),
				$(gold-dfa-edge 24,19),
				$(gold-dfa-edge 21,20),
			),# Total 4 edge(s).
			$(gold-dfa-state 19,-1,
				$(gold-dfa-edge 22,17),
				$(gold-dfa-edge 23,18),
				$(gold-dfa-edge 24,19),
				$(gold-dfa-edge 21,20),
			),# Total 4 edge(s).
			$(gold-dfa-state 20,-1,
				$(gold-dfa-edge 22,17),
				$(gold-dfa-edge 24,21),
				$(gold-dfa-edge 25,22),
				$(gold-dfa-edge 21,20),
				$(gold-dfa-edge 8,23),
			),# Total 5 edge(s).
			$(gold-dfa-state 21,-1,
				$(gold-dfa-edge 22,17),
				$(gold-dfa-edge 23,18),
				$(gold-dfa-edge 24,19),
				$(gold-dfa-edge 21,20),
			),# Total 4 edge(s).
			$(gold-dfa-state 22,-1,
				$(gold-dfa-edge 22,17),
				$(gold-dfa-edge 23,18),
				$(gold-dfa-edge 24,19),
				$(gold-dfa-edge 21,20),
			),# Total 4 edge(s).
			$(gold-dfa-state 23,2,
				$(gold-dfa-edge 22,17),
				$(gold-dfa-edge 23,18),
				$(gold-dfa-edge 24,19),
				$(gold-dfa-edge 21,20),
			),# Total 4 edge(s).
			$(gold-dfa-state 24,2,
				$(gold-dfa-edge 26,25),
				$(gold-dfa-edge 27,26),
				$(gold-dfa-edge 28,27),
			),# Total 3 edge(s).
			$(gold-dfa-state 25,2,
				$(gold-dfa-edge 26,25),
				$(gold-dfa-edge 27,26),
				$(gold-dfa-edge 28,27),
			),# Total 3 edge(s).
			$(gold-dfa-state 26,-1,
				$(gold-dfa-edge 28,27),
			),# Total 1 edge(s).
			$(gold-dfa-state 27,2,
			),# Total 0 edge(s).
			$(gold-dfa-state 28,13,
				$(gold-dfa-edge 29,7),
				$(gold-dfa-edge 30,29),
			),# Total 2 edge(s).
			$(gold-dfa-state 29,13,
				$(gold-dfa-edge 31,7),
				$(gold-dfa-edge 16,30),
			),# Total 2 edge(s).
			$(gold-dfa-state 30,13,
				$(gold-dfa-edge 32,7),
				$(gold-dfa-edge 33,31),
			),# Total 2 edge(s).
			$(gold-dfa-state 31,13,
				$(gold-dfa-edge 34,7),
				$(gold-dfa-edge 35,32),
			),# Total 2 edge(s).
			$(gold-dfa-state 32,13,
				$(gold-dfa-edge 36,7),
				$(gold-dfa-edge 9,33),
			),# Total 2 edge(s).
			$(gold-dfa-state 33,13,
				$(gold-dfa-edge 37,7),
				$(gold-dfa-edge 38,34),
			),# Total 2 edge(s).
			$(gold-dfa-state 34,13,
				$(gold-dfa-edge 32,7),
				$(gold-dfa-edge 33,35),
			),# Total 2 edge(s).
			$(gold-dfa-state 35,9,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
			$(gold-dfa-state 36,13,
				$(gold-dfa-edge 39,7),
				$(gold-dfa-edge 11,37),
			),# Total 2 edge(s).
			$(gold-dfa-state 37,13,
				$(gold-dfa-edge 40,7),
				$(gold-dfa-edge 15,38),
			),# Total 2 edge(s).
			$(gold-dfa-state 38,13,
				$(gold-dfa-edge 39,7),
				$(gold-dfa-edge 11,39),
			),# Total 2 edge(s).
			$(gold-dfa-state 39,13,
				$(gold-dfa-edge 41,7),
				$(gold-dfa-edge 42,40),
			),# Total 2 edge(s).
			$(gold-dfa-state 40,13,
				$(gold-dfa-edge 43,7),
				$(gold-dfa-edge 10,41),
			),# Total 2 edge(s).
			$(gold-dfa-state 41,13,
				$(gold-dfa-edge 31,7),
				$(gold-dfa-edge 16,42),
			),# Total 2 edge(s).
			$(gold-dfa-state 42,10,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
			$(gold-dfa-state 43,13,
				$(gold-dfa-edge 44,7),
				$(gold-dfa-edge 45,44),
			),# Total 2 edge(s).
			$(gold-dfa-state 44,13,
				$(gold-dfa-edge 32,7),
				$(gold-dfa-edge 33,45),
			),# Total 2 edge(s).
			$(gold-dfa-state 45,13,
				$(gold-dfa-edge 39,7),
				$(gold-dfa-edge 11,46),
			),# Total 2 edge(s).
			$(gold-dfa-state 46,13,
				$(gold-dfa-edge 41,7),
				$(gold-dfa-edge 42,47),
			),# Total 2 edge(s).
			$(gold-dfa-state 47,13,
				$(gold-dfa-edge 43,7),
				$(gold-dfa-edge 10,48),
			),# Total 2 edge(s).
			$(gold-dfa-state 48,13,
				$(gold-dfa-edge 31,7),
				$(gold-dfa-edge 16,49),
			),# Total 2 edge(s).
			$(gold-dfa-state 49,11,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
			$(gold-dfa-state 50,13,
				$(gold-dfa-edge 46,7),
				$(gold-dfa-edge 13,51),
			),# Total 2 edge(s).
			$(gold-dfa-state 51,13,
				$(gold-dfa-edge 47,7),
				$(gold-dfa-edge 48,52),
			),# Total 2 edge(s).
			$(gold-dfa-state 52,13,
				$(gold-dfa-edge 39,7),
				$(gold-dfa-edge 11,53),
			),# Total 2 edge(s).
			$(gold-dfa-state 53,12,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
			$(gold-dfa-state 54,13,
				$(gold-dfa-edge 49,7),
				$(gold-dfa-edge 14,55),
			),# Total 2 edge(s).
			$(gold-dfa-state 55,13,
				$(gold-dfa-edge 40,7),
				$(gold-dfa-edge 15,56),
			),# Total 2 edge(s).
			$(gold-dfa-state 56,13,
				$(gold-dfa-edge 50,7),
				$(gold-dfa-edge 51,57),
			),# Total 2 edge(s).
			$(gold-dfa-state 57,13,
				$(gold-dfa-edge 34,7),
				$(gold-dfa-edge 35,58),
			),# Total 2 edge(s).
			$(gold-dfa-state 58,13,
				$(gold-dfa-edge 32,7),
				$(gold-dfa-edge 33,59),
			),# Total 2 edge(s).
			$(gold-dfa-state 59,14,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
			$(gold-dfa-state 60,13,
				$(gold-dfa-edge 50,7),
				$(gold-dfa-edge 51,61),
			),# Total 2 edge(s).
			$(gold-dfa-state 61,13,
				$(gold-dfa-edge 43,7),
				$(gold-dfa-edge 10,62),
			),# Total 2 edge(s).
			$(gold-dfa-state 62,13,
				$(gold-dfa-edge 52,7),
				$(gold-dfa-edge 53,63),
			),# Total 2 edge(s).
			$(gold-dfa-state 63,13,
				$(gold-dfa-edge 47,7),
				$(gold-dfa-edge 48,64),
			),# Total 2 edge(s).
			$(gold-dfa-state 64,13,
				$(gold-dfa-edge 39,7),
				$(gold-dfa-edge 11,65),
			),# Total 2 edge(s).
			$(gold-dfa-state 65,15,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
			$(gold-dfa-state 66,13,
				$(gold-dfa-edge 36,7),
				$(gold-dfa-edge 9,67),
			),# Total 2 edge(s).
			$(gold-dfa-state 67,13,
				$(gold-dfa-edge 37,7),
				$(gold-dfa-edge 38,68),
			),# Total 2 edge(s).
			$(gold-dfa-state 68,13,
				$(gold-dfa-edge 54,7),
				$(gold-dfa-edge 55,69),
			),# Total 2 edge(s).
			$(gold-dfa-state 69,13,
				$(gold-dfa-edge 36,7),
				$(gold-dfa-edge 9,70),
			),# Total 2 edge(s).
			$(gold-dfa-state 70,13,
				$(gold-dfa-edge 56,7),
				$(gold-dfa-edge 57,71),
			),# Total 2 edge(s).
			$(gold-dfa-state 71,13,
				$(gold-dfa-edge 39,7),
				$(gold-dfa-edge 11,72),
			),# Total 2 edge(s).
			$(gold-dfa-state 72,16,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
			$(gold-dfa-state 73,13,
				$(gold-dfa-edge 58,7),
				$(gold-dfa-edge 51,74),
				$(gold-dfa-edge 33,79),
			),# Total 3 edge(s).
			$(gold-dfa-state 74,13,
				$(gold-dfa-edge 52,7),
				$(gold-dfa-edge 53,75),
			),# Total 2 edge(s).
			$(gold-dfa-state 75,13,
				$(gold-dfa-edge 34,7),
				$(gold-dfa-edge 35,76),
			),# Total 2 edge(s).
			$(gold-dfa-state 76,13,
				$(gold-dfa-edge 37,7),
				$(gold-dfa-edge 38,77),
			),# Total 2 edge(s).
			$(gold-dfa-state 77,13,
				$(gold-dfa-edge 39,7),
				$(gold-dfa-edge 11,78),
			),# Total 2 edge(s).
			$(gold-dfa-state 78,17,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
			$(gold-dfa-state 79,13,
				$(gold-dfa-edge 36,7),
				$(gold-dfa-edge 9,80),
			),# Total 2 edge(s).
			$(gold-dfa-state 80,13,
				$(gold-dfa-edge 32,7),
				$(gold-dfa-edge 33,81),
			),# Total 2 edge(s).
			$(gold-dfa-state 81,13,
				$(gold-dfa-edge 46,7),
				$(gold-dfa-edge 13,82),
			),# Total 2 edge(s).
			$(gold-dfa-state 82,13,
				$(gold-dfa-edge 37,7),
				$(gold-dfa-edge 38,83),
			),# Total 2 edge(s).
			$(gold-dfa-state 83,18,
				$(gold-dfa-edge 17,7),
			),# Total 1 edge(s).
		),# Total 84 state(s).

		$(gold-lalr-table 0,# <- Initial state
			$(gold-lalr-state 0,
				$(gold-lalr-action 16,1,1),# Shift to State 1
				$(gold-lalr-action 23,3,2),# Go to State 2
				$(gold-lalr-action 30,3,3),# Go to State 3
				$(gold-lalr-action 0,2,6),# Reduce Production 6
				$(gold-lalr-action 9,2,6),# Reduce Production 6
				$(gold-lalr-action 14,2,6),# Reduce Production 6
				$(gold-lalr-action 15,2,6),# Reduce Production 6
				$(gold-lalr-action 18,2,6)# Reduce Production 6
			),# Total 8 action(s).
			$(gold-lalr-state 1,
				$(gold-lalr-action 13,1,4),# Shift to State 4
				$(gold-lalr-action 31,3,5)# Go to State 5
			),# Total 2 action(s).
			$(gold-lalr-state 2,
				$(gold-lalr-action 0,4,0)# Accept 0
			),# Total 1 action(s).
			$(gold-lalr-state 3,
				$(gold-lalr-action 14,1,6),# Shift to State 6
				$(gold-lalr-action 21,3,7),# Go to State 7
				$(gold-lalr-action 22,3,8),# Go to State 8
				$(gold-lalr-action 0,2,8),# Reduce Production 8
				$(gold-lalr-action 9,2,8),# Reduce Production 8
				$(gold-lalr-action 15,2,8),# Reduce Production 8
				$(gold-lalr-action 18,2,8)# Reduce Production 8
			),# Total 7 action(s).
			$(gold-lalr-state 4,
				$(gold-lalr-action 4,1,9),# Shift to State 9
				$(gold-lalr-action 3,2,1),# Reduce Production 1
				$(gold-lalr-action 5,2,1),# Reduce Production 1
				$(gold-lalr-action 6,2,1),# Reduce Production 1
				$(gold-lalr-action 7,2,1)# Reduce Production 1
			),# Total 5 action(s).
			$(gold-lalr-state 5,
				$(gold-lalr-action 6,1,10)# Shift to State 10
			),# Total 1 action(s).
			$(gold-lalr-state 6,
				$(gold-lalr-action 13,1,4),# Shift to State 4
				$(gold-lalr-action 31,3,11),# Go to State 11
				$(gold-lalr-action 32,3,12)# Go to State 12
			),# Total 3 action(s).
			$(gold-lalr-state 7,
				$(gold-lalr-action 14,1,6),# Shift to State 6
				$(gold-lalr-action 21,3,7),# Go to State 7
				$(gold-lalr-action 22,3,13),# Go to State 13
				$(gold-lalr-action 0,2,8),# Reduce Production 8
				$(gold-lalr-action 9,2,8),# Reduce Production 8
				$(gold-lalr-action 15,2,8),# Reduce Production 8
				$(gold-lalr-action 18,2,8)# Reduce Production 8
			),# Total 7 action(s).
			$(gold-lalr-state 8,
				$(gold-lalr-action 9,1,14),# Shift to State 14
				$(gold-lalr-action 18,1,15),# Shift to State 15
				$(gold-lalr-action 26,3,16),# Go to State 16
				$(gold-lalr-action 27,3,17),# Go to State 17
				$(gold-lalr-action 28,3,18),# Go to State 18
				$(gold-lalr-action 29,3,19),# Go to State 19
				$(gold-lalr-action 0,2,11),# Reduce Production 11
				$(gold-lalr-action 15,2,14)# Reduce Production 14
			),# Total 8 action(s).
			$(gold-lalr-state 9,
				$(gold-lalr-action 13,1,4),# Shift to State 4
				$(gold-lalr-action 31,3,20)# Go to State 20
			),# Total 2 action(s).
			$(gold-lalr-state 10,
				$(gold-lalr-action 0,2,5),# Reduce Production 5
				$(gold-lalr-action 9,2,5),# Reduce Production 5
				$(gold-lalr-action 14,2,5),# Reduce Production 5
				$(gold-lalr-action 15,2,5),# Reduce Production 5
				$(gold-lalr-action 18,2,5)# Reduce Production 5
			),# Total 5 action(s).
			$(gold-lalr-state 11,
				$(gold-lalr-action 5,1,21),# Shift to State 21
				$(gold-lalr-action 6,2,3)# Reduce Production 3
			),# Total 2 action(s).
			$(gold-lalr-state 12,
				$(gold-lalr-action 6,1,22)# Shift to State 22
			),# Total 1 action(s).
			$(gold-lalr-state 13,
				$(gold-lalr-action 0,2,7),# Reduce Production 7
				$(gold-lalr-action 9,2,7),# Reduce Production 7
				$(gold-lalr-action 15,2,7),# Reduce Production 7
				$(gold-lalr-action 18,2,7)# Reduce Production 7
			),# Total 4 action(s).
			$(gold-lalr-state 14,
				$(gold-lalr-action 9,2,16),# Reduce Production 16
				$(gold-lalr-action 15,2,16),# Reduce Production 16
				$(gold-lalr-action 18,2,16)# Reduce Production 16
			),# Total 3 action(s).
			$(gold-lalr-state 15,
				$(gold-lalr-action 9,2,15),# Reduce Production 15
				$(gold-lalr-action 15,2,15),# Reduce Production 15
				$(gold-lalr-action 18,2,15)# Reduce Production 15
			),# Total 3 action(s).
			$(gold-lalr-state 16,
				$(gold-lalr-action 9,1,14),# Shift to State 14
				$(gold-lalr-action 18,1,15),# Shift to State 15
				$(gold-lalr-action 26,3,16),# Go to State 16
				$(gold-lalr-action 27,3,23),# Go to State 23
				$(gold-lalr-action 28,3,18),# Go to State 18
				$(gold-lalr-action 29,3,19),# Go to State 19
				$(gold-lalr-action 0,2,11),# Reduce Production 11
				$(gold-lalr-action 15,2,14)# Reduce Production 14
			),# Total 8 action(s).
			$(gold-lalr-state 17,
				$(gold-lalr-action 0,2,4)# Reduce Production 4
			),# Total 1 action(s).
			$(gold-lalr-state 18,
				$(gold-lalr-action 9,1,14),# Shift to State 14
				$(gold-lalr-action 18,1,15),# Shift to State 15
				$(gold-lalr-action 28,3,18),# Go to State 18
				$(gold-lalr-action 29,3,24),# Go to State 24
				$(gold-lalr-action 15,2,14)# Reduce Production 14
			),# Total 5 action(s).
			$(gold-lalr-state 19,
				$(gold-lalr-action 15,1,25)# Shift to State 25
			),# Total 1 action(s).
			$(gold-lalr-state 20,
				$(gold-lalr-action 3,2,0),# Reduce Production 0
				$(gold-lalr-action 5,2,0),# Reduce Production 0
				$(gold-lalr-action 6,2,0),# Reduce Production 0
				$(gold-lalr-action 7,2,0)# Reduce Production 0
			),# Total 4 action(s).
			$(gold-lalr-state 21,
				$(gold-lalr-action 6,2,2)# Reduce Production 2
			),# Total 1 action(s).
			$(gold-lalr-state 22,
				$(gold-lalr-action 0,2,9),# Reduce Production 9
				$(gold-lalr-action 9,2,9),# Reduce Production 9
				$(gold-lalr-action 14,2,9),# Reduce Production 9
				$(gold-lalr-action 15,2,9),# Reduce Production 9
				$(gold-lalr-action 18,2,9)# Reduce Production 9
			),# Total 5 action(s).
			$(gold-lalr-state 23,
				$(gold-lalr-action 0,2,10)# Reduce Production 10
			),# Total 1 action(s).
			$(gold-lalr-state 24,
				$(gold-lalr-action 15,2,13)# Reduce Production 13
			),# Total 1 action(s).
			$(gold-lalr-state 25,
				$(gold-lalr-action 13,1,26)# Shift to State 26
			),# Total 1 action(s).
			$(gold-lalr-state 26,
				$(gold-lalr-action 11,1,27),# Shift to State 27
				$(gold-lalr-action 37,3,28),# Go to State 28
				$(gold-lalr-action 7,2,18)# Reduce Production 18
			),# Total 3 action(s).
			$(gold-lalr-state 27,
				$(gold-lalr-action 13,1,4),# Shift to State 4
				$(gold-lalr-action 31,3,29),# Go to State 29
				$(gold-lalr-action 38,3,30)# Go to State 30
			),# Total 3 action(s).
			$(gold-lalr-state 28,
				$(gold-lalr-action 7,1,31)# Shift to State 31
			),# Total 1 action(s).
			$(gold-lalr-state 29,
				$(gold-lalr-action 3,1,32),# Shift to State 32
				$(gold-lalr-action 7,2,20)# Reduce Production 20
			),# Total 2 action(s).
			$(gold-lalr-state 30,
				$(gold-lalr-action 7,2,17)# Reduce Production 17
			),# Total 1 action(s).
			$(gold-lalr-state 31,
				$(gold-lalr-action 10,1,33),# Shift to State 33
				$(gold-lalr-action 17,1,34),# Shift to State 34
				$(gold-lalr-action 20,3,35),# Go to State 35
				$(gold-lalr-action 24,3,36),# Go to State 36
				$(gold-lalr-action 25,3,37),# Go to State 37
				$(gold-lalr-action 34,3,38),# Go to State 38
				$(gold-lalr-action 8,2,22)# Reduce Production 22
			),# Total 7 action(s).
			$(gold-lalr-state 32,
				$(gold-lalr-action 13,1,4),# Shift to State 4
				$(gold-lalr-action 31,3,29),# Go to State 29
				$(gold-lalr-action 38,3,39)# Go to State 39
			),# Total 3 action(s).
			$(gold-lalr-state 33,
				$(gold-lalr-action 8,2,31),# Reduce Production 31
				$(gold-lalr-action 10,2,31),# Reduce Production 31
				$(gold-lalr-action 17,2,31)# Reduce Production 31
			),# Total 3 action(s).
			$(gold-lalr-state 34,
				$(gold-lalr-action 7,1,40),# Shift to State 40
				$(gold-lalr-action 12,1,41),# Shift to State 41
				$(gold-lalr-action 33,3,42),# Go to State 42
				$(gold-lalr-action 35,3,43)# Go to State 43
			),# Total 4 action(s).
			$(gold-lalr-state 35,
				$(gold-lalr-action 8,2,24),# Reduce Production 24
				$(gold-lalr-action 10,2,24),# Reduce Production 24
				$(gold-lalr-action 17,2,24)# Reduce Production 24
			),# Total 3 action(s).
			$(gold-lalr-state 36,
				$(gold-lalr-action 10,1,33),# Shift to State 33
				$(gold-lalr-action 17,1,34),# Shift to State 34
				$(gold-lalr-action 20,3,35),# Go to State 35
				$(gold-lalr-action 24,3,36),# Go to State 36
				$(gold-lalr-action 25,3,44),# Go to State 44
				$(gold-lalr-action 34,3,38),# Go to State 38
				$(gold-lalr-action 8,2,22)# Reduce Production 22
			),# Total 7 action(s).
			$(gold-lalr-state 37,
				$(gold-lalr-action 8,1,45)# Shift to State 45
			),# Total 1 action(s).
			$(gold-lalr-state 38,
				$(gold-lalr-action 8,2,23),# Reduce Production 23
				$(gold-lalr-action 10,2,23),# Reduce Production 23
				$(gold-lalr-action 17,2,23)# Reduce Production 23
			),# Total 3 action(s).
			$(gold-lalr-state 39,
				$(gold-lalr-action 7,2,19)# Reduce Production 19
			),# Total 1 action(s).
			$(gold-lalr-state 40,
				$(gold-lalr-action 12,1,41),# Shift to State 41
				$(gold-lalr-action 35,3,46),# Go to State 46
				$(gold-lalr-action 36,3,47),# Go to State 47
				$(gold-lalr-action 8,2,29)# Reduce Production 29
			),# Total 4 action(s).
			$(gold-lalr-state 41,
				$(gold-lalr-action 19,1,48)# Shift to State 48
			),# Total 1 action(s).
			$(gold-lalr-state 42,
				$(gold-lalr-action 8,2,25),# Reduce Production 25
				$(gold-lalr-action 10,2,25),# Reduce Production 25
				$(gold-lalr-action 17,2,25)# Reduce Production 25
			),# Total 3 action(s).
			$(gold-lalr-state 43,
				$(gold-lalr-action 8,2,27),# Reduce Production 27
				$(gold-lalr-action 10,2,27),# Reduce Production 27
				$(gold-lalr-action 17,2,27)# Reduce Production 27
			),# Total 3 action(s).
			$(gold-lalr-state 44,
				$(gold-lalr-action 8,2,21)# Reduce Production 21
			),# Total 1 action(s).
			$(gold-lalr-state 45,
				$(gold-lalr-action 0,2,12),# Reduce Production 12
				$(gold-lalr-action 9,2,12),# Reduce Production 12
				$(gold-lalr-action 15,2,12),# Reduce Production 12
				$(gold-lalr-action 18,2,12)# Reduce Production 12
			),# Total 4 action(s).
			$(gold-lalr-state 46,
				$(gold-lalr-action 12,1,41),# Shift to State 41
				$(gold-lalr-action 35,3,46),# Go to State 46
				$(gold-lalr-action 36,3,49),# Go to State 49
				$(gold-lalr-action 8,2,29)# Reduce Production 29
			),# Total 4 action(s).
			$(gold-lalr-state 47,
				$(gold-lalr-action 8,1,50)# Shift to State 50
			),# Total 1 action(s).
			$(gold-lalr-state 48,
				$(gold-lalr-action 6,1,51)# Shift to State 51
			),# Total 1 action(s).
			$(gold-lalr-state 49,
				$(gold-lalr-action 8,2,28)# Reduce Production 28
			),# Total 1 action(s).
			$(gold-lalr-state 50,
				$(gold-lalr-action 8,2,26),# Reduce Production 26
				$(gold-lalr-action 10,2,26),# Reduce Production 26
				$(gold-lalr-action 17,2,26)# Reduce Production 26
			),# Total 3 action(s).
			$(gold-lalr-state 51,
				$(gold-lalr-action 8,2,30),# Reduce Production 30
				$(gold-lalr-action 10,2,30),# Reduce Production 30
				$(gold-lalr-action 12,2,30),# Reduce Production 30
				$(gold-lalr-action 17,2,30)# Reduce Production 30
			)# Total 4 action(s).
		)# Total 52 state(s).

	)
endef # __gold_$(gold_prefix)_parse

$(def_all)


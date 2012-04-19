# Generated by Xpand using M2Make template.

# Model of 'myFile' package.

ifndef __mybuild_myfile_model_mk
__mybuild_myfile_model_mk := 1

include mk/model/model_impl.mk

#
# Model object 'FileContentRoot'.
#
# The following features are defined:
#   - reference 'types'
#   - attribute 'imports'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyFileContentRoot
	# Extends 'ENamedObject' class.
	$(eobject MyFile_FileContentRoot,
		MyFileContentRoot,ENamedObject,)

	# Property 'types... : MyType'.
	$(eobject-reference MyFile_FileContentRoot_types,
		types,MyType,fileContentRoot,changeable many containment)

	# Property 'imports...'.
	$(eobject-attribute MyFile_FileContentRoot_imports,
		imports,changeable many)

	# PROTECTED REGION ID(MyFile_FileContentRoot) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'Type'.
#
# The following features are defined:
#   - reference 'fileContentRoot'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyType # abstract
	# Extends 'ENamedObject', 'MyAnnotationTarget' classes.
	$(eobject MyFile_Type,
		MyType,ENamedObject MyAnnotationTarget,abstract)

	# Property 'fileContentRoot : MyFileContentRoot'.
	$(eobject-reference MyFile_Type_fileContentRoot,
		fileContentRoot,MyFileContentRoot,types,changeable container)

	# PROTECTED REGION ID(MyFile_Type) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'AnnotationType'.
#
# The following features are defined:
#   - reference 'options'
#
# The following features are inherited from 'Type':
#   - reference 'fileContentRoot'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyAnnotationType
	# Extends 'MyType' class.
	$(eobject MyFile_AnnotationType,
		MyAnnotationType,MyType,)

	# Property 'options... : MyOption'.
	$(eobject-reference MyFile_AnnotationType_options,
		options,MyOption,,changeable many containment)

	# PROTECTED REGION ID(MyFile_AnnotationType) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'Annotation'.
#
# The following features are defined:
#   - reference 'type'
#   - reference 'target'
#   - reference 'bindings'
#
define class-MyAnnotation
	# Extends 'EObject' class (implicitly).
	$(eobject MyFile_Annotation,
		MyAnnotation,,)

	# Property 'type : MyAnnotationType'.
	# Property 'type_link : ELink'.
	$(eobject-reference MyFile_Annotation_type,
		type,MyAnnotationType,,changeable linkable)

	# Property 'target : MyAnnotationTarget'.
	$(eobject-reference MyFile_Annotation_target,
		target,MyAnnotationTarget,annotations,changeable container)

	# Property 'bindings... : MyOptionBinding'.
	$(eobject-reference MyFile_Annotation_bindings,
		bindings,MyOptionBinding,,changeable many containment)

	# PROTECTED REGION ID(MyFile_Annotation) ENABLED START
	$(property qualifiedName)

	$(getter qualifiedName,
		$(get $(get type).qualifiedName))
	# PROTECTED REGION END
endef

#
# Model object 'AnnotationTarget'.
#
# The following features are defined:
#   - reference 'annotations'
#
define class-MyAnnotationTarget # abstract
	# Extends 'EObject' class (implicitly).
	$(eobject MyFile_AnnotationTarget,
		MyAnnotationTarget,,abstract)

	# Property 'annotations... : MyAnnotation'.
	$(eobject-reference MyFile_AnnotationTarget_annotations,
		annotations,MyAnnotation,target,changeable many containment)

	# PROTECTED REGION ID(MyFile_AnnotationTarget) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'Interface'.
#
# The following features are defined:
#   - reference 'features'
#
# The following features are inherited from 'Type':
#   - reference 'fileContentRoot'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyInterface
	# Extends 'MyType' class.
	$(eobject MyFile_Interface,
		MyInterface,MyType,)

	# Property 'features... : MyFeature'.
	$(eobject-reference MyFile_Interface_features,
		features,MyFeature,interface,changeable many containment)

	# PROTECTED REGION ID(MyFile_Interface) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'Feature'.
#
# The following features are defined:
#   - reference 'interface'
#   - reference 'providedBy'
#   - reference 'requiredBy'
#   - reference 'superFeatures'
#   - reference 'subFeatures'
#   - reference 'allSuperFeatures'
#   - reference 'allSubFeatures'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyFeature
	# Extends 'ENamedObject' class.
	$(eobject MyFile_Feature,
		MyFeature,ENamedObject,)

	# Property 'interface : MyInterface'.
	$(eobject-reference MyFile_Feature_interface,
		interface,MyInterface,features,changeable container)

	# Property 'providedBy... : MyModuleType'.
	# Property 'providedBy_links... : ELink'.
	$(eobject-reference MyFile_Feature_providedBy,
		providedBy,MyModuleType,provides,changeable many linkable)

	# Property 'requiredBy... : MyModuleType'.
	# Property 'requiredBy_links... : ELink'.
	$(eobject-reference MyFile_Feature_requiredBy,
		requiredBy,MyModuleType,requires,changeable many linkable)

	# Property 'superFeatures... : MyFeature'.
	# Property 'superFeatures_links... : ELink'.
	$(eobject-reference MyFile_Feature_superFeatures,
		superFeatures,MyFeature,subFeatures,changeable many linkable)

	# Property 'subFeatures... : MyFeature'.
	# Property 'subFeatures_links... : ELink'.
	$(eobject-reference MyFile_Feature_subFeatures,
		subFeatures,MyFeature,superFeatures,changeable many linkable)

	# Reference 'allSuperFeatures' [0..*]: bidirectional, derived.
	$(property allSuperFeatures... : MyFeature)
	# PROTECTED REGION ID(MyFile_Feature_allSuperFeatures) ENABLED START
	$(getter allSuperFeatures,
		$(for super <- $(get superFeatures),
			$(super) $(get super->allSuperFeatures)))
				
	$(setter allSuperFeatures,
		$(error $0($1): NIY))
	# PROTECTED REGION END

	# Reference 'allSubFeatures' [0..*]: bidirectional, derived.
	$(property allSubFeatures... : MyFeature)
	# PROTECTED REGION ID(MyFile_Feature_allSubFeatures) ENABLED START
	$(getter allSubFeatures,
		$(for sub <- $(get subFeatures),
			$(sub) $(get sub->allSubFeatures)))
				
	$(setter allSubFeatures,
		$(error $0($1): NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(MyFile_Feature) ENABLED START
	# PROTECTED REGION END
endef

#
# Model object 'ModuleType'.
#
# The following features and operations are defined:
#   - attribute 'modifiers'
#   - attribute 'static'
#   - attribute 'abstract'
#   - reference 'depends'
#   - reference 'dependsMembers'
#   - reference 'dependent'
#   - reference 'provides'
#   - reference 'providesMembers'
#   - reference 'requires'
#   - reference 'requiresMembers'
#   - reference 'sources'
#   - reference 'sourcesMembers'
#   - reference 'objects'
#   - reference 'objectsMembers'
#   - reference 'options'
#   - reference 'optionsMembers'
#   - reference 'allOptions'
#   - reference 'subTypes'
#   - reference 'superType'
#   - reference 'allSubTypes'
#   - reference 'allSuperTypes'
#   - operation 'isSubTypeOf'
#   - operation 'isSuperTypeOf'
#
# The following features are inherited from 'Type':
#   - reference 'fileContentRoot'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyModuleType
	# Extends 'MyType' class.
	$(eobject MyFile_ModuleType,
		MyModuleType,MyType,)

	# Property 'modifiers'.
	$(eobject-attribute MyFile_ModuleType_modifiers,
		modifiers,changeable)

	# Attribute 'static': derived.
	$(property isStatic)
	# PROTECTED REGION ID(MyFile_ModuleType_isStatic) ENABLED START
	$(getter isStatic,
		$(filter static,$(get-field modifiers)))
	$(setter isStatic,
		$(if $1,$(set+ modifiers,static),$(set- modifiers,static)))
	# PROTECTED REGION END

	# Attribute 'abstract': derived.
	$(property isAbstract)
	# PROTECTED REGION ID(MyFile_ModuleType_isAbstract) ENABLED START
	$(getter isAbstract,
		$(filter abstract,$(get-field modifiers)))
	$(setter isAbstract,
		$(if $1,$(set+ modifiers,abstract),$(set- modifiers,abstract)))
	# PROTECTED REGION END

	# Reference 'depends' [0..*]: bidirectional, derived.
	$(property depends... : MyModuleType)
	# PROTECTED REGION ID(MyFile_ModuleType_depends) ENABLED START
	$(getter depends,
		$(invoke getMembers,depends,modules))
#	# TODO Uncomment and implement me.
	$(setter depends,
		$(error $0($1): NIY))
	# PROTECTED REGION END

	# Property 'dependsMembers... : MyDependsMember'.
	$(eobject-reference MyFile_ModuleType_dependsMembers,
		dependsMembers,MyDependsMember,,changeable many containment)

	# Property 'dependent... : MyModuleType'.
	# Property 'dependent_links... : ELink'.
	$(eobject-reference MyFile_ModuleType_dependent,
		dependent,MyModuleType,depends,changeable many linkable)

	# Reference 'provides' [0..*]: bidirectional, derived.
	$(property provides... : MyFeature)
	# PROTECTED REGION ID(MyFile_ModuleType_provides) ENABLED START
	$(getter provides,
		$(invoke getMembers,provides,features))
#	# TODO Uncomment and implement me.
	$(setter provides,
		$(error $0($1): NIY))
	# PROTECTED REGION END

	# Property 'providesMembers... : MyProvidesMember'.
	$(eobject-reference MyFile_ModuleType_providesMembers,
		providesMembers,MyProvidesMember,,changeable many containment)

	# Reference 'requires' [0..*]: bidirectional, derived.
	$(property requires... : MyFeature)
	# PROTECTED REGION ID(MyFile_ModuleType_requires) ENABLED START
	$(getter requires,
		$(invoke getMembers,requires,features))
#	# TODO Uncomment and implement me.
	$(setter requires,
		$(error $0($1): NIY))
	# PROTECTED REGION END

	# Property 'requiresMembers... : MyRequiresMember'.
	$(eobject-reference MyFile_ModuleType_requiresMembers,
		requiresMembers,MyRequiresMember,,changeable many containment)

	# Reference 'sources' [0..*]: containment, derived.
	$(property sources... : MyFileName)
	# PROTECTED REGION ID(MyFile_ModuleType_sources) ENABLED START
	$(getter sources,
		$(invoke getMembers,sources,files))
#	# TODO Uncomment and implement me.
	$(setter sources,
		$(error $0($1): NIY))
	# PROTECTED REGION END

	# Property 'sourcesMembers... : MySourceMember'.
	$(eobject-reference MyFile_ModuleType_sourcesMembers,
		sourcesMembers,MySourceMember,,changeable many containment)

	# Reference 'objects' [0..*]: containment, derived.
	$(property objects... : MyFileName)
	# PROTECTED REGION ID(MyFile_ModuleType_objects) ENABLED START
	$(getter objects,
		$(invoke getMembers,objects,files))
#	# TODO Uncomment and implement me.
	$(setter objects,
		$(error $0($1): NIY))
	# PROTECTED REGION END

	# Property 'objectsMembers... : MySourceMember'.
	$(eobject-reference MyFile_ModuleType_objectsMembers,
		objectsMembers,MySourceMember,,changeable many containment)

	# Reference 'options' [0..*]: containment, derived.
	$(property options... : MyOption)
	# PROTECTED REGION ID(MyFile_ModuleType_options) ENABLED START
#	# TODO Uncomment and implement me.
	$(getter options,
		$(invoke getMembers,options,options))
#	# TODO Uncomment and implement me.
	$(setter options,
		$(error $0($1): NIY))
	# PROTECTED REGION END

	# Property 'optionsMembers... : MyOptionMember'.
	$(eobject-reference MyFile_ModuleType_optionsMembers,
		optionsMembers,MyOptionMember,,changeable many containment)

	# Reference 'allOptions' [0..1]: derived.
	$(property allOptions : MyOption)
	# PROTECTED REGION ID(MyFile_ModuleType_allOptions) ENABLED START
	$(getter allOptions,
		$(with $(for opt <- $(get options),
				$(get opt->name)),
			$(get options)\
			$(for super <- $(get superType),
				superOpt <- $(get super->allOptions),
				$(if $(filter $1,$(get superOpt->name)),,
			       		$(superOpt)))))


	$(setter allOptions,
		$(error $0($1): NIY))
	# PROTECTED REGION END

	# Property 'subTypes... : MyModuleType'.
	# Property 'subTypes_links... : ELink'.
	$(eobject-reference MyFile_ModuleType_subTypes,
		subTypes,MyModuleType,superType,changeable many linkable)

	# Property 'superType : MyModuleType'.
	# Property 'superType_link : ELink'.
	$(eobject-reference MyFile_ModuleType_superType,
		superType,MyModuleType,subTypes,changeable linkable)

	# Reference 'allSubTypes' [0..*]: bidirectional, derived, read-only.
	$(property allSubTypes... : MyModuleType)
	# PROTECTED REGION ID(MyFile_ModuleType_allSubTypes) ENABLED START
	$(getter allSubTypes,
		$(for subType <- $(get subTypes),	
			$(subType)\
			$(get subType->allSubTypes)))
	# PROTECTED REGION END

	# Reference 'allSuperTypes' [0..*]: bidirectional, derived, read-only.
	$(property allSuperTypes... : MyModuleType)
	# PROTECTED REGION ID(MyFile_ModuleType_allSuperTypes) ENABLED START
	$(getter allSuperTypes,
		$(get superType) $(foreach s,$(get superType),$(get s->allSuperTypes)))
	# PROTECTED REGION END

	# Method 'isSubTypeOf'.
	#   1. another : MyModuleType
	# PROTECTED REGION ID(MyFile_ModuleType_isSubTypeOf) ENABLED START
	# TODO Uncomment and implement me.
	$(method isSubTypeOf,
		$(filter $1,$(get allSuperTypes)))
	# PROTECTED REGION END

	# Method 'isSuperTypeOf'.
	#   1. another : MyModuleType
	# PROTECTED REGION ID(MyFile_ModuleType_isSuperTypeOf) ENABLED START
#	# TODO Uncomment and implement me.
	$(method isSuperTypeOf,
		$(error $0($1): NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(MyFile_ModuleType) ENABLED START
	$(setter modifiers,
		$(set-field modifiers,$(sort $1)))
		
	# Set members with type
	#  1. Type name
	#  2. Member object 
	#$(method setMembers,
		#$(set-field members,$1.$2))

	# Get members content (with type)
	#  1. Type name
	#  2. Content name
	$(method getMembers,
		$(for member <- $(get $1Members),
			$(get member->$2)))
	# PROTECTED REGION END
endef

#
# Model object 'Option'.
#
# The following features and operations are defined:
#   - reference 'defaultValue'
#   - operation 'validateValue'
#   - operation 'getId'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyOption # abstract
	# Extends 'ENamedObject', 'MyAnnotationTarget' classes.
	$(eobject MyFile_Option,
		MyOption,ENamedObject MyAnnotationTarget,abstract)

	# Property 'defaultValue : MyOptionValue'.
	$(eobject-reference MyFile_Option_defaultValue,
		defaultValue,MyOptionValue,,changeable containment)

	# Method 'validateValue'.
	# PROTECTED REGION ID(MyFile_Option_validateValue) ENABLED START
#	# TODO Uncomment and implement me.
	$(method validateValue,
		$(error $0(): NIY))
	# PROTECTED REGION END

	# Method 'getId'.
	# PROTECTED REGION ID(MyFile_Option_getId) ENABLED START
	$(method getId,
		$(error $0(): Must not be called on absract class))
	# PROTECTED REGION END

	# PROTECTED REGION ID(MyFile_Option) ENABLED START
	
	# Args:
	#   1. Option type in upcase
	$(method __getId,
		OPTION_$1_$(subst .,__,$(get qualifiedName)))
	# PROTECTED REGION END
endef

#
# Model object 'StringOption'.
#
# The following operations are defined:
#   - operation 'validateValue'
#
# The following features and operations are inherited from 'Option':
#   - reference 'defaultValue'
#   - operation 'validateValue'
#   - operation 'getId'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyStringOption
	# Extends 'MyOption' class.
	$(eobject MyFile_StringOption,
		MyStringOption,MyOption,)

	# Method 'validateValue'.
	# PROTECTED REGION ID(MyFile_StringOption_validateValue) ENABLED START
#	# TODO Uncomment and implement me.
	$(method validateValue,
		$(invoke MyFile_StringOptionValue->isInstance,$1))
	# PROTECTED REGION END

	# PROTECTED REGION ID(MyFile_StringOption) ENABLED START
	$(method getId,
		$(invoke __getId,STRING))
	# PROTECTED REGION END
endef

#
# Model object 'NumberOption'.
#
# The following operations are defined:
#   - operation 'validateValue'
#
# The following features and operations are inherited from 'Option':
#   - reference 'defaultValue'
#   - operation 'validateValue'
#   - operation 'getId'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyNumberOption
	# Extends 'MyOption' class.
	$(eobject MyFile_NumberOption,
		MyNumberOption,MyOption,)

	# Method 'validateValue'.
	# PROTECTED REGION ID(MyFile_NumberOption_validateValue) ENABLED START
#	# TODO Uncomment and implement me.
	$(method validateValue,
		$(invoke MyFile_NumberOptionValue->isInstance,$1))
	# PROTECTED REGION END

	# PROTECTED REGION ID(MyFile_NumberOption) ENABLED START
	$(method getId,
		$(invoke __getId,NUMBER))
	# PROTECTED REGION END
endef

#
# Model object 'BooleanOption'.
#
# The following operations are defined:
#   - operation 'validateValue'
#
# The following features and operations are inherited from 'Option':
#   - reference 'defaultValue'
#   - operation 'validateValue'
#   - operation 'getId'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyBooleanOption
	# Extends 'MyOption' class.
	$(eobject MyFile_BooleanOption,
		MyBooleanOption,MyOption,)

	# Method 'validateValue'.
	# PROTECTED REGION ID(MyFile_BooleanOption_validateValue) ENABLED START
#	# TODO Uncomment and implement me.
	$(method validateValue,
		$(invoke MyFile_BooleanOptionValue->isInstance,$1))
	# PROTECTED REGION END

	# PROTECTED REGION ID(MyFile_BooleanOption) ENABLED START
	$(method getId,
		$(invoke __getId,BOOLEAN))
	# PROTECTED REGION END
endef

#
# Model object 'TypeReferenceOption'.
#
# The following features and operations are defined:
#   - reference 'type'
#   - operation 'validateValue'
#
# The following features and operations are inherited from 'Option':
#   - reference 'defaultValue'
#   - operation 'validateValue'
#   - operation 'getId'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-MyTypeReferenceOption
	# Extends 'MyOption' class.
	$(eobject MyFile_TypeReferenceOption,
		MyTypeReferenceOption,MyOption,)

	# Property 'type : MyType'.
	# Property 'type_link : ELink'.
	$(eobject-reference MyFile_TypeReferenceOption_type,
		type,MyType,,changeable linkable)

	# Method 'validateValue'.
	# PROTECTED REGION ID(MyFile_TypeReferenceOption_validateValue) ENABLED START
#	# TODO Uncomment and implement me.
	$(method validateValue,
		$(error $0(): NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(MyFile_TypeReferenceOption) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'OptionValue'.
#
# The following operations are defined:
#   - operation 'toString'
#
define class-MyOptionValue # abstract
	# Extends 'EObject' class (implicitly).
	$(eobject MyFile_OptionValue,
		MyOptionValue,,abstract)

	# Method 'toString'.
	# PROTECTED REGION ID(MyFile_OptionValue_toString) ENABLED START
#	# TODO Uncomment and implement me.
	$(method toString,
		$(error $0(): NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(MyFile_OptionValue) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'StringOptionValue'.
#
# The following features are defined:
#   - attribute 'value'
#
# The following operations are inherited from 'OptionValue':
#   - operation 'toString'
#
define class-MyStringOptionValue
	# Extends 'MyOptionValue' class.
	$(eobject MyFile_StringOptionValue,
		MyStringOptionValue,MyOptionValue,)

	# Property 'value'.
	$(eobject-attribute MyFile_StringOptionValue_value,
		value,changeable)

	# PROTECTED REGION ID(MyFile_StringOptionValue) ENABLED START
	$(method toString,
		$(get value))

	$(if $(value 1),
		$(set value,$1))	
	# PROTECTED REGION END
endef

#
# Model object 'NumberOptionValue'.
#
# The following features are defined:
#   - attribute 'value'
#
# The following operations are inherited from 'OptionValue':
#   - operation 'toString'
#
define class-MyNumberOptionValue
	# Extends 'MyOptionValue' class.
	$(eobject MyFile_NumberOptionValue,
		MyNumberOptionValue,MyOptionValue,)

	# Property 'value'.
	$(eobject-attribute MyFile_NumberOptionValue_value,
		value,changeable)

	# PROTECTED REGION ID(MyFile_NumberOptionValue) ENABLED START
	$(method toString,
		$(get-field value))

	$(if $(value 1),
		$(set-field value,$1))	
	# PROTECTED REGION END
endef

#
# Model object 'BooleanOptionValue'.
#
# The following features are defined:
#   - attribute 'value'
#
# The following operations are inherited from 'OptionValue':
#   - operation 'toString'
#
define class-MyBooleanOptionValue
	# Extends 'MyOptionValue' class.
	$(eobject MyFile_BooleanOptionValue,
		MyBooleanOptionValue,MyOptionValue,)

	# Property 'isValue'.
	$(eobject-attribute MyFile_BooleanOptionValue_isValue,
		isValue,changeable)

	# PROTECTED REGION ID(MyFile_BooleanOptionValue) ENABLED START
	$(method toString,
		$(if $(get-field value),
			1,
			0))

	$(if $(value 1),
		$(set value,$1))	
	# PROTECTED REGION END
endef

#
# Model object 'TypeReferenceOptionValue'.
#
# The following features are defined:
#   - reference 'value'
#
# The following operations are inherited from 'OptionValue':
#   - operation 'toString'
#
define class-MyTypeReferenceOptionValue
	# Extends 'MyOptionValue' class.
	$(eobject MyFile_TypeReferenceOptionValue,
		MyTypeReferenceOptionValue,MyOptionValue,)

	# Property 'value : MyType'.
	# Property 'value_link : ELink'.
	$(eobject-reference MyFile_TypeReferenceOptionValue_value,
		value,MyType,,changeable linkable)

	# PROTECTED REGION ID(MyFile_TypeReferenceOptionValue) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'OptionBinding'.
#
# The following features are defined:
#   - reference 'option'
#   - reference 'optionValue'
#
define class-MyOptionBinding
	# Extends 'EObject' class (implicitly).
	$(eobject MyFile_OptionBinding,
		MyOptionBinding,,)

	# Property 'option : MyOption'.
	# Property 'option_link : ELink'.
	$(eobject-reference MyFile_OptionBinding_option,
		option,MyOption,,changeable linkable)

	# Property 'optionValue : MyOptionValue'.
	$(eobject-reference MyFile_OptionBinding_optionValue,
		optionValue,MyOptionValue,,changeable containment)

	# PROTECTED REGION ID(MyFile_OptionBinding) ENABLED START
	$(method setOptionValue,
		$(for opt <- $(get option),
			$(if $(invoke opt->validate,$1),
				$(set-field optionValue,$1))))
	# PROTECTED REGION END
endef

#
# Model object 'Member'.
#
# The following features are defined:
#   - reference 'module'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
define class-MyMember
	# Extends 'MyAnnotationTarget' class.
	$(eobject MyFile_Member,
		MyMember,MyAnnotationTarget,)

	# Property 'module : MyModuleType'.
	# Property 'module_link : ELink'.
	$(eobject-reference MyFile_Member_module,
		module,MyModuleType,,changeable linkable)

	# PROTECTED REGION ID(MyFile_Member) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'FileName'.
#
# The following features are defined:
#   - attribute 'fileName'
#   - attribute 'fileFullName'
#
define class-MyFileName
	# Extends 'EObject' class (implicitly).
	$(eobject MyFile_FileName,
		MyFileName,,)

	# Property 'fileName'.
	$(eobject-attribute MyFile_FileName_fileName,
		fileName,changeable)

	# Attribute 'fileFullName': derived, read-only.
	$(property fileFullName)
	# PROTECTED REGION ID(MyFile_FileName_fileFullName) ENABLED START
	$(getter fileFullName,
		$(dir $(get $(get eResource).fileName))$(get fileName))

	# PROTECTED REGION END

	# PROTECTED REGION ID(MyFile_FileName) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'DependsMember'.
#
# The following features are defined:
#   - reference 'modules'
#
# The following features are inherited from 'Member':
#   - reference 'module'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
define class-MyDependsMember
	# Extends 'MyMember' class.
	$(eobject MyFile_DependsMember,
		MyDependsMember,MyMember,)

	# Property 'modules... : MyModuleType'.
	# Property 'modules_links... : ELink'.
	$(eobject-reference MyFile_DependsMember_modules,
		modules,MyModuleType,,changeable many linkable)

	# PROTECTED REGION ID(MyFile_DependsMember) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'RequiresMember'.
#
# The following features are defined:
#   - reference 'features'
#
# The following features are inherited from 'Member':
#   - reference 'module'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
define class-MyRequiresMember
	# Extends 'MyMember' class.
	$(eobject MyFile_RequiresMember,
		MyRequiresMember,MyMember,)

	# Property 'features... : MyFeature'.
	# Property 'features_links... : ELink'.
	$(eobject-reference MyFile_RequiresMember_features,
		features,MyFeature,,changeable many linkable)

	# PROTECTED REGION ID(MyFile_RequiresMember) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'ProvidesMember'.
#
# The following features are defined:
#   - reference 'features'
#
# The following features are inherited from 'Member':
#   - reference 'module'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
define class-MyProvidesMember
	# Extends 'MyMember' class.
	$(eobject MyFile_ProvidesMember,
		MyProvidesMember,MyMember,)

	# Property 'features... : MyFeature'.
	# Property 'features_links... : ELink'.
	$(eobject-reference MyFile_ProvidesMember_features,
		features,MyFeature,,changeable many linkable)

	# PROTECTED REGION ID(MyFile_ProvidesMember) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'SourceMember'.
#
# The following features are defined:
#   - reference 'files'
#
# The following features are inherited from 'Member':
#   - reference 'module'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
define class-MySourceMember
	# Extends 'MyMember' class.
	$(eobject MyFile_SourceMember,
		MySourceMember,MyMember,)

	# Property 'files... : MyFileName'.
	$(eobject-reference MyFile_SourceMember_files,
		files,MyFileName,,changeable many containment)

	# PROTECTED REGION ID(MyFile_SourceMember) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'ObjectMember'.
#
# The following features are defined:
#   - reference 'files'
#
# The following features are inherited from 'Member':
#   - reference 'module'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
define class-MyObjectMember
	# Extends 'MyMember' class.
	$(eobject MyFile_ObjectMember,
		MyObjectMember,MyMember,)

	# Property 'files... : MyFileName'.
	$(eobject-reference MyFile_ObjectMember_files,
		files,MyFileName,,changeable many containment)

	# PROTECTED REGION ID(MyFile_ObjectMember) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'OptionMember'.
#
# The following features are defined:
#   - reference 'options'
#
# The following features are inherited from 'Member':
#   - reference 'module'
#
# The following features are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#
define class-MyOptionMember
	# Extends 'MyMember' class.
	$(eobject MyFile_OptionMember,
		MyOptionMember,MyMember,)

	# Property 'options... : MyOption'.
	$(eobject-reference MyFile_OptionMember_options,
		options,MyOption,,changeable many containment)

	# PROTECTED REGION ID(MyFile_OptionMember) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# PROTECTED REGION ID(MyFile) ENABLED START
# TODO Add custom implementation here and remove this comment.
# PROTECTED REGION END

$(def_all)

endif # __mybuild_myfile_model_mk


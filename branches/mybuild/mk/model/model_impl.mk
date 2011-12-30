# Generated by Xpand using M2Make template.

# Model implementation of 'EModel' package.

ifndef __model_model_impl_mk
__model_model_impl_mk := $(lastword $(MAKEFILE_LIST))

# Base class for all modelled objects of this package.
define class-EModelNodeImpl
	$(super ENodeImpl)

	# Returns a reference to 'EModel' meta model.
	$(getter eMetaModel,
		$(eModelMetaModel))

endef

# Implementation of 'ENode' model object .
define class-ENodeImpl
	$(super ENode)

	$(super EModelNodeImpl)

	$(getter eMetaClass,$(get eModelMetaModel->ENode))

	# Reference 'eMetaClass' [0..1]: volatile, read-only.
	$(property eMetaClass : EMetaClass)
	# PROTECTED REGION ID(ENode_eMetaClass) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eMetaClass,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Attribute 'eResource': volatile, read-only.
	$(property eResource : EResource)
	# PROTECTED REGION ID(ENode_eResource) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eResource,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eContainer' [0..1]: volatile, read-only.
	$(property eContainer : ENode)
	# PROTECTED REGION ID(ENode_eContainer) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eContainer,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eRootContainer' [0..1]: volatile, read-only.
	$(property eRootContainer : ENode)
	# PROTECTED REGION ID(ENode_eRootContainer) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eRootContainer,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eContents' [0..*]: bidirectional, volatile, read-only.
	$(property eContents... : ENode)
	# PROTECTED REGION ID(ENode_eContents) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eContents,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eAllContents' [0..*]: bidirectional, volatile, read-only.
	$(property eAllContents... : ENode)
	# PROTECTED REGION ID(ENode_eAllContents) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eAllContents,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(ENode) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'ELink' model object .
define class-ELinkImpl
	$(super ELink)

	$(super EModelNodeImpl)
	$(super ENamedImpl)

	$(getter eMetaClass,$(get eModelMetaModel->ELink))

	# Reference 'eMetaReference' [0..1].
	$(property eMetaReference : EMetaReference)
	$(field eMetaReference : EMetaReference)
	$(getter eMetaReference,
		$(get-field eMetaReference))
	$(setter eMetaReference,
		$(invoke doSetReference,$(get eModelMetaModel->ELink_eMetaReference),$1))

	# PROTECTED REGION ID(ELink) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'EMetaType' model object .
define class-EMetaTypeImpl
	$(super EMetaType)

	$(super EModelNodeImpl)
	$(super ENamedImpl)

	$(getter eMetaClass,$(get eModelMetaModel->EMetaType))

	# Attribute 'instanceClass'.
	$(property-field instanceClass : EString)

	# Reference 'eMetaModel' [0..1]: bidirectional, container, read-only.
	$(property eMetaModel : EMetaModel)
	$(getter eMetaModel,
		$(invoke doGetContainerReference,$(get eModelMetaModel->EMetaType_eMetaModel)))

	# 'isInstance : EBoolean' operation.
	#   1. object : ENode
	# PROTECTED REGION ID(EMetaType_isInstance) ENABLED START
#	# TODO Uncomment and implement me.
#	$(method isInstance,
#		$(error $0($1): NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(EMetaType) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'EMetaClass' model object .
define class-EMetaClassImpl
	$(super EMetaClass)

	$(super EModelNodeImpl)
	$(super EMetaTypeImpl)

	$(getter eMetaClass,$(get eModelMetaModel->EMetaClass))

	# Attribute 'abstract'.
	$(property-field isAbstract : EBoolean)

	# Attribute 'interface'.
	$(property-field isInterface : EBoolean)

	# Reference 'eSuperTypes' [0..*].
	$(property eSuperTypes... : EMetaClass)
	$(field eSuperTypes... : EMetaClass)
	$(getter eSuperTypes,
		$(get-field eSuperTypes))
	$(setter eSuperTypes,
		$(invoke doSetReference,$(get eModelMetaModel->EMetaClass_eSuperTypes),$1))
	$(setter+ eSuperTypes,
		$(invoke doAddReference,$(get eModelMetaModel->EMetaClass_eSuperTypes),$1))
	$(setter- eSuperTypes,
		$(invoke doRemoveReference,$(get eModelMetaModel->EMetaClass_eSuperTypes),$1))

	# Reference 'eAllSuperTypes' [0..*]: volatile, read-only.
	$(property eAllSuperTypes... : EMetaClass)
	# PROTECTED REGION ID(EMetaClass_eAllSuperTypes) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eAllSuperTypes,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eFeatures' [0..*]: bidirectional, containment.
	$(property eFeatures... : EMetaFeature)
	$(field eFeatures... : EMetaFeature)
	$(getter eFeatures,
		$(get-field eFeatures))
	$(setter eFeatures,
		$(invoke doSetReference,$(get eModelMetaModel->EMetaClass_eFeatures),$1))
	$(setter+ eFeatures,
		$(invoke doAddReference,$(get eModelMetaModel->EMetaClass_eFeatures),$1))
	$(setter- eFeatures,
		$(invoke doRemoveReference,$(get eModelMetaModel->EMetaClass_eFeatures),$1))

	# Reference 'eAllFeatures' [0..*]: volatile, read-only.
	$(property eAllFeatures... : EMetaFeature)
	# PROTECTED REGION ID(EMetaClass_eAllFeatures) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eAllFeatures,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eAttributes' [0..*]: volatile, read-only.
	$(property eAttributes... : EMetaAttribute)
	# PROTECTED REGION ID(EMetaClass_eAttributes) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eAttributes,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eAllAttributes' [0..*]: volatile, read-only.
	$(property eAllAttributes... : EMetaAttribute)
	# PROTECTED REGION ID(EMetaClass_eAllAttributes) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eAllAttributes,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eReferences' [0..*]: volatile, read-only.
	$(property eReferences... : EMetaReference)
	# PROTECTED REGION ID(EMetaClass_eReferences) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eReferences,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eAllReferences' [0..*]: volatile, read-only.
	$(property eAllReferences... : EMetaReference)
	# PROTECTED REGION ID(EMetaClass_eAllReferences) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eAllReferences,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eAllContainments' [0..*]: volatile, read-only.
	$(property eAllContainments... : EMetaReference)
	# PROTECTED REGION ID(EMetaClass_eAllContainments) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eAllContainments,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# 'isSuperTypeOf : EBoolean' operation.
	#   1. someClass : EMetaClass
	# PROTECTED REGION ID(EMetaClass_isSuperTypeOf) ENABLED START
#	# TODO Uncomment and implement me.
#	$(method isSuperTypeOf,
#		$(error $0($1): NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(EMetaClass) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'EMetaPrimitive' model object .
define class-EMetaPrimitiveImpl
	$(super EMetaPrimitive)

	$(super EModelNodeImpl)
	$(super EMetaTypeImpl)

	$(getter eMetaClass,$(get eModelMetaModel->EMetaPrimitive))

	# PROTECTED REGION ID(EMetaPrimitive) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'EMetaFeature' model object .
define class-EMetaFeatureImpl
	$(super EMetaFeature)

	$(super EModelNodeImpl)
	$(super ETypedImpl)

	$(getter eMetaClass,$(get eModelMetaModel->EMetaFeature))

	# Attribute 'changeable'.
	$(property-field isChangeable : EBoolean)

	# Attribute 'volatile'.
	$(property-field isVolatile : EBoolean)

	# Attribute 'transient'.
	$(property-field isTransient : EBoolean)

	# Attribute 'derived'.
	$(property-field isDerived : EBoolean)

	# Attribute 'instanceProperty'.
	$(property-field instanceProperty : EString)

	# Reference 'eContainingClass' [0..1]: bidirectional, container, read-only.
	$(property eContainingClass : EMetaClass)
	$(getter eContainingClass,
		$(invoke doGetContainerReference,$(get eModelMetaModel->EMetaFeature_eContainingClass)))

	# PROTECTED REGION ID(EMetaFeature) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'EMetaReference' model object .
define class-EMetaReferenceImpl
	$(super EMetaReference)

	$(super EModelNodeImpl)
	$(super EMetaFeatureImpl)

	$(getter eMetaClass,$(get eModelMetaModel->EMetaReference))

	# Attribute 'containment'.
	$(property-field isContainment : EBoolean)

	# Attribute 'container': volatile, read-only.
	$(property isContainer : EBoolean)
	# PROTECTED REGION ID(EMetaReference_container) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter isContainer,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eOpposite' [0..1].
	$(property eOpposite : EMetaReference)
	$(field eOpposite : EMetaReference)
	$(getter eOpposite,
		$(get-field eOpposite))
	$(setter eOpposite,
		$(invoke doSetReference,$(get eModelMetaModel->EMetaReference_eOpposite),$1))

	# Reference 'eReferenceType' [1..1]: volatile, read-only.
	$(property eReferenceType : EMetaClass)
	# PROTECTED REGION ID(EMetaReference_eReferenceType) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eReferenceType,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(EMetaReference) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'EMetaAttribute' model object .
define class-EMetaAttributeImpl
	$(super EMetaAttribute)

	$(super EModelNodeImpl)
	$(super EMetaFeatureImpl)

	$(getter eMetaClass,$(get eModelMetaModel->EMetaAttribute))

	# Reference 'eAttributeType' [1..1]: volatile, read-only.
	$(property eAttributeType : EMetaPrimitive)
	# PROTECTED REGION ID(EMetaAttribute_eAttributeType) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eAttributeType,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(EMetaAttribute) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'EMetaModel' model object .
define class-EMetaModelImpl
	$(super EMetaModel)

	$(super EModelNodeImpl)
	$(super ENamedImpl)

	$(getter eMetaClass,$(get eModelMetaModel->EMetaModel))

	# Reference 'eFactory' [1..1]: bidirectional.
	$(property eFactory : EModelFactory)
	$(field eFactory : EModelFactory)
	$(getter eFactory,
		$(get-field eFactory))
	$(setter eFactory,
		$(invoke doSetReference,$(get eModelMetaModel->EMetaModel_eFactory),$1))

	# Reference 'eTypes' [0..*]: bidirectional, containment.
	$(property eTypes... : EMetaType)
	$(field eTypes... : EMetaType)
	$(getter eTypes,
		$(get-field eTypes))
	$(setter eTypes,
		$(invoke doSetReference,$(get eModelMetaModel->EMetaModel_eTypes),$1))
	$(setter+ eTypes,
		$(invoke doAddReference,$(get eModelMetaModel->EMetaModel_eTypes),$1))
	$(setter- eTypes,
		$(invoke doRemoveReference,$(get eModelMetaModel->EMetaModel_eTypes),$1))

	# PROTECTED REGION ID(EMetaModel) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'EModelFactory' model object .
define class-EModelFactoryImpl
	$(super EModelFactory)

	$(super EModelNodeImpl)

	$(getter eMetaClass,$(get eModelMetaModel->EModelFactory))

	# Reference 'eMetaModel' [1..1]: bidirectional.
	$(property eMetaModel : EMetaModel)
	$(field eMetaModel : EMetaModel)
	$(getter eMetaModel,
		$(get-field eMetaModel))
	$(setter eMetaModel,
		$(invoke doSetReference,$(get eModelMetaModel->EModelFactory_eMetaModel),$1))

	# PROTECTED REGION ID(EModelFactory) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'ENamed' model object .
define class-ENamedImpl
	$(super ENamed)

	$(super EModelNodeImpl)

	$(getter eMetaClass,$(get eModelMetaModel->ENamed))

	# Attribute 'name'.
	$(property-field name : EString)

	# PROTECTED REGION ID(ENamed) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'ETyped' model object .
define class-ETypedImpl
	$(super ETyped)

	$(super EModelNodeImpl)
	$(super ENamedImpl)

	$(getter eMetaClass,$(get eModelMetaModel->ETyped))

	# Attribute 'lowerBound'.
	$(property-field lowerBound : EInt)

	# Attribute 'upperBound'.
	$(property-field upperBound : EInt)

	# Reference 'eType' [0..1].
	$(property eType : EMetaType)
	$(field eType : EMetaType)
	$(getter eType,
		$(get-field eType))
	$(setter eType,
		$(invoke doSetReference,$(get eModelMetaModel->ETyped_eType),$1))

	# PROTECTED REGION ID(ETyped) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

$(def_all)

endif # __model_model_impl_mk


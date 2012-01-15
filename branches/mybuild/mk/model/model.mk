# Generated by Xpand using M2Make template.

# Model of 'EModel' package.

ifndef __model_model_mk
__model_model_mk := $(lastword $(MAKEFILE_LIST))


#
# Model object 'ENode'.
#
# The following features are available:
#   - reference 'eMetaClass'
#   - attribute 'eResource'
#   - reference 'eContainer'
#   - reference 'eRootContainer'
#   - reference 'eContents'
#   - reference 'eAllContents'
#   - reference 'eLinks'
#   - reference 'eResolvedLinks'
#   - reference 'eInverseResolvedLinks'
#   - reference 'eUnresolvedLinks'
#   - reference 'eRefs'
#   - reference 'eInverseRefs'
#   - reference 'eLinkedRefs'
#   - reference 'eInverseLinkedRefs'
#   - reference 'eImmediateRefs'
#   - reference 'eInverseImmediateRefs'
#
# To instantiate this class use 'EModelFactory.createENode'.
define class-ENode
#	$(super ENode)

	# 'eMetaClass' reference.
	$(property eMetaClass : EMetaClass)# read-only.

	# 'eResource' attribute.
	$(property eResource)# read-only.

	# 'eContainer' bidirectional reference.
	# The opposite reference is 'eContents'.
	$(property eContainer : ENode)# read-only.

	# 'eRootContainer' reference.
	$(property eRootContainer : ENode)# read-only.

	# 'eContents' bidirectional reference.
	# The opposite reference is 'eContainer'.
	$(property eContents... : ENode)# read-only.

	# 'eAllContents' reference.
	$(property eAllContents... : ENode)# read-only.

	# 'eLinks' bidirectional containment reference.
	# The opposite reference is 'ELink.eSource'.
	$(property eLinks... : ELink)# read-only.

	# 'eResolvedLinks' reference.
	$(property eResolvedLinks... : ELink)# read-only.

	# 'eInverseResolvedLinks' bidirectional reference.
	# The opposite reference is 'ELink.eDestination'.
	$(property eInverseResolvedLinks... : ELink)# read-only.

	# 'eUnresolvedLinks' reference.
	$(property eUnresolvedLinks... : ELink)# read-only.

	# 'eRefs' bidirectional reference.
	# The opposite reference is 'eInverseRefs'.
	$(property eRefs... : ENode)# read-only.

	# 'eInverseRefs' bidirectional reference.
	# The opposite reference is 'eRefs'.
	$(property eInverseRefs... : ENode)# read-only.

	# 'eLinkedRefs' bidirectional reference.
	# The opposite reference is 'eInverseLinkedRefs'.
	$(property eLinkedRefs... : ENode)# read-only.

	# 'eInverseLinkedRefs' bidirectional reference.
	# The opposite reference is 'eLinkedRefs'.
	$(property eInverseLinkedRefs... : ENode)# read-only.

	# 'eImmediateRefs' bidirectional reference.
	# The opposite reference is 'eInverseImmediateRefs'.
	$(property eImmediateRefs... : ENode)# read-only.

	# 'eInverseImmediateRefs' bidirectional reference.
	# The opposite reference is 'eImmediateRefs'.
	$(property eInverseImmediateRefs... : ENode)# read-only.

endef

#
# Model object 'ELink'.
#
# The following features are available:
#   - reference 'eMetaReference'
#   - reference 'eSource'
#   - reference 'eDestination'
#
# To instantiate this class use 'EModelFactory.createELink'.
define class-ELink
	$(super ENode)
	$(super ENamed)

	# 'eMetaReference' reference.
	$(property eMetaReference : EMetaReference)

	# 'eSource' bidirectional container reference.
	# The opposite reference is 'ENode.eLinks'.
	$(property eSource : ENode)# read-only.

	# 'eDestination' bidirectional reference.
	# The opposite reference is 'ENode.eInverseResolvedLinks'.
	$(property eDestination : ENode)# read-only.

endef

#
# Model object 'EMetaType'.
#
# The following features are available:
#   - attribute 'instanceClass'
#   - reference 'eMetaModel'
#
# This is an abstract class. You can't instantiate it directly.
define class-EMetaType
	$(super ENode)
	$(super ENamed)

	# 'instanceClass' attribute.
	$(property instanceClass)

	# 'eMetaModel' bidirectional container reference.
	# The opposite reference is 'EMetaModel.eTypes'.
	$(property eMetaModel : EMetaModel)# read-only.

endef

#
# Model object 'EMetaClass'.
#
# The following features are available:
#   - attribute 'abstract'
#   - attribute 'interface'
#   - reference 'eSuperTypes'
#   - reference 'eAllSuperTypes'
#   - reference 'eFeatures'
#   - reference 'eAllFeatures'
#   - reference 'eAttributes'
#   - reference 'eAllAttributes'
#   - reference 'eReferences'
#   - reference 'eAllReferences'
#   - reference 'eAllContainments'
#
# To instantiate this class use 'EModelFactory.createEMetaClass'.
define class-EMetaClass
	$(super ENode)
	$(super EMetaType)

	# 'abstract' attribute.
	$(property isAbstract)

	# 'interface' attribute.
	$(property isInterface)

	# 'eSuperTypes' reference.
	$(property eSuperTypes... : EMetaClass)

	# 'eAllSuperTypes' reference.
	$(property eAllSuperTypes... : EMetaClass)# read-only.

	# 'eFeatures' bidirectional containment reference.
	# The opposite reference is 'EMetaFeature.eContainingClass'.
	$(property eFeatures... : EMetaFeature)

	# 'eAllFeatures' reference.
	$(property eAllFeatures... : EMetaFeature)# read-only.

	# 'eAttributes' reference.
	$(property eAttributes... : EMetaAttribute)# read-only.

	# 'eAllAttributes' reference.
	$(property eAllAttributes... : EMetaAttribute)# read-only.

	# 'eReferences' reference.
	$(property eReferences... : EMetaReference)# read-only.

	# 'eAllReferences' reference.
	$(property eAllReferences... : EMetaReference)# read-only.

	# 'eAllContainments' reference.
	$(property eAllContainments... : EMetaReference)# read-only.

	# 'isSuperTypeOf' operation.
	#   1. someClass : EMetaClass
	$(method isSuperTypeOf)

	# 'isInstance' operation.
	#   1. object : ENode
	$(method isInstance)

endef

#
# Model object 'EMetaPrimitive'.
#
# To instantiate this class use 'EModelFactory.createEMetaPrimitive'.
define class-EMetaPrimitive
	$(super ENode)
	$(super EMetaType)

endef

#
# Model object 'EMetaFeature'.
#
# The following features are available:
#   - attribute 'changeable'
#   - attribute 'volatile'
#   - attribute 'transient'
#   - attribute 'derived'
#   - attribute 'instanceProperty'
#   - reference 'eContainingClass'
#
# This is an abstract class. You can't instantiate it directly.
define class-EMetaFeature
	$(super ENode)
	$(super ETyped)

	# 'changeable' attribute.
	$(property isChangeable)

	# 'volatile' attribute.
	$(property isVolatile)

	# 'transient' attribute.
	$(property isTransient)

	# 'derived' attribute.
	$(property isDerived)

	# 'instanceProperty' attribute.
	$(property instanceProperty)

	# 'eContainingClass' bidirectional container reference.
	# The opposite reference is 'EMetaClass.eFeatures'.
	$(property eContainingClass : EMetaClass)# read-only.

endef

#
# Model object 'EMetaReference'.
#
# The following features are available:
#   - attribute 'containment'
#   - attribute 'container'
#   - reference 'eOpposite'
#   - reference 'eReferenceType'
#
# To instantiate this class use 'EModelFactory.createEMetaReference'.
define class-EMetaReference
	$(super ENode)
	$(super EMetaFeature)

	# 'containment' attribute.
	$(property isContainment)

	# 'container' attribute.
	$(property isContainer)# read-only.

	# 'eOpposite' reference.
	$(property eOpposite : EMetaReference)

	# 'eReferenceType' reference.
	$(property eReferenceType : EMetaClass)# read-only.

endef

#
# Model object 'EMetaAttribute'.
#
# The following features are available:
#   - reference 'eAttributeType'
#
# To instantiate this class use 'EModelFactory.createEMetaAttribute'.
define class-EMetaAttribute
	$(super ENode)
	$(super EMetaFeature)

	# 'eAttributeType' reference.
	$(property eAttributeType : EMetaPrimitive)# read-only.

endef

#
# Model object 'EMetaModel'.
#
# The following features are available:
#   - reference 'eFactory'
#   - reference 'eTypes'
#
# To instantiate this class use 'EModelFactory.createEMetaModel'.
define class-EMetaModel
	$(super ENode)
	$(super ENamed)

	# 'eFactory' bidirectional reference.
	# The opposite reference is 'EFactory.eMetaModel'.
	$(property eFactory : EFactory)

	# 'eTypes' bidirectional containment reference.
	# The opposite reference is 'EMetaType.eMetaModel'.
	$(property eTypes... : EMetaType)

endef

#
# Model object 'EFactory'.
#
# The following features are available:
#   - reference 'eMetaModel'
#
# To instantiate this class use 'EModelFactory.createEFactory'.
define class-EFactory
	$(super ENode)

	# 'eMetaModel' bidirectional reference.
	# The opposite reference is 'EMetaModel.eFactory'.
	$(property eMetaModel : EMetaModel)

endef

#
# Model object 'ENamed'.
#
# The following features are available:
#   - attribute 'name'
#
# This is an abstract class. You can't instantiate it directly.
define class-ENamed
	$(super ENode)

	# 'name' attribute.
	$(property name)

endef

#
# Model object 'ETyped'.
#
# The following features are available:
#   - attribute 'lowerBound'
#   - attribute 'upperBound'
#   - attribute 'many'
#   - reference 'eType'
#
# This is an abstract class. You can't instantiate it directly.
define class-ETyped
	$(super ENode)
	$(super ENamed)

	# 'lowerBound' attribute.
	$(property lowerBound)

	# 'upperBound' attribute.
	$(property upperBound)

	# 'many' attribute.
	$(property isMany)# read-only.

	# 'eType' reference.
	$(property eType : EMetaType)

endef

$(def_all)

include $(dir $(__model_model_mk))model_impl.mk

endif # __model_model_mk


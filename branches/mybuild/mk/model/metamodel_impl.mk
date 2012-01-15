# Generated by Xpand using M2Make template.

# Metamodel implementation for 'EModel' package.

ifndef __model_metamodel_mk
$(error \
	Do not include this file directly, include 'metamodel.mk' instead!)
endif # __model_metamodel_mk

# Creates and initializes contents of 'EModel' meta model.
define class-EModelMetaModelImpl
	$(super EModelMetaModel)

	$(super EMetaModelImpl)

	# Define properties as fields.

	$(property-field ENode : EMetaClass,
		$(invoke createMetaClass,ENode))
	$(property-field ENode_eMetaClass : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eMetaClass))
	$(property-field ENode_eResource : EMetaAttribute,
		$(invoke createMetaAttribute,$(get ENode),ENode_eResource))
	$(property-field ENode_eContainer : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eContainer))
	$(property-field ENode_eRootContainer : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eRootContainer))
	$(property-field ENode_eContents : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eContents))
	$(property-field ENode_eAllContents : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eAllContents))
	$(property-field ENode_eLinks : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eLinks))
	$(property-field ENode_eResolvedLinks : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eResolvedLinks))
	$(property-field ENode_eInverseResolvedLinks : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eInverseResolvedLinks))
	$(property-field ENode_eUnresolvedLinks : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eUnresolvedLinks))
	$(property-field ENode_eRefs : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eRefs))
	$(property-field ENode_eInverseRefs : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eInverseRefs))
	$(property-field ENode_eLinkedRefs : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eLinkedRefs))
	$(property-field ENode_eInverseLinkedRefs : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eInverseLinkedRefs))
	$(property-field ENode_eImmediateRefs : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eImmediateRefs))
	$(property-field ENode_eInverseImmediateRefs : EMetaReference,
		$(invoke createMetaReference,$(get ENode),ENode_eInverseImmediateRefs))

	$(property-field ELink : EMetaClass,
		$(invoke createMetaClass,ELink))
	$(property-field ELink_eMetaReference : EMetaReference,
		$(invoke createMetaReference,$(get ELink),ELink_eMetaReference))
	$(property-field ELink_eSource : EMetaReference,
		$(invoke createMetaReference,$(get ELink),ELink_eSource))
	$(property-field ELink_eDestination : EMetaReference,
		$(invoke createMetaReference,$(get ELink),ELink_eDestination))

	$(property-field EMetaType : EMetaClass,
		$(invoke createMetaClass,EMetaType))
	$(property-field EMetaType_instanceClass : EMetaAttribute,
		$(invoke createMetaAttribute,$(get EMetaType),EMetaType_instanceClass))
	$(property-field EMetaType_eMetaModel : EMetaReference,
		$(invoke createMetaReference,$(get EMetaType),EMetaType_eMetaModel))

	$(property-field EMetaClass : EMetaClass,
		$(invoke createMetaClass,EMetaClass))
	$(property-field EMetaClass_abstract : EMetaAttribute,
		$(invoke createMetaAttribute,$(get EMetaClass),EMetaClass_abstract))
	$(property-field EMetaClass_interface : EMetaAttribute,
		$(invoke createMetaAttribute,$(get EMetaClass),EMetaClass_interface))
	$(property-field EMetaClass_eSuperTypes : EMetaReference,
		$(invoke createMetaReference,$(get EMetaClass),EMetaClass_eSuperTypes))
	$(property-field EMetaClass_eAllSuperTypes : EMetaReference,
		$(invoke createMetaReference,$(get EMetaClass),EMetaClass_eAllSuperTypes))
	$(property-field EMetaClass_eFeatures : EMetaReference,
		$(invoke createMetaReference,$(get EMetaClass),EMetaClass_eFeatures))
	$(property-field EMetaClass_eAllFeatures : EMetaReference,
		$(invoke createMetaReference,$(get EMetaClass),EMetaClass_eAllFeatures))
	$(property-field EMetaClass_eAttributes : EMetaReference,
		$(invoke createMetaReference,$(get EMetaClass),EMetaClass_eAttributes))
	$(property-field EMetaClass_eAllAttributes : EMetaReference,
		$(invoke createMetaReference,$(get EMetaClass),EMetaClass_eAllAttributes))
	$(property-field EMetaClass_eReferences : EMetaReference,
		$(invoke createMetaReference,$(get EMetaClass),EMetaClass_eReferences))
	$(property-field EMetaClass_eAllReferences : EMetaReference,
		$(invoke createMetaReference,$(get EMetaClass),EMetaClass_eAllReferences))
	$(property-field EMetaClass_eAllContainments : EMetaReference,
		$(invoke createMetaReference,$(get EMetaClass),EMetaClass_eAllContainments))

	$(property-field EMetaPrimitive : EMetaClass,
		$(invoke createMetaClass,EMetaPrimitive))

	$(property-field EMetaFeature : EMetaClass,
		$(invoke createMetaClass,EMetaFeature))
	$(property-field EMetaFeature_changeable : EMetaAttribute,
		$(invoke createMetaAttribute,$(get EMetaFeature),EMetaFeature_changeable))
	$(property-field EMetaFeature_volatile : EMetaAttribute,
		$(invoke createMetaAttribute,$(get EMetaFeature),EMetaFeature_volatile))
	$(property-field EMetaFeature_transient : EMetaAttribute,
		$(invoke createMetaAttribute,$(get EMetaFeature),EMetaFeature_transient))
	$(property-field EMetaFeature_derived : EMetaAttribute,
		$(invoke createMetaAttribute,$(get EMetaFeature),EMetaFeature_derived))
	$(property-field EMetaFeature_instanceProperty : EMetaAttribute,
		$(invoke createMetaAttribute,$(get EMetaFeature),EMetaFeature_instanceProperty))
	$(property-field EMetaFeature_eContainingClass : EMetaReference,
		$(invoke createMetaReference,$(get EMetaFeature),EMetaFeature_eContainingClass))

	$(property-field EMetaReference : EMetaClass,
		$(invoke createMetaClass,EMetaReference))
	$(property-field EMetaReference_containment : EMetaAttribute,
		$(invoke createMetaAttribute,$(get EMetaReference),EMetaReference_containment))
	$(property-field EMetaReference_container : EMetaAttribute,
		$(invoke createMetaAttribute,$(get EMetaReference),EMetaReference_container))
	$(property-field EMetaReference_eOpposite : EMetaReference,
		$(invoke createMetaReference,$(get EMetaReference),EMetaReference_eOpposite))
	$(property-field EMetaReference_eReferenceType : EMetaReference,
		$(invoke createMetaReference,$(get EMetaReference),EMetaReference_eReferenceType))

	$(property-field EMetaAttribute : EMetaClass,
		$(invoke createMetaClass,EMetaAttribute))
	$(property-field EMetaAttribute_eAttributeType : EMetaReference,
		$(invoke createMetaReference,$(get EMetaAttribute),EMetaAttribute_eAttributeType))

	$(property-field EMetaModel : EMetaClass,
		$(invoke createMetaClass,EMetaModel))
	$(property-field EMetaModel_eFactory : EMetaReference,
		$(invoke createMetaReference,$(get EMetaModel),EMetaModel_eFactory))
	$(property-field EMetaModel_eTypes : EMetaReference,
		$(invoke createMetaReference,$(get EMetaModel),EMetaModel_eTypes))

	$(property-field EFactory : EMetaClass,
		$(invoke createMetaClass,EFactory))
	$(property-field EFactory_eMetaModel : EMetaReference,
		$(invoke createMetaReference,$(get EFactory),EFactory_eMetaModel))

	$(property-field ENamed : EMetaClass,
		$(invoke createMetaClass,ENamed))
	$(property-field ENamed_name : EMetaAttribute,
		$(invoke createMetaAttribute,$(get ENamed),ENamed_name))

	$(property-field ETyped : EMetaClass,
		$(invoke createMetaClass,ETyped))
	$(property-field ETyped_lowerBound : EMetaAttribute,
		$(invoke createMetaAttribute,$(get ETyped),ETyped_lowerBound))
	$(property-field ETyped_upperBound : EMetaAttribute,
		$(invoke createMetaAttribute,$(get ETyped),ETyped_upperBound))
	$(property-field ETyped_many : EMetaAttribute,
		$(invoke createMetaAttribute,$(get ETyped),ETyped_many))
	$(property-field ETyped_eType : EMetaReference,
		$(invoke createMetaReference,$(get ETyped),ETyped_eType))

	# Initialize the objects and relations between them.

	$(invoke initMetaClass,$(get ENode),
		ENode,,)
	$(invoke initMetaReference,$(get ENode_eMetaClass),
		eMetaClass,0,1,$(get EMetaClass),,volatile derived transient)
	$(invoke initMetaAttribute,$(get ENode_eResource),
		eResource,0,1,volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eContainer),
		eContainer,0,1,$(get ENode),$(get ENode_eContents),volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eRootContainer),
		eRootContainer,0,1,$(get ENode),,volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eContents),
		eContents,0,,$(get ENode),$(get ENode_eContainer),volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eAllContents),
		eAllContents,0,,$(get ENode),,volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eLinks),
		eLinks,0,,$(get ELink),$(get ELink_eSource),volatile derived transient containment)
	$(invoke initMetaReference,$(get ENode_eResolvedLinks),
		eResolvedLinks,0,,$(get ELink),,volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eInverseResolvedLinks),
		eInverseResolvedLinks,0,,$(get ELink),$(get ELink_eDestination),volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eUnresolvedLinks),
		eUnresolvedLinks,0,,$(get ELink),,volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eRefs),
		eRefs,0,,$(get ENode),$(get ENode_eInverseRefs),volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eInverseRefs),
		eInverseRefs,0,,$(get ENode),$(get ENode_eRefs),volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eLinkedRefs),
		eLinkedRefs,0,,$(get ENode),$(get ENode_eInverseLinkedRefs),volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eInverseLinkedRefs),
		eInverseLinkedRefs,0,,$(get ENode),$(get ENode_eLinkedRefs),volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eImmediateRefs),
		eImmediateRefs,0,,$(get ENode),$(get ENode_eInverseImmediateRefs),volatile derived transient)
	$(invoke initMetaReference,$(get ENode_eInverseImmediateRefs),
		eInverseImmediateRefs,0,,$(get ENode),$(get ENode_eImmediateRefs),volatile derived transient)

	$(invoke initMetaClass,$(get ELink),
		ELink,$(get ENamed),)
	$(invoke initMetaReference,$(get ELink_eMetaReference),
		eMetaReference,0,1,$(get EMetaReference),,changeable)
	$(invoke initMetaReference,$(get ELink_eSource),
		eSource,0,1,$(get ENode),$(get ENode_eLinks),volatile derived transient container)
	$(invoke initMetaReference,$(get ELink_eDestination),
		eDestination,0,1,$(get ENode),$(get ENode_eInverseResolvedLinks),volatile derived transient)

	$(invoke initMetaClass,$(get EMetaType),
		EMetaType,$(get ENamed),abstract)
	$(invoke initMetaAttribute,$(get EMetaType_instanceClass),
		instanceClass,0,1,changeable)
	$(invoke initMetaReference,$(get EMetaType_eMetaModel),
		eMetaModel,0,1,$(get EMetaModel),$(get EMetaModel_eTypes),transient container)

	$(invoke initMetaClass,$(get EMetaClass),
		EMetaClass,$(get EMetaType),)
	$(invoke initMetaAttribute,$(get EMetaClass_abstract),
		abstract,0,1,changeable)
	$(invoke initMetaAttribute,$(get EMetaClass_interface),
		interface,0,1,changeable)
	$(invoke initMetaReference,$(get EMetaClass_eSuperTypes),
		eSuperTypes,0,,$(get EMetaClass),,changeable)
	$(invoke initMetaReference,$(get EMetaClass_eAllSuperTypes),
		eAllSuperTypes,0,,$(get EMetaClass),,volatile derived transient)
	$(invoke initMetaReference,$(get EMetaClass_eFeatures),
		eFeatures,0,,$(get EMetaFeature),$(get EMetaFeature_eContainingClass),changeable containment)
	$(invoke initMetaReference,$(get EMetaClass_eAllFeatures),
		eAllFeatures,0,,$(get EMetaFeature),,volatile derived transient)
	$(invoke initMetaReference,$(get EMetaClass_eAttributes),
		eAttributes,0,,$(get EMetaAttribute),,volatile derived transient)
	$(invoke initMetaReference,$(get EMetaClass_eAllAttributes),
		eAllAttributes,0,,$(get EMetaAttribute),,volatile derived transient)
	$(invoke initMetaReference,$(get EMetaClass_eReferences),
		eReferences,0,,$(get EMetaReference),,volatile derived transient)
	$(invoke initMetaReference,$(get EMetaClass_eAllReferences),
		eAllReferences,0,,$(get EMetaReference),,volatile derived transient)
	$(invoke initMetaReference,$(get EMetaClass_eAllContainments),
		eAllContainments,0,,$(get EMetaReference),,volatile derived transient)

	$(invoke initMetaClass,$(get EMetaPrimitive),
		EMetaPrimitive,$(get EMetaType),)

	$(invoke initMetaClass,$(get EMetaFeature),
		EMetaFeature,$(get ETyped),abstract)
	$(invoke initMetaAttribute,$(get EMetaFeature_changeable),
		changeable,0,1,changeable)
	$(invoke initMetaAttribute,$(get EMetaFeature_volatile),
		volatile,0,1,changeable)
	$(invoke initMetaAttribute,$(get EMetaFeature_transient),
		transient,0,1,changeable)
	$(invoke initMetaAttribute,$(get EMetaFeature_derived),
		derived,0,1,changeable)
	$(invoke initMetaAttribute,$(get EMetaFeature_instanceProperty),
		instanceProperty,0,1,changeable)
	$(invoke initMetaReference,$(get EMetaFeature_eContainingClass),
		eContainingClass,0,1,$(get EMetaClass),$(get EMetaClass_eFeatures),transient container)

	$(invoke initMetaClass,$(get EMetaReference),
		EMetaReference,$(get EMetaFeature),)
	$(invoke initMetaAttribute,$(get EMetaReference_containment),
		containment,0,1,changeable)
	$(invoke initMetaAttribute,$(get EMetaReference_container),
		container,0,1,volatile derived transient)
	$(invoke initMetaReference,$(get EMetaReference_eOpposite),
		eOpposite,0,1,$(get EMetaReference),,changeable)
	$(invoke initMetaReference,$(get EMetaReference_eReferenceType),
		eReferenceType,1,1,$(get EMetaClass),,volatile derived transient)

	$(invoke initMetaClass,$(get EMetaAttribute),
		EMetaAttribute,$(get EMetaFeature),)
	$(invoke initMetaReference,$(get EMetaAttribute_eAttributeType),
		eAttributeType,1,1,$(get EMetaPrimitive),,volatile derived transient)

	$(invoke initMetaClass,$(get EMetaModel),
		EMetaModel,$(get ENamed),)
	$(invoke initMetaReference,$(get EMetaModel_eFactory),
		eFactory,1,1,$(get EFactory),$(get EFactory_eMetaModel),changeable transient)
	$(invoke initMetaReference,$(get EMetaModel_eTypes),
		eTypes,0,,$(get EMetaType),$(get EMetaType_eMetaModel),changeable containment)

	$(invoke initMetaClass,$(get EFactory),
		EFactory,,)
	$(invoke initMetaReference,$(get EFactory_eMetaModel),
		eMetaModel,1,1,$(get EMetaModel),$(get EMetaModel_eFactory),changeable transient)

	$(invoke initMetaClass,$(get ENamed),
		ENamed,,abstract)
	$(invoke initMetaAttribute,$(get ENamed_name),
		name,0,1,changeable)

	$(invoke initMetaClass,$(get ETyped),
		ETyped,$(get ENamed),abstract)
	$(invoke initMetaAttribute,$(get ETyped_lowerBound),
		lowerBound,0,1,changeable)
	$(invoke initMetaAttribute,$(get ETyped_upperBound),
		upperBound,0,1,changeable)
	$(invoke initMetaAttribute,$(get ETyped_many),
		many,0,1,volatile derived transient)
	$(invoke initMetaReference,$(get ETyped_eType),
		eType,0,1,$(get EMetaType),,changeable)

	# Bind objects to instance classes and features to properties.

	$(invoke bindMetaClass,$(get ENode),ENode)
	$(invoke bindMetaFeature,$(get ENode_eMetaClass),eMetaClass)
	$(invoke bindMetaFeature,$(get ENode_eResource),eResource)
	$(invoke bindMetaFeature,$(get ENode_eContainer),eContainer)
	$(invoke bindMetaFeature,$(get ENode_eRootContainer),eRootContainer)
	$(invoke bindMetaFeature,$(get ENode_eContents),eContents)
	$(invoke bindMetaFeature,$(get ENode_eAllContents),eAllContents)
	$(invoke bindMetaFeature,$(get ENode_eLinks),eLinks)
	$(invoke bindMetaFeature,$(get ENode_eResolvedLinks),eResolvedLinks)
	$(invoke bindMetaFeature,$(get ENode_eInverseResolvedLinks),eInverseResolvedLinks)
	$(invoke bindMetaFeature,$(get ENode_eUnresolvedLinks),eUnresolvedLinks)
	$(invoke bindMetaFeature,$(get ENode_eRefs),eRefs)
	$(invoke bindMetaFeature,$(get ENode_eInverseRefs),eInverseRefs)
	$(invoke bindMetaFeature,$(get ENode_eLinkedRefs),eLinkedRefs)
	$(invoke bindMetaFeature,$(get ENode_eInverseLinkedRefs),eInverseLinkedRefs)
	$(invoke bindMetaFeature,$(get ENode_eImmediateRefs),eImmediateRefs)
	$(invoke bindMetaFeature,$(get ENode_eInverseImmediateRefs),eInverseImmediateRefs)

	$(invoke bindMetaClass,$(get ELink),ELink)
	$(invoke bindMetaFeature,$(get ELink_eMetaReference),eMetaReference)
	$(invoke bindMetaFeature,$(get ELink_eSource),eSource)
	$(invoke bindMetaFeature,$(get ELink_eDestination),eDestination)

	$(invoke bindMetaClass,$(get EMetaType),EMetaType)
	$(invoke bindMetaFeature,$(get EMetaType_instanceClass),instanceClass)
	$(invoke bindMetaFeature,$(get EMetaType_eMetaModel),eMetaModel)

	$(invoke bindMetaClass,$(get EMetaClass),EMetaClass)
	$(invoke bindMetaFeature,$(get EMetaClass_abstract),isAbstract)
	$(invoke bindMetaFeature,$(get EMetaClass_interface),isInterface)
	$(invoke bindMetaFeature,$(get EMetaClass_eSuperTypes),eSuperTypes)
	$(invoke bindMetaFeature,$(get EMetaClass_eAllSuperTypes),eAllSuperTypes)
	$(invoke bindMetaFeature,$(get EMetaClass_eFeatures),eFeatures)
	$(invoke bindMetaFeature,$(get EMetaClass_eAllFeatures),eAllFeatures)
	$(invoke bindMetaFeature,$(get EMetaClass_eAttributes),eAttributes)
	$(invoke bindMetaFeature,$(get EMetaClass_eAllAttributes),eAllAttributes)
	$(invoke bindMetaFeature,$(get EMetaClass_eReferences),eReferences)
	$(invoke bindMetaFeature,$(get EMetaClass_eAllReferences),eAllReferences)
	$(invoke bindMetaFeature,$(get EMetaClass_eAllContainments),eAllContainments)

	$(invoke bindMetaClass,$(get EMetaPrimitive),EMetaPrimitive)

	$(invoke bindMetaClass,$(get EMetaFeature),EMetaFeature)
	$(invoke bindMetaFeature,$(get EMetaFeature_changeable),isChangeable)
	$(invoke bindMetaFeature,$(get EMetaFeature_volatile),isVolatile)
	$(invoke bindMetaFeature,$(get EMetaFeature_transient),isTransient)
	$(invoke bindMetaFeature,$(get EMetaFeature_derived),isDerived)
	$(invoke bindMetaFeature,$(get EMetaFeature_instanceProperty),instanceProperty)
	$(invoke bindMetaFeature,$(get EMetaFeature_eContainingClass),eContainingClass)

	$(invoke bindMetaClass,$(get EMetaReference),EMetaReference)
	$(invoke bindMetaFeature,$(get EMetaReference_containment),isContainment)
	$(invoke bindMetaFeature,$(get EMetaReference_container),isContainer)
	$(invoke bindMetaFeature,$(get EMetaReference_eOpposite),eOpposite)
	$(invoke bindMetaFeature,$(get EMetaReference_eReferenceType),eReferenceType)

	$(invoke bindMetaClass,$(get EMetaAttribute),EMetaAttribute)
	$(invoke bindMetaFeature,$(get EMetaAttribute_eAttributeType),eAttributeType)

	$(invoke bindMetaClass,$(get EMetaModel),EMetaModel)
	$(invoke bindMetaFeature,$(get EMetaModel_eFactory),eFactory)
	$(invoke bindMetaFeature,$(get EMetaModel_eTypes),eTypes)

	$(invoke bindMetaClass,$(get EFactory),EFactory)
	$(invoke bindMetaFeature,$(get EFactory_eMetaModel),eMetaModel)

	$(invoke bindMetaClass,$(get ENamed),ENamed)
	$(invoke bindMetaFeature,$(get ENamed_name),name)

	$(invoke bindMetaClass,$(get ETyped),ETyped)
	$(invoke bindMetaFeature,$(get ETyped_lowerBound),lowerBound)
	$(invoke bindMetaFeature,$(get ETyped_upperBound),upperBound)
	$(invoke bindMetaFeature,$(get ETyped_many),isMany)
	$(invoke bindMetaFeature,$(get ETyped_eType),eType)

endef

$(def_all)


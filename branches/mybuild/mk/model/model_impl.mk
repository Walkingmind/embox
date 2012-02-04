# Generated by Xpand using M2Make template.

# Model implementation of 'EModel' package.

ifndef __model_model_mk
$(error \
	Do not include this file directly, include 'model.mk' instead!)
endif # __model_model_mk

# Implementation of 'EObject' model object.
define class-EObjectImpl
	$(super EObject)

	# Reference 'eMetaClass' [0..1]: derived, read-only.
	$(property eMetaClass : EMetaClass)
	# PROTECTED REGION ID(EObject_eMetaClass) ENABLED START
	$(getter eMetaClass,$(error Subclass must override eMetaClass property))
	# PROTECTED REGION END

	# Attribute 'eResource': derived, read-only.
	$(property eResource)
	# PROTECTED REGION ID(EObject_eResource) ENABLED START
	$(getter eResource,
		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eContainer' [0..1]: bidirectional, derived, read-only.
	$(property eContainer : EObject)
	# PROTECTED REGION ID(EObject_eContainer) ENABLED START
	$(getter eContainer,
		$(get-field __eContainer))
	# PROTECTED REGION END

	# Reference 'eRootContainer' [0..1]: derived, read-only.
	$(property eRootContainer : EObject)
	# PROTECTED REGION ID(EObject_eRootContainer) ENABLED START
	$(getter eRootContainer,
		$(or $(for container <- $(get eContainer),
				$(get container->eRootContainer)),
			$(this)))
	# PROTECTED REGION END

	# Reference 'eContents' [0..*]: bidirectional, derived, read-only.
	$(property eContents... : EObject)
	# PROTECTED REGION ID(EObject_eContents) ENABLED START
	$(getter eContents,
		$(for metaReference <- $(get $(get eMetaClass).eAllContainments),
			$(get $(get metaReference->instanceProperty))))
	# PROTECTED REGION END

	# Reference 'eAllContents' [0..*]: derived, read-only.
	$(property eAllContents... : EObject)
	# PROTECTED REGION ID(EObject_eAllContents) ENABLED START
	$(getter eAllContents,
		$(for child <- $(get eContents),
			$(child) $(get child->eAllContents)))
	# PROTECTED REGION END

	# Reference 'eLinks' [0..*]: bidirectional, derived, read-only.
	$(property eLinks... : ELink)
	# PROTECTED REGION ID(EObject_eLinks) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eLinks,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eResolvedLinks' [0..*]: derived, read-only.
	$(property eResolvedLinks... : ELink)
	# PROTECTED REGION ID(EObject_eResolvedLinks) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eResolvedLinks,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eUnresolvedLinks' [0..*]: derived, read-only.
	$(property eUnresolvedLinks... : ELink)
	# PROTECTED REGION ID(EObject_eUnresolvedLinks) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eUnresolvedLinks,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eRefs' [0..*]: bidirectional, derived, read-only.
	$(property eRefs... : EObject)
	# PROTECTED REGION ID(EObject_eRefs) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eRefs,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eInverseRefs' [0..*]: bidirectional, derived, read-only.
	$(property eInverseRefs... : EObject)
	# PROTECTED REGION ID(EObject_eInverseRefs) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eInverseRefs,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eLinkedRefs' [0..*]: bidirectional, derived, read-only.
	$(property eLinkedRefs... : ENamedObject)
	# PROTECTED REGION ID(EObject_eLinkedRefs) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eLinkedRefs,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eImmediateRefs' [0..*]: bidirectional, derived, read-only.
	$(property eImmediateRefs... : EObject)
	# PROTECTED REGION ID(EObject_eImmediateRefs) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eImmediateRefs,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eInverseImmediateRefs' [0..*]: bidirectional, derived, read-only.
	$(property eInverseImmediateRefs... : EObject)
	# PROTECTED REGION ID(EObject_eInverseImmediateRefs) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eInverseImmediateRefs,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# 'isAncestorOf' operation.
	#   1. object : EObject
	# PROTECTED REGION ID(EObject_isAncestorOf) ENABLED START
	$(method isAncestorOf,
		$(for container <- $(get 1->eContainer),
			$(or $(filter $(this),$(container)),
				$(invoke isAncestorOf,$(container)))))
	# PROTECTED REGION END

	# 'getContainerOfType : EObject' operation.
	#   1. someClass : EMetaClass
	# PROTECTED REGION ID(EObject_getContainerOfType) ENABLED START
	$(method getContainerOfType,
		$(for container <- $(get eContainer),
			$(if $(invoke 1->isInstance,$(container)),
				$(container),$(invoke container->getContainerOfType,$1))))
	# PROTECTED REGION END

	# PROTECTED REGION ID(EObject) ENABLED START

	# 'property/oppositeProperty.object'
	$(field __eContainer : EObject)

	# 'property[.link].object'
	$(field __eOppositeRefs... : EObject)

	# 'property/[oppositeProperty].link'
	$(field __eUnresolvedLinks... : ELink)

	# Params:
	#   1. Property name.
	$(method __eGetContainer,
		$(filter $1/%,$(get-field __eContainer))
	)

	# Params:
	#   1. Property name.
	#   2. New container.
	#   3. Containment property in the container.
	$(method __eSetContainer,
		$(assert $(not $(multiword $2)))

		$(for oldContainer <- $(get-field __eContainer),
			$(set-field- oldContainer->$(notdir $(basename $(oldContainer))),
				$(this))
		)

		$(set-field __eContainer,$1/$3$2)

		$(for newContainer <- $2,
			$(set-field+ newContainer->$3,$(this))
		)
	)

	# Params:
	#   1. Property name.
	#   2. What to add.
	$(method __eAdd,
		$(set-field+ $1,$2)
		$(silent-for e <- $2,
			$(set-field+ e->__eOppositeRefs,$1$(this)))
	)

	# Params:
	#   1. Property name.
	#   2. What to add.
	#   3. Opposite property.
	$(method __eAddContainment,
		$(silent-for e <- $2,
			$(invoke e->__eSetContainer,$3,$(this),$1))
	)

	# Params:
	#   1. Property name.
	#   2. What to add.
	#   3. Opposite property.
	$(method __eAddBidirectional,
		$(set-field+ $1,$2)
		$(silent-for e <- $2,
			$(set-field+ e->$3,$(this)))
	)

	# Params:
	#   1. Property name.
	#   2. What to remove.
	$(method __eRemove,
		$(foreach ,$2,$(error $0: NIY))
	)

	# Params:
	#   1. Property name.
	#   2. What to remove.
	#   3. Opposite property.
	$(method __eRemoveBidirectional,
		$(foreach ,$2,$(error $0: NIY))
	)

	# Params:
	#   1. Property name.
	#   2. What to remove.
	#   3. Opposite property.
	$(method __eRemoveContainment,
		$(foreach ,$2,$(error $0: NIY))
	)

	# Params:
	#   1. Property name.
	#   2. New value.
	$(method __eSet,
		$(invoke __eRemove,$1,$(get-field $1))
		$(invoke __eAdd,$1,$2)
	)

	# Params:
	#   1. Property name.
	#   2. New value.
	#   3. Opposite property.
	$(method __eSetBidirectional,
		$(invoke __eRemoveBidirectional,$1,$(get-field $1),$3)
		$(invoke __eAddBidirectional,$1,$2,$3)
	)

	# Params:
	#   1. Property name.
	#   2. New value.
	#   3. Opposite property.
	$(method __eSetContainment,
		$(invoke __eRemoveContainment,$1,$(get-field $1),$3)
		$(invoke __eAddContainment,$1,$2,$3)
	)

	# Params:
	#   1. Property name.
	#   2. What to add.
	$(method __eAdd_link,
		$(with $1,$2,
			# Resolved links suffixed by destination.
			$(for link <- $2,
				$(set-field link->__eContainer,$1/eLinks$(this))
				$(for dst <- $(get link->eTarget),
					$(link)$(dst))),

			$(set-field+ $1,$3)
			$(silent-for link_dst <- $3,
				$(set-field+ link_dst->__eOppositeRefs,
					$1$(basename $(link_dst))$(this)))

			$(set-field+ __eUnresolvedLinks,
				$(addprefix $1/,$(filter-out $(basename $3),$2)))
		)
	)

	# Params:
	#   1. Property name.
	#   2. What to add.
	#   3. Opposite property.
	$(method __eAddBidirectional_link,
		$(with $1,$2,$3,
			# Resolved links suffixed by destination.
			$(for link <- $2,
				$(set-field link->__eContainer,$1/eLinks$(this))
				$(for dst <- $(get link->eTarget),
					$(link)$(dst))),

			$(set-field+ $1,$4)
			$(silent-for link_dst <- $4,
				$(set-field+ link_dst->$3,$(basename $(link_dst))$(this)))

			$(set-field+ __eUnresolvedLinks,
				$(addprefix $1/$3,$(filter-out $(basename $3),$2)))
		)
	)

	# Params:
	#   1. Property name.
	#   2. What to remove.
	$(method __eRemove_link,
		$(foreach ,$2,$(error $0: NIY))
	)

	# Params:
	#   1. Property name.
	#   2. What to remove.
	#   3. Opposite property.
	$(method __eRemoveBidirectional_link,
		$(foreach ,$2,$(error $0: NIY))
	)

	# Params:
	#   1. Property name.
	#   2. New value.
	$(method __eSet_link,
		$(invoke __eRemove_link,$1,$(get-field $1))
		$(invoke __eAdd_link,$1,$2)
	)

	# Params:
	#   1. Property name.
	#   2. New value.
	#   3. Opposite property.
	$(method __eSetBidirectional_link,
		$(invoke __eRemoveBidirectional_link,$1,$(get-field $1),$3)
		$(invoke __eAddBidirectional_link,$1,$2,$3)
	)

	# PROTECTED REGION END
endef

# Implementation of 'ENamedObject' model object.
define class-ENamedObjectImpl
	$(super ENamedObject)

	$(super EObjectImpl)

	$(getter eMetaClass,$(EModel_ENamedObject))

	# Attribute 'name'.
	$(property-field name)

	# Attribute 'qualifiedName': derived, read-only.
	$(property qualifiedName)
	# PROTECTED REGION ID(ENamedObject_qualifiedName) ENABLED START
	$(getter qualifiedName,
		$(for namedContainer <- $(invoke getContainerOfType,$(EModel_ENamedObject)),
			parentName <- $(get namedContainer->qualifiedName),
			$(parentName)$(if $(get name),.))$(get name))
	# PROTECTED REGION END

	# Reference 'eInverseResolvedLinks' [0..*]: bidirectional, derived, read-only.
	$(property eInverseResolvedLinks... : ELink)
	# PROTECTED REGION ID(ENamedObject_eInverseResolvedLinks) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eInverseResolvedLinks,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eInverseLinkedRefs' [0..*]: bidirectional, derived, read-only.
	$(property eInverseLinkedRefs... : EObject)
	# PROTECTED REGION ID(ENamedObject_eInverseLinkedRefs) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eInverseLinkedRefs,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(ENamedObject) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'ELink' model object.
define class-ELinkImpl
	$(super ELink)

	$(super EObjectImpl)
	$(super ENamedObjectImpl)

	$(getter eMetaClass,$(EModel_ELink))

	# Reference 'eMetaReference' [0..1]: derived, read-only.
	$(property eMetaReference : EMetaReference)
	# PROTECTED REGION ID(ELink_eMetaReference) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter eMetaReference,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'eSource' [0..1]: bidirectional, read-only.
	$(property eSource : EObject)
	$(field eSource : EObject)
	$(getter eSource,
		$(get-field eSource))

	# Reference 'eTarget' [0..1]: bidirectional, derived.
	$(property eTarget : ENamedObject)
	# PROTECTED REGION ID(ELink_eTarget) ENABLED START
	$(field eTarget : EObject)
	$(getter eTarget,
		$(get-field eTarget))
#	# TODO Uncomment and implement me.
#	$(setter eTarget,
#		$(error $0($1): NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(ELink) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EMetaType' model object.
define class-EMetaTypeImpl
	$(super EMetaType)

	$(super EObjectImpl)
	$(super ENamedObjectImpl)

	$(getter eMetaClass,$(EModel_EMetaType))

	# Attribute 'instanceClass'.
	$(property-field instanceClass)

	# Reference 'eMetaModel' [0..1]: bidirectional, container, read-only.
	$(property eMetaModel : EMetaModel)
	$(getter eMetaModel,
		$(invoke __eGetContainer,eMetaModel))

	# PROTECTED REGION ID(EMetaType) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EMetaClass' model object.
define class-EMetaClassImpl
	$(super EMetaClass)

	$(super EObjectImpl)
	$(super EMetaTypeImpl)

	$(getter eMetaClass,$(EModel_EMetaClass))

	# Attribute 'abstract'.
	$(property-field isAbstract)

	# Attribute 'interface'.
	$(property-field isInterface)

	# Reference 'eSuperTypes' [0..*].
	$(property eSuperTypes... : EMetaClass)
	$(field eSuperTypes... : EMetaClass)
	$(getter eSuperTypes,
		$(get-field eSuperTypes))
	$(setter eSuperTypes,
		$(invoke __eSet,eSuperTypes,$(suffix $1),))
	$(setter+ eSuperTypes,
		$(invoke __eAdd,eSuperTypes,$(suffix $1),))
	$(setter- eSuperTypes,
		$(invoke __eRemove,eSuperTypes,$(suffix $1),))

	# Reference 'eAllSuperTypes' [0..*]: derived, read-only.
	$(property eAllSuperTypes... : EMetaClass)
	# PROTECTED REGION ID(EMetaClass_eAllSuperTypes) ENABLED START
	$(getter eAllSuperTypes,
		# TODO inefficient.
		$(sort \
			$(foreach superType,$(get eSuperTypes),$(superType) \
				$(get superType->eAllSuperTypes))))
	# PROTECTED REGION END

	# Reference 'eFeatures' [0..*]: bidirectional, containment.
	$(property eFeatures... : EMetaFeature)
	$(field eFeatures... : EMetaFeature)
	$(getter eFeatures,
		$(get-field eFeatures))
	$(setter eFeatures,
		$(invoke __eSetContainment,eFeatures,$(suffix $1),eContainingClass))
	$(setter+ eFeatures,
		$(invoke __eAddContainment,eFeatures,$(suffix $1),eContainingClass))
	$(setter- eFeatures,
		$(invoke __eRemoveContainment,eFeatures,$(suffix $1),eContainingClass))

	# Reference 'eAllFeatures' [0..*]: derived, read-only.
	$(property eAllFeatures... : EMetaFeature)
	# PROTECTED REGION ID(EMetaClass_eAllFeatures) ENABLED START
	$(getter eAllFeatures,
		$(sort $(get eFeatures) \
			$(foreach superType,$(get eSuperTypes),
				$(get superType->eAllFeatures))))
	# PROTECTED REGION END

	# Reference 'eAttributes' [0..*]: derived, read-only.
	$(property eAttributes... : EMetaAttribute)
	# PROTECTED REGION ID(EMetaClass_eAttributes) ENABLED START
	$(getter eAttributes,
		$(invoke filterFeaturesByClass,$(get eFeatures),
			$(EModel_EMetaAttribute)))
	# PROTECTED REGION END

	# Reference 'eAllAttributes' [0..*]: derived, read-only.
	$(property eAllAttributes... : EMetaAttribute)
	# PROTECTED REGION ID(EMetaClass_eAllAttributes) ENABLED START
	$(getter eAllAttributes,
		$(invoke filterFeaturesByClass,$(get eAllFeatures),
			$(EModel_EMetaAttribute)))
	# PROTECTED REGION END

	# Reference 'eReferences' [0..*]: derived, read-only.
	$(property eReferences... : EMetaReference)
	# PROTECTED REGION ID(EMetaClass_eReferences) ENABLED START
	$(getter eReferences,
		$(invoke filterFeaturesByClass,$(get eFeatures),
			$(EModel_EMetaReference)))
	# PROTECTED REGION END

	# Reference 'eAllReferences' [0..*]: derived, read-only.
	$(property eAllReferences... : EMetaReference)
	# PROTECTED REGION ID(EMetaClass_eAllReferences) ENABLED START
	$(getter eAllReferences,
		$(invoke filterFeaturesByClass,$(get eAllFeatures),
			$(EModel_EMetaReference)))
	# PROTECTED REGION END

	# Reference 'eAllContainments' [0..*]: derived, read-only.
	$(property eAllContainments... : EMetaReference)
	# PROTECTED REGION ID(EMetaClass_eAllContainments) ENABLED START
	$(getter eAllContainments,
		$(foreach reference,$(get eAllReferences),
			$(if $(get reference->isContainment),$(reference))))
	# PROTECTED REGION END

	# 'isSuperTypeOf' operation.
	#   1. someClass : EMetaClass
	# PROTECTED REGION ID(EMetaClass_isSuperTypeOf) ENABLED START
	$(method isSuperTypeOf,
		$(filter $1 $(get 1->eAllSuperTypes),$(this)))
	# PROTECTED REGION END

	# 'isInstance' operation.
	#   1. object : EObject
	# PROTECTED REGION ID(EMetaClass_isInstance) ENABLED START
	$(method isInstance,
		$(invoke isSuperTypeOf,$(get 1->eMetaClass)))
	# PROTECTED REGION END

	# PROTECTED REGION ID(EMetaClass) ENABLED START

	# Params:
	#   1. List of features.
	#   2. Meta class.
	$(method filterFeaturesByClass,
		$(foreach feature,$1,
			$(if $(invoke 2->isInstance,$(feature)),
				$(feature)))
	)

	# PROTECTED REGION END
endef

# Implementation of 'EMetaPrimitive' model object.
define class-EMetaPrimitiveImpl
	$(super EMetaPrimitive)

	$(super EObjectImpl)
	$(super EMetaTypeImpl)

	$(getter eMetaClass,$(EModel_EMetaPrimitive))

	# PROTECTED REGION ID(EMetaPrimitive) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EMetaFeature' model object.
define class-EMetaFeatureImpl
	$(super EMetaFeature)

	$(super EObjectImpl)
	$(super ETypedImpl)

	$(getter eMetaClass,$(EModel_EMetaFeature))

	# Attribute 'changeable'.
	$(property-field isChangeable)

	# Attribute 'derived'.
	$(property-field isDerived)

	# Attribute 'instanceProperty'.
	$(property-field instanceProperty)

	# Reference 'eContainingClass' [0..1]: bidirectional, container, read-only.
	$(property eContainingClass : EMetaClass)
	$(getter eContainingClass,
		$(invoke __eGetContainer,eContainingClass))

	# PROTECTED REGION ID(EMetaFeature) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EMetaReference' model object.
define class-EMetaReferenceImpl
	$(super EMetaReference)

	$(super EObjectImpl)
	$(super EMetaFeatureImpl)

	$(getter eMetaClass,$(EModel_EMetaReference))

	# Attribute 'containment'.
	$(property-field isContainment)

	# Attribute 'container': derived, read-only.
	$(property isContainer)
	# PROTECTED REGION ID(EMetaReference_isContainer) ENABLED START
	$(getter isContainer,
		$(foreach opposite,$(get eOpposite),$(get opposite->isContainment)))
	# PROTECTED REGION END

	# Reference 'eOpposite' [0..1].
	$(property eOpposite : EMetaReference)
	$(field eOpposite : EMetaReference)
	$(getter eOpposite,
		$(get-field eOpposite))
	$(setter eOpposite,
		$(invoke __eSet,eOpposite,$(suffix $1),))

	# Reference 'eReferenceType' [1..1]: derived, read-only.
	$(property eReferenceType : EMetaClass)
	# PROTECTED REGION ID(EMetaReference_eReferenceType) ENABLED START
	$(getter eReferenceType,
		$(instance-of $(get eType),EMetaClass))
	# PROTECTED REGION END

	# PROTECTED REGION ID(EMetaReference) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EMetaAttribute' model object.
define class-EMetaAttributeImpl
	$(super EMetaAttribute)

	$(super EObjectImpl)
	$(super EMetaFeatureImpl)

	$(getter eMetaClass,$(EModel_EMetaAttribute))

	# Reference 'eAttributeType' [1..1]: derived, read-only.
	$(property eAttributeType : EMetaPrimitive)
	# PROTECTED REGION ID(EMetaAttribute_eAttributeType) ENABLED START
	$(getter eAttributeType,
		$(instance-of $(get eType),EMetaPrimitive))
	# PROTECTED REGION END

	# PROTECTED REGION ID(EMetaAttribute) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EMetaModel' model object.
define class-EMetaModelImpl
	$(super EMetaModel)

	$(super EObjectImpl)
	$(super ENamedObjectImpl)

	$(getter eMetaClass,$(EModel_EMetaModel))

	# Reference 'eTypes' [0..*]: bidirectional, containment.
	$(property eTypes... : EMetaType)
	$(field eTypes... : EMetaType)
	$(getter eTypes,
		$(get-field eTypes))
	$(setter eTypes,
		$(invoke __eSetContainment,eTypes,$(suffix $1),eMetaModel))
	$(setter+ eTypes,
		$(invoke __eAddContainment,eTypes,$(suffix $1),eMetaModel))
	$(setter- eTypes,
		$(invoke __eRemoveContainment,eTypes,$(suffix $1),eMetaModel))

	# PROTECTED REGION ID(EMetaModel) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'ETyped' model object.
define class-ETypedImpl
	$(super ETyped)

	$(super EObjectImpl)
	$(super ENamedObjectImpl)

	$(getter eMetaClass,$(EModel_ETyped))

	# Attribute 'many'.
	$(property-field isMany)

	# Reference 'eType' [0..1].
	$(property eType : EMetaType)
	$(field eType : EMetaType)
	$(getter eType,
		$(get-field eType))
	$(setter eType,
		$(invoke __eSet,eType,$(suffix $1),))

	# PROTECTED REGION ID(ETyped) ENABLED START
	# PROTECTED REGION END
endef

$(def_all)


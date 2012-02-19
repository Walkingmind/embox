# Generated by Xpand using M2Make template.

# Model implementation of 'EModel' package.

ifndef __model_model_mk
$(error \
	Do not include this file directly, include 'model.mk' instead!)
endif # __model_model_mk

include mk/model/eobject.mk

# Implementation of 'EObject' model object.
define class-EObjectImpl

	# Reference 'eMetaClass' [0..1]: derived, read-only.
	$(property eMetaClass : EMetaClass)
	# PROTECTED REGION ID(EObject_eMetaClass) ENABLED START
	$(getter eMetaClass,
		$($(get eMetaClassId)))
	# PROTECTED REGION END

	# Attribute 'eMetaClassId': derived, read-only.
	$(property eMetaClassId)
	# PROTECTED REGION ID(EObject_eMetaClassId) ENABLED START
	$(getter eMetaClassId,$(error Subclass must override eMetaClassId property))
	# PROTECTED REGION END

	# Attribute 'eResource': derived, read-only.
	$(property eResource)
	# PROTECTED REGION ID(EObject_eResource) ENABLED START
	$(getter eResource,
		$(get-field $(invoke eRootContainer).__eContainer))
	# PROTECTED REGION END

	# 'isAncestorOf' operation.
	#   1. object : EObject
	# PROTECTED REGION ID(EObject_isAncestorOf) ENABLED START
	$(method isAncestorOf,
		$(for container <- $(invoke 1->eContainer),
			$(or $(filter $(this),$(container)),
				$(invoke isAncestorOf,$(container)))))
	# PROTECTED REGION END

	# 'eContainer : EObject' operation.
	# PROTECTED REGION ID(EObject_eContainer) ENABLED START
	$(method eContainer,
		$(for c <- $(get-field __eContainer),
			$(if $(basename $c),$(suffix $c))))
	# PROTECTED REGION END

	# 'eContainerOfType : EObject' operation.
	#   1. someClass : EMetaClass
	# PROTECTED REGION ID(EObject_eContainerOfType) ENABLED START
	$(method eContainerOfType,
		$(for container <- $(invoke eContainer),
			$(if $(invoke 1->isInstance,$(container)),
				$(container),$(invoke container->eContainerOfType,$1))))
	# PROTECTED REGION END

	# 'eRootContainer : EObject' operation.
	# PROTECTED REGION ID(EObject_eRootContainer) ENABLED START
	$(method eRootContainer,
		$(or $(for container <- $(invoke eContainer),
				$(invoke container->eRootContainer)),
			$(this)))
	# PROTECTED REGION END

	# 'eContents... : EObject' operation.
	# PROTECTED REGION ID(EObject_eContents) ENABLED START
	$(method eContents,
		$(for metaReference <- $(get $(get eMetaClass).eAllContainments),
			$(get $(get metaReference->instanceProperty))))
	# PROTECTED REGION END

	# 'eContentsOfType... : EObject' operation.
	# PROTECTED REGION ID(EObject_eContentsOfType) ENABLED START
#	# TODO Uncomment and implement me.
#	$(method eContentsOfType,
#		$(error $0(): NIY))
	# PROTECTED REGION END

	# 'eAllContents... : EObject' operation.
	# PROTECTED REGION ID(EObject_eAllContents) ENABLED START
	$(method eAllContents,
		$(for child <- $(invoke eContents),
			$(child) $(invoke child->eAllContents)))
	# PROTECTED REGION END

	# 'eLinks... : ELink' operation.
	# PROTECTED REGION ID(EObject_eLinks) ENABLED START
	$(method eLinks,
		$(subst ./,,$(dir \
			$(for metaReference <- $(get $(get eMetaClass).eAllLinkables),
				$(get-field $(get-field metaReference->instanceProperty)))
		))
	)
	# PROTECTED REGION END

	# 'eResolvedLinks... : ELink' operation.
	# PROTECTED REGION ID(EObject_eResolvedLinks) ENABLED START
	$(method eResolvedLinks,
		$(for l <- $(invoke eLinks),
			$(if $(invoke l->eTarget),$l))
	)
	# PROTECTED REGION END

	# 'eUnresolvedLinks... : ELink' operation.
	# PROTECTED REGION ID(EObject_eUnresolvedLinks) ENABLED START
	$(method eUnresolvedLinks,
		$(subst ./,,$(filter %./,
			$(for metaReference <- $(get $(get eMetaClass).eAllLinkables),
				$(get-field $(get-field metaReference->instanceProperty)))
		))
	)
	# PROTECTED REGION END

	# PROTECTED REGION ID(EObject) ENABLED START

	# 'property/oppositeProperty.object'
	# '.object' for resource containment.
	$(field __eContainer : EObject)

	# 'property[.link].object'
	$(field __eOppositeRefs... : EObject)

	$(method __serialize_extra_objects,
		$(invoke eLinks) \
		$(suffix $(get-field __eOppositeRefs) \
			$(basename $(get-field __eOppositeRefs))))

	# PROTECTED REGION END
endef

# Implementation of 'ENamedObject' model object.
define class-ENamedObjectImpl
	$(eobject EModel_ENamedObject,
		ENamedObject,,)

	# Attribute 'name'.
	$(eobject-attribute EModel_ENamedObject_name,
		name,changeable)

	# Attribute 'qualifiedName': derived, read-only.
	$(property qualifiedName)
	# PROTECTED REGION ID(ENamedObject_qualifiedName) ENABLED START
	$(getter qualifiedName,
		$(for namedContainer <- $(invoke eContainerOfType,$(EModel_ENamedObject)),
			parentName <- $(get namedContainer->qualifiedName),
			$(parentName)$(if $(get name),.))$(get name))
	# PROTECTED REGION END

	# 'eInverseResolvedLinks... : ELink' operation.
	# PROTECTED REGION ID(ENamedObject_eInverseResolvedLinks) ENABLED START
	$(method eInverseResolvedLinks,
#		$(suffix $(basename \
#			$(get-field __eOppositeRefs) \
#			$(for metaReference <- $(get $(get eMetaClass).eAllCrossReferences),
#				$(get-field $(get-field metaReference->instanceProperty)))
#		))
	)
	# PROTECTED REGION END

	# PROTECTED REGION ID(ENamedObject) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'ELink' model object.
define class-ELinkImpl
	$(eobject EModel_ELink,
		ELink,ENamedObject,)

	# Reference 'eMetaReference' [0..1]: derived, read-only.
	$(property eMetaReference : EMetaReference)
	# PROTECTED REGION ID(ELink_eMetaReference) ENABLED START
	$(getter eMetaReference,
		$(value $(get eMetaReferenceId)))
	# PROTECTED REGION END

	# Attribute 'eMetaReferenceId': derived, read-only.
	$(property eMetaReferenceId)
	# PROTECTED REGION ID(ELink_eMetaReferenceId) ENABLED START
	$(getter eMetaReferenceId,
		$(basename $(get-field __eContainer)))
	# PROTECTED REGION END

	# 'eSource : EObject' operation.
	# PROTECTED REGION ID(ELink_eSource) ENABLED START
	$(method eSource,
		$(suffix $(get-field __eContainer)))
	# PROTECTED REGION END

	# 'eTarget : EObject' operation.
	# PROTECTED REGION ID(ELink_eTarget) ENABLED START
	$(field eTarget : EObject)
	$(method eTarget,
		$(get-field eTarget))
	# PROTECTED REGION END

	# 'resolve' operation.
	#   1. object : EObject
	# PROTECTED REGION ID(ELink_resolve) ENABLED START
	$(method resolve,
		$(call __eLinkSetTarget,$(suffix $1)))
	# PROTECTED REGION END

	# 'deresolve' operation.
	# PROTECTED REGION ID(ELink_deresolve) ENABLED START
#	# TODO Uncomment and implement me.
	$(method deresolve,
		$(error $0(): NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(ELink) ENABLED START

	$(getter eResource,
		$(for s <- $(invoke eSource),
			$(get s->eResource)))

	$(method eContainer,)

	# PROTECTED REGION END
endef

# Implementation of 'EMetaModel' model object.
define class-EMetaModelImpl
	$(eobject EModel_EMetaModel,
		EMetaModel,ENamedObject EFreezable,)

	# Reference 'eTypes' [0..*]: bidirectional, containment.
	$(eobject-reference EModel_EMetaModel_eTypes,
		eTypes,EMetaType,eMetaModel,changeable many containment)

	# PROTECTED REGION ID(EMetaModel) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EMetaType' model object.
define class-EMetaTypeImpl
	$(eobject EModel_EMetaType,
		EMetaType,ENamedObject EFreezable,abstract)

	# Attribute 'instanceClass'.
	$(eobject-attribute EModel_EMetaType_instanceClass,
		instanceClass,changeable)

	# Reference 'eMetaModel' [0..1]: bidirectional, container, read-only.
	$(eobject-reference EModel_EMetaType_eMetaModel,
		eMetaModel,EMetaModel,eTypes,container)

	# PROTECTED REGION ID(EMetaType) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EMetaClass' model object.
define class-EMetaClassImpl
	$(eobject EModel_EMetaClass,
		EMetaClass,EMetaType,)

	# Attribute 'abstract'.
	$(eobject-attribute EModel_EMetaClass_isAbstract,
		isAbstract,changeable)

	# Attribute 'interface'.
	$(eobject-attribute EModel_EMetaClass_isInterface,
		isInterface,changeable)

	# Reference 'eSuperTypes' [0..*].
	$(eobject-reference EModel_EMetaClass_eSuperTypes,
		eSuperTypes,EMetaClass,,changeable many)

	# Reference 'eAllSuperTypes' [0..*]: derived, read-only.
	$(property eAllSuperTypes... : EMetaClass)
	# PROTECTED REGION ID(EMetaClass_eAllSuperTypes) ENABLED START
	$(getter eAllSuperTypes,
		# Inefficient, but nobody actually cares because of freezing
		# the metamodel before using it.
		$(sort \
			$(foreach superType,$(get eSuperTypes),$(superType) \
				$(get superType->eAllSuperTypes))))
	# PROTECTED REGION END

	# Reference 'eFeatures' [0..*]: bidirectional, containment.
	$(eobject-reference EModel_EMetaClass_eFeatures,
		eFeatures,EMetaFeature,eContainingClass,changeable many containment)

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

	# Reference 'eAllCrossReferences' [0..*]: derived, read-only.
	$(property eAllCrossReferences... : EMetaReference)
	# PROTECTED REGION ID(EMetaClass_eAllCrossReferences) ENABLED START
	$(getter eAllCrossReferences,
		$(foreach reference,$(get eAllReferences),
			$(if $(get reference->isCrossReference),$(reference))))
	# PROTECTED REGION END

	# Reference 'eAllContainments' [0..*]: derived, read-only.
	$(property eAllContainments... : EMetaReference)
	# PROTECTED REGION ID(EMetaClass_eAllContainments) ENABLED START
	$(getter eAllContainments,
		$(foreach reference,$(get eAllReferences),
			$(if $(get reference->isContainment),$(reference))))
	# PROTECTED REGION END

	# Reference 'eAllLinkables' [0..*]: derived, read-only.
	$(property eAllLinkables... : EMetaReference)
	# PROTECTED REGION ID(EMetaClass_eAllLinkables) ENABLED START
	$(getter eAllLinkables,
		$(foreach reference,$(get eAllReferences),
			$(if $(get reference->isLinkable),$(reference))))
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
	$(eobject EModel_EMetaPrimitive,
		EMetaPrimitive,EMetaType,)

	# PROTECTED REGION ID(EMetaPrimitive) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EMetaFeature' model object.
define class-EMetaFeatureImpl
	$(eobject EModel_EMetaFeature,
		EMetaFeature,ETyped EFreezable,abstract)

	# Attribute 'changeable'.
	$(eobject-attribute EModel_EMetaFeature_isChangeable,
		isChangeable,changeable)

	# Attribute 'derived'.
	$(eobject-attribute EModel_EMetaFeature_isDerived,
		isDerived,changeable)

	# Attribute 'instanceProperty'.
	$(eobject-attribute EModel_EMetaFeature_instanceProperty,
		instanceProperty,changeable)

	# Reference 'eContainingClass' [0..1]: bidirectional, container, read-only.
	$(eobject-reference EModel_EMetaFeature_eContainingClass,
		eContainingClass,EMetaClass,eFeatures,container)

	# PROTECTED REGION ID(EMetaFeature) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EMetaReference' model object.
define class-EMetaReferenceImpl
	$(eobject EModel_EMetaReference,
		EMetaReference,EMetaFeature,)

	# Attribute 'containment'.
	$(eobject-attribute EModel_EMetaReference_isContainment,
		isContainment,changeable)

	# Attribute 'container': derived, read-only.
	$(property isContainer)
	# PROTECTED REGION ID(EMetaReference_isContainer) ENABLED START
	$(getter isContainer,
		$(for opposite <- $(get eOpposite),
			$(get opposite->isContainment)))
	# PROTECTED REGION END

	# Attribute 'linkable'.
	$(eobject-attribute EModel_EMetaReference_isLinkable,
		isLinkable,changeable)

	# Attribute 'crossReference': derived, read-only.
	$(property isCrossReference)
	# PROTECTED REGION ID(EMetaReference_isCrossReference) ENABLED START
	$(getter isCrossReference,
		$(not $(or $(get isContainment),
			$(for opposite <- $(get eOpposite),
				$(get opposite->isContainment)))))
	# PROTECTED REGION END

	# Reference 'eOpposite' [0..1].
	$(eobject-reference EModel_EMetaReference_eOpposite,
		eOpposite,EMetaReference,,changeable)

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
	$(eobject EModel_EMetaAttribute,
		EMetaAttribute,EMetaFeature,)

	# Reference 'eAttributeType' [1..1]: derived, read-only.
	$(property eAttributeType : EMetaPrimitive)
	# PROTECTED REGION ID(EMetaAttribute_eAttributeType) ENABLED START
	$(getter eAttributeType,
		$(instance-of $(get eType),EMetaPrimitive))
	# PROTECTED REGION END

	# PROTECTED REGION ID(EMetaAttribute) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'ETyped' model object.
define class-ETypedImpl
	$(eobject EModel_ETyped,
		ETyped,ENamedObject,abstract)

	# Attribute 'many'.
	$(eobject-attribute EModel_ETyped_isMany,
		isMany,changeable)

	# Reference 'eType' [0..1].
	$(eobject-reference EModel_ETyped_eType,
		eType,EMetaType,,changeable)

	# PROTECTED REGION ID(ETyped) ENABLED START
	# PROTECTED REGION END
endef

# Implementation of 'EFreezable' model object.
define class-EFreezableImpl
	$(eobject EModel_EFreezable,
		EFreezable,,abstract)

	# 'freeze' operation.
	# PROTECTED REGION ID(EFreezable_freeze) ENABLED START
	$(method freeze,
		$(silent-for f <- $(get $(get eMetaClass).eAllFeatures),
			$(if $(get f->isDerived),
				$(call var_assign_simple,
					$(this).$(get f->instanceProperty)_frozen,
					$(get $(get f->instanceProperty)))))
		$(call var_assign_simple,$(this),
			$(invoke getFrozenProxyClass)))
	# PROTECTED REGION END

	# PROTECTED REGION ID(EFreezable) ENABLED START

	# Return:
	#   Name of proxifier class.
	$(method getFrozenProxyClass,
		$(for proxyClass <- $(class $(this))FrozenProxy,
			$(or $(class-exists $(proxyClass)),
				$(call var_assign_recursive_sl,class-$(proxyClass),
					$(invoke generateFrozenProxyClassBody))
				$(call def,class-$(proxyClass))
				$(proxyClass)))
	)

	# Return:
	#   Code for the class being defined.
	$(method generateFrozenProxyClassBody,
		$$(super $(class $(this)))

		$(for f <- $(get $(get eMetaClass).eAllFeatures),
			$(if $(get f->isDerived),
				$$(field $(get f->instanceProperty)_frozen
					$(if $(get f->isMany),...)
					$(for t <- $(get f->eType),
						$(if $(invoke EModel_EMetaClass->isInstance,$t),
							: $(get t->name))))
				$$(getter $(get f->instanceProperty),
					$$(get-field $(get f->instanceProperty)_frozen))
			)
			$(for s <- \
				$(if $(get f->isChangeable),
					setter \
					$(if $(get f->isMany),
						setter+ setter-)),
				$$($s $(get f->instanceProperty),
					$$(error $$0($$1): Frozen))
			)
		)
	)
	# PROTECTED REGION END
endef

$(def_all)


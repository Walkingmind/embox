# Generated by Xpand using M2Make template.

# Model of 'EModel' package.

ifndef __model_model_mk
__model_model_mk := 1

include mk/model/model_impl.mk

#
# Model object 'EObject'.
#
# The following features and operations are defined:
#   - reference 'eMetaClass'
#   - attribute 'eMetaClassId'
#   - attribute 'eResource'
#   - operation 'isAncestorOf'
#   - operation 'eContainer'
#   - operation 'eContainerOfType'
#   - operation 'eRootContainer'
#   - operation 'eContents'
#   - operation 'eContentsOfType'
#   - operation 'eAllContents'
#   - operation 'eAllContentsOfType'
#   - operation 'eLinks'
#   - operation 'eResolvedLinks'
#   - operation 'eUnresolvedLinks'
#
define class-EObject

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

	# Method 'isAncestorOf'.
	#   1. object : EObject
	# PROTECTED REGION ID(EObject_isAncestorOf) ENABLED START
	$(method isAncestorOf,
		$(for container <- $(invoke 1->eContainer),
			$(or $(filter $(this),$(container)),
				$(invoke isAncestorOf,$(container)))))
	# PROTECTED REGION END

	# Method 'eContainer : EObject'.
	# PROTECTED REGION ID(EObject_eContainer) ENABLED START
	$(method eContainer : EObject,
		$(for c <- $(get-field __eContainer),
			$(if $(basename $c),$(suffix $c))))
	# PROTECTED REGION END

	# Method 'eContainerOfType : EObject'.
	#   1. someClass : EMetaClass
	# PROTECTED REGION ID(EObject_eContainerOfType) ENABLED START
	$(method eContainerOfType,
		$(for container <- $(invoke eContainer),
			$(if $(invoke 1->isInstance,$(container)),
				$(container),$(invoke container->eContainerOfType,$1))))
	# PROTECTED REGION END

	# Method 'eRootContainer : EObject'.
	# PROTECTED REGION ID(EObject_eRootContainer) ENABLED START
	$(method eRootContainer : EObject,
		$(or $(for container <- $(invoke eContainer),
				$(invoke container->eRootContainer)),
			$(this)))
	# PROTECTED REGION END

	# Method 'eContents... : EObject'.
	# PROTECTED REGION ID(EObject_eContents) ENABLED START
	$(method eContents... : EObject,
		$(for metaReference <- $(get $(get eMetaClass).eAllContainments),
			$(get $(get metaReference->instanceProperty))))
	# PROTECTED REGION END

	# Method 'eContentsOfType... : EObject'.
	#   1. someClass : EMetaClass
	# PROTECTED REGION ID(EObject_eContentsOfType) ENABLED START
	$(method eContentsOfType... : EObject,
		$(for metaReference <- $(get $(get eMetaClass).eAllContainments),
			$(if $(invoke 1->isSuperTypeOf,
					$(get metaReference->eReferenceType)),
				$(get $(get metaReference->instanceProperty)),
				$(for child <- $(get $(get metaReference->instanceProperty)),
					$(invoke child->eContentsOfType,$1))
			)
		)
	)
	# PROTECTED REGION END

	# Method 'eAllContents... : EObject'.
	# PROTECTED REGION ID(EObject_eAllContents) ENABLED START
	$(method eAllContents... : EObject,
		$(for child <- $(invoke eContents),
			$(child) $(invoke child->eAllContents)))
	# PROTECTED REGION END

	# Method 'eAllContentsOfType... : EObject'.
	#   1. someClass : EMetaClass
	# PROTECTED REGION ID(EObject_eAllContentsOfType) ENABLED START
	$(method eAllContentsOfType... : EObject,
		$(for child <- $(invoke eContentsOfType,$1),
			$(child) $(invoke child->eAllContentsOfType,$1)))
	# PROTECTED REGION END

	# Method 'eLinks... : ELink'.
	# PROTECTED REGION ID(EObject_eLinks) ENABLED START
	$(method eLinks... : ELink,
		$(subst ./,,$(dir \
			$(for metaReference <- $(get $(get eMetaClass).eAllLinkables),
				$(get-field $(get-field metaReference->instanceProperty)))
		))
	)
	# PROTECTED REGION END

	# Method 'eResolvedLinks... : ELink'.
	# PROTECTED REGION ID(EObject_eResolvedLinks) ENABLED START
	$(method eResolvedLinks... : ELink,
		$(for l <- $(invoke eLinks),
			$(if $(invoke l->eTarget),$l))
	)
	# PROTECTED REGION END

	# Method 'eUnresolvedLinks... : ELink'.
	# PROTECTED REGION ID(EObject_eUnresolvedLinks) ENABLED START
	$(method eUnresolvedLinks... : ELink,
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

#
# Model object 'ENamedObject'.
#
# The following features and operations are defined:
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-ENamedObject
	# Extends 'EObject' class (implicitly).
	$(eobject EModel_ENamedObject,
		ENamedObject,,)

	# Property 'name'.
	$(eobject-attribute EModel_ENamedObject_name,
		name,changeable)

	# Attribute 'qualifiedName': derived, read-only.
	$(property qualifiedName)
	# PROTECTED REGION ID(ENamedObject_qualifiedName) ENABLED START
	$(getter qualifiedName,
		$(for namedContainer <- $(invoke eContainerOfType,$(EModel_ENamedObject)),
			parentName <- $(get namedContainer->qualifiedName),
			$(parentName)$(if $(get-field name),.))$(get-field name))
	# PROTECTED REGION END

	# Property 'origin'.
	$(eobject-attribute EModel_ENamedObject_origin,
		origin,changeable)

	# Method 'eInverseResolvedLinks... : ELink'.
	# PROTECTED REGION ID(ENamedObject_eInverseResolvedLinks) ENABLED START
	$(method eInverseResolvedLinks,
		$(error NIY)
#		$(suffix $(basename \
#			$(get-field __eOppositeRefs) \
#			$(for metaReference <- $(get $(get eMetaClass).eAllCrossReferences),
#				$(get-field $(get-field metaReference->instanceProperty)))
#		))
	)
	# PROTECTED REGION END

	# PROTECTED REGION ID(ENamedObject) ENABLED START
	$(setter name,
		$(assert $(if $1,$(and $(singleword [$1]),$(filter-out .% %.,$1)),ok),
			Invalid name: '$1')
		$(set-field name,$1))
	# PROTECTED REGION END
endef

#
# Model object 'ELink'.
#
# The following features and operations are defined:
#   - reference 'eMetaReference'
#   - attribute 'eMetaReferenceId'
#   - attribute 'eResource'
#   - attribute 'name'
#   - attribute 'origin'
#   - operation 'eSource'
#   - operation 'eTarget'
#   - operation 'resolve'
#   - operation 'deresolve'
#
define class-ELink

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
		$(basename $(get-field eSource)))
	# PROTECTED REGION END

	# Attribute 'eResource': derived, read-only.
	$(property eResource)
	# PROTECTED REGION ID(ELink_eResource) ENABLED START
	$(getter eResource,
		$(for s <- $(invoke eSource),
			$(get s->eResource)))
	# PROTECTED REGION END

	# Property 'name'.
	$(eobject-attribute EModel_ELink_name,
		name,changeable)

	# Property 'origin'.
	$(eobject-attribute EModel_ELink_origin,
		origin,changeable)

	# Method 'eSource : EObject'.
	# PROTECTED REGION ID(ELink_eSource) ENABLED START
	$(method eSource : EObject,
		$(suffix $(get-field eSource)))
	# PROTECTED REGION END

	# Method 'eTarget : EObject'.
	# PROTECTED REGION ID(ELink_eTarget) ENABLED START
	$(method eTarget : EObject,
		$(get-field eTarget))
	# PROTECTED REGION END

	# Method 'resolve'.
	#   1. object : EObject
	# PROTECTED REGION ID(ELink_resolve) ENABLED START
	$(method resolve,
		$(call __eLinkSetTarget,$(suffix $1)))
	# PROTECTED REGION END

	# Method 'deresolve'.
	# PROTECTED REGION ID(ELink_deresolve) ENABLED START
#	# TODO Uncomment and implement me.
	$(method deresolve,
		$(error $0(): NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(ELink) ENABLED START
	
	# 'metaRefernceId.object'
	$(field eSource : EObject)

	# '.object'
	$(field eTarget : EObject)

	# 'property[.link].object'
	$(field __eOppositeRefs... : EObject)

	$(method eContainer : EObject,)

	# Constructor:
	#   As a special exception, ELink takes two optional constructor arguments:
	#     1. (optional) Name.
	#     2. (optional) Origin.
	$(if $(value 1),
		$(set name,$1))
	$(if $(value 2),
		$(set origin,$2))

	# PROTECTED REGION END
endef

#
# Model object 'EMetaModel'.
#
# The following features are defined:
#   - reference 'eTypes'
#
# The following operations are inherited from 'EFreezable':
#   - operation 'freeze'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-EMetaModel
	# Extends 'ENamedObject', 'EFreezable' classes.
	$(eobject EModel_EMetaModel,
		EMetaModel,ENamedObject EFreezable,)

	# Property 'eTypes... : EMetaType'.
	$(eobject-reference EModel_EMetaModel_eTypes,
		eTypes,EMetaType,eMetaModel,changeable many containment)

	# PROTECTED REGION ID(EMetaModel) ENABLED START
	# PROTECTED REGION END
endef

#
# Model object 'EMetaType'.
#
# The following features are defined:
#   - attribute 'instanceClass'
#   - reference 'eMetaModel'
#
# The following operations are inherited from 'EFreezable':
#   - operation 'freeze'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-EMetaType # abstract
	# Extends 'ENamedObject', 'EFreezable' classes.
	$(eobject EModel_EMetaType,
		EMetaType,ENamedObject EFreezable,abstract)

	# Property 'instanceClass'.
	$(eobject-attribute EModel_EMetaType_instanceClass,
		instanceClass,changeable)

	# Property 'eMetaModel : EMetaModel' (read-only).
	$(eobject-reference EModel_EMetaType_eMetaModel,
		eMetaModel,EMetaModel,eTypes,container)

	# PROTECTED REGION ID(EMetaType) ENABLED START
	# PROTECTED REGION END
endef

#
# Model object 'EMetaClass'.
#
# The following features and operations are defined:
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
#   - reference 'eAllCrossReferences'
#   - reference 'eAllContainments'
#   - reference 'eAllLinkables'
#   - operation 'isSuperTypeOf'
#   - operation 'isInstance'
#
# The following features are inherited from 'EMetaType':
#   - attribute 'instanceClass'
#   - reference 'eMetaModel'
#
# The following operations are inherited from 'EFreezable':
#   - operation 'freeze'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-EMetaClass
	# Extends 'EMetaType' class.
	$(eobject EModel_EMetaClass,
		EMetaClass,EMetaType,)

	# Property 'isAbstract'.
	$(eobject-attribute EModel_EMetaClass_isAbstract,
		isAbstract,changeable)

	# Property 'isInterface'.
	$(eobject-attribute EModel_EMetaClass_isInterface,
		isInterface,changeable)

	# Property 'eSuperTypes... : EMetaClass'.
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

	# Property 'eFeatures... : EMetaFeature'.
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

	# Method 'isSuperTypeOf'.
	#   1. someClass : EMetaClass
	# PROTECTED REGION ID(EMetaClass_isSuperTypeOf) ENABLED START
	$(method isSuperTypeOf,
		$(filter $(this),$1 $(get 1->eAllSuperTypes)))
	# PROTECTED REGION END

	# Method 'isInstance'.
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

#
# Model object 'EMetaPrimitive'.
#
# No features or operations defined.
#
# The following features are inherited from 'EMetaType':
#   - attribute 'instanceClass'
#   - reference 'eMetaModel'
#
# The following operations are inherited from 'EFreezable':
#   - operation 'freeze'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-EMetaPrimitive
	# Extends 'EMetaType' class.
	$(eobject EModel_EMetaPrimitive,
		EMetaPrimitive,EMetaType,)

	# PROTECTED REGION ID(EMetaPrimitive) ENABLED START
	# PROTECTED REGION END
endef

#
# Model object 'EMetaFeature'.
#
# The following features are defined:
#   - attribute 'changeable'
#   - attribute 'derived'
#   - attribute 'instanceProperty'
#   - reference 'eContainingClass'
#
# The following operations are inherited from 'EFreezable':
#   - operation 'freeze'
#
# The following features are inherited from 'ETyped':
#   - attribute 'many'
#   - reference 'eType'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-EMetaFeature # abstract
	# Extends 'ETyped', 'EFreezable' classes.
	$(eobject EModel_EMetaFeature,
		EMetaFeature,ETyped EFreezable,abstract)

	# Property 'isChangeable'.
	$(eobject-attribute EModel_EMetaFeature_isChangeable,
		isChangeable,changeable)

	# Property 'isDerived'.
	$(eobject-attribute EModel_EMetaFeature_isDerived,
		isDerived,changeable)

	# Property 'instanceProperty'.
	$(eobject-attribute EModel_EMetaFeature_instanceProperty,
		instanceProperty,changeable)

	# Property 'eContainingClass : EMetaClass' (read-only).
	$(eobject-reference EModel_EMetaFeature_eContainingClass,
		eContainingClass,EMetaClass,eFeatures,container)

	# PROTECTED REGION ID(EMetaFeature) ENABLED START
	# PROTECTED REGION END
endef

#
# Model object 'EMetaReference'.
#
# The following features are defined:
#   - attribute 'containment'
#   - attribute 'container'
#   - attribute 'linkable'
#   - attribute 'crossReference'
#   - reference 'eOpposite'
#   - reference 'eReferenceType'
#
# The following features are inherited from 'EMetaFeature':
#   - attribute 'changeable'
#   - attribute 'derived'
#   - attribute 'instanceProperty'
#   - reference 'eContainingClass'
#
# The following operations are inherited from 'EFreezable':
#   - operation 'freeze'
#
# The following features are inherited from 'ETyped':
#   - attribute 'many'
#   - reference 'eType'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-EMetaReference
	# Extends 'EMetaFeature' class.
	$(eobject EModel_EMetaReference,
		EMetaReference,EMetaFeature,)

	# Property 'isContainment'.
	$(eobject-attribute EModel_EMetaReference_isContainment,
		isContainment,changeable)

	# Attribute 'container': derived, read-only.
	$(property isContainer)
	# PROTECTED REGION ID(EMetaReference_isContainer) ENABLED START
	$(getter isContainer,
		$(for opposite <- $(get eOpposite),
			$(get opposite->isContainment)))
	# PROTECTED REGION END

	# Property 'isLinkable'.
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

	# Property 'eOpposite : EMetaReference'.
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

#
# Model object 'EMetaAttribute'.
#
# The following features are defined:
#   - reference 'eAttributeType'
#
# The following features are inherited from 'EMetaFeature':
#   - attribute 'changeable'
#   - attribute 'derived'
#   - attribute 'instanceProperty'
#   - reference 'eContainingClass'
#
# The following operations are inherited from 'EFreezable':
#   - operation 'freeze'
#
# The following features are inherited from 'ETyped':
#   - attribute 'many'
#   - reference 'eType'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-EMetaAttribute
	# Extends 'EMetaFeature' class.
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

#
# Model object 'ETyped'.
#
# The following features are defined:
#   - attribute 'many'
#   - reference 'eType'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-ETyped # abstract
	# Extends 'ENamedObject' class.
	$(eobject EModel_ETyped,
		ETyped,ENamedObject,abstract)

	# Property 'isMany'.
	$(eobject-attribute EModel_ETyped_isMany,
		isMany,changeable)

	# Property 'eType : EMetaType'.
	$(eobject-reference EModel_ETyped_eType,
		eType,EMetaType,,changeable)

	# PROTECTED REGION ID(ETyped) ENABLED START
	# PROTECTED REGION END
endef

#
# Model object 'EFreezable'.
#
# The following operations are defined:
#   - operation 'freeze'
#
define class-EFreezable # abstract
	# Extends 'EObject' class (implicitly).
	$(eobject EModel_EFreezable,
		EFreezable,,abstract)

	# Method 'freeze'.
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

endif # __model_model_mk


# $Id$
#
# Builtins for generated implementations of modeled objects
# and runtime support for managing object references.
#
#   Date: Feb 17, 2012
# Author: Eldar Abusalimov
#

ifndef __model_eobject_mk
__model_eobject_mk := 1

# Param:
#   1. Meta class ID.
#   2. Instance class name.
#   3. Super classes.
#   4. Flags, which may contain:
#        abstract, interface
define builtin_func-eobject
	$(call __def_do,

		# Extends implementations of each super class.
		$(foreach s,$(or $3,EObject),
			$$(super $s))

		$$(getter eMetaClassId,
			$1)
		# A little optimization.
		$$(getter eMetaClass,
			$$($1))
	)
endef

# Param:
#   1. Meta feature ID.
#   2. Instance property name.
#   3. Flags, which may contain:
#        changeable many
define builtin_func-eobject-attribute
	$(call __def_do,
		$(if $(filter changeable,$3),
			# Changeable attributes are just property-fields.
			$$(property-field $2$(if $(filter many,$3),...)),

			# Otherwise, only getter should be defined.
			$$(property $2$(if $(filter many,$3),...))
			$$(field $2$(if $(filter many,$3),...))
			$$(getter $2,
				$$(get-field $2))
		)
	)
endef

# Param:
#   1. Meta feature ID.
#   2. Instance property name.
#   3. Reference class.
#   4. Opposite property name (if any).
#   5. Flags, which may contain:
#        changeable many containment container linkable
define builtin_func-eobject-reference
	$(call __def_do,

		# Declare a propery (though it has already been declared in API class).
		$$(property $2$(if $(filter many,$5),...) : $3)

		# Generate getter.
		$(if $(filter contain%,$5),
			# Container and containment references share the same field.
			$$(getter $2,
				$$(suffix $$(filter $2/%,$$(get-field \
					$(if $(filter container,$5),__eContainer,__eContents))))),

			# Otherwise define a new field.
			# Cross references are stored in raw fields.
			$$(field $2$(if $(filter many,$5),...))
			# There is also a custom serializer for such fields.
			$$(method __serialize_field-$2,
				$$(call __eObjectSerializeCrossReference,$2,$1))

			$$(getter $2,
				# Linkable references also support on-demand linkage.
				$(if $(filter linkable,$5),
					$$(call __eObjectResolveLinks,
						$$(filter %./,$$(get-field $2)),$1))
				# Getting suffix is mandatory here!
				$$(suffix $$(get-field $2)))
		)

		$(for fn_suffix <-
			$(if $(filter containment,$5),Containment,
				$(if $(filter container,$5),Container,
					$(if $4,Bidirectional,Unidirectional))),
			property <- $2,

			$(__eobject_ref_setter)

			$(if $(filter linkable,$5),
				$(for property <- $(property)_link$(if $(filter many,$5),s),
					fn_suffix <- $(fn_suffix)_link,

					# Declare a propery for links.
					$$(property $(property)$(if $(filter many,$5),...) : $3)

					$$(getter $(property),
						$$(subst ./,,$$(dir $$(get-field $2))))

					$(__eobject_ref_setter)
				)
			)
		)
	)
endef

# Param:
#   Same as to 'eobject-reference' builtin.
# Context:
#   'property'
#   'fn_suffix'
define __eobject_ref_setter
	$(if $(filter changeable,$5),
		$$(setter $(property),
			$(if $(not $(filter many,$5)),
				$$(assert $$(not $$2),
					Set '$$2' invoked for a non-list EReference $1)
			)
			$$(call __eObjectSet$(fn_suffix)$$2,$2,$$(suffix $$1),$4,$1))
	)
endef

# Params:
#   1. Property name.
#   2. Meta reference ID.
define __eObjectSerializeCrossReference
	$(assert $(not $(or $(get $2->isContainment),$(get $2->isContainer))),
		$0: Can't handle non-cross references)
	# '.link./.target'
	# '.link./'
	#        '.target'
	# '.oplink.target'
	$(for r <- $(get-field $1),
		$(for l <- $(subst ./,,$(dir $r)),# Link.
			$($l.__serial_id__)./)
		$(for t <- $(suffix $r),# Target.
			$(for l <- $(basename $(notdir $r)),# Opposite link.
				$($l.__serial_id__))
			$($t.__serial_id__)))
endef

# Params:
#   1. Property name.
#   2. New container.
#   3. Containment property in the container.
define __eObjectSetContainer
	$(assert $(not $(multiword $2)))

	$(for oldContainer <- $(get-field __eContainer),
		$(if $(basename $(oldContainer)),
			# Regular containment.
			$(set-field- oldContainer->__eContents,
				$(notdir $(basename $(oldContainer)))/$(this)),
			# Resource containment.
			$(set oldContainer->contentsRoot,)
		)
	)

	$(set-field __eContainer,$1/$3$2)

	$(for newContainer <- $2,
		$(set-field+ newContainer->__eContents,$3/$(this)))
endef

# Params:
#   1. Property name.
#   2. What to add.
#   3. Opposite property.
define __eObjectSetContainment+
	$(silent-for this <- $2,
		# XXX Using '__this'. -- Eldar
		$(call __eObjectSetContainer,$3,$(__this),$1))
endef

# Params:
#   1. Property name.
#   2. What to add.
define __eObjectSetUnidirectional+
	$(set-field+ $1,$2)
endef

# Params:
#   1. Property name.
#   2. What to add.
#   3. Opposite property.
define __eObjectSetBidirectional+
	$(set-field+ $1,$2)
	$(silent-for e <- $2,
		$(set-field+ e->$3,$(this)))
endef

# Params:
#   1. Property name.
#   2. What to remove.
#   3. Opposite property.
define __eObjectSetContainment-
	$(foreach ,$2,$(warning $0: NIY))
endef

# Params:
#   1. Property name.
#   2. What to remove.
define __eObjectSetUnidirectional-
	$(foreach ,$2,$(warning $0: NIY))
endef

# Params:
#   1. Property name.
#   2. What to remove.
#   3. Opposite property.
define __eObjectSetBidirectional-
	$(foreach ,$2,$(warning $0: NIY))
endef

# Params:
#   1. Property name.
#   2. New value.
#   3. Opposite property.
define __eObjectSetContainment
	$(call __eObjectSetContainment-,$1,$(get $1),$3)
	$(call __eObjectSetContainment+,$1,$2,$3)
endef

# Params:
#   1. Property name.
#   2. New value.
define __eObjectSetUnidirectional
	$(set-field $1,)#TODO Deresolve of link before removing not implemented
	$(call __eObjectSetUnidirectional+,$1,$2)
endef

# Params:
#   1. Property name.
#   2. New value.
#   3. Opposite property.
define __eObjectSetBidirectional
	$(call __eObjectSetBidirectional-,$1,$(get-field $1),$3)
	$(call __eObjectSetBidirectional+,$1,$2,$3)
endef

# Params:
#   1. Property name.
#   2. What to add.
#   3. Empty.
#   4. Meta reference ID.
define __eObjectSetUnidirectional_link+
	$(set-field+ $1,
		$(for link <- $2,
			$(assert $(not $(get-field link->eSource)),
				Link $(link) has already got a source)
			$(set-field link->eSource,$4$(this))
			# 'link./target' for resolved links, 'link./' otherwise.
			$(link)./$(get-field link->eTarget))
	)
endef

# Params:
#   1. Property name.
#   2. What to add.
#   3. Opposite property.
#   4. Meta reference ID.
define __eObjectSetBidirectional_link+
	$(set-field+ $1,
		$(for link <- $2,
			$(assert $(not $(get-field link->eSource)),
				Link $(link) has already got a source)
			$(set-field link->eSource,$4$(this))
			# 'link./target' for resolved links, 'link./' otherwise.
			$(link)./$(for target <- $(get-field link->eTarget),
						$(set-field+ target->$3,$(link)$(this))
						$(target)))
	)
endef

# Params:
#   1. Property name.
#   2. What to remove.
define __eObjectSetUnidirectional_link-
	$(foreach ,$2,$(warning $0: NIY))
endef

# Params:
#   1. Property name.
#   2. What to remove.
#   3. Opposite property.
define __eObjectSetBidirectional_link-
	$(foreach ,$2,$(warning $0: NIY))
endef

# Params:
#   1. Property name.
#   2. New value.
#   3. Empty.
#   4. Meta reference ID.
define __eObjectSetUnidirectional_link
	$(call __eObjectSetUnidirectional_link-,$1,$(get-field $1))
	$(call __eObjectSetUnidirectional_link+,$1,$2,,$4)
endef

# Params:
#   1. Property name.
#   2. New value.
#   3. Opposite property.
#   4. Meta reference ID.
define __eObjectSetBidirectional_link
	$(call __eObjectSetBidirectional_link-,$1,$(get-field $1),$3)
	$(call __eObjectSetBidirectional_link+,$1,$2,$3,$4)
endef

# Params:
#   1. List of unresolved (at the call time) references with './' at their ends.
#   2. Meta reference ID.
define __eObjectResolveLinks
	$(and $1,$(for resource <- $(get this->eResource),
				resourceSet <- $(get resource->resourceSet),
#		$(for link <- $(subst ./,,$1),
#			$(warning on-demand linkage: \
#				[$(get link->eMetaReference)] '$(get link->name)'))
		$(invoke $(get resourceSet->linker).resolveLinksGroup,
			$(subst ./,,$1),$($2))
	),)
endef

# Params:
#   1. New value of 'eTarget' property of this link.
define __eLinkSetTarget
	$(assert $(not $(multiword $1)))
	$(assert $(invoke eSource),
		Can't set a target on the link with no source)

	$(for oldTarget <- $(get-field eTarget),
		$(warning $0: NIY; (old target: '$(oldTarget)')))

	$(set-field eTarget,$1)

	$(for newTarget <- $1,
		source <- $(invoke eSource),
		metaReference <- $(get eMetaReference),
		referenceProperty <- $(get metaReference->instanceProperty),

		$(set-field source->$(referenceProperty),
			$(patsubst $(this)./,$(this)./$(newTarget),
				$(get-field source->$(referenceProperty))))

		$(for opposite <- $(get metaReference->eOpposite),
			$(set-field+ newTarget->$(get opposite->instanceProperty),
				$(this)$(source)))
	)
endef

$(def_all)

endif # __model_eobject_mk


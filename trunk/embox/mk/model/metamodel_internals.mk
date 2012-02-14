# $Id: $
#
# Metamodel internal utils.
#
#   Date: Jan 20, 2011
# Author: Eldar Abusalimov
#

ifndef __model_metamodel_internals_mk
__model_metamodel_internals_mk := 1

include mk/model/factory.mk

#
# Meta object instantiation.
#

# Params:
#   1. Meta model ID (unused).
define eMetaModelCreate
	$(for model <- $(invoke eModelFactory->createEMetaModel),
		# Do nothing special.
		$(model))
endef

# Params:
#   1. Meta model.
#   2. Meta class ID (unused).
define eMetaClassCreate
	$(for class <- $(invoke eModelFactory->createEMetaClass),
		$(set+ 1->eTypes,$(class))
		$(class))
endef

# Params:
#   1. Meta class.
#   2. Meta feature ID (unused).
define eMetaAttributeCreate
	$(for feature <- $(invoke eModelFactory->createEMetaAttribute),
		$(set+ 1->eFeatures,$(feature))
		$(feature))
endef

# Params:
#   1. Meta class.
#   2. Meta feature ID (unused).
define eMetaReferenceCreate
	$(for feature <- $(invoke eModelFactory->createEMetaReference),
		$(set+ 1->eFeatures,$(feature))
		$(feature))
endef

#
# Objects initialization.
#

# Params:
#   1. Meta model.
#   2. Name.
define eMetaModelInit
	$(set 1->name,$2)
endef

# Params:
#   1. Meta class.
#   2. Name.
#   3. Super types...
#   4. Flags...
define eMetaClassInit
	$(set 1->name,$2)
	$(set 1->eSuperTypes,$3)
	$(set 1->isAbstract,$(filter abstract,$4))
	$(set 1->isInterface,$(filter interface,$4))
endef

# Params:
#   1. Meta attribute.
#   2. Name.
#   3. Flags...
define eMetaAttributeInit
	$(call __eMetaFeatureInit,$1,$2,$3)
endef

# Params:
#   1. Meta reference.
#   2. Name.
#   3. Referenced class.
#   4. Opposite reference (if any).
#   5. Flags...
define eMetaReferenceInit
	$(call __eMetaFeatureInit,$1,$2,$5)
	$(set 1->eType,$3)
	$(set 1->eOpposite,$4)
	$(set 1->isContainment,$(filter containment,$5))
endef

# Params:
#   1. Meta feature.
#   2. Name.
#   3. Flags...
define __eMetaFeatureInit
	$(set 1->name,$2)
	$(set 1->isChangeable,$(filter changeable,$3))
	$(set 1->isDerived,$(filter derived,$3))
endef

#
# Binding to native class/properties.
#

# Params:
#   1. Meta class.
#   2. Instance class name.
define eMetaClassBind
	$(assert $(class-exists $2),
		Can't bind meta type '$(get 1->name)' to undefined class '$2')
	$(set 1->instanceClass,$2)
endef

# Params:
#   1. Meta feature.
#   2. Instance property name.
define eMetaFeatureBind
	$(assert $(class-has-property \
			$(get $(get 1->eContainingClass).instanceClass),$2),
		Can't bind meta feature '$(get 1->name)' to undefined property '$2'
		of class '$(get $(get 1->eContainingClass).instanceClass)')
	$(set 1->instanceProperty,$2)
endef

# Params:
#   1. Meta model.
define eMetaModelFreeze
	$(for metaModel <- $1,
		$(for metaType <- $(get metaModel->eTypes),
			$(for metaFeature <- $(get metaType->eFeatures),
				$(invoke metaFeature->freeze))
			$(invoke metaType->freeze))
		$(invoke metaModel->freeze))
endef

$(def_all)

endif # __model_metamodel_internals_mk


# Generated by Xpand using M2Make template.

# Model of 'myFile' package.

ifndef __mybuild_myfile_model_mk
__mybuild_myfile_model_mk := $(lastword $(MAKEFILE_LIST))

include $(dir $(__mybuild_myfile_model_mk))myfile-model_impl.mk


#
# Model object 'Model'.
#
# The following features are available:
#   - reference 'package'
#   - reference 'imports'
#   - reference 'entities'
#
# To instantiate this class use 'MyFileFactory.createModel'.
define class-Model
	$(super Node)

	# Returns the value of the 'package' containment reference.
	$(method getPackage)
	# Sets the value of the 'package' containment reference.
	#   1. New value.
	$(method setPackage)

	# Returns the value of the 'imports' containment reference.
	$(method getImports)
	# Sets the value of the 'imports' containment reference.
	#   1. New value.
	$(method setImports)
	# Adds new elements to the 'imports' containment reference.
	#   1. Elements to add.
	$(method addImports)
	# Removes elements from the 'imports' containment reference.
	#   1. Elements to remove.
	$(method removeImports)
	# Removes all elements from the 'imports' containment reference.
	$(method clearImports)

	# Returns the value of the 'entities' containment reference.
	#   1. Optional subtype of Entity to filter on:
	#       'Interface'
	#       'Module'
	$(method getEntities)
	# Sets the value of the 'entities' containment reference.
	#   1. New value.
	$(method setEntities)
	# Adds new elements to the 'entities' containment reference.
	#   1. Elements to add.
	$(method addEntities)
	# Removes elements from the 'entities' containment reference.
	#   1. Elements to remove.
	$(method removeEntities)
	# Removes all elements from the 'entities' containment reference.
	$(method clearEntities)
endef

#
# Model object 'Package'.
#
# The following features are available:
#   - attribute 'name'
#
# To instantiate this class use 'MyFileFactory.createPackage'.
define class-Package
	$(super Node)

	# Returns the value of the 'name' attribute.
	$(method getName)
	# Sets the value of the 'name' attribute.
	#   1. New value.
	$(method setName)
endef

#
# Model object 'Import'.
#
# The following features are available:
#   - attribute 'importedNamespace'
#
# To instantiate this class use 'MyFileFactory.createImport'.
define class-Import
	$(super Node)

	# Returns the value of the 'importedNamespace' attribute.
	$(method getImportedNamespace)
	# Sets the value of the 'importedNamespace' attribute.
	#   1. New value.
	$(method setImportedNamespace)
endef

#
# Model object 'Entity'.
#
# The following features are available:
#   - attribute 'name'
#
# To instantiate this class use 'MyFileFactory.createEntity'.
define class-Entity
	$(super Node)

	# Returns the value of the 'name' attribute.
	$(method getName)
	# Sets the value of the 'name' attribute.
	#   1. New value.
	$(method setName)
endef

#
# Model object 'Interface'.
#
# The following features are available:
#   - reference 'superType'
#   - reference 'features'
#   - reference 'subTypes'
#
# To instantiate this class use 'MyFileFactory.createInterface'.
define class-Interface
	$(super Node)
	$(super Entity)

	# Returns the value of the 'superType' reference.
	$(method getSuperType)
	# Sets the value of the 'superType' reference.
	#   1. New value.
	$(method setSuperType)

	# Returns the value of the 'features' containment reference.
	$(method getFeatures)
	# Sets the value of the 'features' containment reference.
	#   1. New value.
	$(method setFeatures)
	# Adds new elements to the 'features' containment reference.
	#   1. Elements to add.
	$(method addFeatures)
	# Removes elements from the 'features' containment reference.
	#   1. Elements to remove.
	$(method removeFeatures)
	# Removes all elements from the 'features' containment reference.
	$(method clearFeatures)

	# Returns the value of the 'subTypes' reference.
	$(method getSubTypes)
	# Sets the value of the 'subTypes' reference.
	#   1. New value.
	$(method setSubTypes)
	# Adds new elements to the 'subTypes' reference.
	#   1. Elements to add.
	$(method addSubTypes)
	# Removes elements from the 'subTypes' reference.
	#   1. Elements to remove.
	$(method removeSubTypes)
	# Removes all elements from the 'subTypes' reference.
	$(method clearSubTypes)
endef

#
# Model object 'Feature'.
#
# The following features are available:
#   - attribute 'name'
#   - reference 'superType'
#   - reference 'interface'
#   - reference 'providedBy'
#   - reference 'requiredBy'
#   - reference 'subTypes'
#
# To instantiate this class use 'MyFileFactory.createFeature'.
define class-Feature
	$(super Node)

	# Returns the value of the 'name' attribute.
	$(method getName)
	# Sets the value of the 'name' attribute.
	#   1. New value.
	$(method setName)

	# Returns the value of the 'superType' reference.
	$(method getSuperType)
	# Sets the value of the 'superType' reference.
	#   1. New value.
	$(method setSuperType)

	# Returns the value of the 'interface' reference.
	$(method getInterface)
	# Sets the value of the 'interface' reference.
	#   1. New value.
	$(method setInterface)

	# Returns the value of the 'providedBy' reference.
	$(method getProvidedBy)
	# Sets the value of the 'providedBy' reference.
	#   1. New value.
	$(method setProvidedBy)
	# Adds new elements to the 'providedBy' reference.
	#   1. Elements to add.
	$(method addProvidedBy)
	# Removes elements from the 'providedBy' reference.
	#   1. Elements to remove.
	$(method removeProvidedBy)
	# Removes all elements from the 'providedBy' reference.
	$(method clearProvidedBy)

	# Returns the value of the 'requiredBy' reference.
	$(method getRequiredBy)
	# Sets the value of the 'requiredBy' reference.
	#   1. New value.
	$(method setRequiredBy)
	# Adds new elements to the 'requiredBy' reference.
	#   1. Elements to add.
	$(method addRequiredBy)
	# Removes elements from the 'requiredBy' reference.
	#   1. Elements to remove.
	$(method removeRequiredBy)
	# Removes all elements from the 'requiredBy' reference.
	$(method clearRequiredBy)

	# Returns the value of the 'subTypes' reference.
	$(method getSubTypes)
	# Sets the value of the 'subTypes' reference.
	#   1. New value.
	$(method setSubTypes)
	# Adds new elements to the 'subTypes' reference.
	#   1. Elements to add.
	$(method addSubTypes)
	# Removes elements from the 'subTypes' reference.
	#   1. Elements to remove.
	$(method removeSubTypes)
	# Removes all elements from the 'subTypes' reference.
	$(method clearSubTypes)
endef

#
# Model object 'Module'.
#
# The following features are available:
#   - attribute 'static'
#   - attribute 'abstract'
#   - reference 'superType'
#   - reference 'subTypes'
#   - reference 'depends'
#   - reference 'dependent'
#   - reference 'provides'
#   - reference 'requires'
#
# To instantiate this class use 'MyFileFactory.createModule'.
define class-Module
	$(super Node)
	$(super Entity)

	# Returns the value of the 'static' attribute.
	$(method getStatic)
	# Sets the value of the 'static' attribute.
	#   1. New value.
	$(method setStatic)

	# Returns the value of the 'abstract' attribute.
	$(method getAbstract)
	# Sets the value of the 'abstract' attribute.
	#   1. New value.
	$(method setAbstract)

	# Returns the value of the 'superType' reference.
	$(method getSuperType)
	# Sets the value of the 'superType' reference.
	#   1. New value.
	$(method setSuperType)

	# Returns the value of the 'subTypes' reference.
	$(method getSubTypes)
	# Sets the value of the 'subTypes' reference.
	#   1. New value.
	$(method setSubTypes)
	# Adds new elements to the 'subTypes' reference.
	#   1. Elements to add.
	$(method addSubTypes)
	# Removes elements from the 'subTypes' reference.
	#   1. Elements to remove.
	$(method removeSubTypes)
	# Removes all elements from the 'subTypes' reference.
	$(method clearSubTypes)

	# Returns the value of the 'depends' reference.
	$(method getDepends)
	# Sets the value of the 'depends' reference.
	#   1. New value.
	$(method setDepends)
	# Adds new elements to the 'depends' reference.
	#   1. Elements to add.
	$(method addDepends)
	# Removes elements from the 'depends' reference.
	#   1. Elements to remove.
	$(method removeDepends)
	# Removes all elements from the 'depends' reference.
	$(method clearDepends)

	# Returns the value of the 'dependent' reference.
	$(method getDependent)
	# Sets the value of the 'dependent' reference.
	#   1. New value.
	$(method setDependent)
	# Adds new elements to the 'dependent' reference.
	#   1. Elements to add.
	$(method addDependent)
	# Removes elements from the 'dependent' reference.
	#   1. Elements to remove.
	$(method removeDependent)
	# Removes all elements from the 'dependent' reference.
	$(method clearDependent)

	# Returns the value of the 'provides' reference.
	$(method getProvides)
	# Sets the value of the 'provides' reference.
	#   1. New value.
	$(method setProvides)
	# Adds new elements to the 'provides' reference.
	#   1. Elements to add.
	$(method addProvides)
	# Removes elements from the 'provides' reference.
	#   1. Elements to remove.
	$(method removeProvides)
	# Removes all elements from the 'provides' reference.
	$(method clearProvides)

	# Returns the value of the 'requires' reference.
	$(method getRequires)
	# Sets the value of the 'requires' reference.
	#   1. New value.
	$(method setRequires)
	# Adds new elements to the 'requires' reference.
	#   1. Elements to add.
	$(method addRequires)
	# Removes elements from the 'requires' reference.
	#   1. Elements to remove.
	$(method removeRequires)
	# Removes all elements from the 'requires' reference.
	$(method clearRequires)
endef

#
# Model object 'Filename'.
#
# The following features are available:
#   - attribute 'name'
#
# To instantiate this class use 'MyFileFactory.createFilename'.
define class-Filename
	$(super Node)

	# Returns the value of the 'name' attribute.
	$(method getName)
	# Sets the value of the 'name' attribute.
	#   1. New value.
	$(method setName)
endef

$(def_all)

endif # __mybuild_myfile_model_mk


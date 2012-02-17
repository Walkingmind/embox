# Generated by Xpand using M2Make template.

# Model implementation of 'myFile' package.

ifndef __mybuild_myfile_model_mk
$(error \
	Do not include this file directly, include 'myfile-model.mk' instead!)
endif # __mybuild_myfile_model_mk

include mk/model/eobject.mk

# Implementation of 'Package' model object.
define class-MyPackageImpl
	$(eobject MyFile_Package,
		MyPackage,ENamedObject,)

	# Reference 'imports' [0..*]: containment.
	$(eobject-reference MyFile_Package_imports,
		imports,MyImport,,changeable many containment)

	# Reference 'entities' [0..*]: bidirectional, containment.
	$(eobject-reference MyFile_Package_entities,
		entities,MyEntity,package,changeable many containment)

	# PROTECTED REGION ID(Package) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Import' model object.
define class-MyImportImpl
	$(eobject MyFile_Import,
		MyImport,,)

	# Attribute 'importName'.
	$(eobject-attribute MyFile_Import_importName,
		importName,changeable)

	# PROTECTED REGION ID(Import) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Entity' model object.
define class-MyEntityImpl
	$(eobject MyFile_Entity,
		MyEntity,ENamedObject,abstract)

	# Reference 'package' [0..1]: bidirectional, container.
	$(eobject-reference MyFile_Entity_package,
		package,MyPackage,entities,changeable container)

	# PROTECTED REGION ID(Entity) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Interface' model object.
define class-MyInterfaceImpl
	$(eobject MyFile_Interface,
		MyInterface,MyEntity MyExtendable,)

	# Reference 'features' [0..*]: bidirectional, containment.
	$(eobject-reference MyFile_Interface_features,
		features,MyFeature,interface,changeable many containment)

	# PROTECTED REGION ID(Interface) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Feature' model object.
define class-MyFeatureImpl
	$(eobject MyFile_Feature,
		MyFeature,ENamedObject MyExtendable,)

	# Reference 'interface' [0..1]: bidirectional, container.
	$(eobject-reference MyFile_Feature_interface,
		interface,MyInterface,features,changeable container)

	# Reference 'providedBy' [0..*]: bidirectional.
	$(eobject-reference MyFile_Feature_providedBy,
		providedBy,MyModule,provides,changeable many linkable)

	# Reference 'requiredBy' [0..*]: bidirectional.
	$(eobject-reference MyFile_Feature_requiredBy,
		requiredBy,MyModule,requires,changeable many linkable)

	# PROTECTED REGION ID(Feature) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Module' model object.
define class-MyModuleImpl
	$(eobject MyFile_Module,
		MyModule,MyEntity MyExtendable,)

	# Attribute 'static'.
	$(eobject-attribute MyFile_Module_isStatic,
		isStatic,changeable)

	# Attribute 'abstract'.
	$(eobject-attribute MyFile_Module_isAbstract,
		isAbstract,changeable)

	# Reference 'depends' [0..*]: bidirectional.
	$(eobject-reference MyFile_Module_depends,
		depends,MyModule,dependent,changeable many linkable)

	# Reference 'dependent' [0..*]: bidirectional.
	$(eobject-reference MyFile_Module_dependent,
		dependent,MyModule,depends,changeable many linkable)

	# Reference 'provides' [0..*]: bidirectional.
	$(eobject-reference MyFile_Module_provides,
		provides,MyFeature,providedBy,changeable many linkable)

	# Reference 'requires' [0..*]: bidirectional.
	$(eobject-reference MyFile_Module_requires,
		requires,MyFeature,requiredBy,changeable many linkable)

	# PROTECTED REGION ID(Module) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Extendable' model object.
define class-MyExtendableImpl
	$(eobject MyFile_Extendable,
		MyExtendable,ENamedObject,abstract)

	# Reference 'subTypes' [0..*]: bidirectional.
	$(eobject-reference MyFile_Extendable_subTypes,
		subTypes,MyExtendable,superType,changeable many linkable)

	# Reference 'superType' [0..1]: bidirectional.
	$(eobject-reference MyFile_Extendable_superType,
		superType,MyExtendable,subTypes,changeable linkable)

	# Reference 'allSubTypes' [0..*]: bidirectional, derived, read-only.
	$(property allSubTypes... : MyExtendable)
	# PROTECTED REGION ID(Extendable_allSubTypes) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter allSubTypes,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'allSuperTypes' [0..*]: bidirectional, derived, read-only.
	$(property allSuperTypes... : MyExtendable)
	# PROTECTED REGION ID(Extendable_allSuperTypes) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter allSuperTypes,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# 'isSubTypeOf' operation.
	#   1. another : MyExtendable
	# PROTECTED REGION ID(Extendable_isSubTypeOf) ENABLED START
#	# TODO Uncomment and implement me.
#	$(method isSubTypeOf,
#		$(error $0($1): NIY))
	# PROTECTED REGION END

	# 'isSuperTypeOf' operation.
	#   1. another : MyExtendable
	# PROTECTED REGION ID(Extendable_isSuperTypeOf) ENABLED START
#	# TODO Uncomment and implement me.
#	$(method isSuperTypeOf,
#		$(error $0($1): NIY))
	# PROTECTED REGION END

	# PROTECTED REGION ID(Extendable) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Filename' model object.
define class-MyFilenameImpl
	$(eobject MyFile_Filename,
		MyFilename,,)

	# PROTECTED REGION ID(Filename) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

$(def_all)


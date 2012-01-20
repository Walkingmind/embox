# Generated by Xpand using M2Make template.

# Model implementation of 'myFile' package.

ifndef __mybuild_myfile_model_mk
$(error \
	Do not include this file directly, include 'myfile-model.mk' instead!)
endif # __mybuild_myfile_model_mk


# Implementation of 'Package' model object.
define class-MyPackageImpl
	$(super MyPackage)

	$(super ENodeImpl)
	$(super MyNamedImpl)

	$(getter eMetaClass,$(MyFile_Package))

	# Reference 'imports' [0..*]: containment.
	$(property imports... : Import)
	$(field imports... : Import)
	$(getter imports,
		$(get-field imports))
	$(setter imports,
		$(invoke __eSetContainment,imports,$(suffix $1),))
	$(setter+ imports,
		$(invoke __eAddContainment,imports,$(suffix $1),))
	$(setter- imports,
		$(invoke __eRemoveContainment,imports,$(suffix $1),))

	# Reference 'entities' [0..*]: bidirectional, containment.
	$(property entities... : Entity)
	$(field entities... : Entity)
	$(getter entities,
		$(get-field entities))
	$(setter entities,
		$(invoke __eSetContainment,entities,$(suffix $1),package))
	$(setter+ entities,
		$(invoke __eAddContainment,entities,$(suffix $1),package))
	$(setter- entities,
		$(invoke __eRemoveContainment,entities,$(suffix $1),package))

	# PROTECTED REGION ID(Package) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Import' model object.
define class-MyImportImpl
	$(super MyImport)

	$(super ENodeImpl)

	$(getter eMetaClass,$(MyFile_Import))

	# Attribute 'importName'.
	$(property-field importName)

	# PROTECTED REGION ID(Import) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Entity' model object.
define class-MyEntityImpl
	$(super MyEntity)

	$(super ENodeImpl)
	$(super MyNamedImpl)

	$(getter eMetaClass,$(MyFile_Entity))

	# Reference 'package' [0..1]: bidirectional, container.
	$(property package : Package)
	$(getter package,
		$(invoke __eGetContainer,package))
	$(setter package,
		$(invoke __eSetBidirectional,package,$(suffix $1),entities))

	# PROTECTED REGION ID(Entity) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Interface' model object.
define class-MyInterfaceImpl
	$(super MyInterface)

	$(super ENodeImpl)
	$(super MyEntityImpl)
	$(super MyExtendableImpl)

	$(getter eMetaClass,$(MyFile_Interface))

	# Reference 'features' [0..*]: bidirectional, containment.
	$(property features... : Feature)
	$(field features... : Feature)
	$(getter features,
		$(get-field features))
	$(setter features,
		$(invoke __eSetContainment,features,$(suffix $1),interface))
	$(setter+ features,
		$(invoke __eAddContainment,features,$(suffix $1),interface))
	$(setter- features,
		$(invoke __eRemoveContainment,features,$(suffix $1),interface))

	# PROTECTED REGION ID(Interface) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Feature' model object.
define class-MyFeatureImpl
	$(super MyFeature)

	$(super ENodeImpl)
	$(super MyNamedImpl)
	$(super MyExtendableImpl)

	$(getter eMetaClass,$(MyFile_Feature))

	# Reference 'interface' [0..1]: bidirectional, container.
	$(property interface : Interface)
	$(getter interface,
		$(invoke __eGetContainer,interface))
	$(setter interface,
		$(invoke __eSetBidirectional,interface,$(suffix $1),features))

	# Reference 'providedBy' [0..*]: bidirectional.
	$(property providedBy... : Module)
	$(field providedBy... : Module)
	$(getter providedBy,
		$(get-field providedBy))
	$(setter providedBy,
		$(invoke __eSetBidirectional,providedBy,$(suffix $1),provides))
	$(setter+ providedBy,
		$(invoke __eAddBidirectional,providedBy,$(suffix $1),provides))
	$(setter- providedBy,
		$(invoke __eRemoveBidirectional,providedBy,$(suffix $1),provides))
	# Link operations.
	$(getter providedBy_links,
		$(invoke __eGetBidirectional_link,providedBy))
	$(setter providedBy_links,
		$(invoke __eSetBidirectional_link,providedBy,$(suffix $1),provides))
	$(setter+ providedBy_links,
		$(invoke __eAddBidirectional_link,providedBy,$(suffix $1),provides))
	$(setter- providedBy_links,
		$(invoke __eRemoveBidirectional_link,providedBy,$(suffix $1),provides))

	# Reference 'requiredBy' [0..*]: bidirectional.
	$(property requiredBy... : Module)
	$(field requiredBy... : Module)
	$(getter requiredBy,
		$(get-field requiredBy))
	$(setter requiredBy,
		$(invoke __eSetBidirectional,requiredBy,$(suffix $1),requires))
	$(setter+ requiredBy,
		$(invoke __eAddBidirectional,requiredBy,$(suffix $1),requires))
	$(setter- requiredBy,
		$(invoke __eRemoveBidirectional,requiredBy,$(suffix $1),requires))
	# Link operations.
	$(getter requiredBy_links,
		$(invoke __eGetBidirectional_link,requiredBy))
	$(setter requiredBy_links,
		$(invoke __eSetBidirectional_link,requiredBy,$(suffix $1),requires))
	$(setter+ requiredBy_links,
		$(invoke __eAddBidirectional_link,requiredBy,$(suffix $1),requires))
	$(setter- requiredBy_links,
		$(invoke __eRemoveBidirectional_link,requiredBy,$(suffix $1),requires))

	# PROTECTED REGION ID(Feature) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Module' model object.
define class-MyModuleImpl
	$(super MyModule)

	$(super ENodeImpl)
	$(super MyEntityImpl)
	$(super MyExtendableImpl)

	$(getter eMetaClass,$(MyFile_Module))

	# Attribute 'static'.
	$(property-field isStatic)

	# Attribute 'abstract'.
	$(property-field isAbstract)

	# Reference 'depends' [0..*]: bidirectional.
	$(property depends... : Module)
	$(field depends... : Module)
	$(getter depends,
		$(get-field depends))
	$(setter depends,
		$(invoke __eSetBidirectional,depends,$(suffix $1),dependent))
	$(setter+ depends,
		$(invoke __eAddBidirectional,depends,$(suffix $1),dependent))
	$(setter- depends,
		$(invoke __eRemoveBidirectional,depends,$(suffix $1),dependent))
	# Link operations.
	$(getter depends_links,
		$(invoke __eGetBidirectional_link,depends))
	$(setter depends_links,
		$(invoke __eSetBidirectional_link,depends,$(suffix $1),dependent))
	$(setter+ depends_links,
		$(invoke __eAddBidirectional_link,depends,$(suffix $1),dependent))
	$(setter- depends_links,
		$(invoke __eRemoveBidirectional_link,depends,$(suffix $1),dependent))

	# Reference 'dependent' [0..*]: bidirectional.
	$(property dependent... : Module)
	$(field dependent... : Module)
	$(getter dependent,
		$(get-field dependent))
	$(setter dependent,
		$(invoke __eSetBidirectional,dependent,$(suffix $1),depends))
	$(setter+ dependent,
		$(invoke __eAddBidirectional,dependent,$(suffix $1),depends))
	$(setter- dependent,
		$(invoke __eRemoveBidirectional,dependent,$(suffix $1),depends))
	# Link operations.
	$(getter dependent_links,
		$(invoke __eGetBidirectional_link,dependent))
	$(setter dependent_links,
		$(invoke __eSetBidirectional_link,dependent,$(suffix $1),depends))
	$(setter+ dependent_links,
		$(invoke __eAddBidirectional_link,dependent,$(suffix $1),depends))
	$(setter- dependent_links,
		$(invoke __eRemoveBidirectional_link,dependent,$(suffix $1),depends))

	# Reference 'provides' [0..*]: bidirectional.
	$(property provides... : Feature)
	$(field provides... : Feature)
	$(getter provides,
		$(get-field provides))
	$(setter provides,
		$(invoke __eSetBidirectional,provides,$(suffix $1),providedBy))
	$(setter+ provides,
		$(invoke __eAddBidirectional,provides,$(suffix $1),providedBy))
	$(setter- provides,
		$(invoke __eRemoveBidirectional,provides,$(suffix $1),providedBy))
	# Link operations.
	$(getter provides_links,
		$(invoke __eGetBidirectional_link,provides))
	$(setter provides_links,
		$(invoke __eSetBidirectional_link,provides,$(suffix $1),providedBy))
	$(setter+ provides_links,
		$(invoke __eAddBidirectional_link,provides,$(suffix $1),providedBy))
	$(setter- provides_links,
		$(invoke __eRemoveBidirectional_link,provides,$(suffix $1),providedBy))

	# Reference 'requires' [0..*]: bidirectional.
	$(property requires... : Feature)
	$(field requires... : Feature)
	$(getter requires,
		$(get-field requires))
	$(setter requires,
		$(invoke __eSetBidirectional,requires,$(suffix $1),requiredBy))
	$(setter+ requires,
		$(invoke __eAddBidirectional,requires,$(suffix $1),requiredBy))
	$(setter- requires,
		$(invoke __eRemoveBidirectional,requires,$(suffix $1),requiredBy))
	# Link operations.
	$(getter requires_links,
		$(invoke __eGetBidirectional_link,requires))
	$(setter requires_links,
		$(invoke __eSetBidirectional_link,requires,$(suffix $1),requiredBy))
	$(setter+ requires_links,
		$(invoke __eAddBidirectional_link,requires,$(suffix $1),requiredBy))
	$(setter- requires_links,
		$(invoke __eRemoveBidirectional_link,requires,$(suffix $1),requiredBy))

	# PROTECTED REGION ID(Module) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Named' model object.
define class-MyNamedImpl
	$(super MyNamed)

	$(super ENodeImpl)

	$(getter eMetaClass,$(MyFile_Named))

	# Attribute 'name'.
	$(property-field name)

	# PROTECTED REGION ID(Named) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# Implementation of 'Extendable' model object.
define class-MyExtendableImpl
	$(super MyExtendable)

	$(super ENodeImpl)

	$(getter eMetaClass,$(MyFile_Extendable))

	# Reference 'subTypes' [0..*]: bidirectional.
	$(property subTypes... : Extendable)
	$(field subTypes... : Extendable)
	$(getter subTypes,
		$(get-field subTypes))
	$(setter subTypes,
		$(invoke __eSetBidirectional,subTypes,$(suffix $1),superType))
	$(setter+ subTypes,
		$(invoke __eAddBidirectional,subTypes,$(suffix $1),superType))
	$(setter- subTypes,
		$(invoke __eRemoveBidirectional,subTypes,$(suffix $1),superType))
	# Link operations.
	$(getter subTypes_links,
		$(invoke __eGetBidirectional_link,subTypes))
	$(setter subTypes_links,
		$(invoke __eSetBidirectional_link,subTypes,$(suffix $1),superType))
	$(setter+ subTypes_links,
		$(invoke __eAddBidirectional_link,subTypes,$(suffix $1),superType))
	$(setter- subTypes_links,
		$(invoke __eRemoveBidirectional_link,subTypes,$(suffix $1),superType))

	# Reference 'superType' [0..1]: bidirectional.
	$(property superType : Extendable)
	$(field superType : Extendable)
	$(getter superType,
		$(get-field superType))
	$(setter superType,
		$(invoke __eSetBidirectional,superType,$(suffix $1),subTypes))
	# Link operations.
	$(getter superType_link,
		$(invoke __eGetBidirectional_link,superType))
	$(setter superType_link,
		$(invoke __eSetBidirectional_link,superType,$(suffix $1),subTypes))

	# Reference 'allSubTypes' [0..*]: bidirectional, volatile, read-only.
	$(property allSubTypes... : Extendable)
	# PROTECTED REGION ID(Extendable_allSubTypes) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter allSubTypes,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# Reference 'allSuperTypes' [0..*]: bidirectional, volatile, read-only.
	$(property allSuperTypes... : Extendable)
	# PROTECTED REGION ID(Extendable_allSuperTypes) ENABLED START
#	# TODO Uncomment and implement me.
#	$(getter allSuperTypes,
#		$(error $0: NIY))
	# PROTECTED REGION END

	# 'isSubTypeOf' operation.
	#   1. another : Extendable
	# PROTECTED REGION ID(Extendable_isSubTypeOf) ENABLED START
#	# TODO Uncomment and implement me.
#	$(method isSubTypeOf,
#		$(error $0($1): NIY))
	# PROTECTED REGION END

	# 'isSuperTypeOf' operation.
	#   1. another : Extendable
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
	$(super MyFilename)

	$(super ENodeImpl)

	$(getter eMetaClass,$(MyFile_Filename))

	# PROTECTED REGION ID(Filename) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

$(def_all)


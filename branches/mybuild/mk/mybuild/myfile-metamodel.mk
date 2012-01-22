# Generated by Xpand using M2Make template.

# Meta model for 'myFile' package.

ifndef __mybuild_myfile_metamodel_mk
__mybuild_myfile_metamodel_mk := $(lastword $(MAKEFILE_LIST))

# Create meta objects.
MyFile := \
	$(call createMetaModel,MyFile)

MyFile_Package := \
	$(call createMetaClass,$(MyFile),MyFile_Package)
MyFile_Package_imports := \
	$(call createMetaReference,$(MyFile_Package),MyFile_Package_imports)
MyFile_Package_entities := \
	$(call createMetaReference,$(MyFile_Package),MyFile_Package_entities)

MyFile_Import := \
	$(call createMetaClass,$(MyFile),MyFile_Import)
MyFile_Import_importName := \
	$(call createMetaAttribute,$(MyFile_Import),MyFile_Import_importName)

MyFile_Entity := \
	$(call createMetaClass,$(MyFile),MyFile_Entity)
MyFile_Entity_package := \
	$(call createMetaReference,$(MyFile_Entity),MyFile_Entity_package)

MyFile_Interface := \
	$(call createMetaClass,$(MyFile),MyFile_Interface)
MyFile_Interface_features := \
	$(call createMetaReference,$(MyFile_Interface),MyFile_Interface_features)

MyFile_Feature := \
	$(call createMetaClass,$(MyFile),MyFile_Feature)
MyFile_Feature_interface := \
	$(call createMetaReference,$(MyFile_Feature),MyFile_Feature_interface)
MyFile_Feature_providedBy := \
	$(call createMetaReference,$(MyFile_Feature),MyFile_Feature_providedBy)
MyFile_Feature_requiredBy := \
	$(call createMetaReference,$(MyFile_Feature),MyFile_Feature_requiredBy)

MyFile_Module := \
	$(call createMetaClass,$(MyFile),MyFile_Module)
MyFile_Module_isStatic := \
	$(call createMetaAttribute,$(MyFile_Module),MyFile_Module_isStatic)
MyFile_Module_isAbstract := \
	$(call createMetaAttribute,$(MyFile_Module),MyFile_Module_isAbstract)
MyFile_Module_depends := \
	$(call createMetaReference,$(MyFile_Module),MyFile_Module_depends)
MyFile_Module_dependent := \
	$(call createMetaReference,$(MyFile_Module),MyFile_Module_dependent)
MyFile_Module_provides := \
	$(call createMetaReference,$(MyFile_Module),MyFile_Module_provides)
MyFile_Module_requires := \
	$(call createMetaReference,$(MyFile_Module),MyFile_Module_requires)

MyFile_Extendable := \
	$(call createMetaClass,$(MyFile),MyFile_Extendable)
MyFile_Extendable_subTypes := \
	$(call createMetaReference,$(MyFile_Extendable),MyFile_Extendable_subTypes)
MyFile_Extendable_superType := \
	$(call createMetaReference,$(MyFile_Extendable),MyFile_Extendable_superType)
MyFile_Extendable_allSubTypes := \
	$(call createMetaReference,$(MyFile_Extendable),MyFile_Extendable_allSubTypes)
MyFile_Extendable_allSuperTypes := \
	$(call createMetaReference,$(MyFile_Extendable),MyFile_Extendable_allSuperTypes)

MyFile_Filename := \
	$(call createMetaClass,$(MyFile),MyFile_Filename)

# Initializes the objects and relations between them.
define __myFile_init
	$(call initMetaModel,$(MyFile),myFile,my)

	$(call initMetaClass,$(MyFile_Package),Package,$(EModel_ENamedObject),)
	$(call initMetaReference,$(MyFile_Package_imports),imports,$(MyFile_Import),,changeable many containment)
	$(call initMetaReference,$(MyFile_Package_entities),entities,$(MyFile_Entity),$(MyFile_Entity_package),changeable many containment)

	$(call initMetaClass,$(MyFile_Import),Import,,)
	$(call initMetaAttribute,$(MyFile_Import_importName),importName,changeable)

	$(call initMetaClass,$(MyFile_Entity),Entity,$(EModel_ENamedObject),abstract)
	$(call initMetaReference,$(MyFile_Entity_package),package,$(MyFile_Package),$(MyFile_Package_entities),changeable container)

	$(call initMetaClass,$(MyFile_Interface),Interface,$(MyFile_Entity) $(MyFile_Extendable),)
	$(call initMetaReference,$(MyFile_Interface_features),features,$(MyFile_Feature),$(MyFile_Feature_interface),changeable many containment)

	$(call initMetaClass,$(MyFile_Feature),Feature,$(EModel_ENamedObject) $(MyFile_Extendable),)
	$(call initMetaReference,$(MyFile_Feature_interface),interface,$(MyFile_Interface),$(MyFile_Interface_features),changeable container)
	$(call initMetaReference,$(MyFile_Feature_providedBy),providedBy,$(MyFile_Module),$(MyFile_Module_provides),changeable many)
	$(call initMetaReference,$(MyFile_Feature_requiredBy),requiredBy,$(MyFile_Module),$(MyFile_Module_requires),changeable many)

	$(call initMetaClass,$(MyFile_Module),Module,$(MyFile_Entity) $(MyFile_Extendable),)
	$(call initMetaAttribute,$(MyFile_Module_isStatic),static,changeable)
	$(call initMetaAttribute,$(MyFile_Module_isAbstract),abstract,changeable)
	$(call initMetaReference,$(MyFile_Module_depends),depends,$(MyFile_Module),$(MyFile_Module_dependent),changeable many)
	$(call initMetaReference,$(MyFile_Module_dependent),dependent,$(MyFile_Module),$(MyFile_Module_depends),changeable many)
	$(call initMetaReference,$(MyFile_Module_provides),provides,$(MyFile_Feature),$(MyFile_Feature_providedBy),changeable many)
	$(call initMetaReference,$(MyFile_Module_requires),requires,$(MyFile_Feature),$(MyFile_Feature_requiredBy),changeable many)

	$(call initMetaClass,$(MyFile_Extendable),Extendable,$(EModel_ENamedObject),abstract)
	$(call initMetaReference,$(MyFile_Extendable_subTypes),subTypes,$(MyFile_Extendable),$(MyFile_Extendable_superType),changeable many)
	$(call initMetaReference,$(MyFile_Extendable_superType),superType,$(MyFile_Extendable),$(MyFile_Extendable_subTypes),changeable)
	$(call initMetaReference,$(MyFile_Extendable_allSubTypes),allSubTypes,$(MyFile_Extendable),$(MyFile_Extendable_allSuperTypes),derived many)
	$(call initMetaReference,$(MyFile_Extendable_allSuperTypes),allSuperTypes,$(MyFile_Extendable),$(MyFile_Extendable_allSubTypes),derived many)

	$(call initMetaClass,$(MyFile_Filename),Filename,,)

endef # __myFile_init

# Binds objects to instance classes and features to properties.
define __myFile_bind
	$(call bindMetaClass,$(MyFile_Package),MyPackage)
	$(call bindMetaFeature,$(MyFile_Package_imports),imports)
	$(call bindMetaFeature,$(MyFile_Package_entities),entities)

	$(call bindMetaClass,$(MyFile_Import),MyImport)
	$(call bindMetaFeature,$(MyFile_Import_importName),importName)

	$(call bindMetaClass,$(MyFile_Entity),MyEntity)
	$(call bindMetaFeature,$(MyFile_Entity_package),package)

	$(call bindMetaClass,$(MyFile_Interface),MyInterface)
	$(call bindMetaFeature,$(MyFile_Interface_features),features)

	$(call bindMetaClass,$(MyFile_Feature),MyFeature)
	$(call bindMetaFeature,$(MyFile_Feature_interface),interface)
	$(call bindMetaFeature,$(MyFile_Feature_providedBy),providedBy)
	$(call bindMetaFeature,$(MyFile_Feature_requiredBy),requiredBy)

	$(call bindMetaClass,$(MyFile_Module),MyModule)
	$(call bindMetaFeature,$(MyFile_Module_isStatic),isStatic)
	$(call bindMetaFeature,$(MyFile_Module_isAbstract),isAbstract)
	$(call bindMetaFeature,$(MyFile_Module_depends),depends)
	$(call bindMetaFeature,$(MyFile_Module_dependent),dependent)
	$(call bindMetaFeature,$(MyFile_Module_provides),provides)
	$(call bindMetaFeature,$(MyFile_Module_requires),requires)

	$(call bindMetaClass,$(MyFile_Extendable),MyExtendable)
	$(call bindMetaFeature,$(MyFile_Extendable_subTypes),subTypes)
	$(call bindMetaFeature,$(MyFile_Extendable_superType),superType)
	$(call bindMetaFeature,$(MyFile_Extendable_allSubTypes),allSubTypes)
	$(call bindMetaFeature,$(MyFile_Extendable_allSuperTypes),allSuperTypes)

	$(call bindMetaClass,$(MyFile_Filename),MyFilename)

endef # __myFile_bind

$(def_all)

$(call __myFile_init)
$(call __myFile_bind)

endif # __mybuild_myfile_metamodel_mk


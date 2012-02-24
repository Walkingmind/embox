# Generated by Xpand using M2Make template.

# Meta model for 'myFile' package.

ifndef __mybuild_myfile_metamodel_mk
__mybuild_myfile_metamodel_mk := 1

include mk/model/metamodel_impl.mk

# Create meta objects.
MyFile := \
	$(call eMetaModelCreate,MyFile)

MyFile_Package := \
	$(call eMetaClassCreate,$(MyFile),MyFile_Package)
MyFile_Package_entities := \
	$(call eMetaReferenceCreate,$(MyFile_Package),MyFile_Package_entities)
MyFile_Package_imports := \
	$(call eMetaAttributeCreate,$(MyFile_Package),MyFile_Package_imports)

MyFile_Entity := \
	$(call eMetaClassCreate,$(MyFile),MyFile_Entity)
MyFile_Entity_package := \
	$(call eMetaReferenceCreate,$(MyFile_Entity),MyFile_Entity_package)

MyFile_Interface := \
	$(call eMetaClassCreate,$(MyFile),MyFile_Interface)
MyFile_Interface_features := \
	$(call eMetaReferenceCreate,$(MyFile_Interface),MyFile_Interface_features)

MyFile_Feature := \
	$(call eMetaClassCreate,$(MyFile),MyFile_Feature)
MyFile_Feature_interface := \
	$(call eMetaReferenceCreate,$(MyFile_Feature),MyFile_Feature_interface)
MyFile_Feature_providedBy := \
	$(call eMetaReferenceCreate,$(MyFile_Feature),MyFile_Feature_providedBy)
MyFile_Feature_requiredBy := \
	$(call eMetaReferenceCreate,$(MyFile_Feature),MyFile_Feature_requiredBy)

MyFile_Module := \
	$(call eMetaClassCreate,$(MyFile),MyFile_Module)
MyFile_Module_isStatic := \
	$(call eMetaAttributeCreate,$(MyFile_Module),MyFile_Module_isStatic)
MyFile_Module_isAbstract := \
	$(call eMetaAttributeCreate,$(MyFile_Module),MyFile_Module_isAbstract)
MyFile_Module_depends := \
	$(call eMetaReferenceCreate,$(MyFile_Module),MyFile_Module_depends)
MyFile_Module_dependent := \
	$(call eMetaReferenceCreate,$(MyFile_Module),MyFile_Module_dependent)
MyFile_Module_provides := \
	$(call eMetaReferenceCreate,$(MyFile_Module),MyFile_Module_provides)
MyFile_Module_requires := \
	$(call eMetaReferenceCreate,$(MyFile_Module),MyFile_Module_requires)
MyFile_Module_sources := \
	$(call eMetaReferenceCreate,$(MyFile_Module),MyFile_Module_sources)
MyFile_Module_objects := \
	$(call eMetaReferenceCreate,$(MyFile_Module),MyFile_Module_objects)

MyFile_Extendable := \
	$(call eMetaClassCreate,$(MyFile),MyFile_Extendable)
MyFile_Extendable_subTypes := \
	$(call eMetaReferenceCreate,$(MyFile_Extendable),MyFile_Extendable_subTypes)
MyFile_Extendable_superType := \
	$(call eMetaReferenceCreate,$(MyFile_Extendable),MyFile_Extendable_superType)
MyFile_Extendable_allSubTypes := \
	$(call eMetaReferenceCreate,$(MyFile_Extendable),MyFile_Extendable_allSubTypes)
MyFile_Extendable_allSuperTypes := \
	$(call eMetaReferenceCreate,$(MyFile_Extendable),MyFile_Extendable_allSuperTypes)

MyFile_File := \
	$(call eMetaClassCreate,$(MyFile),MyFile_File)
MyFile_File_fileName := \
	$(call eMetaAttributeCreate,$(MyFile_File),MyFile_File_fileName)

# Initializes the objects and relations between them.
define __myFile_init
	$(call eMetaModelInit,$(MyFile),myFile,my)

	$(call eMetaClassInit,$(MyFile_Package),Package,$(EModel_ENamedObject),)
	$(call eMetaReferenceInit,$(MyFile_Package_entities),entities,$(MyFile_Entity),$(MyFile_Entity_package),changeable many containment)
	$(call eMetaAttributeInit,$(MyFile_Package_imports),imports,changeable many)

	$(call eMetaClassInit,$(MyFile_Entity),Entity,$(EModel_ENamedObject),abstract)
	$(call eMetaReferenceInit,$(MyFile_Entity_package),package,$(MyFile_Package),$(MyFile_Package_entities),changeable container)

	$(call eMetaClassInit,$(MyFile_Interface),Interface,$(MyFile_Entity) $(MyFile_Extendable),)
	$(call eMetaReferenceInit,$(MyFile_Interface_features),features,$(MyFile_Feature),$(MyFile_Feature_interface),changeable many containment)

	$(call eMetaClassInit,$(MyFile_Feature),Feature,$(EModel_ENamedObject) $(MyFile_Extendable),)
	$(call eMetaReferenceInit,$(MyFile_Feature_interface),interface,$(MyFile_Interface),$(MyFile_Interface_features),changeable container)
	$(call eMetaReferenceInit,$(MyFile_Feature_providedBy),providedBy,$(MyFile_Module),$(MyFile_Module_provides),changeable many linkable)
	$(call eMetaReferenceInit,$(MyFile_Feature_requiredBy),requiredBy,$(MyFile_Module),$(MyFile_Module_requires),changeable many linkable)

	$(call eMetaClassInit,$(MyFile_Module),Module,$(MyFile_Entity) $(MyFile_Extendable),)
	$(call eMetaAttributeInit,$(MyFile_Module_isStatic),static,changeable)
	$(call eMetaAttributeInit,$(MyFile_Module_isAbstract),abstract,changeable)
	$(call eMetaReferenceInit,$(MyFile_Module_depends),depends,$(MyFile_Module),$(MyFile_Module_dependent),changeable many linkable)
	$(call eMetaReferenceInit,$(MyFile_Module_dependent),dependent,$(MyFile_Module),$(MyFile_Module_depends),changeable many linkable)
	$(call eMetaReferenceInit,$(MyFile_Module_provides),provides,$(MyFile_Feature),$(MyFile_Feature_providedBy),changeable many linkable)
	$(call eMetaReferenceInit,$(MyFile_Module_requires),requires,$(MyFile_Feature),$(MyFile_Feature_requiredBy),changeable many linkable)
	$(call eMetaReferenceInit,$(MyFile_Module_sources),sources,$(MyFile_File),,changeable many containment)
	$(call eMetaReferenceInit,$(MyFile_Module_objects),objects,$(MyFile_File),,changeable many containment)

	$(call eMetaClassInit,$(MyFile_Extendable),Extendable,$(EModel_ENamedObject),abstract)
	$(call eMetaReferenceInit,$(MyFile_Extendable_subTypes),subTypes,$(MyFile_Extendable),$(MyFile_Extendable_superType),changeable many linkable)
	$(call eMetaReferenceInit,$(MyFile_Extendable_superType),superType,$(MyFile_Extendable),$(MyFile_Extendable_subTypes),changeable linkable)
	$(call eMetaReferenceInit,$(MyFile_Extendable_allSubTypes),allSubTypes,$(MyFile_Extendable),$(MyFile_Extendable_allSuperTypes),derived many)
	$(call eMetaReferenceInit,$(MyFile_Extendable_allSuperTypes),allSuperTypes,$(MyFile_Extendable),$(MyFile_Extendable_allSubTypes),derived many)

	$(call eMetaClassInit,$(MyFile_File),File,,)
	$(call eMetaAttributeInit,$(MyFile_File_fileName),fileName,changeable)

endef # __myFile_init

# Binds objects to instance classes and features to properties.
define __myFile_bind
	$(call eMetaClassBind,$(MyFile_Package),MyPackage)
	$(call eMetaFeatureBind,$(MyFile_Package_entities),entities)
	$(call eMetaFeatureBind,$(MyFile_Package_imports),imports)

	$(call eMetaClassBind,$(MyFile_Entity),MyEntity)
	$(call eMetaFeatureBind,$(MyFile_Entity_package),package)

	$(call eMetaClassBind,$(MyFile_Interface),MyInterface)
	$(call eMetaFeatureBind,$(MyFile_Interface_features),features)

	$(call eMetaClassBind,$(MyFile_Feature),MyFeature)
	$(call eMetaFeatureBind,$(MyFile_Feature_interface),interface)
	$(call eMetaFeatureBind,$(MyFile_Feature_providedBy),providedBy)
	$(call eMetaFeatureBind,$(MyFile_Feature_requiredBy),requiredBy)

	$(call eMetaClassBind,$(MyFile_Module),MyModule)
	$(call eMetaFeatureBind,$(MyFile_Module_isStatic),isStatic)
	$(call eMetaFeatureBind,$(MyFile_Module_isAbstract),isAbstract)
	$(call eMetaFeatureBind,$(MyFile_Module_depends),depends)
	$(call eMetaFeatureBind,$(MyFile_Module_dependent),dependent)
	$(call eMetaFeatureBind,$(MyFile_Module_provides),provides)
	$(call eMetaFeatureBind,$(MyFile_Module_requires),requires)
	$(call eMetaFeatureBind,$(MyFile_Module_sources),sources)
	$(call eMetaFeatureBind,$(MyFile_Module_objects),objects)

	$(call eMetaClassBind,$(MyFile_Extendable),MyExtendable)
	$(call eMetaFeatureBind,$(MyFile_Extendable_subTypes),subTypes)
	$(call eMetaFeatureBind,$(MyFile_Extendable_superType),superType)
	$(call eMetaFeatureBind,$(MyFile_Extendable_allSubTypes),allSubTypes)
	$(call eMetaFeatureBind,$(MyFile_Extendable_allSuperTypes),allSuperTypes)

	$(call eMetaClassBind,$(MyFile_File),MyFile)
	$(call eMetaFeatureBind,$(MyFile_File_fileName),fileName)

endef # __myFile_bind

$(def_all)

$(call __myFile_init)
$(call __myFile_bind)

$(call eMetaModelFreeze,$(MyFile))

endif # __mybuild_myfile_metamodel_mk


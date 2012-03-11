# Generated by Xpand using M2Make template.

# Meta model for 'configFile' package.

ifndef __mybuild_configfile_metamodel_mk
__mybuild_configfile_metamodel_mk := 1

include mk/model/metamodel_impl.mk

# Create meta objects.
ConfigFile := \
	$(call eMetaModelCreate,ConfigFile)

ConfigFile_FileContent := \
	$(call eMetaClassCreate,$(ConfigFile),ConfigFile_FileContent)
ConfigFile_FileContent_configurations := \
	$(call eMetaReferenceCreate,$(ConfigFile_FileContent),ConfigFile_FileContent_configurations)
ConfigFile_FileContent_imports := \
	$(call eMetaAttributeCreate,$(ConfigFile_FileContent),ConfigFile_FileContent_imports)

ConfigFile_Configuration := \
	$(call eMetaClassCreate,$(ConfigFile),ConfigFile_Configuration)
ConfigFile_Configuration_fileContent := \
	$(call eMetaReferenceCreate,$(ConfigFile_Configuration),ConfigFile_Configuration_fileContent)
ConfigFile_Configuration_includes := \
	$(call eMetaReferenceCreate,$(ConfigFile_Configuration),ConfigFile_Configuration_includes)

ConfigFile_Include := \
	$(call eMetaClassCreate,$(ConfigFile),ConfigFile_Include)
ConfigFile_Include_module := \
	$(call eMetaReferenceCreate,$(ConfigFile_Include),ConfigFile_Include_module)
ConfigFile_Include_optionBindings := \
	$(call eMetaReferenceCreate,$(ConfigFile_Include),ConfigFile_Include_optionBindings)

ConfigFile_OptionBinding := \
	$(call eMetaClassCreate,$(ConfigFile),ConfigFile_OptionBinding)
ConfigFile_OptionBinding_value := \
	$(call eMetaAttributeCreate,$(ConfigFile_OptionBinding),ConfigFile_OptionBinding_value)

# Initializes the objects and relations between them.
define __configFile_init
	$(call eMetaModelInit,$(ConfigFile),configFile,cfg)

	$(call eMetaClassInit,$(ConfigFile_FileContent),FileContent,$(EModel_ENamedObject),)
	$(call eMetaReferenceInit,$(ConfigFile_FileContent_configurations),configurations,$(ConfigFile_Configuration),$(ConfigFile_Configuration_fileContent),changeable many containment)
	$(call eMetaAttributeInit,$(ConfigFile_FileContent_imports),imports,changeable many)

	$(call eMetaClassInit,$(ConfigFile_Configuration),Configuration,$(EModel_ENamedObject),abstract)
	$(call eMetaReferenceInit,$(ConfigFile_Configuration_fileContent),fileContent,$(ConfigFile_FileContent),$(ConfigFile_FileContent_configurations),changeable container)
	$(call eMetaReferenceInit,$(ConfigFile_Configuration_includes),includes,$(ConfigFile_Include),,changeable many containment)

	$(call eMetaClassInit,$(ConfigFile_Include),Include,,)
	$(call eMetaReferenceInit,$(ConfigFile_Include_module),module,$(MyFile_Module),,changeable linkable)
	$(call eMetaReferenceInit,$(ConfigFile_Include_optionBindings),optionBindings,$(ConfigFile_OptionBinding),,changeable many containment)

	$(call eMetaClassInit,$(ConfigFile_OptionBinding),OptionBinding,,)
	$(call eMetaAttributeInit,$(ConfigFile_OptionBinding_value),value,changeable)

endef # __configFile_init

# Binds objects to instance classes and features to properties.
define __configFile_bind
	$(call eMetaClassBind,$(ConfigFile_FileContent),CfgFileContent)
	$(call eMetaFeatureBind,$(ConfigFile_FileContent_configurations),configurations)
	$(call eMetaFeatureBind,$(ConfigFile_FileContent_imports),imports)

	$(call eMetaClassBind,$(ConfigFile_Configuration),CfgConfiguration)
	$(call eMetaFeatureBind,$(ConfigFile_Configuration_fileContent),fileContent)
	$(call eMetaFeatureBind,$(ConfigFile_Configuration_includes),includes)

	$(call eMetaClassBind,$(ConfigFile_Include),CfgInclude)
	$(call eMetaFeatureBind,$(ConfigFile_Include_module),module)
	$(call eMetaFeatureBind,$(ConfigFile_Include_optionBindings),optionBindings)

	$(call eMetaClassBind,$(ConfigFile_OptionBinding),CfgOptionBinding)
	$(call eMetaFeatureBind,$(ConfigFile_OptionBinding_value),value)

endef # __configFile_bind

$(def_all)

$(call __configFile_init)
$(call __configFile_bind)

$(call eMetaModelFreeze,$(ConfigFile))

endif # __mybuild_configfile_metamodel_mk


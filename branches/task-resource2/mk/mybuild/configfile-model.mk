# Generated by Xpand using M2Make template.

# Model of 'configFile' package.

ifndef __mybuild_configfile_model_mk
__mybuild_configfile_model_mk := 1

include mk/model/model_impl.mk

#
# Model object 'FileContentRoot'.
#
# The following features are defined:
#   - reference 'configuration'
#   - attribute 'imports'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-CfgFileContentRoot
	# Extends 'ENamedObject' class.
	$(eobject ConfigFile_FileContentRoot,
		CfgFileContentRoot,ENamedObject,)

	# Property 'configuration : CfgConfiguration'.
	$(eobject-reference ConfigFile_FileContentRoot_configuration,
		configuration,CfgConfiguration,fileContentRoot,changeable containment)

	# Property 'imports...'.
	$(eobject-attribute ConfigFile_FileContentRoot_imports,
		imports,changeable many)

	# PROTECTED REGION ID(ConfigFile_FileContentRoot) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'Configuration'.
#
# The following features are defined:
#   - reference 'fileContentRoot'
#   - reference 'includes'
#
# The following features and operations are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#   - operation 'getAnnotationsOfType'
#   - operation 'getAnnotationBindingsOfOption'
#   - operation 'getAnnotationValuesOfOption'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-CfgConfiguration
	# Extends 'ENamedObject', 'MyAnnotationTarget' classes.
	$(eobject ConfigFile_Configuration,
		CfgConfiguration,ENamedObject MyAnnotationTarget,)

	# Property 'fileContentRoot : CfgFileContentRoot'.
	$(eobject-reference ConfigFile_Configuration_fileContentRoot,
		fileContentRoot,CfgFileContentRoot,configuration,changeable container)

	# Property 'includes... : CfgInclude'.
	$(eobject-reference ConfigFile_Configuration_includes,
		includes,CfgInclude,,changeable many containment)

	# PROTECTED REGION ID(ConfigFile_Configuration) ENABLED START
	# PROTECTED REGION END
endef

#
# Model object 'Include'.
#
# The following features are defined:
#   - reference 'module'
#   - reference 'optionBindings'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
# The following features and operations are inherited from 'AnnotationTarget':
#   - reference 'annotations'
#   - operation 'getAnnotationsOfType'
#   - operation 'getAnnotationBindingsOfOption'
#   - operation 'getAnnotationValuesOfOption'
#
define class-CfgInclude
	# Extends 'MyAnnotationTarget', 'ENamedObject' classes.
	$(eobject ConfigFile_Include,
		CfgInclude,MyAnnotationTarget ENamedObject,)

	# Property 'module... : MyModuleType'.
	# Property 'module_links... : ELink'.
	$(eobject-reference ConfigFile_Include_module,
		module,MyModuleType,,changeable many linkable)

	# Property 'optionBindings... : MyOptionBinding'.
	$(eobject-reference ConfigFile_Include_optionBindings,
		optionBindings,MyOptionBinding,,changeable many containment)

	# PROTECTED REGION ID(ConfigFile_Include) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

# PROTECTED REGION ID(ConfigFile) ENABLED START
# TODO Add custom implementation here and remove this comment.
# PROTECTED REGION END

$(def_all)

endif # __mybuild_configfile_model_mk


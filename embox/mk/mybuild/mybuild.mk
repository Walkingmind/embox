# $Id$
#
#
#   Date: Feb 10, 2012
# Author: Eldar Abusalimov
#

ifndef __mybuild_mybuild_mk
__mybuild_mybuild_mk := 1

include mk/mybuild/myfile-resource.mk

chekers_list := \
	Mybuild.closeInstances \
	Mybuild.testsAnnotations \
	Mybuild.specifyInstances \
	Mybuild.checkAbstractRealization \
	Mybuild.checkFeatureRealization \
	Mybuild.optionBind \
	Mybuild.optionCheckUnique \
	Mybuild.optionCheckConstraints



# Main check procedures. Check modules with checkers sequence.
# Out of every checkers passed to next's in, so checkers can add
# or remove instances from input. Every checkers also called with 
# passed checkers list, so cheking can be restarted for some 
# instances with already passed chekers only.
#
# Args:
# 	1. Cheking instances
# 	2. Checkers list
# 	3. Passed checkers list
define check
	$(if $2,
		$(call check,
			$(call $(firstword $2),$1,$3),
			$(wordlist 2,$(words $2),$2),
			$3 $(firstword $2)),
		$1)
endef

LABEL-DefaultImpl := mybuild.lang.DefaultImpl
LABEL-IfNeed      := mybuild.lang.IfNeed
LABEL-For         := mybuild.lang.For
LABEL-TestFor := mybuild.lang.TestFor

excludeAnnotations := $(LABEL-IfNeed)
leftToRightParentAnnotations := $(LABEL-IfNeed) $(LABEL-For)

define getAnnotation
	$(strip $(for annot <- $1,
		annotType<-$(get annot->type),
		$(if $(eq $(get annotType->qualifiedName),$2),
			$(if $(value 3),
				$(for bind <- $(get annot->bindings),
					$(if $(eq $3,$(get $(get bind->option).name)),
						$(get bind->value))),
				$2))))

endef

# Constructor args:
#   1. Configuration.
define class-Mybuild
	$(map moduleInstanceStore... : ModuleInstance) #by module
	$(map activeFeatures... : ModuleInstance) #by feature
	$(property-field recommendations)

# Public:

	# Creates build model from the configuration.
	#
	# Args:
	#   1. Configuration.
	# Return:
	#   New instance of CfgBuild.
	$(method createBuild,
		$(assert $(singleword $1))
		$(for configuration <- $1,
			build <-$(new Build),
			issueReceiver <- $(new IssueReceiver),

			$(set build->configuration,$(configuration))
			$(set-field build->issueReceiver,$(issueReceiver))

			$(set build->modules, 
				$(invoke getBuildModules))

			$(build))
	)

# Private:

	# Gets all modulesInstance's created according configResourceSet
	#
	# Context:
	#   'configuration'
	#   'issueReceiver'
	# Return:
	#	List of avaible moduleInstances. Some of them may not be created, then
	#	issue will be created
	$(method getBuildModules,
		$(with \
			$(for \
				cfgInclude <- $(get configuration->includes),
				module <- $(get cfgInclude->module),
				$(if $(strip \
						$(call Mybuild.processIncludeAnnotations,$(module),
						$(get cfgInclude->annotations))),

					$(for moduleInst <- $(invoke moduleInstance,$(module)),
						$(set moduleInst->includeMember,$(cfgInclude))
						$(moduleInst)))),

			$(call check,$1,$(chekers_list),)
			))

	$(method __addIssue,
		$(invoke issueReceiver->addIssues,$(new InstantiateIssue,
			$(for includeMember <- $(get 1->includeMember),
				$(get includeMember->eResource)),
			$2,
			$(for includeMember <- $(get 1->includeMember),
				$(get includeMember->origin)),
			$3
			)))

	$(method processIncludeAnnotations,
		$(if $2,,$1)
		$(for annot <-$2,
			annotName <- $(get annot->qualifiedName),
			$(if $(filter $(annotName),$(excludeAnnotations)),,$1)
			$(if $(filter $(annotName),$(leftToRightParentAnnotations)),
				$(if $(invoke \
						$(get-field \
							$(get $(get annot->bindings).value)
							.value)
						.isSuperTypeOf,$1),,
					$(invoke issueReceiver->addIssues,$(new InstantiateIssue,
						$(get cfgInclude->eResource),
						error,
						$(get cfgInclude->origin),
						Annotation $(annotName) value should be \
							target's parent))))
			$(if $(eq $(annotName),$(LABEL-IfNeed)),	
				$(set+ recommendations,
					$(invoke $(get $(get annot->bindings).value).toString)
					$1))))

	$(method closeInstances,
		$(for inst <- $1,
			$(inst) \
			$(invoke instanceClosure,$(inst))))

	$(method testAnnotTestGet,
		$(for testModLiteral<-$(call getAnnotation,
				$(get mod->annotations),$(LABEL-TestFor),value),
			$(get testModLiteral->value)) \
		$(if $(strip $(get inst->includeMember)),
			$(for annotLiteral<-$(call getAnnotation,
					$(get $(get inst->includeMember).annotations),
					$(LABEL-TestFor),value),
				$(get annotLiteral->value))))

	$(method testAnnotTestingGet,
		$(if $(strip $(get inst->includeMember)),
			$(for \
				testModLiteral<-$(call getAnnotation,
					$(get $(get inst->includeMember).annotations),
					mybuild.lang.WithTest,value), 
				testMod<-$(get testModLiteral->value),

				$(with \
					$(for testModTestAnnot <- $(call getAnnotation,
							$(get testMod->annotations),mybuild.lang.TestFor,
							value),
						testModTestTarget <- $(get testModTestAnnot->value),
						$(if \
							$(filter $(mod),
								$(testModTestTarget) \
								$(get testModTestTarget->allSubTypes)),
							1)),
					$(if $(strip $1),
						$(testMod),
						$(invoke __addIssue,$(inst),error,
							$(get mod->qualifiedName) inclusion requested \
							$(get testMod->qualifiedName) as test; but it is \
							not defined test))))

			$(if $(strip $(call getAnnotation,
					$(get $(get inst->includeMember).annotations),
					mybuild.lang.WithAllTests)),
				$(for \
					buildMod <- $(call allModules),
					testLiteral <- $(call getAnnotation,
						$(get buildMod->annotations),mybuild.lang.TestFor,
						value),
					testMod <- $(get testLiteral->value),
					$(if 
						$(filter $(mod),
							$(testMod) \
							$(get testMod->allSubTypes)),
						$(testMod))))))
			
	$(method testAnnotTestDo,
		$(set+ testModInst->afterDepends,$(inst)))

	$(method testAnnotTestingDo,
		$(set+ inst->afterDepends,$(testModInst)))
		
	$(method testsAnnotations,
		$(for \
			inst <- $1,	
			mod <- $(get inst->type),
			$(inst) \
			$(for targetAction <-Test Testing,
				testMod <- $(call Mybuild.testAnnot$(targetAction)Get),
				testModWas <-was$(map-get moduleInstanceStore/$(testMod)),
				testModInst <-$(invoke moduleInstance,$(testMod)),

				$(if $(filter was,$(testModWas)),			
					$(call check,$(testModInst),$3,))
				$(call Mybuild.testAnnot$(targetAction)Do))))
	
	$(method specifyInstances,
		$(for inst <- $1,
			$(with $(or $(strip $(for \
						rule<-$(get recommendations),
						targetInstance<-$(map-get \
							build->moduleInstanceByName/$(basename $(rule))),
						targetModule<-$(suffix $(rule)),

						$(if $(and $(filter $(inst),$(targetInstance)),
									$(invoke targetModule->isSubTypeOf,
										$(get targetInstance->type))), 
								$(call check,
									$(invoke moduleInstance,
										$(targetModule)),
									$2 $0,)	
								))),
					$(strip $(for \
						mod <- $(get inst->type),
						annotValue <- $(call getAnnotation,
								$(get mod->annotations),
								$(LABEL-DefaultImpl),
								value),
						$(call check,
							$(invoke moduleInstance,
								$(get annotValue->value)),
							$2 $0,)))),
				$(if $1,$1,$(inst)))))

	# Cheker for abstract realization. If there is only one subtype of given 
	# abstract module, it will included to build with all dependencies, which 
	# are also checked for abstract realization with `check' restart 
	#
	# Args:
	#	1. List of ModuleInstance 
	#	2. Checkers, which ModuleInstances was passed.
	$(method checkAbstractRealization,
		$(for inst <- $1,
			instType <- $(get inst->type),
			$(if $(get instType->isAbstract), 
				$(if $(singleword $(get instType->subTypes)),
					$(call check,
						$(invoke moduleInstance,
							$(get instType->subTypes)),
						$2 $0,),
					$(inst)
					$(invoke issueReceiver->addIssues,
						$(new InstantiateIssue,,error,,
							No abstract realization: \
								$(get instType->qualifiedName)))),
				$(inst))))

	# Helper method, returns string representation of moduleInstance origin
	#
	# Args:
	#	1. ModuleInstance
	# Return:
	#	String representation of ModuleInstance origin
	$(method getInstDepsOrigin,
		$(for \
			inst <- $1,
			instType <- $(get inst->type),
			$(if $(get inst->includeMember),
				$(for \
					includeMember <- $(get inst->includeMember),
					resource <- $(get includeMember->eResource),
						$(get instType->qualifiedName)(
						$(get resource->fileName):
						$(get includeMember->origin))),
				$(get instType->qualifiedName)(As dependence))))


	# Checks that ModuleInstances have all feature realization in current build
	# 
	# Context:
	#	IssueReceiver
	# Args:
	#	1. List of ModuleInstance
	#	2. Checkers, which ModuleInstances was passed.
	# Return:
	#   None.
	# Side effect:
	#	Probably issue was added to IssueReceiver
	$(method checkFeatureRealization,
		$(for inst <- $1,
			instType <- $(get inst->type),
			$(if $(strip \
				$(for require <- $(get instType->requires),
					$(if $(map-get activeFeatures/$(require)),#OK 
						,error#Feature not realized, error
						$(invoke issueReceiver->addIssues,
							$(new InstantiateIssue,,error,,
							Feature $(get require->qualifiedName) required by \
								$(get instType->qualifiedName) is not 
								implemented))))),
				,$(inst))))

		
	
	# Bind options for ModuleInstances (set ModuleInstance optionBinding field 
	# with option binding)
	# 
	# Context:
	#	Issue Receiver
	# Args:
	#	1. List of ModuleInstance
	#	2. Checkers, which ModuleInstances was passed.
	# Return:
	#   None.
	# Side effect:
	#	Probably issue was added to IssueReceiver
	$(method optionBind,
		$(for \
			modInst <- $1,
			mod <- $(get modInst->type),
			$(if $(strip \
				$(for \
					opt<-$(get mod->allOptions),
					optValue <- $(or $(if $(get modInst->includeMember),
											# if module was explicitly enabled
											# from configs and probably has
											# config option bindings
										$(invoke findOptValue,$(opt),
											$(get $(get modInst->includeMember).
														optionBindings))),
								 $(get opt->defaultValue),),
					$(if $(optValue),
						$(silent-for optInst <- $(new OptionInstance),
							$(set optInst->option,$(opt))
							$(set optInst->value,$(optValue))
							$(set+ modInst->options,$(optInst))),
						$(invoke __addIssue,$(modInst),warning,
							Could not bind option $(get opt->name) in module \
								$(get mod->qualifiedName) to a value)Error)))
				,,$(modInst))))

	$(map optionUniq)
	$(map optionSet)

	$(method optionCheckUniqueMark,
		$(if $(and $1,$2),
			$(map-set optionUniq/$(get 1->value),1),
			$(if $2,
				$(invoke __addIssue,
					$(inst),
					warning,
					$(get optType->qualifiedName) has @Unique without @Type))
		1))
	
	$(method optionCheckUniqueCheck,
			$(if $1,
				$(for \
					inst<-$3,
					typeId<-$(get 1->value),
					valueMark <- $(subst $(\s),_,
						$(get $(get opt->value).value)),
					setMark<-$(typeId)_set_$(valueMark),
					$(if $(map-get optionUniq/$(typeId)),
						$(for anotherOpt<-$(map-get optionSet/$(setMark)),
							Error
							$(invoke __addIssue,$(inst),error,
								Unique type $(typeId) assigned many times \
								to same value in \
								$(get optType->qualifiedName) \
								(first assing occured in \
								$(get $(get anotherOpt->option).qualifiedName) \
								inclusion)
							))
						$(map-set optionSet/$(setMark),$(opt))))))
	
	$(method optionCheckUnique,
		$(for phase <- Mybuild.optionCheckUniqueMark \
						Mybuild.optionCheckUniqueCheck,
			$(with $1,$(for inst <- $1,
				opt<-$(get inst->options),
				optType<-$(get opt->option),
				member<-$(invoke optType->eContainer),
				$(with \
					$(call getAnnotation,
						$(get member->annotations),
						mybuild.lang.Type,
						value),
					$(call getAnnotation,
						$(get member->annotations),
						mybuild.lang.Unique),
					$(inst),
					
					$($(phase)))),

				$(if $(strip $2),,$1))))

	$(method optionCheckConstraints,
		$(with $1,$(for inst<-$1,
				opt<-$(get inst->options),
				optVal <- $(get opt->value),
				optValRaw <- $(get optVal->value),
				optType<-$(get opt->option),
				member<-$(invoke optType->eContainer),
				$(if $(invoke MyFile_NumberOption->isInstance,$(optType)),
					$(with \
						$(for cmp <- ge gt le lt,
							val <- $(call getAnnotation,
										$(get member->annotations),
										mybuild.lang.NumConstraint,
										$(cmp)),
					$(if \
						$(shell if [ ! $(optValRaw) -$(cmp) $(get val->value) ]; \
							then echo 1; fi),
						$(invoke __addIssue,$(inst),error,option $(get optType->qualifiedName) \
							constraint check error)))))),

			$(if $(strip $2),
				,
				$1)))

	# Find option binding for option within list.
	# 
	# Args:
	#	1. Option
	#	2. List of OptionBinding
	# Return:
	#	OptionBindings for given option
	$(method findOptValue,
		$(for \
			opt <- $1,
			optName <- $(get opt->name),
			optBinding <- $2,
			optBindOpt <- $(get optBinding->option),
			optBindName <- $(get optBindOpt->name),
			optBindVal <- $(get optBinding->value),
			$(if $(and $(eq $(optName),$(optBindName)),
					$(invoke opt->validateValue,$(optBindVal))),
				$(optBindVal))))

	# Effectivelly allocate ModuleInstance.
	# If there are ModuleInstance for module supertype, it will be returned,
	# else new ModuleInstance returned.
	#
	# Returned ModuleInstance is not initialized.
	#
	# Context:
	#	IssueReceiver
	#	cfgInclude. IncludeMember of processing ModuleInstance requiest.
	#	mod. Module for which ModuleInstance is creating.
	# Args:
	#	None.
	# Return:
	#	Uninitialized ModuleInstance
	# Side effect:
	#	Probably issue was added in case mod has incompatible hierarchy 
	#	sibiling (sibiling extends one of mod supertype but nor extends
	#	mod, neither is one of mods subtype).
	$(method moduleInstanceSuper,
		$(with \
			$(sort \
				$(for super <- $(mod) $(get mod->allSuperTypes),
					$(map-get moduleInstanceStore/$(super)))),
			$(if $1,
				$(if $(filter $(get 1->type),$(mod) $(get mod->allSuperTypes)), 
					$1,
					$(if $(filter $(get 1->type),$(get mod->allSubTypes)),$1,
						$(invoke issueReceiver->addIssues,
							$(new InstantiateIssue,
								$(for includeMember <- $(cfgInclude),
									$(get includeMember->eResource)),
								error,
								$(for includeMember <- $(cfgInclude),
									$(get includeMember->origin)),
								Module $(get mod->qualifiedName) extends module \
									supertype already extended by incompatible \
									$(invoke getInstDepsOrigin,$1)))
					)),
				$(new ModuleInstance,$(mod)))))

	$(method setInstanceToType,
			$(set 1->type,$2)

			$(for super <- $2 $(get 2->allSuperTypes),
				$(map-set build->moduleInstanceByName/$(get super->qualifiedName),
					$1)
				$(map-set moduleInstanceStore/$(super),
					$1))

			$(for provide <- $(get 2->provides),
				opt <- $(provide) $(get provide->allSubFeatures),
				$(map-set+ activeFeatures/$(opt),
					$1)))
		

	# Get ModuleInstance for Module
	# 
	# Args:
	#	1. Module
	# Return:
	#	ModuleInstance instance 
	# SideEffect:
	#	Build realized features appends Module features
	$(method moduleInstance,
		$(for \
			mod<-$1,
			moduleInstance<-$(call Mybuild.moduleInstanceSuper),
	
			$(if $(or $(if $(get moduleInstance->type),,1),
						$(invoke $(get moduleInstance->type).isSuperTypeOf,
							$(mod))),
				$(invoke setInstanceToType,$(moduleInstance),$(mod)))

			$(moduleInstance)))
	
	# Get ModuleInstance closure of given  Module
	#
	# Args:
	#  1. Module, that not presented in build
	# Return:
	#  List of ModuleInstance for module, that have no reperesents yet
	$(method instanceClosure,
		$(for thisInst<-$1,
			mod <- $(get thisInst->type),
			dep <- $(get mod->depends),
			was <- was$(map-get moduleInstanceStore/$(dep)),
			depInst <- $(invoke moduleInstance,$(dep)),
			$(if $(filter $(depInst),$(get thisInst->depends)),,
				$(set+ thisInst->depends,$(depInst)))

			$(if $(filter was,$(was)),
				$(depInst)) \

			$(invoke instanceClosure,$(depInst))))

endef

# Takes a resource set of configfiles and creates build for each configuration.
# Returns the argument.
define mybuild_create_build
	$(invoke $(new Mybuild).createBuild,
		$(call mybuild_get_active_configuration,$1))
endef

# 1. Config files resource set.
define mybuild_get_active_configuration
	$(for resource <- $(get 1->resources),
		root <- $(get resource->contentsRoot),
		$(get root->configuration))
endef

define allModules
	$(sort \
		$(for \
			resource <- $(get __myfile_resource_set->resources),
			obj <- $(get resource->contents),
			$(if $(invoke MyFile_ModuleType->isInstance,$(obj)),
				$(obj))))
endef

define printInstance
	$(for inst<-$1,
		mod <- $(get inst->type),
		--- $(get mod->qualifiedName) ---$(\n)
		Inclusion reason: $(if $(get inst->includeMember),
								explicit,
								as dependence)$(\n)
		Depends:$(\n)
		$(for dep <- $(get inst->depends),
			$(\t)$(get $(get dep->type).qualifiedName)$(\n))
		Dependents:$(\n)
		$(for dep <- $(get inst->dependent),
			$(\t)$(get $(get dep->type).qualifiedName)$(\n))
		OptInsts:$(\n)
		$(for optInst <- $(get inst->options),
			opt <- $(get optInst->option),
			val <-$(get optInst->value),
			$(\t)$(get opt->name) : $(get val->value)$(\n))
		Sources:$(\n)
		$(for srcMember <- $(get mod->sourcesMembers),
				src <- $(get srcMember->files),
	       		$(for annot<-$(get srcMember->annotations),
					annotType <- $(get annot->type),
					annotName <- $(get annotType->qualifiedName),
					annotBind <- $(get annot->bindings),
					@$(annotName):$(\n)
					$(for opt <- $(get annotBind->option),
						optName <- $(get opt->name),
						optValue <- $(get $(get annotBind->value).value),
						$(\t)$(optName) = $(optValue)$(\n)))
				$(get src->fileFullName)$(\n))
	)
endef

define printInstances
	$(for buildBuild<-$1,
		$(warning $(call printInstance,$(get buildBuild->modules)))))
endef 

define printIssues
	$(for issueReceiver <- $(get-field 1->issueReceiver),
		$(if $(invoke issueReceiver->getIssues),
			$(invoke issueReceiver->printIssues)))
endef

define listInstances
		$(strip	$(get 1->modules))
endef

define class-InstantiateIssue
	$(super BaseIssue,$(value 1),$(value 2),$(value 3),$(value 4))

endef

$(def_all)

endif # __mybuild_mybuild_mk

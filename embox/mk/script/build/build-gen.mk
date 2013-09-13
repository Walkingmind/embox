# $Id$
#
#   Date: Apr 25, 2012
# Author: Eldar Abusalimov
#

include mk/script/script-common.mk

# Wraps the given rule with a script which compares the command output with
# the original file (if it exists) and replaces the latter only in case when
# contents differ.
#   1. Output file.
#   2. The complete command which should output its result to the temporary
#      file specified in the '$OUTFILE' environment variable.
cmd_notouch = \
	set_on_error_trap() { trap "$$1" INT QUIT TERM HUP EXIT; };            \
	COMMAND=$(call sh_quote,set_on_error_trap "$(RM) $$OUTFILE"; { $2; }); \
	OUTFILE=$(call trim,$1);                                               \
	if [ ! -f $$OUTFILE ];                                                 \
	then                                                                   \
		__OUTDIR=`dirname $$OUTFILE`;                                      \
		{ [ -d $$__OUTDIR ] || $(MKDIR) $$__OUTDIR; }                      \
			&& eval "$$COMMAND" && set_on_error_trap -;                    \
	else                                                                   \
		__OUTFILE=$$OUTFILE; OUTFILE=$${TMPDIR:-/tmp}/Mybuild.$$$$;        \
		eval "$$COMMAND"                                                   \
			&& { cmp -s $$OUTFILE $$__OUTFILE >/dev/null 2>&1              \
					|| { $(MV) $$OUTFILE $$__OUTFILE                       \
							&& set_on_error_trap -; }; };                  \
	fi

#cmd_notouch = \
	OUTFILE=$(call trim,$1); { $2; }

#   1. Output file.
#   2. The command which outputs its result to stdout.
cmd_notouch_stdout = \
	$(call cmd_notouch,$1,{ $2; } > $$OUTFILE)

sh_quote = \
	'$(subst ','\'',$1)'
fmt_line = \
	$(if $2,$1)$(subst $(\n),$(\n)$1,$2)

# 1. Text to comment.
gen_comment = \
	$(PRINTF) '%s\n' \
		$(call sh_quote,$(call fmt_line,$(\h) ,$1))

gen_banner = \
	$(PRINTF) '%s\n\n' \
		$(call sh_quote,$(call fmt_line,$(\h) ,$(GEN_BANNER)))

# 1. Variable name.
# 2. Value.
gen_make_var = \
	$(PRINTF) '%s := %s\n\n' \
		$(call sh_quote,$1) \
		$(call sh_quote,$2)

# 1. Variable name.
# 2. Value.
gen_make_var_list = \
	$(PRINTF) '%s := $(foreach ,$2,\\\n\t%s)\n\n' \
		$(call sh_quote,$1) \
		$(foreach v,$2,$(call sh_quote,$v))

# 1. Target.
# 2. Prerequisites.
# 3. Recipe.
gen_make_rule = \
	$(PRINTF) '%s : %s\n%s\n\n' \
		$(call sh_quote,$1)     \
		$(call sh_quote,$2)     \
		$(call sh_quote,$(call fmt_line,$(\t),$3))

# 1. Target.
# 2. Prerequisites.
gen_make_dep = \
	$(PRINTF) '%s : %s\n\n' \
		$(call sh_quote,$1) \
		$(call sh_quote,$2)

# 1. Target.
# 2. Variable name.
# 3. Value.
gen_make_tsvar = \
	$(PRINTF) '%s : %s := %s\n\n' \
		$(call sh_quote,$1) \
		$(call sh_quote,$2) \
		$(call sh_quote,$3)

# 1. Target.
# 2. Variable name.
# 3. Value (assumed to be a list).
gen_make_tsvar_list = \
	$(PRINTF) '%s : %s := $(foreach ,$3,\\\n\t\t%s)\n\n' \
		$(call sh_quote,$1) \
		$(call sh_quote,$2) \
		$(foreach v,$3,$(call sh_quote,$v))

# 1. Makefile
# 2. Whether to use silent '-include'.
gen_make_include = \
	$(PRINTF) '%sinclude %s\n\n' \
		$(call sh_quote,$(if $(value 2),-)) \
		$(call sh_quote,$1)

# Working with these lists...

build_modules := \
	$(call get,$(build_model),modules)
build_sources := \
	$(foreach m,$(build_modules), \
		$(addprefix $m,$(call get,$m,sources)))

#
# Global artifacts.
#

@build_image := \
	$(build_model:%=build-image-rmk/%)

@build_include_mk := \
	$(build_model:%=build-include-mk/%)

@build_initfs := \
	$(build_model:%=build-initfs-rmk/%)

@build_all = \
	$(@build_image) \
	$(@build_include_mk) \
	$(@build_initfs)

all .PHONY : $(@build_all)

$(@build_all) : a_modules = $(suffix $(@module_ar_rmk))
$(@build_all) : o_modules = $(suffix $(@module_ld_rmk))

build_image_rmk_mk_pat     = $(MKGEN_DIR)/%.rule.mk
build_image_rmk_target_pat = $1

$(@build_image) : @file    = $(patsubst %,$(build_image_rmk_mk_pat),image)
$(@build_image) : mk_file  = \
		$(patsubst %,$(value build_image_rmk_mk_pat),image)
$(@build_image) : target_file = \
		$(patsubst %,$(value build_image_rmk_target_pat),image)

$(@build_image) : scripts = $(patsubst %,$(value source_cpp_rmk_o_pat), \
			$(call source_base,$(@source_cpp_rmk)))
$(@build_image) : objs = $(patsubst %,$(value module_ld_rmk_o_pat), \
			$(call module_path,$(o_modules)))
$(@build_image) : libs = \
		$(patsubst %,$(value source_a_rmk_o_pat), \
			$(basename $(call module_a_source_files,$(build_modules)))) \
		$(patsubst %,$(value module_ar_rmk_a_pat), \
			$(call module_path,$(a_modules)))

$(@build_image) :
	@$(call cmd_notouch_stdout,$(@file), \
		$(gen_banner); \
		$(call gen_comment,Arg: target file(s) to define rules for.); \
		$(PRINTF) 'define __image_rule\n\n'; \
		$(call gen_make_dep,$(target_file),$$$$(image_prerequisites)); \
		$(call gen_make_tsvar,$(target_file),mk_file,$(mk_file)); \
		$(call gen_make_tsvar_list,$(target_file),ld_scripts,$(scripts)); \
		$(call gen_make_tsvar_list,$(target_file),ld_objs,$(objs)); \
		$(call gen_make_tsvar_list,$(target_file),ld_libs,$(libs)); \
		$(PRINTF) 'endef '; \
		$(call gen_comment,__image_rule))

$(@build_include_mk) : @file = $(MKGEN_DIR)/include.mk
$(@build_include_mk) : image_rmk = \
		$(patsubst %,$(value build_image_rmk_mk_pat),image)
$(@build_include_mk) : source_rmk = \
		$(patsubst %,$(value source_rmk_mk_pat), \
			$(call source_file,$(@source_rmk)))
$(@build_include_mk) : module_ar_rmk = \
		$(patsubst %,$(value module_ar_rmk_mk_pat), \
			$(call module_path,$(@module_ar_rmk)))
$(@build_include_mk) : module_ld_rmk = \
		$(patsubst %,$(value module_ld_rmk_mk_pat), \
			$(call module_path,$(@module_ld_rmk)))
$(@build_include_mk) : module_extbld_rmk = \
		$(patsubst %,$(value module_extbld_rmk_mk_pat), \
			$(call module_path,$(@module_extbld_rmk)))
$(@build_include_mk) : initfs_rmk = \
		$(patsubst %,$(value build_initfs_rmk_mk_pat),$(build_initfs))

$(@build_include_mk) :
	@$(call cmd_notouch_stdout,$(@file), \
		$(gen_banner); \
		$(call gen_make_var,__include_image,$(image_rmk)); \
		$(call gen_make_var,__include_initfs,$(initfs_rmk)); \
		$(call gen_make_var_list,__include, \
			$(source_rmk) $(module_extbld_rmk) \
			$(module_ar_rmk) $(module_ld_rmk)))

build_initfs := initfs

$(@build_initfs) : initfs = $(build_initfs)

build_initfs_rmk_mk_pat     = $(MKGEN_DIR)/%.rule.mk
build_initfs_rmk_target_pat = $(ROOTFS_IMAGE)

$(@build_initfs) : @file    = $(initfs:%=$(build_initfs_rmk_mk_pat))
$(@build_initfs) : mk_file  = \
		$(patsubst %,$(value build_initfs_rmk_mk_pat),$$(build_initfs))
$(@build_initfs) : target_file = \
		$(patsubst %,$(value build_initfs_rmk_target_pat),$$(build_initfs))

$(@build_initfs) : cpio_files = \
		$(call source_initfs_cp_o_file,$(@source_initfs_cp_rmk))

$(@build_initfs) :
	@$(call cmd_notouch_stdout,$(@file), \
		$(gen_banner); \
		$(call gen_make_var,build_initfs,$(initfs)); \
		$(call gen_make_dep,$(target_file),$$$$(initfs_prerequisites)); \
		$(call gen_make_tsvar,$(target_file),mk_file,$(mk_file)); \
		$(call gen_make_tsvar_list,$(target_file),cpio_files,$(cpio_files)))

#
# Per-module artifacts.
#

source_file = $(call get,$1,fileFullName)
source_base = $(basename $(source_file))

source_o_pats   := %.o
source_a_pats   := %.a
source_cc_pats  := %.S %.c %.cpp %.cxx
source_mk_pats  := %.mk
source_cpp_pats := %.lds.S

module_occ_source_files = \
	$(filter $(source_cc_pats) $(source_o_pats),$(filter-out $(source_cpp_pats), \
		$(call source_file,$(call get,$1,sources))))

module_a_source_files = \
	$(filter $(source_a_pats),$(call source_file,$(call get,$1,sources)))

filter_with_occ = \
	$(foreach m,$1,$(if $(call module_occ_source_files,$m),$m))

static_modules    := $(call filter_static_modules,$(build_modules))
nonstatic_modules := $(filter-out $(static_modules), $(build_modules))


@module_ld_rmk := \
	$(patsubst %,module-ld-rmk/%, \
		$(call filter_with_occ,$(nonstatic_modules)))

@module_ar_rmk := \
	$(patsubst %,module-ar-rmk/%, \
		$(call filter_with_occ,$(static_modules)))

my_cmd_name   := $(call mybuild_resolve_or_die,mybuild.lang.Cmd.name)

check_atmost_one = \
	$(if $(word 2,$1), \
		$(error Too many Cmd names for \
			'$(call get,$(call get,$m,type),qualifiedName)': \
			$(call get,$1,value)),$1)

@module_lds := \
	$(foreach m,$(nonstatic_modules), \
		$(patsubst %,module-lds-rmk/%$m, \
			$(call check_atmost_one,$(call invoke, \
				$(call get,$m,allTypes),getAnnotationValuesOfOption, \
				$(my_cmd_name)))))

@module_hdr := \
	$(foreach m,$(build_modules), \
		$(patsubst %,module-h/%$m, \
			$(call get,$m,allTypes)))

my_bld_script := $(call mybuild_resolve_or_die,mybuild.lang.Build.script)

@module_extbld_rmk := \
	$(foreach m,$(build_modules), \
		$(patsubst %,module-extbld-rmk/%$m, \
			$(call invoke,$(call get,$m,allTypes),getAnnotationValuesOfOption,$(my_bld_script))))

@module_all = \
	$(@module_lds) \
	$(@module_hdr) \
	$(@module_ld_rmk) \
	$(@module_ar_rmk) \
	$(@module_extbld_rmk)

all .PHONY : $(@module_all)

module_fqn  = $(call get,$(call get,$1,type),qualifiedName)
module_path = $(subst .,/,$(module_fqn))
module_id   = $(subst .,__,$(module_fqn))

$(@module_all) : fqn   = $(call module_fqn,$@)
$(@module_all) : path  = $(call module_path,$@)


module_ar_rmk_mk_pat = $(MKGEN_DIR)/module/%.ar_rule.mk
module_ar_rmk_a_pat  = $(OBJ_DIR)/module/%.a

module_ld_rmk_mk_pat = $(MKGEN_DIR)/module/%.ld_rule.mk
module_ld_rmk_o_pat  = $(OBJ_DIR)/module/%.o

$(@module_ld_rmk) : kind := ld
$(@module_ar_rmk) : kind := ar

$(@module_ld_rmk) $(@module_ar_rmk) : @file   = \
		$(path:%=$(module_$(kind)_rmk_mk_pat))
$(@module_ld_rmk) $(@module_ar_rmk) : mk_file = \
		$(patsubst %,$(value module_$(kind)_rmk_mk_pat),$$(module_path))

$(@module_ld_rmk) : out_file = \
		$(patsubst %,$(value module_ld_rmk_o_pat),$$(module_path))
$(@module_ar_rmk) : out_file = \
		$(patsubst %,$(value module_ar_rmk_a_pat),$$(module_path))

$(@module_ld_rmk) $(@module_ar_rmk) : objs = \
		$(patsubst %,$(value source_occ_rmk_o_pat), \
			$(basename $(call module_occ_source_files,$@)))

$(@module_ld_rmk) $(@module_ar_rmk) : lds_file = \
		$(patsubst %,$(value module_lds_pat), \
			$(if $(filter %$(suffix $@),$(@module_lds)),$(path)))

$(@module_ld_rmk) $(@module_ar_rmk) :
	@$(call cmd_notouch_stdout,$(@file), \
		$(gen_banner); \
		$(call gen_make_var,module_path,$(path)); \
		$(call gen_make_dep,$(out_file),$$$$($(kind)_prerequisites)); \
		$(call gen_make_tsvar,$(out_file),reloc_lds,$(lds_file)); \
		$(call gen_make_tsvar,$(out_file),mk_file,$(mk_file)); \
		$(call gen_make_tsvar_list,$(out_file),$(kind)_objs,$(objs)))


# 1. module instance
# 2. app name
define __lds_template
/* Autogenerated file. Do not edit. */
SECTIONS {
	.data.$2 : { *(.data) }
	.bss.$2  : { *(.bss) }
}
endef

module_lds_pat = $(SRCGEN_DIR)/module/%.lds
module_hdr_pat = $(SRCGEN_DIR)/include/module/%.h

$(@module_lds) : @file = $(path:%=$(module_lds_pat))
$(@module_lds) : cmd_name = $(call get,$(basename $@),value)

$(@module_hdr) : @file = $(type_path:%=$(module_hdr_pat))
$(@module_hdr) : type = $(basename $@)
$(@module_hdr) : type_fqn = $(call get,$(type),qualifiedName)
$(@module_hdr) : type_path = $(subst .,/,$(type_fqn))

$(@module_hdr) : content = $(call __header_template,$@,$(type_fqn))
$(@module_lds) : content = $(call __lds_template,$@,$(cmd_name))

$(@module_hdr) $(@module_lds) : printf_escape = \
		$(subst $(\t),\t,$(subst $(\n),\n,$(subst \,\\,$1)))

$(@module_hdr) $(@module_lds) :
	@$(call cmd_notouch_stdout,$(@file), \
		$(PRINTF) '%b' $(call sh_quote,$(call printf_escape,$(content))))


module_extbld_rmk_mk_pat     = $(MKGEN_DIR)/%.extbld_rule.mk
module_extbld_rmk_target_pat = __extbld-%

$(@module_extbld_rmk) : @file   = $(path:%=$(module_extbld_rmk_mk_pat))
$(@module_extbld_rmk) : mk_file = $(patsubst %,$(value module_extbld_rmk_mk_pat),$$(module_path))
$(@module_extbld_rmk) : target = $(patsubst %,$(value module_extbld_rmk_target_pat),$$(module_path))
$(@module_extbld_rmk) : script = $(call get,$(basename $@),value)
$(@module_extbld_rmk) : kind := extbld

$(@module_extbld_rmk) :
	@$(call cmd_notouch_stdout,$(@file), \
		$(gen_banner); \
		$(call gen_make_var,module_path,$(path)); \
		$(call gen_make_dep,__extbld .PHONY,$(target)); \
		$(call gen_make_dep,$(target),$$$$($(kind)_prerequisites)); \
		$(call gen_make_tsvar,$(target),mk_file,$(mk_file)); \
		$(call gen_make_rule,$(target),,$(script)))

#
# Per-source artifacts.
#

source_member = $(call invoke,$1,eContainer)
source_annotation_values = \
	$(call invoke,$(source_member),getAnnotationValuesOfOption,$2)
source_annotations = \
	$(call invoke,$(source_member),getAnnotationsOfType,$2)

my_gen_script := $(call mybuild_resolve_or_die,mybuild.lang.Generated.script)

@source_gen := \
	$(foreach s,$(build_sources), \
		$(patsubst %,source-gen/%$s, \
			$(call source_annotation_values,$s,$(my_gen_script))))

my_initfs := $(call mybuild_resolve_or_die,mybuild.lang.InitFS)
my_initfs_target := $(call mybuild_resolve_or_die,mybuild.lang.InitFS.target)
my_initfs_chmod := $(call mybuild_resolve_or_die,mybuild.lang.InitFS.chmod)
my_initfs_chown := $(call mybuild_resolve_or_die,mybuild.lang.InitFS.chown)

@source_initfs_cp_rmk := \
	$(foreach s,$(build_sources), \
		$(if $(call source_annotations,$s,$(my_initfs)), \
			source-initfs-cp-rmk/$(strip \
				$(call source_annotation_values,$s,$(my_initfs_target)))$s))

@source_rmk := \
	$(foreach s,$(build_sources), \
		$(foreach f,$(call get,$s,fileName),$(or \
			$(and $(filter $(source_cpp_pats),$f),source-cpp-rmk/$s), \
			$(and $(filter $(source_cc_pats),$f), source-cc-rmk/$s), \
			$(and $(filter $(source_mk_pats),$f), source-mk-rmk/$s), \
			$(and $(filter $(source_a_pats),$f),  source-a-rmk/$s), \
			$(and $(filter $(source_o_pats),$f),  source-o-rmk/$s))))

@source_o_rmk   := $(filter source-o-rmk/%,$(@source_rmk))
@source_a_rmk   := $(filter source-a-rmk/%,$(@source_rmk))
@source_cc_rmk  := $(filter source-cc-rmk/%,$(@source_rmk))
@source_mk_rmk  := $(filter source-mk-rmk/%,$(@source_rmk))
@source_cpp_rmk := $(filter source-cpp-rmk/%,$(@source_rmk))

$(@source_o_rmk)   : kind := o
$(@source_a_rmk)   : kind := a
$(@source_cc_rmk)  : kind := cc
$(@source_mk_rmk)  : kind := mk
$(@source_cpp_rmk) : kind := cpp

@source_rmk += \
	$(@source_initfs_cp_rmk)

# task/???.module.source
@source_all = \
	$(@source_gen) \
	$(@source_rmk)

all .PHONY : $(@source_all)

$(@source_all) : module = $(basename $@)

$(@source_all) : file = $(call source_file,$@)
$(@source_all) : base = $(call source_base,$@)

$(@source_all) : values_of = $(call source_annotation_values,$@,$1)

my_rule_script  = $(call mybuild_resolve_or_die,mybuild.lang.Rule.script)
my_rule_prereqs = $(call mybuild_resolve_or_die,mybuild.lang.Rule.prerequisites)

$(@source_all) : script  = $(call get,$(call values_of,$(my_rule_script)),value)
$(@source_all) : prereqs = $(call get,$(call values_of,$(my_rule_prereqs)),value)

$(@source_o_rmk) $(@source_a_rmk) : script  = $(or \
			$(call get,$(call values_of,$(my_rule_script)),value), \
			$$(CP) $(file) $$@)

my_defmacro_val := $(call mybuild_resolve_or_die,mybuild.lang.DefineMacro.value)
my_incpath_val  := $(call mybuild_resolve_or_die,mybuild.lang.IncludePath.value)

$(@source_rmk) : includes = $(call values_of,$(my_incpath_val))
$(@source_rmk) : defines  = $(call values_of,$(my_defmacro_val))

$(@source_rmk) : do_flags = $(foreach f,$2,$1$(call sh_quote,$(call get,$f,value)))
$(@source_rmk) : flags = $(call trim, \
			$(call do_flags,-I,$(includes)) \
			-include $(patsubst %,$(value module_hdr_pat),$(call module_path,$(module))) \
			-D__EMBUILD_MOD__=$(call module_id,$(module)) \
			$(call do_flags,-D,$(defines)))

source_rmk_mk_pat   = $(MKGEN_DIR)/%.rule.mk

$(@source_rmk) : @file   = $(file:%=$(source_rmk_mk_pat))
$(@source_rmk) : mk_file = $(patsubst %,$(value source_rmk_mk_pat),$$(source_file))

source_occ_rmk_o_pat = $(OBJ_DIR)/%.o

source_o_rmk_o_pat   = $(OBJ_DIR)/%.o
source_a_rmk_o_pat   = $(OBJ_DIR)/%.a
source_cc_rmk_o_pat  = $(OBJ_DIR)/%.o
source_cpp_rmk_o_pat = $(OBJ_DIR)/%# foo.lds.S -> foo.lds

$(@source_rmk)  : o_file = $(patsubst %,$(value source_$(kind)_rmk_o_pat),$$(source_base))

$(@source_cpp_rmk) $(@source_cc_rmk) $(@source_o_rmk) $(@source_a_rmk):
	@$(call cmd_notouch_stdout,$(@file), \
		$(gen_banner); \
		$(call gen_make_var,source_file,$(file)); \
		$(call gen_make_var,source_base,$$(basename $$(source_file))); \
		$(call gen_make_dep,$(o_file),$$$$($(kind)_prerequisites)); \
		$(call gen_make_tsvar,$(o_file),mk_file,$(mk_file)); \
		$(call gen_make_tsvar,$(o_file),flags,$(flags)); \
		$(call gen_make_rule,$(o_file),$(prereqs),$(script)); \
		$(call gen_make_include,$$(OBJ_DIR)/$$(source_base).d,silent))

$(@source_mk_rmk):
	@$(call cmd_notouch_stdout,$(@file), \
		$(gen_banner); \
		$(call gen_make_include,$(file)))

source_initfs_cp_o_file = \
	$(addprefix $$(ROOTFS_DIR)/, \
		$(foreach s,$1,$(or \
			$(call get,$(notdir $(basename $(basename $s))),value), \
			$(call get,$s,fileName))))

$(@source_initfs_cp_rmk) : o_file = $(call source_initfs_cp_o_file,$@)

$(@source_initfs_cp_rmk) : src_file = $(file)
$(@source_initfs_cp_rmk) : mk_file = $(patsubst %,$(value source_rmk_mk_pat),$(file))
$(@source_initfs_cp_rmk) : kind := initfs_cp
$(@source_initfs_cp_rmk) : str_of = \
		$(call sh_quote,$(call get,$(call values_of,$1),value))
$(@source_initfs_cp_rmk) : chmod = $(call str_of,$(my_initfs_chmod))
$(@source_initfs_cp_rmk) : chown = $(call str_of,$(my_initfs_chown))

$(@source_initfs_cp_rmk) :
	@$(call cmd_notouch_stdout,$(@file), \
		$(gen_banner); \
		$(call gen_make_dep,$(o_file),$$$$($(kind)_prerequisites)); \
		$(call gen_make_tsvar,$(o_file),src_file,$(src_file)); \
		$(call gen_make_tsvar,$(o_file),chmod,$(chmod)); \
		$(call gen_make_tsvar,$(o_file),chown,$(chown)); \
		$(call gen_make_tsvar,$(o_file),mk_file,$(mk_file)))

$(@source_gen) : @file = $(SRCGEN_DIR)/$(file)
$(@source_gen) : gen_string = $(basename $(basename $@))
$(@source_gen) : script = $(call expand,$(call get,$(gen_string),value))

$(@source_gen) :
# Plus sign is for case when generator script is also Make-based.
# Avoids 'jobserver unavailable' warning for parallel builds.
	+@$(call cmd_notouch_stdout,$(@file), \
		$(script))


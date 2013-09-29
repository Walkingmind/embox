# $Id:  $
#
#   Date: Sep 27, 2012
# Author: Eldar Abusalimov
#

include mk/script/script-common.mk


my_app := $(call mybuild_resolve_or_die,mybuild.lang.App)

is_app = \
	$(strip $(call invoke, \
		$(call get,$1,allTypes),getAnnotationsOfType,$(my_app)))

fqn2id = $(subst .,__,$1)

app_ids := \
	$(foreach m,$(call get,$(build_model),modules), \
		$(if $(call is_app,$m), \
			$(call fqn2id,$(call get,$(call get,$m,type),qualifiedName))))

#
# The output.
#

define file_header
/* $(GEN_BANNER) */

#include <asm-generic/embox.lds.h>

SECTIONS {
endef

define section_header
	.$1 : {
		__app_$1_start = .;
endef

define section_item
		__app_$2_$1_vma = .;
		*(.app.$1.$2)
		__app_$2_$1_len = ABSOLUTE(. - __app_$2_$1_vma);

endef

define section_footer
		__app_$1_end = .;
	}

endef

define file_footer
	.reserve.app.data : {
		__app_reserve_start = .;
		. += ABSOLUTE(__app_data_end -
		              __app_data_start);
		__app_reserve_end = .;
	}
}
endef


$(info $(file_header))

print_section = \
	$(info $(call section_header,$1)) \
	$(foreach n,$(app_ids),$(info $(call section_item,$1,$n))) \
	$(info $(call section_footer,$1))

$(call print_section,data)
$(call print_section,bss)

$(info $(file_footer))


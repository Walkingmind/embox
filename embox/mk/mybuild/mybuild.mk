# $Id: $
#
#   Date: Feb 10, 2012
# Author: Eldar Abusalimov
#

ifndef __mybuild_mybuild_mk
__mybuild_mybuild_mk := 1

include mk/mybuild/resource.mk

# Constructor args:
#   1. (Optional) List of resource objects.
define class-mybuild

	$(property-field resources... : resource)

	$(property __unresolved_links... : module_link)
	$(getter __unresolved_links,
		$(for r <- $(get resources),
			o <- $(get r->exports),
			f <- depends_refs super_module_ref,
			l <- $(get o->$f),
				$(if $(not $(invoke $l.resolved?)),$l))
	)

	# Takes a list of resource objects and links them together.
	$(method link,
		$(set-field resources,$(suffix $1))
		$(silent-for \
			l <- $(get __unresolved_links),
			r <- $(get resources),
			m <- $(filter $(get l->link_name).%,$(get r->exports)),
				$(if $(eq $(basename $m),$(get l->link_name)),
					$(invoke l->resolve,$m)))
	)

	$(if $(value 1),$(invoke link,$1))
endef

mybuild_model_instance = $(__mybuild_model_instance)

$(def_all)

endif # __mybuild_mybuild_mk

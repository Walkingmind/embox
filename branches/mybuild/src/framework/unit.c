/**
 * @file
 * @brief TODO
 *
 * @date 11.03.10
 * @author Eldar Abusalimov
 */

#include <string.h>
#include <kernel/prom_printf.h>

#include <framework/mod/ops.h>
#include <framework/mod/api.h>

#include <embox/unit.h>

static int unit_mod_enable(struct mod_info *mod_info);
static int unit_mod_disable(struct mod_info *mod_info);

const struct mod_ops __unit_mod_ops = {
	.enable  = &unit_mod_enable,
	.disable = &unit_mod_disable,
};

static int unit_mod_enable(struct mod_info *mod_info) {
	int ret = 0;
	struct unit *unit = (struct unit *) mod_info->data;
//	const struct mod *mod = mod_info->mod; /* used only for trace => warning when prom_printf equeal nothing => broken compilation */

	if (NULL == unit->init) {
		return 0;
	}

	prom_printf("\tunit: initializing %s.%s: ", mod_info->mod->package->name, mod_info->mod->name);
	if (0 == (ret = unit->init())) {
		prom_printf("done\n");
	} else {
		prom_printf("error: %s\n", strerror(-ret));
	}

	return ret;
}

static int unit_mod_disable(struct mod_info *mod_info) {
	int ret = 0;
	struct unit *unit = (struct unit *) mod_info->data;
//	const struct mod *mod = mod_info->mod;

	if (NULL == unit->fini) {
		return 0;
	}

	prom_printf("unit: finalizing %s.%s: ", mod_info->mod->package->name, mod_info->mod->name);
	if (0 == (ret = unit->fini())) {
		prom_printf("done\n");
	} else {
		prom_printf("error: %s\n", strerror(-ret));
	}

	return ret;
}

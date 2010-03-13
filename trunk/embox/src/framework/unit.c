/**
 * @file
 * @brief TODO
 *
 * @date 11.03.2010
 * @author Eldar Abusalimov
 */

#include <common.h>

#include <embox/unit.h>
#include <embox/mod.h>

static int unit_mod_enable(struct mod *mod);
static int unit_mod_disable(struct mod *mod);

struct mod_ops __unit_mod_ops = { .enable = &unit_mod_enable,
		.disable = &unit_mod_disable };

static int unit_mod_enable(struct mod *mod) {
	int ret = 0;
	struct unit *unit = (struct unit *) mod->data_ref->data;

	if (NULL == unit->init) {
		return 0;
	}

	TRACE("unit: initializing %s.%s: ", mod->package->name, mod->name);
	if (0 == (ret = unit->init())) {
		TRACE("done\n");
	} else {
		TRACE("error\n");
	}

	return ret;
}

static int unit_mod_disable(struct mod *mod) {
	int ret = 0;
	struct unit *unit = (struct unit *) mod->data_ref->data;

	if (NULL == unit->fini) {
		return 0;
	}

	TRACE("unit: finalizing %s.%s: ", mod->package->name, mod->name);
	if (0 == (ret = unit->fini())) {
		TRACE("done\n");
	} else {
		TRACE("error\n");
	}

	return ret;
}

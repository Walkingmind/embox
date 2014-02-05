/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    05.02.2014
 */

#include <stdbool.h>
#include <errno.h>
#include <debug/symbol.h>
#include <kernel/printk.h>
#include <embox/unit.h>

extern const struct symbol __symbol_table[];
extern const size_t __symbol_table_size;

EMBOX_UNIT_INIT(coverage_init);

#define COVERAGE_TABLE_SIZE OPTION_GET(NUMBER,coverage_table_size)
static bool coverage_table[COVERAGE_TABLE_SIZE];

void __cyg_profile_func_enter(void *func, void *caller) {	
	const struct symbol *sym;
	int sym_pos;

	sym = symbol_lookup(func);
	if (!sym)
		return;
	
	sym_pos = sym - __symbol_table;
	if (!(0 <= sym_pos && sym_pos < __symbol_table_size))
		return;

	coverage_table[sym_pos] = 1;
}

void __cyg_profile_func_exit(void *func, void *caller) {

}

int coverage_getstat(const struct symbol **sym_table, const bool **cov_table) {

	*sym_table = __symbol_table;
	*cov_table = coverage_table;

	return __symbol_table_size;
}

static int coverage_init(void) {

	if (COVERAGE_TABLE_SIZE < __symbol_table_size) {
		printk("\n[%s]: coverage_table_size too small, "
				"try to increase it\n", __func__);
		return -ENOMEM;
	}

	return 0;
}

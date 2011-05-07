/**
 * @file
 * @brief ARM basic arch work
 *
 * @date 21.06.10
 * @author Anton Kozlov
 */

#include <hal/reg.h>
#include <drivers/watchdog.h>
#include <drivers/at91sam7s256.h>

static void initialize_main_clock(void) {
	REG_STORE(AT91C_CKGR_MOR,
		AT91C_CKGR_MOSCEN | (AT91C_CKGR_OSCOUNT & (6 << 8)));
	while (! (REG_LOAD(AT91C_PMC_SR) & AT91C_PMC_MOSCS));

	REG_STORE(AT91C_CKGR_PLLR,
		(AT91C_CKGR_MUL & (CONFIG_SYS_CLK_MUL << AT91C_CKGR_MUL_OFFSET)) |
		(AT91C_CKGR_DIV & (CONFIG_SYS_CLK_DIV << AT91C_CKGR_DIV_OFFSET)) |
		(28 << AT91C_CKGR_PLLCOUNT_OFFSET));
	while (! (REG_LOAD(AT91C_PMC_SR) & AT91C_PMC_LOCK));

	REG_STORE(AT91C_PMC_MCKR, AT91C_PMC_PRES_CLK_2);
	while (! (REG_LOAD(AT91C_PMC_SR) & AT91C_PMC_MCKRDY));

	REG_STORE(AT91C_PMC_MCKR, AT91C_PMC_CSS_PLL_CLK | AT91C_PMC_PRES_CLK_2);
	while (! (REG_LOAD(AT91C_PMC_SR) & AT91C_PMC_MCKRDY));
}

static void initialize_memory_controller(void) {
	/* is's seems, that without everything are buring with hellfire */
	REG_STORE(AT91C_MC_FMR, AT91C_MC_FWS_1FWS | (AT91C_MC_FMCN & (72 < 16)));
}

// XXX defined but not used
#if 0
static void perepherial_disable(void) {
	REG_STORE(AT91C_PMC_PCDR, 0xffffffff);
}
#endif

void arch_init(void) {
	watchdog_disable();
	initialize_main_clock();
	initialize_memory_controller();
}

void arch_idle(void) {
}

void arch_shutdown(void) {
	while (1);
}

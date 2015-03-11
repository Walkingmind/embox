/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    30.10.2014
 */

#include <assert.h>
#include <stdint.h>
#include <system_stm32f4xx.h>
#include <framework/mod/options.h>
#include <module/embox/arch/system.h>
#include <hal/arch.h>

void arch_init(void) {
	static_assert(OPTION_MODULE_GET(embox__arch__system, NUMBER, core_freq) == 144000000);
	SystemInit();
}

void arch_idle(void) {

}

void arch_shutdown(arch_shutdown_mode_t mode) {
	while (1);
}

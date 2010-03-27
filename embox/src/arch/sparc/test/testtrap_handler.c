/**
 * @file
 *
 * @date 25.03.2010
 * @author Alexander Batyukov
 */

#include <asm/traps_core.h>
#include <test/testtraps_core.h>
#include <stdio.h>

trap_handler_t test_handler[MAX_SOFTTRAP_NUMBER];

void test_soft_trap_handler(uint8_t tt) {
	if (NULL == test_handler)
		return;
	test_handler[tt - MIN_SOFT_TRAP_NUMBER](0,0);
}

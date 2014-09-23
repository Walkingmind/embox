/**
 * @file
 *
 * @date 15.03.10
 * @author Anton Bondarev
 * @author Alexander Batyukov
 */

#ifndef SPARC_TESTTRAPS_H_
#define SPARC_TESTTRAPS_H_

#include <stdint.h>
#include <hal/env/traps_core.h>

#define CONFIG_TRAP_TABLE_SIZE 0x100
extern trap_handler_t test_handlers[CONFIG_TRAP_TABLE_SIZE];

extern uint32_t *__test_trap_table;

#endif /* SPARC_TESTTRAPS_H_ */

/**
 * @file
 *
 * @brief MIPS build-in timer
 *
 * @date 04.07.2012
 * @author Anton Bondarev
 */

#include <asm/mipsregs.h>
#include <kernel/time/clock_source.h>
#include <embox/unit.h>

static struct clock_source mips_clock_source = {
	.name = "mips_clk",
//	.event_device = &mips_event_device,
//	.counter_device = &mips_counter_device,
//	.read = clock_source_read /* attach default read function */
};

static int pit_clock_init(void) {
	clock_source_register(&mips_clock_source);
	return 0;
}

EMBOX_UNIT_INIT(pit_clock_init);

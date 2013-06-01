/**
 * @file
 * @brief Context switch test
 *
 * @date 20.04.10
 * @author Eldar Abusalimov
 */

#include <hal/context.h>
#include <embox/test.h>
#include <stdio.h>
#define STACK_SZ 0x10000

EMBOX_TEST(run);

#define TRACE(msg) 

static struct context entry_context, infinite_context, redundant_context;
static char entry_stack[STACK_SZ];
static char infinite_stack[STACK_SZ];

static unsigned int mask = 0x55555555;

static void entry(void) {
	TRACE("entry begin\n");
	while (mask) {
		test_assert(mask & 1);
		mask >>= 1;

		context_switch(&entry_context, &infinite_context);
	}
	TRACE("entry end (should not be reached)\n");
}

static void infinite(void) {
	while (mask) {
		test_assert(0 == (mask & 1));
		mask >>= 1;

		context_switch(&infinite_context, &entry_context);
	}
	context_switch(&infinite_context, &redundant_context);
}

static int run(void) {
	context_init(&entry_context, true);
	context_set_entry(&entry_context, entry);
	context_set_stack(&entry_context, entry_stack + STACK_SZ);

	context_init(&infinite_context, true);
	context_set_entry(&infinite_context, infinite);
	context_set_stack(&infinite_context, infinite_stack + STACK_SZ);

	TRACE("test begin\n");
	context_switch(&redundant_context, &entry_context);
	TRACE("test end\n");

	return 0;
}

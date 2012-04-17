/**
 * @file
 * @brief TODO --Alina.
 *
 * @date 18.03.2012
 * @author Alina Kramar
 */

#include <stdio.h>
#include <embox/cmd.h>
#include <util/array.h>
#include <util/location.h>
#include <profiler/tracing/trace.h>

EMBOX_CMD(exec);

extern struct __trace_point * const __trace_points_array[];

//static void print_usage(void) {
//	printf("%s\n", "Usage: tpprint");
//}

static int exec(int argc, char **argv) {

	struct __trace_point *tp;

	array_nullterm_foreach(tp, __trace_points_array) {
		printf("%10s - %d\n", tp->name, tp->count);
	}

	return 0;
}

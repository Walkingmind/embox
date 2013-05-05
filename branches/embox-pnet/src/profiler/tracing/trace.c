/**
 * @file
 * @brief TODO
 *
 * @date 18.03.2012
 * @author Alina Kramar
 */

#include <string.h>

#include <util/array.h>
#include <util/location.h>

#include <kernel/time/clock_source.h>
#include <kernel/time/ktime.h>
#include <kernel/time/itimer.h>

#include <profiler/tracing/trace.h>

ARRAY_SPREAD_DEF_TERMINATED(typeof(struct __trace_point *),
		__trace_points_array, NULL);
ARRAY_SPREAD_DEF_TERMINATED(typeof(struct __trace_block *),
		__trace_blocks_array, NULL);

void __tracepoint_handle(struct __trace_point *tp) {
	if (tp->active) {
		tp->count++;
	}
}

void trace_block_enter(struct __trace_block *tb) {
	bool (*hnd)(void *target);

	if (tb->active && (0 == trace_block_diff(tb))) {
		hnd = tb->begin->tp_enabled;
		if (hnd && hnd(tb->begin->target)) {
			itimer_init(tb->tc, clock_source_get_best(CS_ANY), 0);
			__tracepoint_handle(tb->begin);
		}
	}
}

void trace_block_leave(struct __trace_block *tb) {
	bool (*hnd)(void *target);

	if (tb->active) {
		hnd = tb->begin->tp_enabled;
		if (hnd && hnd(tb->end->target)) {
			tb->time = (int) (itimer_read(tb->tc));
			// FIXME
			if (tb->time > 1000000) {
				tb->time -= 1000000;
			}
			tb->total_time += tb->time; /* usec */
			__tracepoint_handle(tb->end);
		}
	}
}

int trace_block_get_time(struct __trace_block *tb) {
	return tb->time;
}

time64_t trace_block_get_total_time(struct __trace_block *tb) {
	return tb->total_time;
}

int trace_block_diff(struct __trace_block *tb) {
	int a = trace_point_get_value(tb->begin);
	int b = trace_point_get_value(tb->end);

	return a - b;
}

struct __trace_block *trace_block_get_by_name(const char *name) {
	struct __trace_block *tb;

	array_nullterm_foreach(tb, __trace_blocks_array)
	{
		if (!strcmp(tb->name, name)) {
			return tb;
		}
	}

	return NULL;
}

void trace_point_set_condition(struct __trace_point *tp, void *cond, bool (*hnd)(void *cond)) {
	tp->target = cond;
	tp->tp_enabled = hnd;
}

int trace_point_get_value(struct __trace_point *tp) {
	return tp->count;
}

struct __trace_point *trace_point_get_by_name(const char *name) {
	struct __trace_point *tp;

	array_nullterm_foreach(tp, __trace_points_array)
	{
		if (!strcmp(tp->name, name)) {
			return tp;
		}
	}

	return NULL;
}

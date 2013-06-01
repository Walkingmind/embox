/**
 * @file
 * @brief TODO
 *
 * @date 18.03.2012
 * @author Alina Kramar
 */

#ifndef PROFILER_TRACING_TRACE_IMPL_H_
#define PROFILER_TRACING_TRACE_IMPL_H_

#include <string.h>
#include <stdbool.h>

#include <util/array.h>
#include <util/location.h>

#include <kernel/time/clock_source.h>
#include <kernel/time/ktime.h>
//#include <kernel/time/timecounter.h>
#include <kernel/time/itimer.h>

struct __trace_point {
	const char *name;
	struct location_func location;
	int count;
	bool active;
};

struct __trace_block {
	struct __trace_point *begin;
	struct __trace_point *end;
	//struct timecounter *tc;
	struct itimer *tc;
	int time;
	bool active;
};

extern struct __trace_point *const __trace_points_array[];
extern struct __trace_block *const __trace_blocks_array[];

#define __TRACE_POINT_DEF(_name, tp_name)   \
		struct __trace_point _name = {      \
			.name = tp_name,                \
			.location = LOCATION_FUNC_INIT, \
			.count = 0,                     \
			.active = true,                 \
		};                                  \
		ARRAY_SPREAD_ADD(__trace_points_array, &_name)

#define __trace_point_set(tp_pointer) \
		__tracepoint_handle(tp_pointer)

#define __TRACE_BLOCK_DEF(tb_name)                           \
	static struct __trace_point b;             \
	static struct __trace_point e; \
	static struct itimer tc;\
	static struct __trace_block tb_name  = {         \
			.begin = &b,      \
			.end   = &e,                             \
			.tc    = &tc,                          \
			.time  = 0,    \
			.active = true, \
	};                                                   \
	ARRAY_SPREAD_ADD(__trace_blocks_array, &tb_name);  \

#define __tp_ref(__name) \
	({                                                        \
		static struct __trace_point __tp = {                  \
			.name = __name,                                   \
			.location = LOCATION_FUNC_INIT,                   \
			.count = 0,                                       \
			.active = true,                                   \
		};                                                    \
		ARRAY_SPREAD_ADD(__trace_points_array, &__tp);        \
		&__tp;                                                \
	})

#define __trace_point(__name) \
	__tracepoint_handle(__tp_ref(__name))

#endif /* PROFILER_TRACING_TRACE_IMPL_H_ */

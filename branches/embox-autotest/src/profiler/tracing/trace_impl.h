/**
 * @file
 * @brief TODO
 *
 * @date 18.03.2012
 * @author Alina Kramar
 * @author Denis Deryugin
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
	const char *name;
	struct location_func location;
	struct __trace_point *begin;
	struct __trace_point *end;
	struct itimer *tc;
	int64_t count;
	time64_t time;
	bool active;
	bool is_entered;
};

#define __TRACE_POINT_DEF(_name, tp_name)   \
		struct __trace_point _name = {      \
			.name = tp_name,                \
			.location = LOCATION_FUNC_INIT, \
			.count = 0,                     \
			.active = true,                 \
		};                                  \
		ARRAY_SPREAD_DECLARE(struct __trace_point *, \
				__trace_points_array);               \
		ARRAY_SPREAD_ADD(__trace_points_array, &_name)

#define __trace_point_set(tp_pointer) \
		__tracepoint_handle(tp_pointer)

#define __TRACE_BLOCK_DEF(tb_name)                  	\
	static struct __trace_point tb_name ## _b;      	\
	static struct __trace_point tb_name ## _e; 			\
	static struct itimer tb_name ## _tc;				\
	static struct __trace_block tb_name  = {        	\
			.name  = #tb_name,							\
			.location = LOCATION_FUNC_INIT,				\
			.begin = &tb_name ## _b,     				\
			.end   = &tb_name ## _e,                	\
			.tc    = &tb_name ## _tc,               	\
			.time  = 0,									\
			.count = 0,									\
			.active = true, 							\
			.is_entered = false,						\
	};                                              	\
	ARRAY_SPREAD_DECLARE(struct __trace_block *,		\
			__trace_blocks_array);              		\
	ARRAY_SPREAD_ADD(__trace_blocks_array, &tb_name)

#define __tp_ref(__name) \
	({                                                        \
		static struct __trace_point __tp = {                  \
			.name = __name,                                   \
			.location = LOCATION_FUNC_INIT,                   \
			.count = 0,                                       \
			.active = true,                                   \
		};                                                    \
		ARRAY_SPREAD_DECLARE(struct __trace_point *,          \
				__trace_points_array);                        \
		ARRAY_SPREAD_ADD(__trace_points_array, &__tp);        \
		&__tp;                                                \
	})

#define __trace_point(__name) \
	__tracepoint_handle(__tp_ref(__name))

#endif /* PROFILER_TRACING_TRACE_IMPL_H_ */

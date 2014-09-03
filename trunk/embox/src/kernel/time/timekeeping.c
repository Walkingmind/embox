/**
 * @file
 * @brief System time correction with NTP
 *
 * @date 25.07.2012
 * @author Alexander Kalmuk
 */

#include <kernel/time/clock_source.h>
#include <kernel/time/itimer.h>
#include <time.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(time_init);

static struct {
	struct clock_source *cs;
	int precision; /*< e.g. NTP precision */
	struct timespec time;
} abstime;

static struct itimer itimer;

void settimeofday(struct timespec *newtime, struct timezone *tz) {
	abstime.time.tv_sec = newtime->tv_sec;
	abstime.time.tv_nsec = newtime->tv_nsec;
	itimer_init(&itimer, abstime.cs, 0);
}

void getnsofday(struct timespec *t, struct timezone *tz) {
	struct timespec ts = {
			.tv_sec = abstime.time.tv_sec,
			.tv_nsec = abstime.time.tv_nsec
	};
	time64_t cur;
       
	assert(itimer.cs);
	assert(itimer.cs->read);
	cur = itimer.cs->read(itimer.cs);

	ts = timespec_add_ns(ts, cur);

	t->tv_sec = ts.tv_sec;
	t->tv_nsec = ts.tv_nsec;
}

static int time_init(void) {
	extern struct clock_source *kernel_clock_source;

	abstime.cs = kernel_clock_source;
	itimer_init(&itimer, kernel_clock_source, 0);

	return 0;
}

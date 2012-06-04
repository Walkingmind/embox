/**
 * @file
 *
 * @brief
 *
 * @date 15.05.2012
 * @author Anton Bondarev
 */

#ifndef KERNEL_TIME_TIMECOUNTER_H_
#define KERNEL_TIME_TIMECOUNTER_H_

#include <kernel/clock_event.h>
#include <kernel/ktime.h>

extern void timecounter_init(struct timecounter *tc,
		const struct clock_event_device *dev, ns_t start_tstamp);

extern ns_t timecounter_read(struct timecounter *tc);

#endif /* KERNEL_TIME_TIMECOUNTER_H_ */

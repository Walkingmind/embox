/*
 * @file Time format conversion
 *
 * @date 11.05.2012
 * @author Alexander Kalmuk
 */

#ifndef KERNEL_KTIME_H_
#define KERNEL_KTIME_H_

#include <stdint.h>

/* Parameters used to convert the time specific values */
#define MSEC_PER_SEC    1000L
#define USEC_PER_MSEC   1000L
#define NSEC_PER_USEC   1000L

/* nanosecond-resolution time format */
typedef uint64_t ns_t;

/*
 * Given a period in ns and frequency in khz, calculate the number of
 * cycles of frequency in period.  Note that we round up to the next
 * cycle, even if we are only slightly over.
 */
static inline uint64_t ns_to_cycles(uint64_t ns, uint32_t khz) {
	return (ns * khz + 999999) / 1000000;
}

static inline ns_t cycles_to_ns(uint64_t cls, uint32_t khz) {
	return (cls * khz + 999999) / 1000000;
}

#endif /* KERNEL_KTIME_H_ */

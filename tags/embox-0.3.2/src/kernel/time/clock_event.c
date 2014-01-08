/**
 * @file
 * @brief
 *
 * @date 16.05.2012
 * @author Alexander Kalmuk
 */
#if 0
#include <util/array.h>
#include <string.h>
#include <kernel/clock_event.h>

ARRAY_SPREAD_DEF(const struct clock_event_device *, __clock_devices);

const struct clock_event_device *cedev_get_by_name(const char *name) {
	const struct clock_event_device *dev;

	array_foreach(dev, __clock_devices, ARRAY_SPREAD_SIZE(__clock_devices)) {
		if (0 == strcmp(dev->name, name)) {
			return dev;
		}
	}

	return NULL;
}

uint32_t clock_source_clock_to_sec(struct clock_source *cs, uint32_t ticks) {
	return ticks / cs->event_device->resolution;
}

const struct clock_event_device *cedev_get_best(enum resolution_mode mode) {
	const struct clock_event_device *dev, *best;
	int best_resolution;

	best_resolution = 0;
	best = NULL;
	switch(mode) {
	case TICKS:
		array_foreach(dev, __clock_devices, ARRAY_SPREAD_SIZE(__clock_devices)) {
			if (dev->resolution > best_resolution) {
				best_resolution = dev->resolution;
				best = dev;
			}
		}
		break;
	case JIFFIES:
		array_foreach(dev, __clock_devices, ARRAY_SPREAD_SIZE(__clock_devices)) {
			if (dev->cs->resolution > best_resolution) {
				best_resolution = dev->cs->resolution;
				best = dev;
			}
		}
		break;
	default:
		break;
	}

	return best;
}
#endif
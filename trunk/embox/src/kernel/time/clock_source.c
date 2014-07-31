/**
 * @file
 * @brief
 *
 * @date 19.06.2012
 * @author Alexander Kalmuk
 * @author Roman Kurbatov
 *         - clock_source_get_list() function.
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <util/array.h>
#include <util/dlist.h>
#include <util/math.h>

#include <mem/misc/pool.h>

#include <kernel/panic.h>
#include <kernel/time/clock_source.h>
#include <kernel/time/time.h>
#include <module/embox/kernel/time/slowdown.h>

#define SLOWDOWN_FACTOR OPTION_MODULE_GET(embox__kernel__time__slowdown, NUMBER, factor)

#include <embox/unit.h>

ARRAY_SPREAD_DEF(const struct time_event_device *, __event_devices);
ARRAY_SPREAD_DEF(const struct time_counter_device *, __counter_devices);

POOL_DEF(clock_source_pool, struct clock_source_head,
						OPTION_GET(NUMBER, clocks_quantity));

DLIST_DEFINE(clock_source_list);

static time64_t cs_full_read(struct clock_source *cs);
static time64_t cs_event_read(struct clock_source *cs);
static time64_t cs_counter_read(struct clock_source *cs);

static inline cycle_t cs_jiffies(struct clock_source *cs) {
	return (cycle_t) cs->jiffies * SLOWDOWN_FACTOR + (cycle_t) cs->jiffies_cnt;
}

static struct clock_source_head *clock_source_find(struct clock_source *cs) {
	struct clock_source_head *csh;

	dlist_foreach_entry(csh, &clock_source_list, lnk) {
		if (cs == csh->clock_source) {
			return csh;
		}
	}

	return NULL;
}

int clock_source_register(struct clock_source *cs) {
	struct clock_source_head *csh;

	if (!cs) {
		return -EINVAL;
	}
	csh = (struct clock_source_head *) pool_alloc(&clock_source_pool);
	if (!csh) {
		return -EBUSY;
	}
	csh->clock_source = cs;

	dlist_add_prev(dlist_head_init(&csh->lnk), &clock_source_list);

	return ENOERR;
}

int clock_source_unregister(struct clock_source *cs) {
	struct clock_source_head *csh;

	if (!cs) {
		return -EINVAL;
	}
	if (NULL == (csh = clock_source_find(cs))) {
		return -EBADF;
	}

	return ENOERR;
}

time64_t clock_source_read(struct clock_source *cs) {
	time64_t ret;
	assert(cs);

	/* See comment to clock_source_read in clock_source.h */
	if (cs->event_device && cs->counter_device) {
		ret = cs_full_read(cs);
	} else if (cs->event_device) {
		ret = cs_event_read(cs);
	} else if (cs->counter_device) {
		ret = cs_counter_read(cs);
	} else {
		panic("all clock sources must have at least one device (event or counter)\n");
	}

	ret /= SLOWDOWN_FACTOR;
	return ret;
}

static time64_t cs_full_read(struct clock_source *cs) {
	static cycle_t prev_cycles, cycles, cycles_all;
	int old_jiffies, cycles_per_jiff, safe;
	struct time_event_device *ed;
	struct time_counter_device *cd;

	assert(cs);

	ed = cs->event_device;
	assert(ed);
	assert(ed->event_hz != 0);

	cd = cs->counter_device;
	assert(cd);
	assert(cd->read);
	assert(cd->cycle_hz != 0);

	cycles_per_jiff = cd->cycle_hz / ed->event_hz;
	safe = 0;

	do {
		old_jiffies = cs_jiffies(cs);
		cycles = cd->read();
		safe++;
	} while (old_jiffies != cs_jiffies(cs) && safe < 3);

	if (ed->pending && ed->pending(ed->irq_nr)) {
		old_jiffies++;
	}

	cycles_all = cycles + (time64_t)old_jiffies * cycles_per_jiff;

	/* TODO cheat. read() will miss for one jiff sometimes. */
	if (cycles_all < prev_cycles) {
		cycles_all += cycles_per_jiff;
	}

	prev_cycles = cycles_all;

	return cycles_to_ns(cd->cycle_hz, cycles_all);
}

static time64_t cs_event_read(struct clock_source *cs) {
	return cycles_to_ns(cs->event_device->event_hz, cs_jiffies(cs));
}

static time64_t cs_counter_read(struct clock_source *cs) {
	return cycles_to_ns(cs->counter_device->cycle_hz, cs->counter_device->read());
}

struct clock_source *clock_source_get_best(enum clock_source_property pr) {
	struct clock_source *cs, *best;
	struct clock_source_head *csh;
	uint32_t best_resolution = 0;
	uint32_t resolution = 0;

	best = NULL;

	dlist_foreach_entry(csh, &clock_source_list, lnk) {
		cs = csh->clock_source;
		
		switch (pr) {
			case CS_ANY:
			case CS_WITH_IRQ:
				if (cs->event_device) {
					resolution = cs->event_device->event_hz;
				}

				if (pr == CS_ANY && cs->counter_device) {
					resolution = max(resolution, cs->counter_device->cycle_hz);
				}
				if (resolution > best_resolution) {
					best_resolution = resolution;
					best = cs;
				}	
			break;
			
			case CS_WITHOUT_IRQ:
				if (cs->counter_device) {
					resolution = cs->counter_device->cycle_hz;
				}
				if (resolution > best_resolution) {
					best_resolution = resolution;
					best = cs;
				}
			break;
		}
	}

	return best;
}

struct dlist_head *clock_source_get_list(void) {
	return &clock_source_list;
}

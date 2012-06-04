/**
 * @file
 * @brief Programmable Interval Timer (PIT) chip driver
 *
 * @date 27.12.10
 * @author Nikolay Korotky
 */

#include <types.h>
#include <errno.h>

#include <asm/io.h>
#include <hal/clock.h>
#include <hal/interrupt.h>
#include <kernel/irq.h>
#include <kernel/panic.h>
#include <util/array.h>
//#include <embox/unit.h>

#include <kernel/clock_source.h>
#include <kernel/clock_event.h>
#include <kernel/ktime.h>

#define INPUT_CLOCK        1193182L /* clock tick rate, Hz */
#define IRQ0               0x0

#define PIT_HZ 1000
static void pit_clock_setup(uint32_t mode);
static int pit_clock_init(void);
static struct clock_source pit_clock_source;

//EMBOX_UNIT_INIT(pit_clock_init);

/**
 * The PIT chip uses the following I/O ports:
 * I/O port     Usage
 * 0x40         Channel 0 data port (read/write)
 * 0x41         Channel 1 data port (read/write)
 * 0x42         Channel 2 data port (read/write)
 * 0x43         Mode/Command register (write only, a read is ignored):
 * +---------------+------------+--------------+---------------+
 * |7             6|5          4|3            1|              0|
 * |Select channel |Access mode |Operating mode|BCD/Binary mode|
 *
 * Select channel:
 *           00 = Channel 0
 *           01 = Channel 1
 *           10 = Channel 2
 *           11 = Read-back command (8254 only)
 * Access mode:
 *           00 = Latch count value command
 *           01 = Access mode: lobyte only
 *           10 = Access mode: hibyte only
 *           11 = Access mode: lobyte/hibyte
 * Operating mode:
 *           000 = Mode 0 (interrupt on terminal count)
 *           001 = Mode 1 (hardware re-triggerable one-shot)
 *           010 = Mode 2 (rate generator)
 *           011 = Mode 3 (square wave generator)
 *           100 = Mode 4 (software triggered strobe)
 *           101 = Mode 5 (hardware triggered strobe)
 *           110 = Mode 2 (rate generator, same as 010b)
 *           111 = Mode 3 (square wave generator, same as 011b)
 * BCD/Binary mode: 0 = 16-bit binary, 1 = four-digit BCD
 */
#define CHANNEL0 0x40
#define CHANNEL1 0x41
#define CHANNEL2 0x42
#define MODE_REG 0x43

/* Mode register bits */
#define PIT_SEL0        0x00    /* select counter 0 */
#define PIT_SEL1        0x40    /* select counter 1 */
#define PIT_SEL2        0x80    /* select counter 2 */
#define PIT_INTTC       0x00    /* mode 0, intr on terminal cnt */
#define PIT_ONESHOT     0x02    /* mode 1, one shot */
#define PIT_RATEGEN     0x04    /* mode 2, rate generator */
#define PIT_SQWAVE      0x06    /* mode 3, square wave */
#define PIT_SWSTROBE    0x08    /* mode 4, s/w triggered strobe */
#define PIT_HWSTROBE    0x0a    /* mode 5, h/w triggered strobe */
#define PIT_LATCH       0x00    /* latch counter for reading */
#define PIT_LSB         0x10    /* r/w counter LSB */
#define PIT_MSB         0x20    /* r/w counter MSB */
#define PIT_16BIT       0x30    /* r/w counter 16 bits, LSB first */
#define PIT_BCD         0x01    /* count in BCD */

static cycle_t i8253_read(const struct cyclecounter *cc) {
	int cnt;

	out8(0x00, MODE_REG);
	/* mb irq_lock */
	cnt = in8(CHANNEL0);
	cnt |= in8(CHANNEL0) << 8;

	cnt = (((INPUT_CLOCK + PIT_HZ / 2) / PIT_HZ) - 1) - cnt;

	return cnt;
}

static volatile uint32_t pit_jiffies = 0;

static inline uint32_t pit_get_jiffies(void) {
	return pit_jiffies;
}

static struct cyclecounter cc = {
	.read = i8253_read,
	.mult = 1,
	.shift = 0
};

static struct clock_event_device pit_device = {
	.set_mode = pit_clock_setup,
	.init = pit_clock_init,
	.cs = &pit_clock_source,
	.resolution = INPUT_CLOCK,
	//.get_jiffies = pit_get_jiffies
	.name = "pit"
};

static struct clock_source pit_clock_source = {
	.name = "pit",
	.flags = 0, /* this flag will be set to correct value by set_mod function */
	.resolution = PIT_HZ,
	.dev = &pit_device,
	.read = pit_get_jiffies,
	.cc = &cc
};


CLOCK_EVENT_DEVICE(&pit_device);

static irq_return_t clock_handler(int irq_nr, void *dev_id) {
	pit_jiffies++;
	clock_tick_handler(irq_nr, dev_id);
	return IRQ_HANDLED;
}

static int pit_clock_init(void) {
	/* Initialization and registration of clock source structure */
	pit_clock_source.flags = 1;
	pit_clock_source.resolution = INPUT_CLOCK;
	pit_clock_source.cc = &cc;
	clock_source_register(&pit_clock_source);

	/* Calculate mult/shift constants to set clock_source used by timer */
	clock_source_calc_mult_shift(&pit_clock_source, INPUT_CLOCK, 0);

	/* Setup initial mode to allow to use timer immediately after initialization
	 * of this module */
	pit_clock_setup(PIT_RATEGEN);

	if (ENOERR != irq_attach((irq_nr_t) IRQ0,
		(irq_handler_t) &clock_handler, 0, NULL, "PIT")) {
		panic("pit timer irq_attach failed");
	}

	return 0;
}

static void pit_clock_setup(uint32_t mode) {
	uint32_t divisor = (INPUT_CLOCK + PIT_HZ / 2) /PIT_HZ;
	/* Propose switch by all modes in future */
	/* Set control byte */
	out8(PIT_RATEGEN | PIT_16BIT | PIT_SEL0, MODE_REG);

	/* Send divisor */
	out8(divisor & 0xFF, CHANNEL0);
	out8((divisor >> 8) & 0xFF, CHANNEL0);
}

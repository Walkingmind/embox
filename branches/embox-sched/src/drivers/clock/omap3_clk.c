/**
 * @file
 * @brief OMAP35x clock device driver
 *
 * @date 15.10.12
 * @author Ilia Vaprol
 */

#include <drivers/irqctrl.h>
#include <hal/clock.h>
#include <hal/reg.h>
#include <hal/system.h>
#include <kernel/irq.h>
#include <kernel/time/clock_source.h>
#include <kernel/printk.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(ti_clk_init);

/* ti8168's timer1 related */

#define TI8168_CLKIN_HZ 27000000

#define CM_TIMER1_CLKSEL 0x48180390
#define CM_CLKIN 0x2

#define GPTIMER31_01_TIDR 0xfff1301
#define GPTIMER31_01_MASK 0xfffffff

#define TI8168_GPTIMER1_BASE ((void *) 0x4802e000)
#define TI8168_GPTIMER1_IRQ 67

#define TI8168_LOAD_VALUE (0xffffffff - (TI8168_CLKIN_HZ / 1000) + 1)

struct gptimer13_1 {
	uint32_t tidr; 		/* 0x00 */
	char unused0[12];	/* 0x04 */
	uint32_t cfg;		/* 0x10 */
	char unused1[12];	/* 0x14 */
	uint32_t eoi;		/* 0x20 */
	uint32_t irqstat_raw;	/* 0x24 */
	uint32_t irqstat;	/* 0x28 */
	uint32_t irqenable_set;	/* 0x2c */
	uint32_t irqenable_clr;	/* 0x30 */
	uint32_t irqwakeen;	/* 0x34 */
	uint32_t tclr;		/* 0x38 */
	uint32_t tcrr;		/* 0x3c */
	uint32_t tldr;		/* 0x40 */
} __attribute__((packed));

/* omap's gptimer */

#define CM_FCLKEN_WKUP  0x48004C00
#define CM_ICLKEN_WKUP  0x48004C10
#define CM_CLKSEL_WKUP  0x48004C40

#define GPTIMER1_BASE ((void *) 0x48318000)
#define GPTIMER1_IRQ 37

struct gptimerxx_x {
	uint32_t tidr; 		/* 0x00 */
	char unused0[12];	/* 0x04 */
	uint32_t cfg;		/* 0x10 */
	uint32_t tistat;	/* 0x14 */
	uint32_t tisr;		/* 0x18 */
	uint32_t tier;		/* 0x1c */
	uint32_t twer;		/* 0x20 */
	uint32_t tclr;		/* 0x24 */
	uint32_t tcrr;		/* 0x28 */
	uint32_t tldr;		/* 0x2c */
	uint32_t ttgr;		/* 0x30 */
	uint32_t twps;		/* 0x34 */
	uint32_t tmar;		/* 0x38 */
	uint32_t tcar1;		/* 0x3c */
	uint32_t tsicr;		/* 0x40 */
	uint32_t tcar2;		/* 0x44 */
	uint32_t tpir;		/* 0x48 */
	uint32_t tnir;		/* 0x4c */
	uint32_t tcvr;		/* 0x50 */
	uint32_t tocr;		/* 0x54 */
	uint32_t towr;		/* 0x54 */
} __attribute__((packed));

#define OMAP_LOAD_VALUE 0xffffffe0

/* common register values */

#define GPTIMER_TCLR_START	(1 << 0)
#define GPTIMER_TCLR_AUTORELOAD (1 << 1)

#define GPTIMER_TIER_OVERFLOW   (1 << 1)
#define GPTIMER_TISR_OVERFLOW   (1 << 1)

static cycle_t common_clk_read(void) {
	return 0;
}

static struct time_counter_device common_clk_counter = {
	.read = common_clk_read,
};

static irq_return_t clock_handler(unsigned int irq_nr, void *data) {
	volatile struct gptimerxx_x *gptimer = GPTIMER1_BASE;
	clock_tick_handler(irq_nr, data);
	REG_STORE(&gptimer->tisr, GPTIMER_TISR_OVERFLOW);
	return IRQ_HANDLED;
}

static int omap3_clk_config(struct time_dev_conf *conf) {
	volatile struct gptimerxx_x *gptimer = GPTIMER1_BASE;

	REG_ORIN(CM_FCLKEN_WKUP, 1);
	REG_ORIN(CM_ICLKEN_WKUP, 1);
	REG_ANDIN(CM_CLKSEL_WKUP, ~1);

	REG_STORE(&gptimer->cfg, 0x2);

	REG_STORE(&gptimer->tpir, 232000);
	REG_STORE(&gptimer->tnir, -768000);

	REG_STORE(&gptimer->tcrr, OMAP_LOAD_VALUE);
	REG_STORE(&gptimer->tldr, OMAP_LOAD_VALUE);

	REG_STORE(&gptimer->tclr, GPTIMER_TCLR_START | GPTIMER_TCLR_AUTORELOAD);

	REG_STORE(&gptimer->tier, GPTIMER_TIER_OVERFLOW);
	REG_STORE(&gptimer->twer, GPTIMER_TIER_OVERFLOW);

	return 0;
}

static struct time_event_device omap3_clk_event = {
	.config = omap3_clk_config,
	.resolution = 1000,
	.irq_nr = GPTIMER1_IRQ,
};

static struct clock_source omap3_clk_clock_source = {
	.name = "omap3_clk",
	.event_device = &omap3_clk_event,
	.counter_device = &common_clk_counter,
	.read = clock_source_read,
};

irq_return_t ti8168_clock_handler(unsigned int irq_nr, void *data) {
	volatile struct gptimer13_1 *gptimer = TI8168_GPTIMER1_BASE;

	clock_tick_handler(irq_nr, data);

	REG_STORE(&gptimer->irqstat, GPTIMER_TISR_OVERFLOW);
	REG_STORE(&gptimer->eoi, 0);

	return IRQ_HANDLED;
}

static int ti8168_clk_config(struct time_dev_conf *conf) {
	volatile struct gptimer13_1 *gptimer = TI8168_GPTIMER1_BASE;

	REG_STORE(CM_TIMER1_CLKSEL, CM_CLKIN);

	REG_STORE(&gptimer->cfg, 0x01);

	while (REG_LOAD(&gptimer->cfg) & 0x01);

	REG_STORE(&gptimer->tcrr, TI8168_LOAD_VALUE);
	REG_STORE(&gptimer->tldr, TI8168_LOAD_VALUE);

	REG_STORE(&gptimer->tclr, GPTIMER_TCLR_START | GPTIMER_TCLR_AUTORELOAD);

	REG_STORE(&gptimer->irqenable_set, GPTIMER_TIER_OVERFLOW);
	REG_STORE(&gptimer->irqwakeen, GPTIMER_TIER_OVERFLOW);

	return 0;
}

static struct time_event_device ti8168_clk_event = {
	.config = ti8168_clk_config,
	.resolution = 1000,
	.irq_nr = TI8168_GPTIMER1_IRQ,
};

struct clock_source ti8168_clk_clock_source = {
	.name = "ti8168",
	.event_device = &ti8168_clk_event,
	.counter_device = &common_clk_counter,
	.read = clock_source_read,
};

static bool gptimer_detect(uint32_t tidr_val, uint32_t mask, void *base) {
	return (mask & REG_LOAD(base)) == (mask & tidr_val);
}

static int ti_clk_init(void) {
	if (gptimer_detect(GPTIMER31_01_TIDR, GPTIMER31_01_MASK, TI8168_GPTIMER1_BASE)) {
		printk("TI8168 gptimer detected on %p\n", TI8168_GPTIMER1_BASE);
		clock_source_register(&ti8168_clk_clock_source);
		return irq_attach(ti8168_clk_event.irq_nr, ti8168_clock_handler, 0, &ti8168_clk_clock_source, "omap3_clk");

	}

	clock_source_register(&omap3_clk_clock_source);
	return irq_attach(GPTIMER1_IRQ, clock_handler, 0, &omap3_clk_clock_source, "omap3_clk");
}


/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    14.10.2013
 */

#include <drivers/irqctrl.h>
#include <hal/clock.h>
#include <hal/reg.h>
#include <hal/system.h>
#include <kernel/irq.h>
#include <kernel/time/clock_source.h>
#include <kernel/printk.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(ti8168_clk_init);

#define TI8168_CLKIN_HZ 27000000

#define CM_TIMER1_CLKSEL 0x48180390
#define CM_CLKIN 0x2

#define GPTIMER31_01_TIDR 0xfff1301
#define GPTIMER31_01_MASK 0xfffffff

#define TI8168_GPTIMER1_BASE ((void *) 0x4802e000)
#define TI8168_GPTIMER1_IRQ 67

#define TI8168_LOAD_VALUE (0xffffffff - (TI8168_CLKIN_HZ / 1000) + 1)

/* common register values */

#define GPTIMER_TCLR_START	(1 << 0)
#define GPTIMER_TCLR_AUTORELOAD (1 << 1)

#define GPTIMER_TIER_OVERFLOW   (1 << 1)
#define GPTIMER_TISR_OVERFLOW   (1 << 1)

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
	.read = clock_source_read,
};

static int ti8168_clk_init(void) {

	clock_source_register(&ti8168_clk_clock_source);
	return irq_attach(ti8168_clk_event.irq_nr, ti8168_clock_handler, 0, &ti8168_clk_clock_source, "omap3_clk");
}

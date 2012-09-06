/**
 * @file
 * @brief Gaisler Research IRQMP Interrupt controller driver.
 *
 * @date 14.04.09
 * @author Anton Bondarev
 * @author Eldar Abusalimov
 */

#include <assert.h>
#include <errno.h>
#include <types.h>

#include <drivers/irqctrl.h>
#include <hal/reg.h>
#include <drivers/amba_pnp.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(unit_init);

struct irqmp_regs {
	/* 0x00 */uint32_t level;
	/* 0x04 */uint32_t pending;
	/* 0x08 */uint32_t force;
	/* 0x0C */uint32_t clear;
	/* 0x10 */uint32_t mpstatus;
	/* 0x14 */uint32_t broadcast;
	/* 0x18 */uint32_t dummy[10];
	/* 0x40 */uint32_t mask;
};

static volatile struct irqmp_regs *dev_regs;

static int dev_regs_init(void);

void interrupt_enable(unsigned int interrupt_nr) {
	assert(interrupt_nr_valid(interrupt_nr));
	assert(NULL != dev_regs);
	REG_ORIN(&dev_regs->mask, 1 << interrupt_nr);
}

void interrupt_disable(unsigned int interrupt_nr) {
	assert(interrupt_nr_valid(interrupt_nr));
	assert(NULL != dev_regs);
	REG_ANDIN(&dev_regs->mask, ~(1 << interrupt_nr));
}

void interrupt_clear(unsigned int interrupt_nr) {
	assert(interrupt_nr_valid(interrupt_nr));
	assert(NULL != dev_regs);
	REG_ORIN(&dev_regs->clear, 1 << interrupt_nr);
	REG_ANDIN(&dev_regs->force, ~(1 << interrupt_nr));
}

void interrupt_force(unsigned int interrupt_nr) {
	assert(interrupt_nr_valid(interrupt_nr));
	assert(NULL != dev_regs);
	REG_ORIN(&dev_regs->force, 1 << interrupt_nr);
}

static int unit_init(void) {
	int error;

	assert(NULL == dev_regs);
	if (0 != (error = dev_regs_init())) {
		return error;
	}
	assert(NULL != dev_regs);

	REG_STORE(&dev_regs->level, 0x0);
	REG_STORE(&dev_regs->mask, 0x0);
	REG_STORE(&dev_regs->pending, 0x0);
	REG_STORE(&dev_regs->force, 0x0);
	REG_STORE(&dev_regs->clear, ~0x0);

	return 0;
}


#ifdef DRIVER_AMBAPP
static int dev_regs_init(void) {
	amba_dev_t amba_dev;
	if (-1 == capture_amba_dev(&amba_dev, AMBAPP_VENDOR_GAISLER,
			AMBAPP_DEVICE_GAISLER_IRQMP, false, false)) {
		return -ENODEV;
	}
	dev_regs = (volatile struct irqmp_regs *) amba_dev.bar[0].start;
	return 0;
}
#elif OPTION_DEFINED(NUMBER,irqmp_base)
static int dev_regs_init(void) {
	dev_regs = (volatile struct irqmp_regs *) OPTION_GET(NUMBER,irqmp_base);
	return 0;
}
#else
# error "Either DRIVER_AMBAPP or irqmp_base option must be defined"
#endif /* DRIVER_AMBAPP */

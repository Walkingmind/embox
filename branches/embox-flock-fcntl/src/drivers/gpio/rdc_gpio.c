/**
 * @file
 * @brief RDC GPIO driver
 *
 * @date 31.03.11
 * @author Nikolay Korotkiy
 */

#include <assert.h>
#include <asm/io.h>
#include <embox/unit.h>

#include <drivers/gpio.h>

EMBOX_UNIT_INIT(gpio_init);

#define RDC_CONTROL   0x80003848
#define RDC_DATA      0x8000384c

#define PCI_ADDR_SEL  0xcf8
#define PCI_DATA_REG  0xcfc

#define GPIO_RTCRD    (1 << 16) /* Red LED */
#define GPIO_RTCAS    (1 << 15) /* Reset button */

static unsigned long g_last_value = 0xffffffff;

static inline void set_control(unsigned long mask) {
	unsigned long tmp;
	/* Select control register */
	out32(RDC_CONTROL, PCI_ADDR_SEL);
	tmp = in32(PCI_DATA_REG);
	/* raise to set GPIO function */
	tmp |= mask;
	out32(tmp, PCI_DATA_REG);
}

static inline void set_data(unsigned long mask) {
	out32(RDC_DATA, PCI_ADDR_SEL);
	g_last_value |= mask;
	out32(g_last_value, PCI_DATA_REG);
}

static inline void clear_data(unsigned long mask) {
	out32(RDC_DATA, PCI_ADDR_SEL);
	g_last_value &= ~mask;
	out32(g_last_value, PCI_DATA_REG);
}

int gpio_settings(struct gpio *gpio, gpio_mask_t mask, int mode) {
	assert(gpio);

	if ((mode & GPIO_MODE_OUT_SECTION) &&
		(mode & GPIO_MODE_IN_SECTION)) { /* mode is incorrect */
		return -1;
	}

	if (mode & GPIO_MODE_INPUT) {
		/* raise logic level to turn off pull-down */
		set_data(mask);
		/* select as GPIO function */
		set_control(mask);
	} else if (mode & GPIO_MODE_OUTPUT) {
		set_control(mask);
	}

	return 0;
}

void gpio_set_level(struct gpio *gpio, gpio_mask_t mask, char level) {

	if(level) {
		set_data(mask);
	} else {
		clear_data(mask);
	}
}

gpio_mask_t gpio_get_level(struct gpio *gpio, gpio_mask_t mask) {
	unsigned long tmp;
	out32(RDC_DATA, PCI_ADDR_SEL);
	tmp = in32(PCI_DATA_REG);
	return tmp & mask;
}

static int gpio_init(void) {
	/* Example: blink led */
	set_control(GPIO_RTCRD);
	out32(RDC_DATA, PCI_ADDR_SEL);
//	out32(0, PCI_DATA_REG);          // red led on
//	out32(GPIO_RTCRD, PCI_DATA_REG); // red led off
	return 0;
}

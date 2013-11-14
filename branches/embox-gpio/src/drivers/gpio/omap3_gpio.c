/**
 * @file
 * @brief OMAP3 GPIO driver
 *
 * @date 1.11.13
 * @author Alexander Kalmuk
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <embox/unit.h>
#include <hal/reg.h>
#include <kernel/printk.h>
#include <drivers/pins.h>
#include <drivers/gpio.h>
#include "omap3_gpio.h"

EMBOX_UNIT_INIT(gpio_init);

static struct gpio omap_gpio[GPIO_MODULE_CNT];

pin_mask_t gpio_get_pin_changed(struct gpio *gpio) {
	return (int) gpio_reg_read(gpio->base, GPIO_IRQSTATUS1);
}

int gpio_settings(struct gpio *gpio, gpio_mask_t mask, int mode) {
	uint32_t l;

	assert(gpio);

	/* check if mode is incorrect */
	if (((mode & GPIO_MODE_OUT_SECTION) && (mode & GPIO_MODE_IN_SECTION)) ||
		((mode & GPIO_MODE_IN_INT_EN) && (mode & GPIO_MODE_IN_INT_DIS))) {
		return -1;
	}

	if (mode & GPIO_MODE_INPUT) {
		gpio_reg_write(gpio->base, GPIO_OE, mask);
	} else if (mode & GPIO_MODE_OUTPUT) {
		l = gpio_reg_read(gpio->base, GPIO_OE);
		gpio_reg_write(gpio->base, GPIO_OE, l & ~mask);
	}

	if (mode & GPIO_MODE_IN_INT_DIS) {
		/* clear front and level detect register, if you need */
		if (GPIO_MODE_INT_MODE_RISING) {
			l = gpio_reg_read(gpio->base, GPIO_RISINGDETECT);
			gpio_reg_write(gpio->base, GPIO_RISINGDETECT, l & ~mask);
		}

		if (GPIO_MODE_INT_MODE_FALLING) {
			l = gpio_reg_read(gpio->base, GPIO_FALLINGDETECT);
			gpio_reg_write(gpio->base, GPIO_FALLINGDETECT, l & ~mask);
		}

		if (GPIO_MODE_INT_MODE_LEVEL0) {
			l = gpio_reg_read(gpio->base, GPIO_LEVELDETECT0);
			gpio_reg_write(gpio->base, GPIO_LEVELDETECT0, l & ~mask);
		}

		if (GPIO_MODE_INT_MODE_LEVEL1) {
			l = gpio_reg_read(gpio->base, GPIO_LEVELDETECT1);
			gpio_reg_write(gpio->base, GPIO_LEVELDETECT1, l & ~mask);
		}
		/* clear oe flags */
		l = gpio_reg_read(gpio->base, GPIO_IRQENABLE1);
		gpio_reg_write(gpio->base, GPIO_IRQENABLE1, l & ~mask);

		return 0;
	}

	if (GPIO_MODE_INT_MODE_RISING) {
		gpio_reg_write(gpio->base, GPIO_RISINGDETECT, mask);
	}

	if (GPIO_MODE_INT_MODE_FALLING) {
		gpio_reg_write(gpio->base, GPIO_FALLINGDETECT, mask);
	}

	if (GPIO_MODE_INT_MODE_LEVEL0) {
		gpio_reg_write(gpio->base, GPIO_LEVELDETECT0, mask);
	}

	if (GPIO_MODE_INT_MODE_LEVEL1) {
		gpio_reg_write(gpio->base, GPIO_LEVELDETECT1, mask);
	}

	return 0;
}

void gpio_set_level(struct gpio *gpio, gpio_mask_t mask, char level) {
	uint32_t l;
	assert(gpio);
	assert((mask & ~((1 << 16) - 1)) == 0);

	if (level) {
		l = gpio_reg_read(gpio->base, GPIO_DATAOUT);
		gpio_reg_write(gpio->base, GPIO_DATAOUT, l | mask);
	} else {
		l = gpio_reg_read(gpio->base, GPIO_CLEARDATAOUT);
		gpio_reg_write(gpio->base, GPIO_CLEARDATAOUT, l | mask);
	}
}

gpio_mask_t gpio_get_level(struct gpio *gpio, gpio_mask_t mask){
	assert(gpio);
	return mask & (gpio_reg_read(gpio->base, GPIO_DATAIN));
}

irq_return_t irq_gpio_handler(unsigned int irq_nr, void *data) {
	int i;
	int changed;
	struct gpio *gpio;

	gpio = &omap_gpio[GPIO_NUM_BY_IRQ(irq_nr)];

	if (NULL == gpio) {
		return IRQ_NONE;
	}

	changed = gpio_get_pin_changed(gpio);

	for (i = 0; i < N_PINS; i++) {
		if (changed & gpio->pin[i].mask) {
			gpio->pin[i].handler(irq_nr, gpio->pin[i].data);
			gpio_reg_write(gpio->base, GPIO_IRQSTATUS1, changed & gpio->pin[i].mask);
			gpio_reg_write(gpio->base, GPIO_IRQSTATUS2, changed & gpio->pin[i].mask);
		}
	}

	return IRQ_HANDLED;
}

int gpio_pin_irq_attach(int gpio_nr, int pin_nr,
		void *pin_handler, unsigned int mode, void *data) {
	struct gpio *gpio;

	gpio = &omap_gpio[gpio_nr];
	assert(gpio);

	gpio->pin[pin_nr].handler = pin_handler;
	gpio->pin[pin_nr].mask = (1 << pin_nr);
	gpio->pin[pin_nr].data = data;
	gpio_settings(gpio, (1 << pin_nr),
			mode | GPIO_MODE_INPUT | GPIO_MODE_IN_INT_EN);

	return 0;
}

int gpio_pin_irq_detach(int gpio_nr, int pin_nr,
		void *pin_handler, unsigned int mode) {
	struct gpio *gpio;

	gpio = &omap_gpio[gpio_nr];
	assert(gpio);

	gpio->pin[pin_nr].handler = NULL;
	gpio_settings(gpio, (1 << pin_nr), mode | GPIO_MODE_IN_INT_DIS);

	return 0;
}

static int gpio_init(void) {
	uint32_t rev;
	int i, ret;
	struct gpio *gpio;
	char str [255];

	for(i = 0; i < GPIO_MODULE_CNT; i++) {

		gpio = &omap_gpio[i];

		memset(gpio, 0, sizeof(struct gpio));

		gpio->base = GPIO_BASE_ADDRESS(i);
		gpio->gpio_nr = i;

		rev = gpio_reg_read(gpio->base, GPIO_REVISION);
		printk("maj = %d, min = %d\n",
				GPIO_REVISION_MAJOR(rev), GPIO_REVISION_MINOR(rev));

		*str = 0;
		sprintf(str,"OMAP_GPIO%d", i);

		if (0 != (ret = irq_attach(GPIO_IRQ(i),
				irq_gpio_handler, 0, gpio, str))) {
			return ret;
		}
	}

	return 0;
}

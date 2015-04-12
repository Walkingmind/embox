/**
 * @file
 * @brief Soft I2C
 *
 * @date 12.12.10
 * @author Anton Kozlov
 */

#include <stdint.h>

#include <drivers/pins.h>
#include <embox/unit.h>
#include <kernel/irq.h>
#include <drivers/soft_i2c.h>
#include <drivers/at91sam7s256.h>
#include <drivers/timer_counter/at91_timer_counter.h>
#include <hal/reg.h>

#define TIMER 0
#define I2C_CLOCK 9600

EMBOX_UNIT_INIT(i2c_unit_init);

#define MAX_PORTS (sizeof(int))
i2c_port_t *ports[MAX_PORTS];
static int port_count = 0;

void pin_set_high(pin_mask_t mask) {
	pin_config_input(mask);
}

void pin_set_low(pin_mask_t mask) {
	pin_clear_output(mask);
	pin_config_output(mask);
}

void scl_set_low(pin_mask_t mask) {
	pin_clear_output(mask);
}

void scl_set_high(pin_mask_t mask) {
	pin_set_output(mask);
}

static void i2c_port_process(i2c_port_t *port) {
	REG_LOAD(AT91C_TC0_SR); //it's norm
	switch (port->state) {
	case SOFT_I2C_START:
		if (pin_get_input(port->sda) && pin_get_input(port->scl)) {
			pin_set_low(port->sda);
			port->state = SOFT_I2C_WRITE_FALL;
		}
		break;
	case SOFT_I2C_READ_FALL:
		if (pin_get_input(port->scl)) {
			scl_set_low(port->scl);
			port->state = SOFT_I2C_READ_RISE;
			if (port->bit_cnt == 8) {
				port->data++;
				port->bit_cnt = 0;
				port->state = SOFT_I2C_READ_ACK_RISE;
				if (port->data_cnt-- == 0) {
					port->state = SOFT_I2C_READ_NOT_ACK_RISE;
				}
			}
		}
		break;
	case SOFT_I2C_READ_NOT_ACK_RISE:
		pin_set_high(port->sda);
		scl_set_high(port->scl);
		port->state = SOFT_I2C_READ_NOT_ACK_FALL;
		break;
	case SOFT_I2C_READ_NOT_ACK_FALL:
		if (pin_get_input(port->scl)) {
			scl_set_low(port->scl);
			port->state = SOFT_I2C_STOP_DATA_FALL;
		}
		break;
	case SOFT_I2C_READ_RISE:
		scl_set_high(port->scl);
		if (pin_get_input(port->scl)) {
			uint8_t *ptr;
			ptr = port->data;
			*ptr = *ptr << 1;
			if (pin_get_input(port->sda)) {
				*ptr = *ptr | 1;
			}
			port->bit_cnt++;
			port->state = SOFT_I2C_READ_FALL;
		}
		break;
	case SOFT_I2C_READ_ACK_FALL:
		if (pin_get_input(port->scl)) {
			scl_set_low(port->scl);
			pin_set_high(port->sda);
			port->state = SOFT_I2C_READ_RISE;
		}
		break;
	case SOFT_I2C_READ_ACK_RISE:
		pin_set_low(port->sda);
		scl_set_high(port->scl);
		port->state = SOFT_I2C_READ_ACK_FALL;
		break;
	case SOFT_I2C_STOP_DATA_FALL:
		pin_set_low(port->sda);
		scl_set_high(port->scl);
		port->state = SOFT_I2C_STOP;
		break;
	case SOFT_I2C_STOP:
		if (pin_get_input(port->scl)) {
			pin_set_high(port->sda);
			port->state = SOFT_I2C_STOP_FALL;
		}
		break;
	case SOFT_I2C_STOP_FALL:
		if (pin_get_input(port->sda) && pin_get_input(port->scl)) {
			scl_set_low(port->scl);
			port->state = SOFT_I2C_STOP_RISE;
		}
		break;
	case SOFT_I2C_STOP_RISE:
		scl_set_high(port->scl);
		port->state = SOFT_I2C_IDLE;
		break;
	case SOFT_I2C_WRITE_FALL:
		if (pin_get_input(port->scl)) {
			scl_set_low(port->scl);
			if (port->write_byte & 0x80) {
				pin_set_high(port->sda);
			} else {
				pin_set_low(port->sda);
			}
			port->write_byte <<= 1;
			if (port->bit_cnt-- == 0) { //0_o
				pin_set_high(port->sda);
				port->state = SOFT_I2C_WRITE_ACK_RISE;
			} else {
				port->state = SOFT_I2C_WRITE_RISE;
			}
		}
		break;
	case SOFT_I2C_WRITE_RISE:
		scl_set_high(port->scl);
		port->state = SOFT_I2C_WRITE_FALL;
		break;
	case SOFT_I2C_WRITE_ACK_RISE:
		scl_set_high(port->scl);
		port->state = SOFT_I2C_WRITE_ACK_FALL;
		if (port->operation == SOFT_I2C_OPERATION_WRITE) {
			port->write_byte = *(port->data++);
			port->bit_cnt = 8;
		}
		break;
	case SOFT_I2C_WRITE_ACK_FALL:
		if (pin_get_input(port->scl)) {
			uint32_t was_state = pin_get_input(port->sda);
			scl_set_low(port->scl);
			if (was_state) {
				port->state = SOFT_I2C_STOP_DATA_FALL;
			} else {
				if (port->operation == SOFT_I2C_OPERATION_WRITE) {
					if (port->write_byte & 0x80) {
						pin_set_high(port->sda);
					} else {
						pin_set_low(port->sda);
					}
					port->write_byte <<= 1;
					port->bit_cnt--;
					port->state = SOFT_I2C_WRITE_RISE;
				} else {
					port->bit_cnt = 0;
					port->state = SOFT_I2C_READ_RISE;
				}
			}
			if (port->data_cnt-- == 0) {
				port->state = SOFT_I2C_STOP_DATA_FALL;
			}
		}
		break;
	case SOFT_I2C_IDLE:
	default:
		break;
	}
}

void i2c_read(i2c_port_t *port, uint8_t addr, uint8_t *data, uint32_t count) {
	port->data = data;
	port->data_cnt = count;
	port->operation = SOFT_I2C_OPERATION_READ;
	port->write_byte = (addr << 1) | 1;
	port->bit_cnt = 8;
	pin_set_high(port->sda);
	scl_set_high(port->scl);
	port->state = SOFT_I2C_START;
}

void i2c_write(i2c_port_t *port, uint8_t addr, uint8_t *data, uint32_t count) {
	port->data = data;
	port->data_cnt = count;
	port->operation = SOFT_I2C_OPERATION_WRITE;
	port->write_byte = (addr << 1) | 0;
	port->bit_cnt = 8;
	pin_set_high(port->sda);
	scl_set_high(port->scl);
	port->state = SOFT_I2C_START;
}

static irq_return_t timer_handler(unsigned int irq_nr, void *data) {
	size_t i;
	REG_LOAD(((uint8_t *) AT91C_TC0_SR) + TIMER * sizeof(AT91S_TCB));
	for (i = 0; i < port_count; i++) {
		i2c_port_process(ports[i]);
	}
	tc_reset(TIMER);
	return IRQ_HANDLED;
}

void i2c_init(i2c_port_t *port) {
	ports[port_count++] = port;
	REG_STORE(AT91C_PIOA_PER, port->scl | port->sda);
	REG_STORE(AT91C_PIOA_PPUER, port->sda);
	REG_STORE(AT91C_PIOA_ODR, port->sda);

	REG_STORE(AT91C_PIOA_MDER, port->scl);
	REG_STORE(AT91C_PIOA_PPUER, port->scl);
	REG_STORE(AT91C_PIOA_SODR, port->scl);
	REG_STORE(AT91C_PIOA_OER, port->scl);

	port->state = SOFT_I2C_IDLE;
}

static int i2c_unit_init(void) {
	tc_init(TIMER);
	/* MCLK/2, RC compare trigger */
	tc_config_input(TIMER, (uint32_t) AT91C_TC_CLKS_TIMER_DIV1_CLOCK);
	/* running on twice speed i2c_clock*/
	tc_set_limit(TIMER, (CONFIG_SYS_CLOCK/2)/(2 * I2C_CLOCK));
	tc_limit_int_enable(TIMER, timer_handler);
	tc_reset(TIMER);
	return 0;
}

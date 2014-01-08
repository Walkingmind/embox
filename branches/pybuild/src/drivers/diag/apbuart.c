/**
 * @file
 * @brief TODO
 *
 * @date 14.02.10
 * @author Eldar Abusalimov
 */

#include <types.h>

#include <embox/unit.h>
#include <hal/reg.h>
#include <hal/system.h>
#include <prom/diag.h>

#define APBUART_BASE  0x80000100
#define DATA_REG             0x0
#define STATUS_REG           0x4
#define CTRL_REG             0x8
#define SCALER_REG           0xc

#define BAUD_RATE \
	OPTION_GET(NUMBER, baud_rate)

#define SCALER_VAL \
	(((SYS_CLOCK * 10) / (BAUD_RATE * 8) - 5) / 10)

void diag_init(void) {
	REG_STORE((volatile uint32_t *) (APBUART_BASE + SCALER_REG), SCALER_VAL);
	REG_STORE((volatile uint32_t *) (APBUART_BASE + CTRL_REG), 0x3);
}

char diag_getc(void) {
	while (!(0x1 & REG_LOAD((volatile uint32_t *) (APBUART_BASE + STATUS_REG)))) {
	}
	return ((char) REG_LOAD((volatile uint32_t *) (APBUART_BASE + DATA_REG)));
}

int diag_has_symbol(void) {
	return (0x1 & REG_LOAD((volatile uint32_t *) (APBUART_BASE + STATUS_REG)));
}

void diag_putc(char ch) {
	while (!(0x4 & REG_LOAD((volatile uint32_t *) (APBUART_BASE + STATUS_REG)))) {
	}
	REG_STORE((volatile uint32_t *) (APBUART_BASE + DATA_REG), (uint32_t) ch);
}
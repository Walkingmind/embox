/**
 * @file
 * @brief
 *
 * @author  Anton Kozlov
 * @date    03.07.2012
 */

#include <stdint.h>

#include <drivers/gpio.h>
#include <hal/reg.h>
#include <hal/system.h>
#include <drivers/diag.h>
#include <embox/unit.h>

#include <drivers/uart_device.h>

EMBOX_UNIT_INIT(stm32uart_mod_init);

struct uart_stm32 {
	uint16_t sr;
	uint16_t reserv0;
	uint16_t dr;
	uint16_t reserv1;
	uint16_t brr;
	uint16_t reserv2;
	uint16_t cr1;
	uint16_t reserv3;
	uint16_t cr2;
	uint16_t reserv4;
	uint16_t cr3;
	uint16_t reserv5;
	uint16_t gtpr;
} __attribute__ ((packed));

#define RCC_APB1RSTR  0x40021010
#define RCC_APB1PWR   0x10000000
#define RCC_APB2ENR   0x40021018
#define RCC_APB2GPIOC 0x00000010

#define RCC_APB2GPIOx 0x000001fc
#define RCC_APB2AFIO  0x00000001

#define UART0 (0x40013800)

#define UART_GPIO GPIO_A

#define TX_PIN  (1 << 9)
#define RX_PIN  (1 << 10)
#define CTS_PIN (1 << 11)
#define RTS_PIN (1 << 12)

#define USART_FLAG_RXNE (1 << 5)
#define USART_FLAG_TXE (1 << 7)

#define USART_FLAG_UE (1 << 13)
#define USART_FLAG_RE (1 << 2)
#define USART_FLAG_TE (1 << 3)

#define RCC_APB2ENR_USART1EN (1 << 14)

static int stm32_uart_putc(struct uart *dev, int ch) {
	struct uart_stm32 *uart = (struct uart_stm32 *) dev->base_addr;

	while (!(REG_LOAD(&uart->sr) & USART_FLAG_TXE)) { }

	REG_STORE(&uart->dr, ch);

	return 0;
}

static int stm32_uart_hasrx(struct uart *dev) {
	struct uart_stm32 *uart = (struct uart_stm32 *) dev->base_addr;

	return (REG_LOAD(&uart->sr) & USART_FLAG_RXNE);
}

static int stm32_uart_getc(struct uart *dev) {
	struct uart_stm32 *uart = (struct uart_stm32 *) dev->base_addr;
	return REG_LOAD(&uart->dr);
}

static int stm32_uart_setup(struct uart *dev, const struct uart_params *params) {
	struct uart_stm32 *uart = (struct uart_stm32 *) dev->base_addr;

	REG_ORIN(RCC_APB1RSTR,RCC_APB1PWR);
	REG_ORIN(RCC_APB2ENR,RCC_APB2GPIOx);
	REG_ORIN(RCC_APB2ENR,RCC_APB2AFIO);

	REG_ORIN(RCC_APB2ENR,RCC_APB2ENR_USART1EN);

	gpio_out(UART_GPIO, TX_PIN , GPIO_MODE_OUT_ALTERNATE);
	gpio_in(UART_GPIO, RX_PIN, 0);

	REG_STORE(&uart->brr, SYS_CLOCK / params->baud_rate);
	REG_ORIN(&uart->cr1, USART_FLAG_RE | USART_FLAG_TE);

	REG_ORIN(&uart->cr1, USART_FLAG_UE);

	return 0;
}

static const struct uart_ops stm32_uart_ops = {
		.uart_getc = stm32_uart_getc,
		.uart_putc = stm32_uart_putc,
		.uart_hasrx = stm32_uart_hasrx,
		.uart_setup = stm32_uart_setup,
};

static struct uart stm32_uart0 = {
		.uart_ops = &stm32_uart_ops,
		.irq_num = 0,
		.base_addr = UART0,
};

static const struct uart_params uart_defparams = {
		.baud_rate = OPTION_GET(NUMBER,baud_rate),
		.parity = 0,
		.n_stop = 1,
		.n_bits = 8,
		.irq = 1,
};

static int stm32uart_diag_init(const struct diag *diag) {
	struct uart_params stm32uart_diag_params = {
		.baud_rate = OPTION_GET(NUMBER,baud_rate),
		.parity = 0,
		.n_stop = 1,
		.n_bits = 8,
		.irq = 0,
	};

	stm32_uart_setup(diag->obj, &stm32uart_diag_params);

	return 0;
};

static void stm32uart_diag_putc(const struct diag *diag, char ch) {
	struct uart *uart = (struct uart *) diag->obj;
	stm32_uart_putc(uart, ch);
}

static char stm32uart_diag_getc(const struct diag *diag) {
	struct uart *uart = (struct uart *) diag->obj;
	return stm32_uart_getc(uart);
}

static int stm32uart_diag_kbhit(const struct diag *diag) {
	struct uart *uart = (struct uart *) diag->obj;
	return stm32_uart_hasrx(uart);
}

DIAG_OPS_DECLARE(
	.init = stm32uart_diag_init,
	.getc = stm32uart_diag_getc,
	.putc = stm32uart_diag_putc,
	.kbhit = stm32uart_diag_kbhit,

	.obj = &stm32_uart0,
);

static int stm32uart_mod_init(void) {
	/*if (!uart_register(&stm32_uart0, &uart_defparams)) {*/
		/*return -1;*/
	/*}*/

	return 0;
}

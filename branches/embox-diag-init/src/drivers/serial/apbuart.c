/**
 * @file
 *
 * @date 13.03.10
 * @author Eldar Abusalimov
 */

#include <stdint.h>
#include <errno.h>

#include <drivers/amba_pnp.h>
#include <embox/device.h>
#include <hal/reg.h>
#include <hal/system.h>
#include <kernel/irq.h>

#include <drivers/diag.h>

#include <drivers/uart_device.h>


#include <embox/unit.h>

#include <kernel/printk.h>

#define BAUD_RATE \
	OPTION_GET(NUMBER, baud_rate)

#define UART_SCALER_VAL \
	(((SYS_CLOCK * 10) / (BAUD_RATE * 8) - 5) / 10)

/* status register bit masks */
#define UART_STAT_DR (1 << 0) /**< Data is available for read in RX register*/
#define UART_STAT_TS (1 << 1) /**< TX shift register is empty */
#define UART_STAT_TE (1 << 2) /**< TX FIFO is empty */
#define UART_STAT_BR (1 << 3) /**< BREAK received */
#define UART_STAT_OV (1 << 4) /**< 1 or more bytes lossed over overflow */
#define UART_STAT_PE (1 << 5) /**< error in parity control */
#define UART_STAT_FE (1 << 6) /**< error in frame */
#define UART_STAT_TH (1 << 7) /**< TX FIFO is half-full */
#define UART_STAT_RH (1 << 8) /**< RX FIFO is half-full */
#define UART_STAT_TF (1 << 9) /**< TX FIFO is full */
#define UART_STAT_RF (1 << 10)/**< RX FIFO is full */

/* control register bit masks */
#define UART_CTRL_RE (1 << 0)  /**< receiver enable */
#define UART_CTRL_TE (1 << 1)  /**< transmitter enable */
#define UART_CTRL_RI (1 << 2)  /**< interrupt after receiving frame */
#define UART_CTRL_TI (1 << 3)  /**< interrupt after transmitting frame */
#define UART_CTRL_PS (1 << 4)  /**< parity check (0 - oddness, 1 - evenness) */
#define UART_CTRL_PE (1 << 5)  /**< parity control enable */
#define UART_CTRL_FL (1 << 6)  /**< flow control with CTS/RTS enable (don't use) */
#define UART_CTRL_LB (1 << 7)  /**< loopback enable */
#define UART_CTRL_EC (1 << 8)  /**< external clock enable */
#define UART_CTRL_TF (1 << 9)  /**< enable interrupt on FIFO transmitter layer */
#define UART_CTRL_RF (1 << 10) /**< enable interrupt on FIFO receiver layer */
#define UART_CTRL_DB (1 << 11) /**< debug mode enable (don't available) */
#define UART_CTRL_OE (1 << 12) /**< output transmitter enable */
#define UART_CTRL_FA (1 << 31) /**< set on when FIFO TX and RX are available */
#define UART_DISABLE_ALL 0

struct apbuart_regs {
	/*------+------+
	 | resv | data |
	 | 31-8 | 7-0  |
	 +------+------*/
	/* 0x0 */uint32_t data;
	/*-------+-------+-------+--+--+--+--+--+--+--+--+--+--+--+
	 | RCNT  | TCNT  | resrv |RF|TF|RH|TH|FE|PE|OV|BR|TE|TS|DR|
	 | 31-26 | 25-20 | 19-11 |10|9 |8 |7 |6 |5 |4 |3 |2 |1 |0 |
	 +-------+-------+-------+--+--+--+--+--+--+--+--+--+--+--*/
	/* 0x4 */uint32_t status;
	/*--+-------+--+--+--+--+--+--+--+--+--+--+--+--+--+
	 |FA| resrv |OE|DB|RF|TF|EC|LB|FL|PE|PS|TI|RI|TE|RE|
	 |31| 30-13 |12|11|10|9 |8 |7 |6 |5 |4 |3 |2 |1 |0 |
	 +--+-------+--+--+--+--+--+--+--+--+--+--+--+--+--*/
	/* 0x8 */uint32_t ctrl;
	/*-------+--------+
	 | resrv | scaler |
	 | 31-12 | 11-0   |
	 +-------+--------*/
	/* 0xC */uint32_t scaler;
};

static volatile struct apbuart_regs *dev_regs;

static int dev_regs_init(void);
static unsigned int irq_num;

EMBOX_UNIT_INIT(uart_init);

static int apbuart_setup(const struct uart_desc *dev, const struct uart_params *params){
	int err;

	if (NULL != dev_regs) {
		return -EBUSY;
	}

	if (0 != (err = dev_regs_init())) {
		return err;
	}
	assert(NULL != dev_regs);

	REG_STORE(&dev_regs->ctrl, UART_DISABLE_ALL);
	REG_STORE(&dev_regs->scaler, UART_SCALER_VAL);
	REG_STORE(&dev_regs->ctrl, UART_CTRL_TE | UART_CTRL_RE | UART_CTRL_RI);
//	REG_STORE(&dev_regs->ctrl, UART_CTRL_TE | UART_CTRL_RE );
	//dev->base_addr = (uint32_t)dev_regs;
	//dev->irq_num = irq_num;

	return 0;
}

static int apbuart_putc(const struct uart_desc *dev, int ch) {
	while (!(UART_STAT_TE & REG_LOAD(&dev_regs->status))) {
	}
	REG_STORE(&dev_regs->data, (uint32_t) ch);

	return 0;
}

static int apbuart_has_symbol(const struct uart_desc *dev) {
	return UART_STAT_DR & REG_LOAD(&dev_regs->status);
}

static int apbuart_getc(const struct uart_desc *dev) {
#if 0
	while (!(UART_STAT_DR & REG_LOAD(&dev_regs->status))) {
	}
#endif
	return REG_LOAD(&dev_regs->data);
}


#ifdef DRIVER_AMBAPP
static int dev_regs_init() {
	amba_dev_t amba_dev;
	if (-1 == capture_amba_dev(&amba_dev, AMBAPP_VENDOR_GAISLER,
					AMBAPP_DEVICE_GAISLER_APBUART, false, false)) {
		printk("can't capture apb dev venID=0x%X, devID=0x%X\n",
				AMBAPP_VENDOR_GAISLER, AMBAPP_DEVICE_GAISLER_APBUART);
		return -ENODEV;
	}
	dev_regs = (volatile struct apbuart_regs *) amba_dev.bar[0].start;
	irq_num = amba_dev.dev_info.irq;
	return 0;
}
#elif OPTION_DEFINED(NUMBER,apbuart_base)
static int dev_regs_init() {
	dev_regs = (volatile struct apbuart_regs *) OPTION_GET(NUMBER,apbuart_base);
	irq_num = OPTION_GET(NUMBER,irq_num);
	return 0;
}
#else
# error "Either DRIVER_AMBAPP or apbuart_base option must be defined"
#endif /* DRIVER_AMBAPP */
#if 0
static struct uart_params uart0_params = {
		.baud_rate = OPTION_GET(NUMBER, baud_rate),
		.parity = 0,
		.n_stop = 1,
		.n_bits = 8
};
#endif

static const struct uart_ops uart_ops = {
		.uart_getc = apbuart_getc,
		.uart_putc = apbuart_putc,
		.uart_hasrx = apbuart_has_symbol,
		.uart_setup = apbuart_setup
};

#define APBUART_BASE  0x80000100

static struct uart_desc uart0 = {
		//.dev_name = "uart0",
		.irq_num = OPTION_GET(NUMBER,irq_num),
		.base_addr = APBUART_BASE,
		//.params = &uart0_params,
		.uart_ops = &uart_ops,
};

static void apbuart_diag_putc(char ch) {
	apbuart_putc(&uart0, ch);
}

static char apbuart_diag_getc(void) {
	return apbuart_getc(&uart0);
}

static int apbuart_diag_kbhit(void) {
	return apbuart_has_symbol(&uart0);
}

static const struct uart_params uart_defparams = {
		.baud_rate = OPTION_GET(NUMBER,baud_rate),
		.parity = 0,
		.n_stop = 1,
		.n_bits = 8,
		.irq = true,
};

static int apbuart_diag_init(void) {
	struct uart_params apbuart_diag_params = {
		.baud_rate = OPTION_GET(NUMBER,baud_rate),
		.parity = 0,
		.n_stop = 1,
		.n_bits = 8,
		.irq = false,
	};

	apbuart_setup(&uart0, &apbuart_diag_params);

	return 0;
};

DIAG_OPS_DECLARE(
	.init = apbuart_diag_init,
	.getc = apbuart_diag_getc,
	.putc = apbuart_diag_putc,
	.kbhit = apbuart_diag_kbhit,
);

static int uart_init(void) {
	if (!uart_register(&uart0, &uart_defparams)) {
		return -1;
	}

	return 0;
}


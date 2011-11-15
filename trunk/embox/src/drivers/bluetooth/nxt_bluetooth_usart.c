/**
 * @file
 * @brief Implements Lego NXT Bluetooth driver.
 *
 * @date 24.02.11
 * @author Anton Bondarev
 */

#include <types.h>
#include <embox/unit.h>
//#include <hal/reg.h>

#include <drivers/at91sam7s256.h>
#include <drivers/pins.h>
#include <drivers/bluetooth.h>
#include <kernel/timer.h>
#include <unistd.h>

//extern void bt_handle(uint8_t *buff);

#define NXT_BT_RX_PIN  ((uint32_t) CONFIG_NXT_BT_RX_PIN)
#define NXT_BT_TX_PIN  ((uint32_t) CONFIG_NXT_BT_TX_PIN)
#define NXT_BT_SCK_PIN ((uint32_t) CONFIG_NXT_BT_SCK_PIN)
#define NXT_BT_RTS_PIN ((uint32_t) CONFIG_NXT_BT_RTS_PIN)
#define NXT_BT_CTS_PIN ((uint32_t) CONFIG_NXT_BT_CTS_PIN)

static volatile AT91PS_USART us_dev_regs = ((AT91PS_USART) CONFIG_NXT_BT_SERIAL_PORT_OFFSET);

#define NXT_BT_ADC_RATE 50000
#define NXT_BT_BAUD_RATE 460800

EMBOX_UNIT_INIT(nxt_bluetooth_init);

static int nop(void) {
	return 0;
}

CALLBACK_INIT_DEF(nxt_bt_rx_handle_t, bt_rx, nop);
CALLBACK_INIT_DEF(nxt_bt_state_handle_t, bt_state, nop);

static void bt_clear_arm7_cmd(void) {
	REG_STORE(AT91C_PIOA_CODR, CONFIG_NXT_BT_CMD_PIN);
}

static void bt_set_arm7_cmd(void) {
	REG_STORE(AT91C_PIOA_SODR, CONFIG_NXT_BT_CMD_PIN);
}

static void bt_set_reset_high(void) {
	REG_STORE(AT91C_PIOA_SODR, CONFIG_NXT_BT_RST_PIN);
}

static void bt_set_reset_low(void) {
	REG_STORE(AT91C_PIOA_CODR, CONFIG_NXT_BT_RST_PIN);
}

void bluetooth_hw_accept_connect(void) {
	bt_set_arm7_cmd();
}

void bluetooth_hw_soft_reset(void) {
	bt_clear_arm7_cmd();
}

static irq_return_t nxt_bt_us_handler(int irq_num, void *dev_id) {
	
	CALLBACK(bt_rx)();
	//nxt_bt_rx_handle();

	return IRQ_HANDLED;
}


size_t bluetooth_write(uint8_t *buff, size_t len) {
	while (!(REG_LOAD(&(us_dev_regs->US_CSR)) & AT91C_US_ENDTX)) {
	}
	REG_STORE(&(us_dev_regs->US_TPR), (uint32_t) buff);
	REG_STORE(&(us_dev_regs->US_TCR), len);
	return len;
}

size_t bluetooth_read(uint8_t *buff, size_t len) {
	REG_STORE(&(us_dev_regs->US_RPR), (uint32_t) buff);
	REG_STORE(&(us_dev_regs->US_RCR), len);

	return 0;
}

static void init_usart(void) {
	/* Configure the usart */
	REG_STORE(AT91C_PMC_PCER, (1 << CONFIG_NXT_BT_US_DEV_ID));

	REG_STORE(AT91C_PIOA_PDR, NXT_BT_RX_PIN | NXT_BT_TX_PIN |
			NXT_BT_SCK_PIN | NXT_BT_RTS_PIN | NXT_BT_CTS_PIN);
	REG_STORE(AT91C_PIOA_ASR, NXT_BT_RX_PIN | NXT_BT_TX_PIN |
			NXT_BT_SCK_PIN | NXT_BT_RTS_PIN | NXT_BT_CTS_PIN);

	REG_STORE(&(us_dev_regs->US_PTCR), (AT91C_PDC_RXTDIS | AT91C_PDC_TXTDIS));
	REG_STORE(&(us_dev_regs->US_CR),  AT91C_US_RSTSTA | AT91C_US_RSTRX | AT91C_US_RSTTX);
	REG_STORE(&(us_dev_regs->US_CR), AT91C_US_STTTO);
	REG_STORE(&(us_dev_regs->US_RTOR), 10000);
	REG_STORE(&(us_dev_regs->US_MR), (AT91C_US_USMODE_HWHSH & ~AT91C_US_SYNC)
			| AT91C_US_CLKS_CLOCK | AT91C_US_CHRL_8_BITS | AT91C_US_PAR_NONE
			| AT91C_US_NBSTOP_1_BIT | AT91C_US_OVER);
	REG_STORE(&(us_dev_regs->US_IDR), ~0);
	REG_STORE(&(us_dev_regs->US_IER), AT91C_US_ENDRX);
	REG_STORE(&(us_dev_regs->US_BRGR), CONFIG_SYS_CLOCK / (8 * NXT_BT_BAUD_RATE));
	REG_STORE(&(us_dev_regs->US_RCR), 0);
	REG_STORE(&(us_dev_regs->US_TCR), 0);
	REG_STORE(&(us_dev_regs->US_RNPR), 0);
	REG_STORE(&(us_dev_regs->US_TNPR), 0);
	REG_LOAD(&(us_dev_regs->US_RHR));
	REG_LOAD(&(us_dev_regs->US_CSR));

	REG_STORE(&(us_dev_regs->US_CR), AT91C_US_RXEN | AT91C_US_TXEN);
	REG_STORE(&(us_dev_regs->US_PTCR), AT91C_PDC_RXTEN | AT91C_PDC_TXTEN);
}

static void init_control_pins(void) {
	/*configure control pins*/
	REG_STORE(AT91C_PIOA_PPUDR, CONFIG_NXT_BT_CMD_PIN);
	pin_config_output(CONFIG_NXT_BT_CS_PIN | CONFIG_NXT_BT_RST_PIN | CONFIG_NXT_BT_CMD_PIN);
	pin_set_output(CONFIG_NXT_BT_CS_PIN | CONFIG_NXT_BT_RST_PIN);
	pin_clear_output(CONFIG_NXT_BT_CMD_PIN);

}

static void init_adc(void) {
	/* Configure the ADC */
	REG_STORE(AT91C_PMC_PCER, (1 << AT91C_ID_ADC));
	REG_STORE(AT91C_ADC_MR, 0);
	REG_ORIN(AT91C_ADC_MR, AT91C_ADC_TRGEN_DIS);
	REG_ORIN(AT91C_ADC_MR, 0x00000500); // 4MHz
	REG_ORIN(AT91C_ADC_MR, 0x001f0000); // 64uS
	REG_ORIN(AT91C_ADC_MR, 0x03000000); // 750nS
	REG_STORE(AT91C_ADC_CHER, AT91C_ADC_CH6 | AT91C_ADC_CH4);
	REG_STORE(AT91C_ADC_CR, AT91C_ADC_START);
}

/* timer handler
 * we scan PIN_BT4 for changing and if it changed bt state switch to disconnect
 *  mode.
 */
static void  nxt_bt_timer_handler(int id) {
	static int bt_last_state; //TODO init state?
	int bt_state = REG_LOAD(AT91C_ADC_CDR6) > 0x200 ? 1 : 0;
	if (bt_last_state != bt_state) {
		if (!bt_state) {
			//nxt_bt_state_handle();
			CALLBACK(bt_state)();
		}
	}
	bt_last_state = bt_state;
	REG_STORE(AT91C_ADC_CR, AT91C_ADC_START);
}

void bluetooth_hw_hard_reset(void) {
	bt_set_reset_low();
	usleep(2000);
	bt_set_reset_high();
	usleep(5000);
}

static int nxt_bluetooth_init(void) {
	static struct sys_timer *ntx_bt_timer;

	init_usart();

	init_control_pins();

	init_adc();

	bt_clear_arm7_cmd();

	irq_attach((irq_nr_t) CONFIG_NXT_BT_US_IRQ,
		(irq_handler_t) nxt_bt_us_handler, 0, NULL, "nxt bt reader");

//TODO may be it must set when bt has been connected?
	timer_set(&ntx_bt_timer, 200, (sys_timer_handler_t) &nxt_bt_timer_handler, NULL);

	return 0;
}


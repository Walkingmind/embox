/**
 * @file
 *
 * @brief Serves all tty devices
 *
 * @date 12.11.2010
 * @author Anton Bondarev
 */

#include <string.h>
#include <drivers/tty.h>
#include <kernel/uart.h>

tty_device_t *cur_tty;
#ifdef CONFIG_TTY_WITH_VTPARSE
struct vtparse tty_vtparse;

void tty_vtparse_callback( struct vtparse *tty_vtparse, struct vt_token *token ) {
#if 0
	printf("action: %d; char: %c\n", token->action , token->ch);
#endif
	printf("new token\n");
}
#endif

int tty_init(void) {
#ifdef CONFIG_TTY_WITH_VTPARSE
	vtparse_init( &tty_vtparse , &tty_vtparse_callback );
#endif
	return 0;
}

int tty_register(tty_device_t *tty) {
	cur_tty = tty;
	return 0;
}

int tty_unregister(tty_device_t *tty) {
	tty->out_busy = false;
	tty->rx_cnt = 0;
	cur_tty = tty;
	return 0;
}

int tty_get_uniq_number(void) {
	return 0;
}
/*
 * add parsed char to receive buffer
 */
int tty_add_char(tty_device_t *tty, int ch) {
#ifdef CONFIG_TTY_WITH_VTPARSE
	vtparse( &tty_vtparse , ch );
#else /* CONFIG_TTY_WITH_VTPARSE */
	if ('\n' == ch && !tty->out_busy) {
		/*add string to output buffer*/
		memcpy((void*)tty->out_buff,(const void*) tty->rx_buff, tty->rx_cnt);
		tty->out_buff[tty->rx_cnt] = '\0';
		tty->rx_cnt = 0;
		tty->out_busy = true;
		uart_putc(ch);
		return 1;
	}
	if(tty->rx_cnt >= TTY_RXBUFF_SIZE) {
		/*buffer is full. drop this symbol*/
		return -1;
	}
	tty->rx_buff[tty->rx_cnt++] = ch;
	uart_putc(ch);
	return 0;
#endif /* CONFIG_TTY_WITH_VTPARSE */
}

uint8_t* tty_readline(tty_device_t *tty) {
	while(!tty->out_busy);
	tty->out_busy = false; 
	return (uint8_t*)tty->out_buff;
}

static uint32_t tty_scanline(uint8_t line[TTY_RXBUFF_SIZE + 1], uint32_t size) {
	int i = 0;
	while('\n' == line[i ++]) {
		if (0 == (size --))
			return 0;
	}
	return (uint32_t)(i - 1);
}

void tty_freeline(tty_device_t *tty, uint8_t *line) {
	uint32_t line_size;
	if(0 != tty->rx_cnt) {
		line_size = tty_scanline((uint8_t*)tty->rx_buff, tty->rx_cnt);
	}
}




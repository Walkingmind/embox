/**
 * @file
 * @brief
 *
 * @date 17.03.2012
 * @author Anton Kozlov
 */

#include <drivers/diag.h>
#include <string.h>

#include <framework/mod/options.h>

#define BUF_LEN OPTION_GET(NUMBER,buffer_len)

static char diag_buf[BUF_LEN + 1]; /* for trailing \0 */
static int diag_buf_head = 0;

static void diag_mem_putc(const struct diag *diag, char ch) {
	if (diag_buf_head == BUF_LEN) {
		diag_buf_head = 0;
	}

	diag_buf[diag_buf_head] = ch;
	diag_buf[diag_buf_head++] = '\0';
}

DIAG_OPS_DECLARE(
	.putc = diag_mem_putc,
);

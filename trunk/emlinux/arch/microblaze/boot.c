/**
 * @file
 *
 * @date 01.07.10
 * @author Nikolay Korotky
 */

#include <linux/kernel.h>

//#define XILINX_UARTLITE_BASEADDR  0x84000000
#define XILINX_UARTLITE_TX_DATA   0x84000020
#define XILINX_UARTLITE_STATUS    0x84000040
//#define XILINX_UARTLITE_BAUDRATE  115200
//#define XILINX_UARTLITE_IRQ_NUM   2
#define STATUS_TX_FIFO_FULL      (1<<(31-28))

unsigned int *uart_tx_data = (unsigned int *)XILINX_UARTLITE_TX_DATA;
unsigned int *uart_status = (unsigned int *)XILINX_UARTLITE_STATUS;

static int xlnx_nbputchar(char c) {
	while(*uart_status & STATUS_TX_FIFO_FULL);
	*uart_tx_data = (unsigned int)c;
	return 0;
}

static int xlnx_nbputstr(const char *str) {
	char *ptr = (char *)str;
	while(*ptr) {
		xlnx_nbputchar(*ptr++);
	}
	return xlnx_nbputchar('\n');
}

/* mark as section .img.main.text, to be referenced in linker script */
int __attribute__ ((__section__ (".img.main.text"))) __main(void) {
	void (*kernel)();

	/* call kernel */
	kernel = (void (*)()) CONFIG_KERNEL_BASE_ADDR;
	xlnx_nbputstr("Call kernel");
	kernel();
	return 0;
}


/**
 * @file
 *
 * @date 01.07.10
 * @author Nikolay Korotky
 */

#include <linux/kernel.h>

//#define XILINX_UARTLITE_BASEADDR  0x84000000
#define XILINX_UARTLITE_TX_DATA   0x84000004
#define XILINX_UARTLITE_STATUS    0x84000008
//#define XILINX_UARTLITE_BAUDRATE  115200
//#define XILINX_UARTLITE_IRQ_NUM   2
#define STATUS_TX_FIFO_FULL      (1<<(31-28))

unsigned int *uart_tx_data = (unsigned int *) XILINX_UARTLITE_TX_DATA;
unsigned int *uart_status = (unsigned int *) XILINX_UARTLITE_STATUS;

static int xlnx_nbputchar(char c) {
	while (*uart_status & STATUS_TX_FIFO_FULL);
	*uart_tx_data = (unsigned int)c;
	return 0;
}

static int xlnx_nbputstr(const char *str) {
	char *ptr = (char *) str;
	while (*ptr) {
		xlnx_nbputchar(*ptr++);
	}
	return xlnx_nbputchar('\n');
}

extern unsigned short bss_start,bss_end;
char *commandline = "console=ttyUL0 rdinit=/sbin/init";

/* mark as section .img.main.text, to be referenced in linker script */
int __attribute__ ((__section__ (".img.main.text"))) __main(void) {

        char *c;
	void (*kernel)(char *, unsigned long, char*);

        /* clear bss */
        c = &bss_start;
        while (c < &bss_end) {
                *c=0;
                c++;
        }

	/* call kernel */
	kernel = (void (*)(char *, unsigned long, char*)) CONFIG_KERNEL_BASE_ADDR;
	xlnx_nbputstr("Call kernel");
	/*
         * Linux Kernel Parameters (passing device tree):
         * r5: pointer to command line
         * r6: pointer to ramdisk
         * r7: pointer to the fdt, followed by the board info data
         */
	kernel(commandline, 0, NULL);
	return 0;
}

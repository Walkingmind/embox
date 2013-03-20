/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    01.03.2013
 */

#include <kernel/host.h>

int diag_kbhit(void) {
	return 0;
}

char diag_getc(void) {
	int len = 1;

	emvisor_send(UV_PWRUPSTRM, EMVISOR_DIAG_IN, &len, sizeof(int));

	while (1);
	return '\0';
}

void diag_putc(char ch) {

	emvisor_send(UV_PWRUPSTRM, EMVISOR_DIAG_OUT, &ch, 1);

}

void diag_init(void) {
	
}

/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    07.03.2013
 */

#include <assert.h>
#include <kernel/host.h>
#include <kernel/umirq.h>
#include <hal/ipl.h>

static int ipl_num;

#include <prom/prom_printf.h>
static void ipl_highest(int signal) {

	prom_printf("recv high\n");
}

static void ipl_lowest(int signal) {
	struct emvisor_msghdr msg;

	ipl_disable();

	if (signal != UV_IRQ) {
		return;
	}

	assert(0 <= emvisor_recvmsg(UV_PRDDOWNSTRM, &msg));

	if (msg.type <= EMVISOR_IRQ) {
		return;
	}

	irq_entry(msg.type - EMVISOR_IRQ);

	ipl_enable();
}

static const host_sighandler_t ipl_table[] = {
	ipl_highest,
	ipl_lowest,
};

void ipl_init(void) {
	ipl_restore(1);
}

ipl_t ipl_save(void) {
	ipl_t ret = ipl_num;

	ipl_restore(0);

	return ret;

}

void ipl_restore(ipl_t ipl) {
	host_signal(UV_IRQ, ipl_table[ipl_num = ipl]);

	/*TODO: flush downstream*/
}

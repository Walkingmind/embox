/**
 * @file
 *
 * @brief
 *
 * @date 24.07.2012
 * @author Anton Bondarev
 */
#include <asm/ptrace.h>
#include <asm/mipsregs.h>
#include <asm/entry.h>
#include <assert.h>

#include <string.h>

second_exception_handler_t exception_handlers[MIPS_EXCEPTIONS_QUANTITY] = {mips_second_exception_handler};


void mips_c_exception_handler(pt_regs_t *regs) {
}

/*
* Copy the generic exception handlers to their final destination.
* This will be overridden later as suitable for a particular
* configuration.
*/
static void mips_setup_exc_table(void) {
	int i;

	/* set all exception handler */
	for(i = 0; i < MIPS_EXCEPTIONS_QUANTITY; i ++) {
		exception_handlers[i] = mips_second_exception_handler;
	}
}

/* setup correct exception table and enable exceptions */
void mips_exception_init(void) {
	unsigned int tmp;

	/* clear BEV bit */
	tmp = mips_read_c0_status();
	tmp &= ~(ST0_BEV);
	mips_write_c0_status(tmp);

	/* clear CauseIV bit */
	tmp = mips_read_c0_cause();
	tmp &= ~(CAUSE_IV);
	mips_write_c0_cause(tmp);

	/* copy first exception handler to correct place */
	memcpy((void *)(EBASE + 0x180), &mips_first_exception_handler, 0x80);

	mips_setup_exc_table();

	/* clear EXL bit */
	tmp = mips_read_c0_status();
	tmp &= ~(ST0_ERL);
	mips_write_c0_status(tmp);

//	asm("syscall\n");
}

void mips_exception_setup(mips_exception_type_t type, second_exception_handler_t handler) {
	exception_handlers[type] = handler;
}

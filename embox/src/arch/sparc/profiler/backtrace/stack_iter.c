/**
 * @file
 * @brief TODO: brief
 *
 * @date 24 Aug, 2012
 * @author Bulychev Anton
 */

#include <stdio.h>
#include "stack_iter.h"

#define RETPC_OFFSET 8

void stack_iter_current(stack_iter_t *f) {
	f->fp = __builtin_frame_address(0);
	f->pc = __builtin_return_address(0) + RETPC_OFFSET;
	f->sf = NULL;
}

// TODO: May be add type of previous: through interruption or not?
int stack_iter_next(stack_iter_t *f) {
	f->sf = f->fp;
	f->fp = f->sf->reg_window.fp;
	if (f->fp == NULL) {
		f->pc = NULL;
		f->sf = NULL;
		return 0;
	}
	f->pc = f->sf->reg_window.ret_pc + RETPC_OFFSET;

	return 1;
}

static void reg_window_print(struct reg_window *rw) {
    printk("%%L: %08x %08x  %08x %08x  %08x %08x  %08x %08x\n",
                    rw->locals[0], rw->locals[1], rw->locals[2], rw->locals[3],
                    rw->locals[4], rw->locals[5], rw->locals[6], rw->locals[7]);
    printk("%%I: %08x %08x  %08x %08x  %08x %08x  %08x %08x\n",
                    rw->ins[0], rw->ins[1], rw->ins[2], rw->ins[3],
                    rw->ins[4], rw->ins[5], (uint32_t) rw->fp, (uint32_t) rw->ret_pc);
}

void stack_iter_print(stack_iter_t *f) {
	printk("frame_address = 0x%08x, return_address = 0x%08x  \n", (uint32_t) f->fp, (uint32_t) f->pc);
	if (f->sf != NULL) {
        reg_window_print(&f->sf->reg_window);
	}
    printk("\n");
}

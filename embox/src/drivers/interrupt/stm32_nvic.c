/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    02.07.2012
 */

#include <assert.h>
#include <types.h>

#include <kernel/critical.h>
#include <hal/reg.h>
#include <hal/ipl.h>
#include <hal/interrupt.h>

#include <kernel/irq.h>
#include <embox/unit.h>

#define NVIC_BASE 0xe000e100
#define NVIC_ENABLE_BASE NVIC_BASE
#define NVIC_CLEAR_BASE (NVIC_BASE + 0x80)
#define NVIC_SET_PEND_BASE (NVIC_BASE + 0x100)
#define NVIC_CLR_PEND_BASE (NVIC_BASE + 0x180)
#define NVIC_ACTIVE_BASE (NVIC_BASE + 0x200)
#define NVIC_PRIOR_BASE (NVIC_BASE + 0x300)

#define SCB_BASE 0xe000ed00
#define SCB_ICSR (SCB_BASE + 0x04)
#define SCB_VTOR (SCB_BASE + 0x08)

#define EXCEPTION_TABLE_SZ 0x20

/**
 * ENABLE, CLEAR, SET_PEND, CLR_PEND, ACTIVE is a base of bit arrays
 * to calculate bit offset in array: calculate 32-bit word offset 
 *     nr / 32 * sizeof(int) == nr / 8
 * and calculate bit offset in word 
 *     nr / 32 
 */

EMBOX_UNIT_INIT(nvic_init);

static uint32_t exception_table[EXCEPTION_TABLE_SZ] __attribute__ ((aligned (128 * sizeof(int))));

void interrupt_handle(void);

extern void *trap_table_start;
extern void *trap_table_end;

static int nvic_init(void) {
	ipl_t ipl;
	int i; 
	void *ptr;

	for (i = 0; i < EXCEPTION_TABLE_SZ; i++) {
		exception_table[i] = ((int) interrupt_handle) | 1;
	}
	
	/* load head from bootstrap table */
	for (ptr = &trap_table_start, i = 0; ptr != &trap_table_end; ptr += 4, i++) {
		exception_table[i] = * (int32_t *) ptr;
	}

	ipl = ipl_save();

	REG_STORE(SCB_VTOR, 1 << 29 /* indicate, table in SRAM */ | 
			(int) exception_table);
	
	ipl_restore(ipl);

	return 0;
}

void interrupt_enable(interrupt_nr_t interrupt_nr) {
	assert(interrupt_nr_valid(interrupt_nr));

	REG_STORE(NVIC_ENABLE_BASE + interrupt_nr / 8, 
			1 << (interrupt_nr / (8 * sizeof(int)) ));
}

void interrupt_disable(interrupt_nr_t interrupt_nr) {
	assert(interrupt_nr_valid(interrupt_nr));
	REG_STORE(NVIC_CLEAR_BASE + interrupt_nr / 8, 
			1 << (interrupt_nr / (8 * sizeof(int)) ));
}

void interrupt_clear(interrupt_nr_t interrupt_nr) {
	assert(interrupt_nr_valid(interrupt_nr));
	REG_STORE(NVIC_CLR_PEND_BASE + interrupt_nr / 8, 
			1 << (interrupt_nr / (8 * sizeof(int)) ));
}

void interrupt_force(interrupt_nr_t interrupt_nr) {
	assert(interrupt_nr_valid(interrupt_nr));
	REG_STORE(NVIC_SET_PEND_BASE + interrupt_nr / 8, 
			1 << (interrupt_nr / (8 * sizeof(int)) ));
}

interrupt_mask_t interrupt_get_status(void) {
	return REG_LOAD(NVIC_ACTIVE_BASE) | 
		REG_LOAD(NVIC_ACTIVE_BASE + 4)
		| REG_LOAD(NVIC_ACTIVE_BASE + 8);
}

void interrupt_handle(void) {
	uint32_t source;

	source = REG_LOAD(SCB_ICSR) & 0x1ff; 

	assert(!critical_inside(CRITICAL_IRQ_LOCK));

	critical_enter(CRITICAL_IRQ_HANDLER);
	
	irq_dispatch(source);
	
	critical_leave(CRITICAL_IRQ_HANDLER);

	critical_dispatch_pending();

}

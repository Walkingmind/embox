/**
 * @file
 * @brief
 *
 * @date 24.12.2012
 * @author Anton Bulychev
 */

#include <embox/unit.h>

#include <string.h>
#include <unistd.h>
#include <types.h>

#include <asm/msr.h>
#include <asm/ap.h>

#include <kernel/cpu.h>
#include <kernel/thread.h>
#include <kernel/spinlock.h>

#include <module/embox/driver/interrupt/lapic.h>

EMBOX_UNIT_INIT(unit_init);

#define TRAMPOLINE_ADDR 0x20000UL

static SPINLOCK_DEFINE(startup_lock);

char AP_STACK[THREAD_STACK_SIZE] __attribute__((aligned(THREAD_STACK_SIZE)));

void startup_ap(void) {
	extern void idt_load(void);

	idt_load();

	lapic_enable();

	thread_init_self(AP_STACK + THREAD_STACK_SIZE, THREAD_STACK_SIZE,
			THREAD_PRIORITY_MIN);

	__asm__ __volatile__ ("sti");

	spin_unlock(&startup_lock);

	while (1) {
		;
	}
}

static inline void init_trampoline(void) {
	/* Initialize gdt */
	memcpy(__ap_gdt, gdt, sizeof(gdt));
	gdt_set_gdtr(&__ap_gdtr, __ap_gdt);
	__ap_sp = AP_STACK + sizeof(AP_STACK) - 4;

	memcpy((void *) TRAMPOLINE_ADDR, &__ap_trampoline,
			(uint32_t) &__ap_trampoline_end - (uint32_t) &__ap_trampoline);
}

/* TODO: FIX THIS! */
static inline void cpu_start(int cpu_id) {
	lapic_send_init_ipi(cpu_id);

	for (int i = 0; i < 20000; i++) {
		__asm__ __volatile__ ("nop");
	}

	lapic_send_init_ipi(cpu_id);

	for (int i = 0; i < 20000; i++) {
		__asm__ __volatile__ ("nop");
	}

	lapic_send_startup_ipi(cpu_id, TRAMPOLINE_ADDR);
}

static int unit_init(void)
{
	/* Initialize trampoline for the APs */
	init_trampoline();

	/* Start all CPUs */
    for (int i = 0; i <= NCPU - 1; i++) {
    	if (i == lapic_id()) {
    		continue;
    	}

    	spin_lock(&startup_lock);
    	cpu_start(i);
    	spin_lock(&startup_lock);
    }

#if 1
    lapic_send_ipi(0x50, 1, LAPIC_IPI_DEST);
#endif

    return 0;
}

/* It is not an arch part */
void resched(void) {
	extern void sched_post_switch(void);

	/* Should we send EOI? */

	sched_post_switch();
}


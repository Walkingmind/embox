/**
 * @file
 *
 * @date 18.12.2012
 * @author Anton Bulychev
 */

#ifndef IRQCTRL_APIC_IMPL_H_
#define IRQCTRL_APIC_IMPL_H_

#include <types.h>

#define __IRQCTRL_IRQS_TOTAL 16

#define LOCAL_APIC_DEF_ADDR	 0xFEE00000 /* Default local apic address */

#define LAPIC_ID	(LOCAL_APIC_DEF_ADDR + 0x020)
#define LAPIC_SIVR  (LOCAL_APIC_DEF_ADDR + 0x0F0)
#define LAPIC_ESR	(LOCAL_APIC_DEF_ADDR + 0x280)
#define LAPIC_ICR1	(LOCAL_APIC_DEF_ADDR + 0x300)
#define LAPIC_ICR2	(LOCAL_APIC_DEF_ADDR + 0x310)

static inline uint32_t lapic_read(uint32_t reg) {
	return *((volatile uint32_t *) reg);
}

static inline void lapic_write(uint32_t reg, uint32_t value) {
	*((volatile uint32_t *) reg) = value;
}

static inline uint32_t lapic_id(void) {
	return lapic_read(LAPIC_ID) >> 24;
}

static inline uint32_t lapic_errstatus(void)
{
	lapic_write(LAPIC_ESR, 0);
	return lapic_read(LAPIC_ESR);
}

extern void lapic_send_init_ipi(uint32_t apic_id);
extern void lapic_send_startup_ipi(uint32_t apic_id, uint32_t trampoline);

#endif /* IRQCTRL_APIC_IMPL_H_ */


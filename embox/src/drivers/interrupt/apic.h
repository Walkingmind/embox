/**
 * @file
 *
 * @date 18.12.2012
 * @author Anton Bulychev
 */

#ifndef IRQCTRL_APIC_IMPL_H_
#define IRQCTRL_APIC_IMPL_H_

#define __IRQCTRL_IRQS_TOTAL 16

#define LOCAL_APIC_DEF_ADDR	 0xfee00000 /* default local apic address */
#define IO_APIC_DEF_ADDR     0xfec00000 /* default i/o apic address */

#define APIC_SPURIOUS_INTERRUPT_VECTOR (LOCAL_APIC_DEF_ADDR + 0x0F0)

static inline uint32_t lapic_read(uint32_t reg) {
	return *((volatile uint32_t *) reg);
}

static inline void lapic_write(uint32_t reg, uint32_t value) {
	*((volatile uint32_t *) reg) = value;
}

#endif /* IRQCTRL_APIC_IMPL_H_ */


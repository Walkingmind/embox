/**
 * @file
 * @brief Interrupt controller interface.
 *
 * @date 25.11.09
 * @author Eldar Abusalimov
 */

#ifndef HAL_INTERRUPT_H_
#define HAL_INTERRUPT_H_

#include <module/embox/arch/interrupt.h>

/**
 * Total amount of interrupt lines available on the controller.
 *
 * @note Implementation should provide @c __INTERRUPT_NRS_TOTAL definition
 * indicating positive constant.
 */
#define INTERRUPT_NRS_TOTAL __INTERRUPT_NRS_TOTAL

/**
 * Checks if the specified @c interrupt_nr is less then #INTERRUPT_NRS_TOTAL
 * value.
 *
 * @param interrupt_nr the number to check
 * @return comparison result
 *
 * @note Most HAL methods uses @link #assert() @endlink instead of checking the
 * input arguments, so kernel should perform necessary checks by itself.
 */
#define interrupt_nr_valid(interrupt_nr) \
	((interrupt_nr_t) interrupt_nr < (interrupt_nr_t) INTERRUPT_NRS_TOTAL)

/**
 * Type representing interrupt line number.
 *
 * @note Implementation should provide @c __interrupt_nr_t type indicating
 * unsigned (it is essential!) integer suitable to hold up to
 * #INTERRUPT_NRS_TOTAL values.
 */
typedef __interrupt_nr_t interrupt_nr_t;

/**
 * Type representing interrupt mask(pending) register.
 *
 * @note Implementation should provide @c __interrupt_nr_t type indicating
 * unsigned (it is essential!) integer suitable to hold up to
 * (1 << #INTERRUPT_NRS_TOTAL)  values.
 */
typedef __interrupt_mask_t interrupt_mask_t;

/**
 * Enables the specified IRQ.
 *
 * @param interrupt_nr the IRQ number to enable
 */
void interrupt_enable(interrupt_nr_t interrupt_nr);

/**
 * Disables the specified IRQ.
 *
 * @param interrupt_nr the IRQ number to disable
 */
void interrupt_disable(interrupt_nr_t interrupt_nr);

/**
 * Clears pending status for the specified IRQ.
 *
 * @param interrupt_nr the IRQ number to clear
 */
void interrupt_clear(interrupt_nr_t interrupt_nr);

/**
 * Forces interrupt controller to generate the specified IRQ.
 *
 * @param interrupt_nr the IRQ number to force
 */
void interrupt_force(interrupt_nr_t interrupt_nr);

/**
 * Receives status of interrupt controller.
 *
 * @return pending register from interrupt controller
 */
interrupt_mask_t interrupt_get_status(void);

extern int i8259_irq_pending(interrupt_nr_t irq);

#endif /* HAL_INTERRUPT_H_ */

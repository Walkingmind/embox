/**
 * @file
 * @brief Periodical Interval Timer interface
 *
 * @date 26.09.10
 * @author Anton Kozlov
 */

#ifndef AT91SAM7_PIT_H_
#define AT91SAM7_PIT_H_

#include <drivers/at91sam7s256.h>

typedef struct _AT91S_PITC {
	at91_reg_t	 PITC_PIMR; 	// Period Interval Mode Register
	at91_reg_t	 PITC_PISR; 	// Period Interval Status Register
	at91_reg_t	 PITC_PIVR; 	// Period Interval Value Register
	at91_reg_t	 PITC_PIIR; 	// Period Interval Image Register
} AT91S_PITC, *AT91PS_PITC;

// -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register --------
#define AT91C_PITC_PIV        ((unsigned int) 0xFFFFF <<  0) // (PITC) Periodic Interval Value
#define AT91C_PITC_PITEN      ((unsigned int) 0x1 << 24) // (PITC) Periodic Interval Timer Enabled
#define AT91C_PITC_PITIEN     ((unsigned int) 0x1 << 25) // (PITC) Periodic Interval Timer Interrupt Enable
// -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register --------
#define AT91C_PITC_PITS       ((unsigned int) 0x1 <<  0) // (PITC) Periodic Interval Timer Status
// -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register --------
#define AT91C_PITC_CPIV       ((unsigned int) 0xFFFFF <<  0) // (PITC) Current Periodic Interval Value
#define AT91C_PITC_PICNT      ((unsigned int) 0xFFF << 20) // (PITC) Periodic Interval Counter
// -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register --------

// ========== Register definition for PITC peripheral ==========
#define AT91C_PITC_PIVR ((at91_reg_t *) 	0xFFFFFD38) // (PITC) Period Interval Value Register
#define AT91C_PITC_PISR ((at91_reg_t *) 	0xFFFFFD34) // (PITC) Period Interval Status Register
#define AT91C_PITC_PIIR ((at91_reg_t *) 	0xFFFFFD3C) // (PITC) Period Interval Image Register
#define AT91C_PITC_PIMR ((at91_reg_t *) 	0xFFFFFD30) // (PITC) Period Interval Mode Register

#endif /* AT91SAM7_PIT_H_ */

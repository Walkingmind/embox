/**
 * @file
 * @brief Utilities for work with PowerPC Microprocessor Family registers
 *
 * @date 07.11.12
 * @author Ilia Vaprol
 */

#ifndef PPC_PSR_H_
#define PPC_PSR_H_

#ifndef __ASSEMBLER__

#define PPC_REG_GET(reg)                               \
    static inline unsigned int __get_##reg(void) {     \
        unsigned int retval;                           \
        __asm__ __volatile__ (                         \
            "mf"#reg" %0"                              \
            : "=r" (retval)                            \
            : /* no input */                           \
            : "memory"                                 \
        );                                             \
        return retval;                                 \
    }                                                  \

#define PPC_REG_SET(reg)                               \
    static inline void __set_##reg(unsigned int val) { \
        __asm__ __volatile__ (                         \
            "mt"#reg" %0"                              \
            : /* no output */                          \
            : "r" (val)                                \
            : /* unspecified register FIXME */         \
        );                                             \
    }                                                  \


/**
 * Machine State Register (MSR)
 */
PPC_REG_GET(msr)
PPC_REG_SET(msr)

/**
 * Save/Restore Register 0 (SRR0)
 */
PPC_REG_GET(srr0)
PPC_REG_SET(srr0)

/**
 * Memory Management Unit Control Register (MMUCR)
 */
PPC_REG_GET(mmucr)
PPC_REG_SET(mmucr)

/**
 * Decrementer Register (DEC)
 */
PPC_REG_GET(dec)
PPC_REG_SET(dec)

/**
 * Decrementer Auto-Reload Register (DECAR)
 */
PPC_REG_SET(decar)

/**
 * Timer Control Register (TCR)
 */
PPC_REG_GET(tcr)
PPC_REG_SET(tcr)

/**
 * Timer Status Register (TSR)
 */
PPC_REG_GET(tsr)
PPC_REG_SET(tsr)

/**
 * Time Base Lower/Upper Registers (TBL/TBU)
 */
PPC_REG_GET(tbl)
PPC_REG_SET(tbl)
PPC_REG_GET(tbu)
PPC_REG_SET(tbu)


#undef PPC_REG_GET
#undef PPC_REG_SET

#endif /* !__ASSEMBLER__ */

#endif /* PPC_PSR_H_ */

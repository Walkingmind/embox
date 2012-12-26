/**
 * @file
 * @brief
 *
 * @date 13.12.12
 * @author Ilia Vaprol
 */

#include <asm/psr.h>
#include <asm/regs.h>
#include <hal/mmu.h>
#include <types.h>

/**
 * TLB Entry Fields
 */
	/* Page Identification Fields */
#define MMU_TLB0_EPN_MASK   0xFFFFFC00 /* Effective Page Number[0:21] */
#define MMU_TBL0_V          0x00000200 /* Vaild[22] */
#define MMU_TBL0_TS         0x00000100 /* Translation Address Spase[23] */
#define MMU_TLB0_SIZE_1KB   0x00000000 /* Page Size[24:27] */
#define MMU_TLB0_SIZE_4KB   0x00000010
#define MMU_TLB0_SIZE_16KB  0x00000020
#define MMU_TLB0_SIZE_64KB  0x00000030
#define MMU_TLB0_SIZE_256KB 0x00000040
#define MMU_TLB0_SIZE_1MB   0x00000050
#define MMU_TLB0_SIZE_16MB  0x00000060
#define MMU_TLB0_SIZE_256MB 0x00000070
#define MMU_TLB0_TPAR_MASK  0x00000008 /* Tag Party[28:31] */
#define MMU_TLB0_TID_MASK   0x00000000 /* Translation ID[32:39] */
	/* Address Translation Fields */
#define MMU_TBL1_RPN_MASK   0xFFFFFC00 /* Real Page Number[0:21] */
#define MMU_TBL1_PAR1_MASK  0x00000300 /* Parity for TLB word 1[22:23] */
#define MMU_TBL1_ERPN_MASK  0x00000008 /* Extended Real Page Number[28:31] */
	/* Storage Attribute Fields */
#define MMU_TLB2_PAR2_MASK  0x00000000 /* Parity for TLB word 2[0:1] */
#define MMU_TLB2_U0         0x00008000 /* User-Definable Storage Attribute 0[16] */
#define MMU_TLB2_U1         0x00004000 /* User-Definable Storage Attribute 1[17] */
#define MMU_TLB2_U2         0x00002000 /* User-Definable Storage Attribute 2[18] */
#define MMU_TLB2_U3         0x00001000 /* User-Definable Storage Attribute 3[19] */
#define MMU_TLB2_W          0x00000800 /* Write-Through[20] */
#define MMU_TLB2_I          0x00000400 /* Caching Inhibited[21] */
#define MMU_TLB2_M          0x00000200 /* Memory Coherence Required[22] */
#define MMU_TLB2_G          0x00000100 /* Guarded[23] */
#define MMU_TLB2_E          0x00000080 /* Endian[24] */
#define MMU_TLB2_UX         0x00000020 /* User State Execute Enable[26] */
#define MMU_TLB2_UW         0x00000010 /* User State Write Enable[27] */
#define MMU_TLB2_UR         0x00000008 /* User State Read Enable[28] */
#define MMU_TLB2_SX         0x00000004 /* Supervisor State Execute Enable[29] */
#define MMU_TLB2_SW         0x00000002 /* Supervisor State Write Enable[30] */
#define MMU_TLB2_SR         0x00000001 /* Supervisor State Read Enable[31] */

#define MMU_TLB_SIZE 64

#include <prom/prom_printf.h>

void mmu_on(void) {
	prom_printf("mmucr %#0X\n", __get_mmucr());
	__set_msr(__get_msr() | (MSR_IS | MSR_DS));
}

void mmu_off(void) {
	__set_msr(__get_msr() & ~(MSR_IS | MSR_DS));
}

static inline mmu_vaddr_t mmu_get_fault_address(void) {
	return (mmu_vaddr_t)__get_srr0();
}

void mmu_set_context(mmu_ctx_t ctx) { }
mmu_ctx_t mmu_create_context(mmu_pgd_t *pgd) { return 0; }

mmu_pgd_t *mmu_get_root(mmu_ctx_t ctx) { return 0; }

/**
 * Present functions
 */
int mmu_pgd_present(mmu_pgd_t *pgd) { return 0; }
int mmu_pmd_present(mmu_pmd_t *pmd) { return 0; }
int mmu_pte_present(mmu_pte_t *pte) { return 0; }

/**
 * Set functions
 */
void mmu_pgd_set(mmu_pgd_t *pgd, mmu_pmd_t *pmd) { }

void mmu_pmd_set(mmu_pmd_t *pmd, mmu_pmd_t *pte) { }

void mmu_pte_set(mmu_pgd_t *pte, mmu_paddr_t addr) { }

/**
 * Value functions
 */
mmu_pmd_t * mmu_pgd_value(mmu_pgd_t *pgd) { return 0; }
mmu_pte_t * mmu_pmd_value(mmu_pmd_t *pmd) { return 0; }
mmu_paddr_t mmu_pte_value(mmu_pte_t *pte) { return 0; }

/**
 * Unset functions
 */
void mmu_pgd_unset(mmu_pgd_t *pgd) { }
void mmu_pmd_unset(mmu_pmd_t *pmd) { }
void mmu_pte_unset(mmu_pgd_t *pte) { }

/**
 * Page Table flags
 */
void mmu_pte_set_writable(mmu_pte_t *pte, int val) { }
void mmu_pte_set_usermode(mmu_pte_t *pte, int val) { }
void mmu_pte_set_cacheable(mmu_pte_t *pte, int val) { }

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

#define MMU_PAGE_SIZE_1KB      0
#define MMU_PAGE_SIZE_4KB      1
#define MMU_PAGE_SIZE_16KB     2
#define MMU_PAGE_SIZE_64KB     3
#define MMU_PAGE_SIZE_256KB    4
#define MMU_PAGE_SIZE_1MB      5
#define MMU_PAGE_SIZE_16MB     6
#define MMU_PAGE_SIZE_256MB    7

#define MMU_TLB_SIZE 64

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
#define MMU_TLB0_SIZE_1KB   0x00000050
#define MMU_TLB0_SIZE_16KB  0x00000060
#define MMU_TLB0_SIZE_256KB 0x00000070
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
#define MMU_TLB2_UX         0x00000004 /* Supervisor State Execute Enable[29] */
#define MMU_TLB2_UW         0x00000002 /* Supervisor State Write Enable[30] */
#define MMU_TLB2_UR         0x00000001 /* Supervisor State Read Enable[31] */

void mmu_on(void) {
	__set_msr(__get_msr() | MSR_IS | MSR_DS);
}

void mmu_set_context(mmu_ctx_t ctx) {
}

mmu_ctx_t mmu_create_context(mmu_pgd_t *pgd) {
	return 0;
#if 0
	mmu_ctx_t ctx = (mmu_ctx_t) (++ctx_counter);
	ctx_table[ctx] = pgd;
	return ctx;
#endif
}

mmu_pgd_t *mmu_get_root(mmu_ctx_t ctx) {
	return 0; /*ctx_table[ctx];*/
}

/**
 * Present functions
 */
int mmu_pgd_present(mmu_pgd_t *pgd) {
	return 1;
}

int mmu_pmd_present(mmu_pmd_t *pmd) {
	return (uint32_t)*pmd & MMU_PAGE_PRESENT;
}

int mmu_pte_present(mmu_pte_t *pte) {
	return (uint32_t)*pte & MMU_PAGE_PRESENT;
}

/**
 * Set functions
 */
void mmu_pgd_set(mmu_pgd_t *pgd, mmu_pmd_t *pmd) {
}

void mmu_pmd_set(mmu_pmd_t *pmd, mmu_pmd_t *pte) {
	*pmd = (mmu_pmd_t)(((uint32_t)pte & ~MMU_PAGE_MASK)
			| MMU_PMD_FLAG | MMU_PAGE_PRESENT);
}

void mmu_pte_set(mmu_pgd_t *pte, mmu_paddr_t addr) {
	*pte = (mmu_pte_t)(((uint32_t)addr & (~MMU_PAGE_MASK)
			| MMU_PAGE_PRESENT);
}

/**
 * Value functions
 */
mmu_pmd_t * mmu_pgd_value(mmu_pgd_t *pgd) {
	return (mmu_pmd_t *)pgd;
}

mmu_pte_t * mmu_pmd_value(mmu_pmd_t *pmd) {
	return (mmu_pte_t *)(*pmd & ~MMU_PAGE_MASK);
}

mmu_paddr_t mmu_pte_value(mmu_pte_t *pte) {
	return (mmu_paddr_t)(*pte & ~MMU_PAGE_MASK);
}

/**
 * Unset functions
 */
void mmu_pgd_unset(mmu_pgd_t *pgd) {
}

void mmu_pmd_unset(mmu_pmd_t *pmd) {
	*pmd = 0;
}

void mmu_pte_unset(mmu_pgd_t *pte) {
	*pte = 0;
}

/**
 * Page Table flags
 */
void mmu_pte_set_writable(mmu_pte_t *pte, int val) {
	*pte = val ? *pte | MMU_PAGE_WRITABLE : *pte & ~MMU_PAGE_WRITABLE;
}

void mmu_pte_set_usermode(mmu_pte_t *pte, int val) {
	*pte = val ? *pte | MMU_PAGE_USERMODE : *pte & ~MMU_PAGE_USERMODE;
}

void mmu_pte_set_cacheable(mmu_pte_t *pte, int val) {
	*pte = val ? *pte | MMU_PAGE_CACHEABLE : *pte & ~MMU_PAGE_CACHEABLE;
}


/**
 * @file
 *
 * @brief Specifies MMU interface.
 *
 * @date 10.03.2010
 * @author Anton Bondarev
 */

#ifndef MMU_CORE_H_
#define MMU_CORE_H_

#include <asm/hal/mm/mmu_core.h>


/** Allows caching for this page*/
#define MMU_PAGE_CACHEABLE    __MMU_PAGE_CACHEABLE
/** Allows writing to this page*/
#define MMU_PAGE_WRITEABLE    __MMU_PAGE_WRITEABLE
/** Allows execute program code from this page*/
#define MMU_PAGE_EXECUTEABLE  __MMU_PAGE_EXECUTEABLE

/**
 * Consider 3-level mapping with GLOBAL, MIDDLE, PAGE tables.
 * This should be defined in particulars archs.
 */
#define MMU_GTABLE_MASK         __MMU_GTABLE_MASK 
#define MMU_GTABLE_MASK_OFFSET  __MMU_GTABLE_MASK_OFFSET
#define MMU_MTABLE_MASK			__MMU_MTABLE_MASK        
#define MMU_MTABLE_MASK_OFFSET  __MMU_MTABLE_MASK_OFFSET
#define MMU_PTABLE_MASK         __MMU_PTABLE_MASK
#define MMU_PTABLE_MASK_OFFSET  __MMU_PTABLE_MASK_OFFSET
#define MMU_PAGE_MASK           __MMU_PAGE_MASK

#define MMU_PTE_TABLE_SIZE		__MMU_PTE_TABLE_SIZE
#define MMU_PMD_TABLE_SIZE		__MMU_PMD_TABLE_SIZE
#define MMU_PGD_TABLE_SIZE		__MMU_PGD_TABLE_SIZE

typedef __mmu_paddr_t paddr_t;
typedef __mmu_vaddr_t vaddr_t;

typedef __mmu_page_flags_t mmu_page_flags_t;

/** pgd - page global directory (page table for specific process) */
typedef __mmu_pgd_t mmu_pgd_t;

/** pgd - page middle directory (page table for specific process) */
typedef __mmu_pmd_t mmu_pmd_t;
/** pgd - page table entry (page table for specific process) */
typedef __mmu_pte_t mmu_pte_t;

/**
 * Defines type for structure of MMU environment. This structure must be
 * describe in platform specific part in file <asm/hal/mm/mmu_core.h>.
 */
typedef __mmu_env_t mmu_env_t;

typedef __mmu_ctx_t mmu_ctx_t;

/** Error code for MMU module operation*/
#define MMU_RRTURN_ERROR     (mmu_ctx)(-1)

/**
 * Setup pointed MMU environment to system.
 *
 * @param env - MMU's environment you want set as current.
 */
extern void mmu_set_env(mmu_env_t *env);

/**
 * Saves current MMU environment. Saved environment can be restore by
 * @link #mmu_restore_env @endlink function. If you want setting own traps
 * handler you must use also @link #traps_save_env @endlink and other
 * function for work with the trap's environment.
 *
 * @param env  - buffer for saving current MMU's environment.
 */
extern void mmu_save_env(mmu_env_t *env);

/**
 * Restores saved MMU's environment. Setups pointed MMU's environment as
 * current. The environment must be saved by @link #mmu_save_env @endlink.
 *
 * @param env - MMU's environment you want set as current.
 */
extern void mmu_restore_env(mmu_env_t *env);

/**
 * Switches on virtual mode in system.
 */
extern void mmu_on(void);

/**
 * Switches off virtual mode in system. Switches on real mode.
 */
extern void mmu_off(void);

/**
 * Maps physic memory region on virtual memory. This function inserts one or
 * more records to mmu tables.
 * Inserting occurs for current process id.
 * Addresses and region's size will be align on mmu page size.
 *
 *
 * @param phy_addr - starting physic address for memory region
 * @param phy_addr - starting physic address for memory region
 * @param virt_addr - wishing virtual address for memory region
 * @param reg_size - wishing size of mapping region
 *
 * @return size of mapped region
 * @retval size of mapped region on success
 * @retval -1 on fail;
 */
extern int mmu_map_region(mmu_ctx_t ctx, paddr_t phy_addr, vaddr_t virt_addr,
		size_t reg_size, mmu_page_flags_t flags);

/**
 * Switches current MMU context, changes active pgd therefore memory mapping.
 * This is used during switching active process
 */
extern void switch_mm(mmu_ctx_t prev, mmu_ctx_t next);

/**
 * Allocates new pgd table.
 *
 * @return new MMU context
 * @retval new MMU context on success
 * @retval -1 on failed
 */
extern  mmu_ctx_t mmu_create_context(void);

/**
 * Delete pgd and all nested table from mmu tables
 *
 * @param ctx MMU context has been created @link #mmu_create_context() @endlink
 */
extern void mmu_delete_context(mmu_ctx_t ctx);

/**
 * Set page entry in pte
 *
 * @param ptep - address of entry in table
 * @param pteval - formated value to write in table 
 */
extern void mmu_set_pte(pte_t *ptep, pte_t pteval);

/**
 * Set context table
 *
 * @param ctxp - address of entry in table
 * @param pgdp - formated address to write in table
 */
extern void mmu_ctxd_set(ctxd_t *ctxp, pgd_t *pgdp);

/**
 * Set global table
 *
 * @param pgdp - address of entry in table
 * @param pmdp - formated address to write in table
 */
extern void mmu_pgd_set(pgd_t * pgdp, pmd_t * pmdp);

/**
 * Set middle table
 *
 * @param pmdp - address of entry in table
 * @param ptep - formated address to write in table
 */
extern void mmu_pmd_set(pmd_t * pmdp, pte_t * ptep);

/**
 * Get middle table
 *
 * @param pgdp - address of entry in table
 */
extern pmd_t *mmu_pgd_get(pgd_t * pgdp);

/**
 * Get entry table
 *
 * @param pmdp - address of entry in table
 */
extern pte_t *mmu_pmd_get(pmd_t * pmdp);

/**
 * Format page entry with specified address and flags 
 *
 * @param addr - physical address
 * @param flags - flags of entry
 */
extern pte_t mmu_pte_format(__mmu_paddr_t addr, __mmu_page_flags_t flags);

/**
 * Get physical address from page entry
 *
 * @param pte - page entry 
 */
extern paddr_t mmu_pte_extract(pte_t pte);

/**
 * Get flags from page entry
 *
 * @param pte - page entry 
 */
extern mmu_page_flags_t mmu_flags_extract(pte_t pte);

/**
 * Checks if the pte is pte.
 * Some archs allow using pte in pmd or pgd 
 *
 * @param pte - page entry 
 */
extern int mmu_is_pte(pte_t pte);

/**
 * Translate flags to arch specified 
 *
 * @param flags - pointer to flags in general format
 * @retval flags in arch specified format
 */
extern __mmu_page_flags_t mmu_flags_translate(mmu_page_flags_t flags);

/**
 * Get root pointer of context
 *
 * @param ctx - context
 * @retval pointer to first pgd of memory 
 */
extern pgd_t * mmu_get_root(mmu_ctx_t ctx);
#endif /* MMU_CORE_H_ */

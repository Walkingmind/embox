/**
 * @file
 *
 * @date 07.04.2010
 * @author Anton Bondarev
 */

#ifndef SPARC_MMU_PAGE_H_
#define SPARC_MMU_PAGE_H_

#include <hal/mm/mmu_core.h>

extern mmu_env_t *cur_env;

#define GET_PGD(ctx) \
	((pgd_t*)((unsigned long)(*(cur_env->ctx + ctx) << 4) & MMU_PTE_PMASK))

#define GET_PMD(ctx) \
	((pmd_t*)((unsigned long)((*GET_PGD(ctx)) << 4) & MMU_PTE_PMASK))

#define GET_PTE(ctx) \
	((pte_t*)((unsigned long)((*GET_PMD(ctx)) << 4) & MMU_PTE_PMASK))

#define GET_FLAGS(ctx, vaddr) \
	((mmu_page_flags_t*)(GET_PMD(ctx) + (vaddr >> MMU_MTABLE_MASK_OFFSET)))


inline static bool mmu_entry_is_pte(pte_t *pte) {
	return (0x2 == (0x3 & (uint32_t)(*pte))) ? true : false;
}

inline static bool mmu_entry_is_valid(pte_t *pte) {
	return (0x0 != (0x3 & (uint32_t)(*pte))) ? true : false;
}

inline static pte_t *mmu_get_next_level_pte(pte_t *ptp, int idx) {
	return (pte_t*)((uint32_t*)((((uint32_t)(*(ptp + idx)) << 4)) & (MMU_PTE_PMASK)));
}

static unsigned long offsets[] = {
	32,
	MMU_GTABLE_MASK_OFFSET,
	MMU_MTABLE_MASK_OFFSET,
	MMU_PTABLE_MASK_OFFSET,
	0
};

static unsigned long masks[] = {
	0xffffffff,
	MMU_GTABLE_MASK,
	MMU_MTABLE_MASK,
	MMU_PTABLE_MASK,
	MMU_PAGE_MASK
};

inline static pte_t *mmu_page_get_entry(mmu_ctx_t ctx, vaddr_t vaddr) {
	pte_t *pte = GET_PGD(ctx);
	int level = 1;

	for(level; level < 4; level ++) {
		if (mmu_entry_is_pte(pte + ((vaddr & masks[level]) >> offsets[level])) /*&& mmu_entry_is_valid(pte)*/) {
			return (pte + ((vaddr & masks[level]) >> offsets[level]));
		}
		pte = mmu_get_next_level_pte(pte, (vaddr & masks[level]) >> offsets[level]);
	}
	return NULL;
}

inline static void mmu_page_mark_writable(mmu_ctx_t ctx, vaddr_t vaddr) {
	pmd_t *m0 = GET_PMD(ctx);
	mmu_page_flags_t *flags;
	vaddr &= ~MMU_PAGE_MASK & MMU_MTABLE_MASK;
	flags = GET_FLAGS(ctx, vaddr);
	mmu_set_pte(m0 + (vaddr>> MMU_MTABLE_MASK_OFFSET),
			*flags | (MMU_PTE_RW << 2));
}

inline static void mmu_page_mark_executeable(mmu_ctx_t ctx, vaddr_t vaddr) {
	pmd_t *m0 = GET_PGD(ctx);
	mmu_page_flags_t *flags;
	vaddr &= ~MMU_PAGE_MASK & MMU_MTABLE_MASK;
	flags = GET_FLAGS(ctx, vaddr);
	mmu_set_pte(m0 + (vaddr >> MMU_MTABLE_MASK_OFFSET),
			*flags | (MMU_PTE_RE << 2));
}

inline static void mmu_page_mark_cacheable(mmu_ctx_t ctx, vaddr_t vaddr) {
	pmd_t *m0 = GET_PMD(ctx);
	mmu_page_flags_t *flags;
	vaddr &= ~MMU_PAGE_MASK & MMU_MTABLE_MASK;
	flags = GET_FLAGS(ctx, vaddr);
	mmu_set_pte(m0 + (vaddr >> MMU_MTABLE_MASK_OFFSET),
			*flags | MMU_PTE_CACHE);
}

inline static mmu_page_flags_t mmu_page_get_flags(mmu_ctx_t ctx, vaddr_t vaddr) {
	mmu_page_flags_t *flags;
	vaddr &= ~MMU_PAGE_MASK & MMU_MTABLE_MASK;
	flags = GET_FLAGS(ctx, vaddr);
	return *flags;
}
#include "asm/cache.h"

inline static void mmu_page_set_flags(mmu_ctx_t ctx, vaddr_t vaddr,
			mmu_page_flags_t flags) {
	pte_t pte_value;
	pte_t *pte = mmu_page_get_entry(ctx, vaddr);
	if (NULL == pte) {
		return;
	}

	pte_value = (*pte) & (~0x1C) ;

	mmu_set_pte(pte,
			pte_value | ((flags & 0x7) << 2));

/*	mmu_flush_cache_all(); */
	mmu_flush_tlb_all();

}

inline static void mmu_page_mark_valid(mmu_ctx_t ctx, vaddr_t vaddr) {
}

inline static void mmu_page_mark_invalide(mmu_ctx_t ctx, vaddr_t vaddr) {
}

#endif /* SPARC_MMU_PAGE_H_ */
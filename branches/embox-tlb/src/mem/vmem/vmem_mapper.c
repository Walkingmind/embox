/**
 * @file
 * @brief
 *
 * @date 05.10.2012
 * @author Anton Bulychev
 */

#include <errno.h>
#include <assert.h>
#include <string.h>

#include <hal/mmu.h>
#include <util/binalign.h>
#include <mem/vmem.h>
#include <mem/vmem/vmem_alloc.h>


static inline void vmem_set_pte_flags(mmu_pte_t *pte, vmem_page_flags_t flags);
static inline int do_map_region(mmu_ctx_t ctx, mmu_paddr_t phy_addr, mmu_vaddr_t virt_addr, size_t reg_size, vmem_page_flags_t flags);
static inline int do_create_space(mmu_ctx_t ctx, mmu_vaddr_t virt_addr, size_t reg_size, vmem_page_flags_t flags);
static inline int do_copy_region(mmu_ctx_t nctx, mmu_ctx_t ctx, mmu_vaddr_t virt_addr, size_t reg_size);

int vmem_map_region(mmu_ctx_t ctx, mmu_paddr_t phy_addr, mmu_vaddr_t virt_addr, size_t reg_size, vmem_page_flags_t flags) {
	int res = do_map_region(ctx, phy_addr, virt_addr, reg_size, flags);

	if (res) {
		vmem_unmap_region(ctx, virt_addr, reg_size, 0);
	}

	return res;
}

int vmem_create_space(mmu_ctx_t ctx, mmu_vaddr_t virt_addr, size_t reg_size, vmem_page_flags_t flags) {
	int res = do_create_space(ctx, virt_addr, reg_size, flags);

	if (res) {
		vmem_unmap_region(ctx, virt_addr, reg_size, 1);
	}

	return res;
}

extern int vmem_copy_region(mmu_ctx_t nctx, mmu_ctx_t ctx, mmu_vaddr_t virt_addr, size_t reg_size) {
	int res = do_copy_region(nctx, ctx, virt_addr, reg_size);

	if (res) {
		vmem_unmap_region(nctx, virt_addr, reg_size, 1);
	}

	return res;
}

int vmem_page_set_flags(mmu_ctx_t ctx, mmu_vaddr_t virt_addr, vmem_page_flags_t flags) {
	size_t pgd_idx, pmd_idx, pte_idx;
	mmu_pgd_t *pgd;
	mmu_pmd_t *pmd;
	mmu_pte_t *pte;

	// Actually, this is unnecessary
	virt_addr = virt_addr & (~MMU_PAGE_MASK);

	pgd = mmu_get_root(ctx);

	pgd_idx = ((uint32_t) virt_addr & MMU_PGD_MASK) >> MMU_PGD_SHIFT;
	pmd_idx = ((uint32_t) virt_addr & MMU_PMD_MASK) >> MMU_PMD_SHIFT;
	pte_idx = ((uint32_t) virt_addr & MMU_PTE_MASK) >> MMU_PTE_SHIFT;

	if (!mmu_pgd_present(pgd + pgd_idx)) {
		return -ENOENT;
	}

	pmd = mmu_pgd_value(pgd + pgd_idx);

	if (!mmu_pmd_present(pmd + pmd_idx)) {
		return -ENOENT;
	}

	pte = mmu_pmd_value(pmd + pmd_idx);

	if (!mmu_pte_present(pte + pte_idx)) {
		return -ENOENT;
	}

	vmem_set_pte_flags(pte + pte_idx, flags);

	return ENOERR;
}

static inline void vmem_set_pte_flags(mmu_pte_t *pte, vmem_page_flags_t flags) {
	mmu_pte_set_writable(pte, flags & VMEM_PAGE_WRITABLE);
	mmu_pte_set_cacheable(pte, flags & VMEM_PAGE_CACHEABLE);
	mmu_pte_set_usermode(pte, flags & VMEM_PAGE_USERMODE);
}

mmu_paddr_t vmem_translate(mmu_ctx_t ctx, mmu_vaddr_t virt_addr) {
	size_t pgd_idx, pmd_idx, pte_idx;
	mmu_pgd_t *pgd;
	mmu_pmd_t *pmd;
	mmu_pte_t *pte;

	pgd = mmu_get_root(ctx);

	pgd_idx = ((uint32_t) virt_addr & MMU_PGD_MASK) >> MMU_PGD_SHIFT;
	pmd_idx = ((uint32_t) virt_addr & MMU_PMD_MASK) >> MMU_PMD_SHIFT;
	pte_idx = ((uint32_t) virt_addr & MMU_PTE_MASK) >> MMU_PTE_SHIFT;

	if (!mmu_pgd_present(pgd + pgd_idx)) {
		return 0;
	}

	pmd = mmu_pgd_value(pgd + pgd_idx);

	if (!mmu_pmd_present(pmd + pmd_idx)) {
		return 0;
	}

	pte = mmu_pmd_value(pmd + pmd_idx);

	if (!mmu_pte_present(pte + pte_idx)) {
		return 0;
	}

	return mmu_pte_value(pte + pte_idx) + (virt_addr & MMU_PAGE_MASK);
}

static inline int do_map_region(mmu_ctx_t ctx, mmu_paddr_t phy_addr, mmu_vaddr_t virt_addr, size_t reg_size, vmem_page_flags_t flags) {
	mmu_pgd_t *pgd;
	mmu_pmd_t *pmd;
	mmu_pte_t *pte;
	mmu_paddr_t p_end = phy_addr + reg_size;
	size_t pgd_idx, pmd_idx, pte_idx;

	/* Considering that all boundaries are already aligned */
	assert(!(virt_addr & MMU_PAGE_MASK));
	assert(!(phy_addr  & MMU_PAGE_MASK));
	assert(!(reg_size  & MMU_PAGE_MASK));

	pgd = mmu_get_root(ctx);

	pgd_idx = ((uint32_t) virt_addr & MMU_PGD_MASK) >> MMU_PGD_SHIFT;
	pmd_idx = ((uint32_t) virt_addr & MMU_PMD_MASK) >> MMU_PMD_SHIFT;
	pte_idx = ((uint32_t) virt_addr & MMU_PTE_MASK) >> MMU_PTE_SHIFT;

	for ( ; pgd_idx < MMU_PGD_ENTRIES; pgd_idx++) {

		if (!mmu_pgd_present(pgd + pgd_idx)) {
			if (!(pmd = vmem_alloc_pmd_table())) {
				return -ENOMEM;
			}
			mmu_pgd_set(pgd + pgd_idx, pmd);
		} else {
			pmd = mmu_pgd_value(pgd + pgd_idx);
		}

		for ( ; pmd_idx < MMU_PMD_ENTRIES; pmd_idx++) {

			if (!mmu_pmd_present(pmd + pmd_idx)) {
				if (!(pte = vmem_alloc_pte_table())) {
					return -ENOMEM;
				}
				mmu_pmd_set(pmd + pmd_idx, pte);
			} else {
				pte = mmu_pmd_value(pmd + pmd_idx);
			}

			for ( ; pte_idx < MMU_PTE_ENTRIES; pte_idx++) {
				/* Considering that address has not mapped yet */
				assert(!mmu_pte_present(pte + pte_idx));

				mmu_pte_set(pte + pte_idx, phy_addr);
				vmem_set_pte_flags(pte + pte_idx, flags);

				virt_addr += MMU_PAGE_SIZE;
				phy_addr  += MMU_PAGE_SIZE;

				if (phy_addr >= p_end) {
					return ENOERR;
				}
			}

			pte_idx = 0;
		}

		pmd_idx = 0;
	}

	return -EINVAL;
}

static inline int do_create_space(mmu_ctx_t ctx, mmu_vaddr_t virt_addr, size_t reg_size, vmem_page_flags_t flags) {
	mmu_pgd_t *pgd;
	mmu_pmd_t *pmd;
	mmu_pte_t *pte;
	mmu_paddr_t v_end = virt_addr + reg_size;
	size_t pgd_idx, pmd_idx, pte_idx;
	void *addr;

	/* Considering that all boundaries are already aligned */
	assert(!(virt_addr & MMU_PAGE_MASK));
	assert(!(reg_size  & MMU_PAGE_MASK));

	pgd = mmu_get_root(ctx);

	pgd_idx = ((uint32_t) virt_addr & MMU_PGD_MASK) >> MMU_PGD_SHIFT;
	pmd_idx = ((uint32_t) virt_addr & MMU_PMD_MASK) >> MMU_PMD_SHIFT;
	pte_idx = ((uint32_t) virt_addr & MMU_PTE_MASK) >> MMU_PTE_SHIFT;

	for ( ; pgd_idx < MMU_PGD_ENTRIES; pgd_idx++) {

		if (!mmu_pgd_present(pgd + pgd_idx)) {
			if (!(pmd = vmem_alloc_pmd_table())) {
				return -ENOMEM;
			}
			mmu_pgd_set(pgd + pgd_idx, pmd);
		} else {
			pmd = mmu_pgd_value(pgd + pgd_idx);
		}

		for ( ; pmd_idx < MMU_PMD_ENTRIES; pmd_idx++) {

			if (!mmu_pmd_present(pmd + pmd_idx)) {
				if (!(pte = vmem_alloc_pte_table())) {
					return -ENOMEM;
				}
				mmu_pmd_set(pmd + pmd_idx, pte);
			} else {
				pte = mmu_pmd_value(pmd + pmd_idx);
			}

			for ( ; pte_idx < MMU_PTE_ENTRIES; pte_idx++) {
				/* Considering that space has not allocated yet */
				assert(!mmu_pte_present(pte + pte_idx));

				if (!(addr = vmem_alloc_page())) {
					return -ENOMEM;
				}

				mmu_pte_set(pte + pte_idx, (mmu_paddr_t) addr);
				vmem_set_pte_flags(pte + pte_idx, flags);

				virt_addr += MMU_PAGE_SIZE;

				if (virt_addr >= v_end) {
					return ENOERR;
				}
			}

			pte_idx = 0;
		}

		pmd_idx = 0;
	}

	return -EINVAL;
}

#define ALIGN_UP(x, aligment) (((x) + (aligment)) & (~((aligment)-1)))

static inline int do_copy_region(mmu_ctx_t nctx, mmu_ctx_t ctx, mmu_vaddr_t virt_addr, size_t reg_size) {
	mmu_pgd_t *pgd, *npgd;
	mmu_pmd_t *pmd, *npmd;
	mmu_pte_t *pte, *npte;
	mmu_paddr_t v_end = virt_addr + reg_size;
	size_t pgd_idx, pmd_idx, pte_idx;
	void *naddr, *tmp_page = (void *) 0x1000;

	/* Considering that all boundaries are already aligned */
	assert(!(virt_addr & MMU_PAGE_MASK));
	assert(!(reg_size  & MMU_PAGE_MASK));

	pgd  = mmu_get_root(ctx);
	npgd = mmu_get_root(nctx);

	pgd_idx = ((uint32_t) virt_addr & MMU_PGD_MASK) >> MMU_PGD_SHIFT;
	pmd_idx = ((uint32_t) virt_addr & MMU_PMD_MASK) >> MMU_PMD_SHIFT;
	pte_idx = ((uint32_t) virt_addr & MMU_PTE_MASK) >> MMU_PTE_SHIFT;

	for ( ; pgd_idx < MMU_PGD_ENTRIES; pgd_idx++) {

		if (mmu_pgd_present(pgd + pgd_idx)) {
			if (!mmu_pgd_present(npgd + pgd_idx)) {
				if (!(npmd = vmem_alloc_pmd_table())) {
					return -ENOMEM;
				}
				mmu_pgd_set(npgd + pgd_idx, npmd);
			} else {
				npmd = mmu_pgd_value(npgd + pgd_idx);
			}
			pmd = mmu_pgd_value(pgd + pgd_idx);

			for ( ; pmd_idx < MMU_PMD_ENTRIES; pmd_idx++) {

				if (mmu_pmd_present(pmd + pmd_idx)) {
					if (!mmu_pmd_present(npmd + pmd_idx)) {
						if (!(npte = vmem_alloc_pte_table())) {
							return -ENOMEM;
						}
						mmu_pmd_set(npmd + pmd_idx, npte);
					} else {
						npte = mmu_pmd_value(npmd + pmd_idx);
					}
					pte = mmu_pmd_value(pmd + pmd_idx);

					for ( ; pte_idx < MMU_PTE_ENTRIES; pte_idx++) {
						if (virt_addr >= v_end) {
							return 0;
						}

						if (mmu_pte_present(pte + pte_idx)) {
							/* Considering that it has not been mapped yet */
							assert(!mmu_pte_present(npte + pte_idx));

							if (!(naddr = vmem_alloc_page())) {
								return -ENOMEM;
							}

							/* Copy memory via NULL */
							if (vmem_map_region(ctx, (mmu_paddr_t) naddr, (mmu_vaddr_t) tmp_page, VMEM_PAGE_SIZE, VMEM_PAGE_WRITABLE)) {
								return -ENOMEM;
							}

							memcpy(tmp_page, (void *) virt_addr, VMEM_PAGE_SIZE);
							vmem_unmap_region(ctx, (mmu_vaddr_t) tmp_page, VMEM_PAGE_SIZE, 0);

							mmu_pte_set(npte + pte_idx, (mmu_paddr_t) naddr);
							mmu_pte_set_usermode(npte + pte_idx, 1);
							mmu_pte_set_writable(npte + pte_idx, 1);
						}

						virt_addr += VMEM_PAGE_SIZE;
					}

					pte_idx = 0;

				} else {
					virt_addr = ALIGN_UP(virt_addr, MMU_PMD_SIZE);

					pte_idx = 0;
				}

			}

			pmd_idx = 0;

		} else {
			virt_addr = ALIGN_UP(virt_addr, MMU_PGD_SIZE);

			pmd_idx = 0;
			pte_idx = 0;
		}
	}

	return 0;
}


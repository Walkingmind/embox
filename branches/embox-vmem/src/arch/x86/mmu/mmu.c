/**
 * @file
 * @brief
 *
 * @date 04.10.2012
 * @author Anton Bulychev
 */

#include <hal/mmu.h>
#include <asm/flags.h>
#include <types.h>

#define MMU_PAGE_PRESENT    (1UL)
#define MMU_PAGE_WRITABLE   (1UL << 1)

static mmu_pgd_t *ctx_table[0x100] __attribute__((aligned(MMU_PAGE_SIZE)));
static int ctx_counter = 0;


static inline void set_cr3(unsigned int pagedir)
{
   asm ("mov %0, %%cr3": :"r" (pagedir));
}

static inline unsigned int get_cr3(void)
{
   unsigned int _cr3;

   asm ("mov %%cr3, %0":"=r" (_cr3));
   return _cr3;
}

static inline void set_cr0(unsigned int val)
{
   asm ("mov %0, %%cr0" : :"r" (val));
}


static inline unsigned int get_cr0(void)
{
   unsigned int _cr0;

   asm ("mov %%cr0, %0":"=r" (_cr0));
   return _cr0;
}

static inline unsigned int get_cr2(void) {
    unsigned int _cr2;

    asm ("mov %%cr2, %0":"=r" (_cr2):);
    return _cr2;
}

void mmu_flush_tlb_single(unsigned long addr) {
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

void mmu_flush_tlb(void) {
	set_cr3(get_cr3());
}

void mmu_on(void) {
    set_cr0(get_cr0() | X86_CR0_PG);
}

void mmu_off(void) {
	set_cr0(get_cr0() & ~X86_CR0_PG);
}

mmu_vaddr_t mmu_get_fault_address(void) {
	return get_cr2();
}

void switch_mm(mmu_ctx_t prev, mmu_ctx_t next) {
	set_cr3((uint32_t) mmu_get_root(next));
}

mmu_ctx_t mmu_create_context(mmu_pgd_t *pgd) {
	mmu_ctx_t ctx = (mmu_ctx_t) (ctx_counter++);
	ctx_table[ctx] = pgd;
	return ctx;
}

mmu_pgd_t *mmu_get_root(mmu_ctx_t ctx) {
	return ctx_table[ctx];
}

/*
 * Page Global Directory
 */

int mmu_pgd_present(mmu_pgd_t *pgd) {
	return 1;
}

void mmu_pgd_set(mmu_pgd_t *pgd, mmu_pmd_t *pmd) {
	return ;
}

mmu_pmd_t *mmu_pgd_follow(mmu_pgd_t *pgd) {
	return (mmu_pmd_t *) pgd;
}

/*
 * Page Middle Directory
 */

int mmu_pmd_present(mmu_pmd_t *pmd) {
	return ((uint32_t) *pmd & MMU_PAGE_PRESENT);
}

void mmu_pmd_set(mmu_pmd_t *pmd, mmu_pmd_t *pte) {
	// TODO: flags
	*pmd = (mmu_pmd_t) ((((uint32_t) pte) & (~MMU_PAGE_MASK))
			| MMU_PAGE_WRITABLE | MMU_PAGE_PRESENT);
}

mmu_pte_t *mmu_pmd_follow(mmu_pmd_t *pmd) {
	return (mmu_pte_t *) ((*pmd) & (~MMU_PAGE_MASK));
}

/*
 * Page Table
 */

int mmu_pte_present(mmu_pte_t *pte) {
	return ((uint32_t) *pte & MMU_PAGE_PRESENT);
}

void mmu_pte_set(mmu_pgd_t *pte, mmu_paddr_t addr) {
	*pte = (mmu_pte_t) ((((uint32_t) addr) & (~MMU_PAGE_MASK))
			| MMU_PAGE_WRITABLE | MMU_PAGE_PRESENT);
}

mmu_paddr_t mmu_pte_follow(mmu_pte_t *pte) {
	return (mmu_paddr_t) ((*pte) & (~MMU_PAGE_MASK));
}

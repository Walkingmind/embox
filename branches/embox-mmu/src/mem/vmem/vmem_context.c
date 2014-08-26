/**
 * @file
 *
 * @date Jul 31, 2014
 * @author: Anton Bondarev
 */
#include <errno.h>

#include <hal/mmu.h>
#include <mem/vmem.h>
#include <mem/vmem/vmem_alloc.h>

#include <kernel/sched/sched_lock.h>


extern int vmem_map_kernel(mmu_ctx_t ctx);
extern mmu_ctx_t mmap_get_current_context(void);

int vmem_create_context(mmu_ctx_t *ctx) {
	mmu_pgd_t *pgd = vmem_alloc_pgd_table();

	if (!pgd) {
		return -ENOMEM;
	}

	*ctx = mmu_create_context(pgd);

	return ENOERR;
}

mmu_ctx_t vmem_current_context(void) {
	return mmap_get_current_context();
}

/* FIXME: remove create context from here */
int vmem_init_context(mmu_ctx_t *ctx) {
	int err;

	if ((err = vmem_create_context(ctx))) {
		return err;
	}

	return vmem_map_kernel(*ctx);
}

void vmem_free_context(mmu_ctx_t ctx) {
	/*
	 * To unmap this context we should switch to kernel task virtual context.
	 * Actually, we can save this context for the later created tasks.
	 */

	sched_lock();
	{
		//XXX: Bad code
		mmu_set_context(1);

		vmem_unmap_region(ctx, 0, 0x80000000UL, 0);
	}
	sched_unlock();
}

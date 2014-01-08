/**
 * @file
 * @brief Implements MMU core interface @link #mmu_core.h @endllink
 *        for Microblaze architecture.
 *
 * @date 10.03.10
 * @author Anton Bondarev
 */

#include <types.h>
#include <string.h>
#include <asm/msr.h>
#include <hal/mm/mmu_core.h>
#include <asm/cache.h>
#include <embox/unit.h>
#include <hal/ipl.h>

/* buffer for utlb records */
static __mmu_table_t system_utlb;

/* main system MMU environment*/
static mmu_env_t system_env;

/* pointer to current MMU environment */
static mmu_env_t *cur_env;

/* cur index in utlb */
static uint32_t cur_utlb_idx;

/* Setup module starting function */
EMBOX_UNIT_INIT(mmu_init);


static inline void mmu_save_status(uint32_t *status) {
	*status = msr_get_value() & MSR_VM_MASK;
//	*status &= ~(MSR_VM_MASK);
}

static inline void mmu_restore_status(uint32_t *status) {
	//msr_set_value(msr_get_value() | ((*status) & ~(MSR_VM_MASK)));
	if (*status & MSR_VM_MASK) {
		mmu_on();
	} else {
		mmu_off();
	}
}

void mmu_on(void) {
#if 0
	register uint32_t msr;
	__asm__ __volatile__ (
		"mfs     %0, rmsr;\n\t"
		"ori   %0, r0, %1;\n\t"
		"mts     rmsr, %0;\n\t" :
		"=r"(msr) :
		"i"(MSR_VM_MASK) :
		"memory"
	);
#else
	__asm__ __volatile__ (
		"msrset  r0, %0;\n\t"
		 :
		 : "i"(MSR_VM_MASK)
	);
#endif
}

void mmu_off(void) {
#if 0
	register uint32_t msr;
	__asm__ __volatile__ (
		"mfs     %0, rmsr;\n\t"
		"andni   %0, r0, %1;\n\t"
		"mts     rmsr, %0;\n\t" :
		"=r"(msr) :
		"i"(MSR_VM_MASK) :
		"memory"
	);
#else
	__asm__ __volatile__ (
		"msrclr  r0, %0;\n\t"
		:
		: "i"(MSR_VM_MASK)

	);
#endif
}

void set_utlb_record(int tlbx, uint32_t tlblo, uint32_t tlbhi) {
	__asm__ __volatile__ (
		"mts rtlbx, %0;\n\t"
		"mts rtlblo, %1;\n\t"
		"mts rtlbhi, %2;\n\t"
		:
		: "r"(tlbx),"r"(tlblo), "r" (tlbhi)
		: "memory"
	);
}

void get_utlb_record(int tlbx, uint32_t *tlblo, uint32_t *tlbhi) {
	uint32_t tmp1, tmp2;
	__asm__ __volatile__ (
		"mts rtlbx, %2;\n\t"
		"mfs %0, rtlblo;\n\t"
		"mfs %1, rtlbhi;\n\t"
		: "=r"(tmp1),"=r" (tmp2)
		: "r"(tlbx)
		: "memory"
	);
	*tlblo = tmp1;
	*tlbhi = tmp2;
}

void mmu_save_table(__mmu_table_t utlb) {
	int i;
	for (i = 0; i < UTLB_QUANTITY_RECORDS; i++) {
		get_utlb_record(i, &(&utlb[i])->tlblo, &(&utlb[i])->tlbhi);
	}
}

void mmu_restore_table(__mmu_table_t utlb) {
	int i;
	for (i = 0; i < UTLB_QUANTITY_RECORDS; i++) {
		set_utlb_record(i, (&utlb[i])->tlblo, (&utlb[i])->tlbhi);
	}
}

static inline uint32_t reg_size_convert(size_t reg_size) {
	switch (reg_size) {
	case 0x400: /* 1kb */
		return RTLBHI_SIZE_1K;
	case 0x1000: /* 4k field */
		return RTLBHI_SIZE_4K;
	case 0x4000: /* 16k field */
		return RTLBHI_SIZE_16K;
	case 0x10000: /* 64k field */
		return RTLBHI_SIZE_64K;
	case 0x40000: /* 256 kb*/
		return RTLBHI_SIZE_256K;
	case 0x100000: /* 1M field */
		return RTLBHI_SIZE_1M;
	case 0x400000: /* 4M field*/
		return RTLBHI_SIZE_4M;
	case 0x1000000: /* 16M field */
		return RTLBHI_SIZE_16M;
	default: /* wrong size*/
		return -1;
	}
}

int mmu_map_region(mmu_ctx_t ctx, paddr_t phy_addr, vaddr_t virt_addr,
		size_t reg_size, uint32_t flags) {
	uint32_t tlblo, tlbhi; /* mmu registers */
	uint32_t size_field;
	/* setup tlbhi register fields */
	size_field = reg_size_convert(reg_size);
	if (-1 == size_field) {
		return -1;
	}
	RTLBHI_SET(tlbhi, virt_addr, size_field);

	/* setup tlbhi register firelds */
	/*(var, phy_addr, cacheable, ex, wr)*/

	RTLBLO_SET(tlblo, phy_addr,
			((flags & MMU_PAGE_CACHEABLE) ? 1 : 0) ,
			((flags & MMU_PAGE_EXECUTEABLE) ? 1 : 0),
			((flags & MMU_PAGE_WRITEABLE) ? 1 : 0));

#if 0
	printk("\n\nin mmu_map_region: ctx = 0x%x, phy_addr = 0x%x, virt_addr = 0x%x,"
			" reg_size = 0x%x, flags = 0x%x\n",
			ctx, phy_addr, virt_addr, reg_size, flags);
	printk("\ttlblo = 0x%X tlbhi=0x%X\n", tlblo, tlbhi);
#endif
	set_utlb_record((cur_utlb_idx++) % UTLB_QUANTITY_RECORDS, tlblo, tlbhi);

	return cur_utlb_idx;
}


void mmu_set_env(mmu_env_t *env) {
	mmu_off();

	/* change cur_env pointer */
	cur_env = env;

	/* flush utlb records */
	mmu_restore_table(env->utlb_table);

	/* set MMU mode */
	if (env->status) {
		mmu_off();
	}

}

void mmu_restore_env(mmu_env_t *env) {
	unsigned int ipl = ipl_save();

	mmu_set_env(env);

	ipl_restore(ipl);
}

void mmu_save_env(mmu_env_t *env) {
	unsigned int ipl = ipl_save();

	/* disable virtual mode*/
	mmu_off();

	mmu_save_status(&(cur_env->status));

	memcpy(env, cur_env, sizeof(mmu_env_t));

#if 0
	/* flush utlb records */
	mmu_save_table(env->utlb_table);
#endif

	if (cur_env->status) {
		mmu_on();
	}

	ipl_restore(ipl);
}

vaddr_t mmu_get_fault_address(void) {
	uint32_t ret;
	__asm__ __volatile__ (
		"mfs	%0, rear; \n\t"
		: "=r" (ret)
	);
	return (vaddr_t) ret;
}

/*
 * Module initializing function.
 * Setups system environment, but neither switch on virtual mode nor
 * write utlb records.
 */
static int mmu_init(void) {
	(&system_env)->status = 0;
	(&system_env)->fault_addr = 0;
	(&system_env)->inst_fault_cnt = (&system_env)->data_fault_cnt = 0;
	(&system_env)->utlb_table = system_utlb;

	cur_env = &system_env;
	cache_disable();
	return 0;
}
/**
 * @file
 * @brief testing mmu module
 *
 * @date 09.06.2009
 * @author Anton Bondarev
 */
#include <shell_command.h>
#include <asm/leon.h>
#include <asm/mmu.h>

#define COMMAND_NAME     "mmu_probe"
#define COMMAND_DESC_MSG "testing mmu module"
#define HELP_MSG         "Usage: mmu_probe [-i] [-v] [-h]"
static const char *man_page =
	#include "mmu_probe_help.inc"
	;

DECLARE_SHELL_COMMAND(COMMAND_NAME, exec, COMMAND_DESC_MSG, HELP_MSG, man_page);

/**
 * show MMU register
 */
static bool mmu_show_reg() {
	printf("Registers MMU:\n");
//	printf("CTLR REG:\t%X\n", srmmu_get_mmureg(SRMMU_CTRL_REG));
//	printf("CTXTBL PTR:\t%X\n", srmmu_get_mmureg(SRMMU_CTXTBL_PTR));
//	printf("CTX REG:\t%X\n", srmmu_get_mmureg(SRMMU_CTX_REG));
//	printf("FAULT STATUS:\t%X\n", srmmu_get_mmureg(SRMMU_FAULT_STATUS));
//	printf("FAULT ADDR:\t%X\n", srmmu_get_mmureg(SRMMU_FAULT_ADDR));
	return 0;
}
static bool mmu_show_version() {
	printf("Registers MMU:\n");
	return 0;
}


#define TLBNUM 4


static bool mmu_probe() {

//	ctxd_t *c0 = (ctxd_t *) &ctx;
//	pgd_t *g0 = (pgd_t *) &pg0;
//	pmd_t *m0 = (pmd_t *) &pm0;
//	pte_t *p0 = (pte_t *) &pt0;
	unsigned long pteval;
	unsigned long j,i, val;
//	unsigned long paddr, vaddr, val;
//	unsigned long *pthaddr = &pth_addr1;
	functype func = mmu_func1;
	//int i = 0;
	//alloc mem for pages
	__asm__(
			".section .data\n\t"
			".align %0\n\t"
			"page0: .skip %0\n\t"
			"page1: .skip %0\n\t"
			"page2: .skip %4\n\t"
			".text\n"
			: : "i" (PAGE_SIZE),
			"i"(SRMMU_PGD_TABLE_SIZE) ,
			"i"(SRMMU_PMD_TABLE_SIZE) ,
			"i"(SRMMU_PTE_TABLE_SIZE) ,
			"i"((3)*PAGE_SIZE) );

	mmu_probe_init();
	mmu_flush_cache_all ();
	mmu_flush_tlb_all ();
	printf ("mmu_test\n");

//	/* one-on-one mapping for context 0 */
	mmu_probe_map_region(0, 0, 0x1000000, MMU_PRIV);
//	mmu_probe_map_region(0x20000000, 0x20000000, 0x1000000, MMU_PRIV);
	mmu_probe_map_region(0x40000000, 0x40000000, 0x1000000, MMU_PRIV);
	mmu_probe_map_region(0x80000000, 0x80000000, 0x1000000, MMU_PRIV);

 /* testarea:
 *  map 0x40000000  at f0080000 [vaddr:(0) (240)(2)(-)] as pmd
 *  map page0       at f0041000 [vaddr:(0) (240)(1)(1)] as page SRMMU_PRIV_RDONLY
 *  map mmu_func1() at f0042000 [vaddr:(0) (240)(1)(2)] as page
 *  map f0043000 - f007f000 [vaddr:(0) (240)(1)(3)] - [vaddr:(0) (240)(1)(63)] as page
 * page fault test:
 *  missing pgd at f1000000 [vaddr:(0) (241)(-)(-)]
 */
	mmu_probe_map_region(0x40000000, 0xf0080000, 0x40000, MMU_PRIV);
	//not alloc here (alloc after page_fault)
	mmu_probe_map_region(0x0, 0xf0042000, 0x1000, 0);
	//first read only during trap clear this flag
	mmu_probe_map_region((unsigned long)&page0, 0xf0041000, 0x1000, MMU_PRIV_RDONLY);
	for (i = 3; i < TLBNUM+3; i++) {
		mmu_probe_map_region((((unsigned long) &page2) + (((i - 3) % 3) * PAGE_SIZE)), (0xf0040000 + (i * PAGE_SIZE)) , 0x1000, MMU_PRIV);
	}
	mmu_probe_repair_table_init((unsigned long)&page0);

//for translation test
	((unsigned long *)&page0)[0] = 0;
	((unsigned long *)&page0)[1] = 0x12345678;

//  //repair table
// *((unsigned long **)&pth_addr) =  pthaddr;
//  /* repair info for fault (0xf1000000)*/
//  pthaddr[0] = (unsigned long) (g0+241);
//  pthaddr[1] = ((0x40000000 >> 4) | SRMMU_ET_PTE | SRMMU_PRIV);
//  pthaddr[2] = 0xf1000000;
//  /* repair info for write protection fault (0xf0041000) */
//  pthaddr[3] = (unsigned long) (p0+1);
//  pthaddr[4] = ((((unsigned long)&page0) >> 4) | SRMMU_ET_PTE | SRMMU_PRIV);
//  pthaddr[5] = 0xf0041000;
//  /* repair info for instruction page fault (0xf0042000) */
//  pthaddr[6] = (unsigned long) (p0+2);
//  pthaddr[7] = ((((unsigned long)func) >> 4) | SRMMU_ET_PTE | SRMMU_PRIV);
//  pthaddr[8] = 0xf0042000;
//  /* repair info for priviledge protection fault (0xf0041000) */
//  pthaddr[9] = (unsigned long) (p0+1);
//  pthaddr[10] = ((((unsigned long)&page0) >> 4) | SRMMU_ET_PTE | SRMMU_EXEC | SRMMU_WRITE);
//  pthaddr[11] = 0xf0041000;



	/* close your eyes and pray ... */
	mmu_probe_start();

	/* do tests*/
//page translation tast page0 in 0xf0041000 addr 0x40000000 0xf0080000
	if ( (*((unsigned long *)0xf0041000)) != 0 ||
		(*((unsigned long *)0xf0041004)) != 0x12345678 ) { MMU_RETURN(1); }

	if ( (*((unsigned long *)0xf0080000)) != (*((unsigned long *)0x40000000))) { MMU_RETURN(2); }

	/* page faults tests*/
//	pthaddr[0] = (unsigned long) (g0+241);
//	pthaddr[1] = ((0x40000000 >> 4) | SRMMU_ET_PTE | SRMMU_PRIV);
//	pthaddr[2] = 0xf1000000;
val = * ((volatile unsigned long *)0xf1000000);
/* write protection fault */
//	/* repair info for write protection fault (0xf0041000) */
//	pthaddr[3] = (unsigned long) (p0+1);
//	pthaddr[4] = ((((unsigned long)&page0) >> 4) | SRMMU_ET_PTE | SRMMU_PRIV);
//	pthaddr[5] = 0xf0041000;
* ((volatile unsigned long *)0xf0041004) = 0x87654321;
	if ( (*((volatile unsigned long *)0xf0041004)) != 0x87654321 ) { MMU_RETURN(3); }

//test several page for modify flags
	for (j = 0xf0043000, i = 3; i < TLBNUM+3; i++, j += 0x1000) {
		*((unsigned long *) j) = j;
		if (*((unsigned long*) (((unsigned long) &page2) + (((i - 3) % 3)
				* PAGE_SIZE))) != j) {
			MMU_RETURN (false);
		}
	}
	flush_data_cache();

//	for (j = 0, i = 3; i < TLBNUM+3; i++) {
//		pteval = (((((unsigned long) &page2) + (((i - 3) % 3) * PAGE_SIZE))
//		>> 4) | SRMMU_ET_PTE | SRMMU_PRIV);
//		if ((*(p0 + i)) & (SRMMU_DIRTY| SRMMU_REF))
//			j++;
//
//		if (((*(p0 + i)) & ~(SRMMU_DIRTY| SRMMU_REF)) != (pteval
//			& ~(SRMMU_DIRTY| SRMMU_REF))) {
//			MMU_RETURN (false);
//		}
//	}
	for (j = 0, i = 3; i < TLBNUM+3; i++) {
		unsigned int page_addr = (((unsigned long) &page2) + (((i - 3) % 3) * PAGE_SIZE));
		unsigned int page_desc = mmu_get_page_desc(page_addr);
		pteval = ((page_addr >> 4) | SRMMU_ET_PTE | SRMMU_PRIV);
		if (mmu_get_page_desc(page_addr) & (SRMMU_DIRTY | SRMMU_REF))
			j++;

		if ((page_desc & ~(SRMMU_DIRTY| SRMMU_REF)) != (pteval
				& ~(SRMMU_DIRTY| SRMMU_REF))) {
			MMU_RETURN (false);
		}
	}


	//at least one entry has to have been flushed
	if (j == 0) {
		MMU_RETURN (false);
	}


	/* instruction page fault */
	func = (functype) 0xf0042000;
	func();

//	/* flush */
//	srmmu_flush_whole_tlb();
//	for (j = 0, i = 3; i < TLBNUM+3; i++) {
//		if ((*(p0 + i)) & (SRMMU_DIRTY| SRMMU_REF))
//		j++;
//	}
//	if (j != TLBNUM) {
//		MMU_RETURN (false);
//	}
//
//	/* check modified & ref bit */
//	if (!srmmu_pte_dirty(p0[1]) || !srmmu_pte_young(p0[1])) {
//		MMU_RETURN (false);
//	}
//
//	if (!srmmu_pte_young(m0[2])) {
//		MMU_RETURN (false);
//	}
//	if (!srmmu_pte_young(p0[2])) {
//	MMU_RETURN (false);
//	}

	printf ("ending mmu testing");
	MMU_RETURN (true);
}

/**
 * handler of command "mmu_probe"
 * It starts tests of mmu mode
 * return 0 if successed
 * return -1 another way
 */
static int exec(int argsc, char **argsv) {
	int nextOption;
	getopt_init();
	do {
		nextOption = getopt(argsc, argsv, "ivh");
		switch(nextOption) {
		case 'h':
			show_help();
			return 0;
		case 'i':
			mmu_show_reg();
			return 0;
		case 'v':
			mmu_show_version();
			return 0;
		case -1:
			break;
		default:
			return 0;
		}
	} while(-1 != nextOption);

	return mmu_probe();
}
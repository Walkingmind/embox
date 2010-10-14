/**
 * @file
 * @brief test page allocator 
 * @details Some random tests for page allocator
 *
 * @date 17.04.10
 * @author Fedor Burdun
 */

#include <embox/test.h>
#include <stdio.h>

#include <lib/page_alloc.h>

#define TEST_COUNT 10
#define TEST_STACK_SIZE	(2*TEST_COUNT+2)

#if 0
//#define DONOTUSE_PAGE_ALLOC           /* for testing test of page alloc =) */
//#define INTERACTIVE_TEST                      /* */
//#define VERBOSE_DEBUG_OUT                     /* Some advanced output (list of page marks) */
//#define VERBOSE_DEBUG_OUT_MALLOC
//#define STACK_POP_FROM_HEAD           /* or tail */ 
#define TEST_COUNT 10
#define MAX_PAGE_FOR_ALLOC 0x10



/**
 * count the number of free pages
 */
size_t free_page_count() {                     
	#ifdef DONOTUSE_PAGE_ALLOC
	return 0;
	#endif
	/* go from prev to next */
	if (get_cmark_p()==NULL) {
		return 0;
	}
	size_t fr = get_cmark_p()->psize;
	pmark_t* cur = get_cmark_p()->pnext;
	while (cur != get_cmark_p()) {
		fr = fr + cur->psize;
		cur = cur->pnext;
	}
	return fr;
}

/**							
 * count the number of allowed pages
 */
size_t allow_page_count() {                    
	#ifdef DONOTUSE_PAGE_ALLOC
	return 0;
	#endif
	/* go from next to prev */
	if (get_cmark_p()==NULL) {
		return PAGE_QUANTITY;
	}
	size_t fr = get_cmark_p()->psize;
	pmark_t* cur = get_cmark_p()->pprev;
	while (cur != get_cmark_p()) {
		fr = fr + cur->psize;
		cur = cur->pprev;
	}
	return PAGE_QUANTITY-fr;
}

/**
 * Debug output memory (print list of markers)
 */
void do_allpage() {
	pmark_t* pcur = get_cmark_p();
	printf("Print map of memory: \n");
	if (pcur == NULL) { /* don't exist list of empty page */
		printf("\tList of free page is empty\n");
		return;
	}

	do {
		printf("\tStruct: %08x\n\t\tsize: %d\n\t\tnext: %08x\n\t\tprev: %08x\n\n", 
			pcur, pcur->psize, pcur->pnext, pcur->pprev);
		pcur = pcur->pnext;
	} while (pcur != get_cmark_p());
}

/**
 * memory error counter
 */
int count_of_error = 0;

/**
 * simply memory checker (sum free and alocated memory must be equal size of pool)
 */
void memory_check() {
	size_t allocp = allow_page_count();
	size_t freep  = free_page_count();
	printf("Allocated: %d ; Free %d \n", allocp , freep );
	if (allocp+freep != PAGE_QUANTITY) {
		printf("WARNING: Sum of allocated and free page don't equal page quality!!! \n");
		++count_of_error;
	}
}

#endif

EMBOX_TEST(run);

static int run(void) {
	void * pointers[TEST_STACK_SIZE];
	void **first,**last;
	int test_id=0;
	int callowed=0,cfree=0;
	first = pointers; last = pointers;

	/* push 2 pop 1 - while it is best idea */

	do {
		if (++test_id<TEST_COUNT) {
			if (NULL == (*last = page_alloc())) {
				printf("No memory! ");
				break;
			}
			last = ++last < pointers+TEST_STACK_SIZE ? last : pointers;

			if (NULL == (*last = page_alloc())) {
				printf("No memory! ");
				break;
			}
			last = ++last < pointers+TEST_STACK_SIZE ? last : pointers;

			callowed += 2;
		}
		page_free(*first);
		first = ++first < pointers+TEST_STACK_SIZE ? first : pointers;
		cfree += 1;

	} while (first!=last); /* queue is not empty */

	printf("Allowed %d free %d: ",callowed,cfree);

	return callowed == cfree ? 0 : 1;
}


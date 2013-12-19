/**
 * @file
 * @brief page allocator 
 * @details Use `page allocator' when we need allocate or free only one page, 
 * else see `multipage allocator' or `malloc'.
 *
 * @date 04.04.10
 * @author Fedor Burdun
 */

#include <errno.h>
#include <lib/page_alloc.h>

#ifndef PAGE_QUANTITY
# define PAGE_QUANTITY 0x100
#endif
#ifndef PAGE_SIZE
# define PAGE_SIZE 0x100
#endif

int page_alloc_hasinit = 0;

#ifdef EXTENDED_TEST

static uint8_t page_pool[PAGE_QUANTITY][PAGE_SIZE];
static pmark_t *cmark_p = (pmark_t *) page_pool;
#else
#define START_MEMORY_ADDR 0x40000000
static pmark_t *cmark_p = (pmark_t *)START_MEMORY_ADDR;
#endif

#ifdef EXTENDED_TEST
pmark_t* get_cmark_p() {
	return cmark_p;
}
#endif

#if 0
/* defragmentation pages */
static void page_defrag(void ) {
}
#endif

/* copy mark structure */
static pmark_t *copy_mark( pmark_t *from , pmark_t *to ) {
	to->psize = from->psize;
	to->pnext = from->pnext;
	to->pprev = from->pprev;
	return to;
}

/* Initialize page allocator */
int page_alloc_init(void) {
	cmark_p->psize = PAGE_QUANTITY;
	cmark_p->pnext	= cmark_p;
	cmark_p->pprev	= cmark_p;

	return 0;
}

/* allocate page */
pmark_t *page_alloc(void) {
	size_t psize = 1;
	pmark_t *pcur,*tmp,*tt;

	if (!page_alloc_hasinit) {
		page_alloc_init();
		page_alloc_hasinit = 1;
	}
	
	if (cmark_p == NULL) { /* don't exist memory enough */
		/* generate error */
		#if 0
		errno = ENOMEM;
		#endif
		return NULL; 
	}
	/* find first proper block */
	pcur = cmark_p;

	/* check finded block */

	/* change list and return value */
	if (pcur->psize > psize ) {
		tt = (unsigned long) pcur + (unsigned long) PAGE_SIZE * 
			(unsigned long) psize; 
		pcur->psize -= psize;
		tmp = cmark_p->pnext;
		cmark_p->pprev->pnext = tt;
		tmp->pprev = tt;
		cmark_p = copy_mark( pcur , tt );
		return pcur;
	} else {
		if (pcur->pnext == pcur) {
			cmark_p = NULL;
			return NULL;
		} else { /* psize == pcur->psize */
			pcur->pprev->pnext = pcur->pnext;
			pcur->pnext->pprev = pcur->pprev;
			cmark_p = pcur->pnext;
			return pcur;
		}
	}
	return NULL;
}

/* free page that was allocated */
void page_free(pmark_t *paddr) { 
	paddr->psize = 1;

	if (cmark_p == NULL) { /* if don't exist any free page */
		paddr->pnext = paddr;
		paddr->pprev = paddr;
		cmark_p = paddr;
	}

	paddr->pnext = cmark_p->pnext;
	paddr->pprev = cmark_p;
	cmark_p->pnext->pprev = paddr;
	cmark_p->pnext = paddr;
}


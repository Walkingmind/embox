/**
 * @file
 * @brief page allocator header
 * @details 
 *
 * @date 04.04.10
 * @author Fedor Burdun
 */

#ifndef __PAGE_ALLOC_H_
#define __PAGE_ALLOC_H_

#include <types.h>

/** Structure of page marker. It occupies at the begin of each free memory
 * block
 */
typedef struct pmark {
	size_t	psize;
	struct pmark *pnext;
	struct pmark *pprev;
}pmark_t;

/**
 * Allocates one physical memory page from the pool. We return pointer to page
 * marker it is hold at the begin of each block therefore we have pointer to
 * physical page which we returned.
 *
 * @return Address of allocated page
 * @retval Address of allocated page on success
 * @retval NULL on fail
 */
pmark_t *page_alloc(void);

/**
 * Frees one page from the pool. This page must be allocated with
 * @link #page_alloc() @endlink function
 *
 * @param paddr pointer to physical page
 * @return Function doesn't return value
 *
 */
void page_free(pmark_t *paddr);

#endif /* __PAGE_ALLOC_H_ */


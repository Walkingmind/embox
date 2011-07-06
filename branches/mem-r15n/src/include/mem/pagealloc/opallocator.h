/**
 * @file
 * @brief page allocator header
 * @details
 *
 * @date 04.04.10
 * @author Fedor Burdun
 */

#ifndef INCLUDE_MEM_PAGEALLOC_OPALLOCATOR_H_
#define INCLUDE_MEM_PAGEALLOC_OPALLOCATOR_H_

#include <types.h>

/**
 * Allocates one physical memory page from the pool. We return pointer to page
 * marker it is hold at the begin of each block therefore we have pointer to
 * physical page which we returned.
 *
 * @return Address of allocated page
 * @retval Address of allocated page on success
 * @retval NULL on fail
 */
extern void *opalloc(void);

/**
 * Frees one page from the pool. This page must be allocated with
 * @link #page_alloc() @endlink function
 *
 * @param paddr pointer to physical page
 * @return Function doesn't return value
 *
 */
extern void opfree(void* paddr);

#endif /* INCLUDE_MEM_PAGELLOC_OPALLOCATOR_H_ */


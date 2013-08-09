/**
 * @file
 * @brief Dynamic memory allocator arbitrary size. Terehov style.
 * @details XXX kmalloc docs
 *
 * @date 02.05.10
 * @author Michail Skorginskii
 */

#ifndef MEM_KMALLOC_H_
#define MEM_KMALLOC_H_

#include <stddef.h>

/**
 * Dynamic memory allocator arbitrary size.
 *
 * @param size requested memory size
 *
 * @return pointer to the memory of the requested size.
 * @retval 0 if there are no memory
 */
extern void *kmalloc(size_t size, int priority);

/**
 * Free memory function.
 *
 * @param ptr pointer at the memory, that must be free
 */
extern void kfree(void *ptr);

#endif /* MEM_KMALLOC_H_ */

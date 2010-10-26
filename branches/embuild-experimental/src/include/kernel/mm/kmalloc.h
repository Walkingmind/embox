/**
 * @file
 * @brief Dynamic memory allocator arbitrary size. Terehov style.
 * @details TODO
 *
 * @date May 02, 2010
 * @author Michail Skorginskii
 *
 * TODO
 * 2) Calloc && realloc.
 */

#ifndef KMALLOC_H
#define KMALLOC_H

#include <sys/types.h>

/**
 * Dynamic memory allocator arbitrary size.
 * 
 * @param size is requested memory size.
 *
 * @return pointer to the memory of the requested size.
 * @retval 0 if there are no memory
 */
extern void* kmalloc(size_t size);

/**
 * Free memory function.
 *
 * @param pointer at the memory, that must be free
 */
extern void kfree(void *ptr);

#endif /* KMALLOC_H_ */


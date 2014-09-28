/**
 * @file
 * @brief Memory allocation API.
 *
 * @details TODO
 * allocator - pool or cache in this context.
 *
 * A fixed-sized memory allocator is an object for dynamically managing fixed-sized memory
 * blocks.
 *
 * The fixed-sized memory allocator functions include the ability to create and delete
 * fixed-sized memory allocator and create and delete objects from allocator
 *
 * When using fixed-sized memory pool functions for memory blocks of different sizes, a
 * fixed-sized memory pool should be created for each size.
 *
 * @date 03.07.2011
 * @author Alexandr Kalmuk
 */

#ifndef MEM_OBJ_ALLOC_H_
#define MEM_OBJ_ALLOC_H_

#include <stddef.h>
#include <util/macro.h>

#include <module/embox/mem/objalloc.h>

/**
 *  Creates and initializes allocator.
 *  @param allocator_nm - name of allocator
 *  @param object_t     - type of objects in allocator
 *  @param objects_nr   - initial count of objects in allocator
 */
#define OBJALLOC_DEF(allocator_nm, object_t, objects_nr) \
	  __OBJALLOC_DEF(allocator_nm, object_t, objects_nr)

/**
 * Structure represents storage for object you save.
 * It may include pool or cache as field according to realization.
 */
typedef __objalloc_t objalloc_t;

/**
 * @param allocator you want to be created
 * @param object_sz bytes per object
 * @param objects_nr is number of object reserved
 *        (for cache it means reserved at first)
 * @return 0 - if allocator was init
 *         ERROR_CODE - if allocator was not destroyed
 */
extern int objalloc_init(objalloc_t *allocator, size_t object_sz,
		size_t objects_nr);

/**
 *
 * @param allocator that must be destroyed
 * @return 0 - if allocator was destroyed
 *         ERROR_CODE - if allocator was not destroyed
 */
extern int objalloc_destroy(objalloc_t *allocator);

/**
 * Allocate single object from the allocator and return it to the caller
 * @param allocator corresponding to allocating object
 * @return the address of allocated object or NULL if allocator is full
 */
extern void *objalloc(objalloc_t *allocator);

/**
 * ree memory function.
 * @param allocator corresponding to freeing object
 * @param object pointer at start address of the memory, that must be free
 */
extern void objfree(objalloc_t *allocator, void* object);

#endif /*MEM_OBJ_ALLOC_H_ */

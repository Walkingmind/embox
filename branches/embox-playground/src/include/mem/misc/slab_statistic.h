/**
 * @file
 * @brief Define functions for statistic for slab allocator
 *
 * @date 14.12.10
 * @author Alexandr Kalmuk
 */

#ifndef MEM_MISC_SLAB_STATISTIC_H_
#define MEM_MISC_SLAB_STATISTIC_H_

/**
 * Return list of free and busy blocks per current slab
 * @param list of free and busy blocks(for objects)
 * @param slabp is pointer to slab, in witch blocks are
 */
extern void sget_blocks_info(struct list_head* list, struct list_head *slabp);

/**
 *
 * @param list is list_head struct:
 * it is'nt a doubly linked list
 * _____________
 *|pseudo_list  |
 *|_____________|____________prev_____________
 *     |next                                 |
 * ____|________       ______               _|____
 *|kmalloc_cache|<--->|cache1|<--->...<--->|cacheN|
 *|_____________|     |______|             |______|
 */
extern void make_caches_list(struct list_head* list);

#endif /* MEM_MISC_SLAB_STATISTIC_H_ */

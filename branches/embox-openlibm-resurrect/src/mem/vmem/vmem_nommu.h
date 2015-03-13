/**
 * @file
 *
 * @date Aug 6, 2014
 * @author: Anton Bondarev
 */

#ifndef VMEM_NOMMU_H_
#define VMEM_NOMMU_H_

static inline void *mmap_device_memory(void *addr,
                           size_t len,
                           int prot,
                           int flags,
                           uint64_t physical){

	return addr;
}

#endif /* VMEM_NOMMU_H_ */

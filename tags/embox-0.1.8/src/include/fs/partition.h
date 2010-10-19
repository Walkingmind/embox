/**
 * @file
 * @brief
 *
 * @date 13.09.10
 * @author Alexander Batyukov
 */

#ifndef PARTITION_H_
#define PARTITION_H_

#include <types.h>

typedef struct _PARTITION_DESCRIPTOR {
	const char *name;
	uint32_t flags;	      /** read-write-execute */
	uint32_t start_addr;  /** start address */
	uint32_t size;        /** size */
	uint32_t type;        /** info about type of content */
	/* operations */
} PARTITION_DESCRIPTOR;

#define __DECLARE_PARTITION(idx, name, flags, start_addr, size, type) \
    static const PARTITION_DESCRIPTOR _descriptor##idx \
		__attribute__ ((used, section(".romfs"))) \
		= { name, flags, start_addr, size, type }

#define DECLARE_PARTITION(idx, name, flags, start_addr, size) \
    __DECLARE_PARTITION(idx, name, flags, start_addr, size, PARTITION_SIMPLE_TYPE)

#define DECLARE_END_PARTITION(name, flags) \
    __DECLARE_PARTITION(100, name, flags, 0, 0, PARTITION_END_TYPE)

#define DECLARE_LINK_PARTITION(idx, name, flags, link_addr) \
	__DECLARE_PARTITION(idx, name, flags, link_addr, 0, PARTITION_LINK_TYPE)

int fs_init_second_level_table(uint32_t addr);

PARTITION_DESCRIPTOR *fs_add_new_partition(char *name, /* temp */ uint32_t addr,
		uint32_t size, uint32_t type);

int fs_delete_partition(PARTITION_DESCRIPTOR *desc);

/* for debug only */
int fs_print_all_partitions(void);
#endif /* PARTITION_H_ */

/**
 * @file
 * @brief
 *
 * @date 14.09.2011
 * @author Anton Bondarev
 */

#ifndef FS_FILE_DESC_H_
#define FS_FILE_DESC_H_

#include <fs/node.h>
#include <fs/file_operation.h>
#include <stddef.h>
#include <fs/flags.h>

struct node;
struct kfile_operations;

struct file_desc {
	struct node *node;
	int flags;
	const struct kfile_operations *ops;
	size_t cursor;
	void *file_info; /* customize in each file system */
};

extern struct file_desc * file_desc_alloc(void);

extern void file_desc_free(struct file_desc *desc);

#endif /* FS_FILE_DESC_H_ */
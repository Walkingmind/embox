/**
 * @file
 *
 * @date 05.10.10
 * @author Nikolay Korotky
 */

#ifndef FS_DRV_H_
#define FS_DRV_H_

#include <fs/file_operation.h>
#include <util/array.h>

struct fsop_desc {
	int (*init)(void *par);
	int (*format)(void *par);
	int (*mount)(void *dev_node, void *dir_node);
	int (*create_node)(struct node *parent_node, struct node *new_node);
	int (*delete_node)(struct node *node);

	/* TODO: consider following to accept nas * as first arg (Anton Kozlov) */
	int (*getxattr)(struct node *node, const char *name,
			char *value, size_t len);
	int (*setxattr)(struct node *node, const char *name,
			const char *value, size_t len, int flags);
	int (*listxattr)(struct node *node, char *list, size_t len);

	int (*truncate)(struct node *node, off_t length);
};

struct kfile_operations;

/**
 * Structure of file system driver.
 * We can mount some file system with name of FS which has been registered in
 * our system.
 */
typedef struct fs_drv {
	const char                    *name;
	const struct kfile_operations *file_op;
	const struct fsop_desc        *fsop;
} fs_drv_t;

extern const fs_drv_t * __fs_drivers_registry[];

#define DECLARE_FILE_SYSTEM_DRIVER(fs_driver) \
		ARRAY_SPREAD_ADD(__fs_drivers_registry, &fs_driver)

/**
 * allocate structure for fs_driver structure
 * @return pointer to allocated memory
 */
extern fs_drv_t *alloc_fs_drivers(void);

/**
 * free early allocated driver with function alloc_fs_drivers
 */
extern void free_fs_drivers(fs_drv_t *);

extern fs_drv_t *fs_driver_find_drv(const char *name);

/**
 * register a new filesystem driver
 * @param fs the file system structure
 */
extern int fs_driver_register_drv(fs_drv_t *);

/**
 * unregister a file system driver
 * @param fs filesystem to unregister
 */
extern int fs_driver_unregister_drv(fs_drv_t *);

#endif /* FS_DRV_H_ */

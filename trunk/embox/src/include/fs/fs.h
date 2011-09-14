/**
 * @file
 *
 * @date 05.10.10
 * @author Nikolay Korotky
 */

#ifndef FS_H_
#define FS_H_

#include <lib/list.h>
#include <fs/file.h>
#include <unistd.h>

typedef int (*FS_CREATE_FUNC)(void *params);
typedef int (*FS_DELETE_FUNC)(const char *file_name);
typedef int (*FS_INIT_FUNC)(void *par);
typedef int (*FS_MOUNT_FUNC)(void *par);

typedef struct fsop_desc {
        FS_INIT_FUNC init;
        FS_CREATE_FUNC create_file;
        FS_DELETE_FUNC delete_file;
        FS_MOUNT_FUNC mount;
} fsop_desc_t;

/**
 * Structure of file system driver.
 * We can mount some file system with name of FS which has been registered in
 * our system.
 */
typedef struct file_system_driver {
	const char          *name;
	const file_operations_t   *file_op;
	const fsop_desc_t         *fsop;
} file_system_driver_t;


extern const file_system_driver_t * __fs_drivers_registry[];

#define DECLARE_FILE_SYSTEM_DRIVER(fs_driver) \
		ARRAY_SPREAD_ADD(__fs_drivers_registry, &fs_driver)

/**
 * allocate structure for fs_driver structure
 * @return pointer to allocated memory
 */
extern file_system_driver_t *alloc_fs_drivers(void);

/**
 * free early allocated driver with function alloc_fs_drivers
 */
extern void free_fs_drivers(file_system_driver_t *);

extern file_system_driver_t *filesystem_find_drv(const char *name);

/**
 * register a new filesystem
 * @param fs the file system structure
 */
extern int filesystem_register_drv(file_system_driver_t *);

/**
 * unregister a file system
 * @param fs filesystem to unregister
 */
extern int filesystem_unregister_drv(file_system_driver_t *);

#endif /* FS_H_ */

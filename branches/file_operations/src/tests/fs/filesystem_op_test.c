/**
 * @file
 * @brief
 *
 * @date 05.07.2012
 * @author Andrey Gazukin
 */

#include <fcntl.h>
#include <stdio.h>

#include <cmd/mkfs.h>
#include <fs/mount.h>
#include <fs/vfs.h>
#include <fs/fs_drv.h>

#include <drivers/ramdisk.h>
#include <embox/block_dev.h>
#include <embox/test.h>

#include <mem/page.h>

EMBOX_TEST_SUITE("fs/filesystem test");

static mount_params_t mount_param;
static fs_drv_t *fs_drv;

TEST_SETUP_SUITE(setup_suite);

TEST_TEARDOWN_SUITE(teardown_suite);

#define FS_NAME  "vfat"
#define FS_DEV  "/dev/ramdisk"
#define FS_TYPE  12
#define FS_BLOCKS  124

TEST_CASE("Create fat filesystem") {
	test_assert_zero(fs_drv->fsop->format((void *)FS_DEV));
}

#define FS_DIR  "/test_fsop"
TEST_CASE("Mount fat filesystem") {
	test_assert_zero(fs_drv->fsop->mount((void *) &mount_param));
}

#define FS_FILE1  "/test_fsop/1/2/3/1.txt"
TEST_CASE("Create file 1") {
	test_assert_zero(create(FS_FILE1, 0));
}

#define FS_FILE2  "/test_fsop/1/2/2.txt"
TEST_CASE("Create file 2") {
	test_assert_zero(create(FS_FILE2, 0));
}

#define FS_DIR3  "/test_fsop/1/2/3"
#define FS_DIR2  "/test_fsop/1/2"
#define FS_DIR1  "/test_fsop/1"
TEST_CASE("Delete file") {
	test_assert_zero(remove(FS_FILE1));
	test_assert_zero(remove(FS_FILE2));
	test_assert(0 > open(FS_FILE1, O_RDONLY));
	test_assert(0 > open(FS_FILE2, O_RDONLY));
	test_assert_zero(remove(FS_DIR3));
	test_assert_zero(remove(FS_DIR2));
	test_assert_zero(remove(FS_DIR1));
	test_assert_zero(remove(FS_DIR));
}

static int setup_suite(void) {
	static ramdisk_create_params_t new_ramdisk;


	new_ramdisk.size = FS_BLOCKS * PAGE_SIZE();
	new_ramdisk.fs_type = FS_TYPE;

	new_ramdisk.fs_name = FS_NAME;
	new_ramdisk.path = FS_DEV;

	ramdisk_create((void *)&new_ramdisk);

	fs_drv = fs_driver_find_drv((const char *) new_ramdisk.fs_name);
	test_assert_not_null(fs_drv);

	mount_param.dev = FS_DEV;
	mount_param.dir = FS_DIR;
	mount_param.dev_node = vfs_find_node(mount_param.dev, NULL);

	return 0;
}

static int teardown_suite(void) {
	test_assert_zero(ramdisk_delete(FS_DEV));

	return 0;
}

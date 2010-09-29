
$_PACKAGE := embox.fs

$_MODS += ramfs romfs rootfs file

$_SRCS-ramfs += ramfs.c
$_SRCS-ramfs += ramfs_cpio.S
$_SRCS-romfs += romfs.c
$_SRCS-rootfs += rootfs.c
$_SRCS-file += file.c

$_CPPFLAGS += -I$(SRC_DIR)/linux-compat/include

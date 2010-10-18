/**
 * @file
 * @brief parse cpio initramfs
 *
 * @date 29.09.10
 * @author Nikolay Korotky
 */
#include <fs/rootfs.h>
#include <fs/vfs.h>
#include <lib/list.h>
#include <lib/cpio.h>
#include <stdlib.h>
#include <string.h>

/**
 * The pathname is followed by NUL bytes so that the total size of the fixed
 * header plus pathname is a multiple of four. Likewise, the file data is
 * padded to a multiple of four bytes.
 */
#define N_ALIGN(len) ((((len) + 1) & ~3) + 2)
#define F_ALIGN(len) (((len) + 3) & ~3)

static cpio_newc_header *parse_item(cpio_newc_header *cpio_h, char *name) {
	char *s;
	size_t i;
	unsigned long parsed[12], file_size, start_addr, mode;
	char buf[9];
	buf[8] = '\0';
	if (memcmp(cpio_h->c_magic, MAGIC_OLD_BINARY, 6)==0) {
		TRACE("Use -H newc option for create cpio arch\n");
		return NULL;
	}
	if (memcmp(cpio_h->c_magic, MAGIC_NEWC, 6)) {
		TRACE("Newc ASCII CPIO format not recognized.\n");
		return NULL;
	}
	s = (char*)cpio_h;
	for (i = 0, s += 6; i < 12; i++, s += 8) {
		memcpy(buf, s, 8);
		parsed[i] = strtol(buf, NULL, 16);
	}

	strncpy(name, (char*)cpio_h + sizeof(cpio_newc_header), parsed[11]);
	name[parsed[11]] = '\0';
	file_size  = parsed[6];
	start_addr = (unsigned long)cpio_h + sizeof(cpio_newc_header) + N_ALIGN(parsed[11]);
	mode       = parsed[1];

	if(0 == strcmp(name, "TRAILER!!!")) {
		return NULL;
	} else {
		//TODO: set start_addr, file_size, mode.
		vfs_add_path(name, NULL);
	}
	return (cpio_newc_header*)F_ALIGN(start_addr + file_size);
}

int unpack_to_rootfs(void) {
	extern char _ramfs_start, _ramfs_end;
	cpio_newc_header *cpio_h, *cpio_next;
	unsigned char buff_name[CONFIG_MAX_LENGTH_FILE_NAME];

	if(&_ramfs_end == &_ramfs_start) {
		TRACE("No availible initramfs\n");
		return -1;
	}
	TRACE("cpio initramfs at 0x%08x\n", &_ramfs_start);
	
	cpio_h = (cpio_newc_header *)&_ramfs_start;
	while(NULL != (cpio_next = parse_item(cpio_h, buff_name))) {
		cpio_h = cpio_next;
		TRACE("%s\n", buff_name);
	}

	return 0;
}

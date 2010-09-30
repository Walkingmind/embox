/**
 * @file
 * @brief mount a filesystem
 *
 * @date 29.09.10
 * @author Nikolay Korotky
 */
#include <shell_command.h>
#include <fs/rootfs.h>
#include <fs/ramfs.h>
#include <lib/list.h>
#include <lib/cpio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_NAME     "mount"
#define COMMAND_DESC_MSG "mount a filesystem"
#define HELP_MSG         "Usage: mount [-h] src dir"

static const char *man_page =
	#include "mount_help.inc"
;

DECLARE_SHELL_COMMAND(COMMAND_NAME, exec, COMMAND_DESC_MSG, HELP_MSG, man_page);

//TODO: workaround.
static int mount_cpio_ramfs(const char *dir) {
	extern char _ramfs_start, _ramfs_end;
	cpio_newc_header *cpio_h;
	unsigned long parsed[12];
	char buf[9];
	char *s;
	int i;
	FSOP_DESCRIPTION *fsop;
	RAMFS_CREATE_PARAM param;
	buf[8] = '\0';
	if(&_ramfs_end == &_ramfs_start) {
		TRACE("No availible ramfs\n");
		return -1;
	}
	cpio_h = (cpio_newc_header *)&_ramfs_start;
	if (!strcmp(cpio_h->c_magic, "070701")) {
		TRACE("Newc ASCII CPIO format not recognized!\n");
		return -1;
	}
	s = (char*)cpio_h;
	for (i = 0, s += 6; i < 12; i++, s += 8) {
		memcpy(buf, s, 8);
		parsed[i] = strtol(buf, NULL, 16);
	}

	strncpy(param.name, (char*)cpio_h + sizeof(cpio_newc_header), parsed[11]);
	param.size = parsed[6];
	param.start_addr = (unsigned int)(cpio_h + sizeof(cpio_newc_header) + parsed[11]);
	param.mode = parsed[1];
	if (NULL == (fsop = rootfs_get_fsopdesc(dir))) {
		LOG_ERROR("Can't find %s\n", dir);
		return -1;
	}
	return fsop->create_file(&param);
}

static int exec(int argsc, char **argsv) {
	int nextOption;
	char *src, *dir;
	getopt_init();
	do {
		nextOption = getopt(argsc, argsv, "h");
		switch (nextOption) {
		case 'h':
			show_help();
			return 0;
		case -1:
			break;
		default:
			return 0;
		}
	} while (-1 != nextOption);
	
	if(argsc > 2) {
		src = argsv[argsc - 2];
		dir = argsv[argsc - 1];
	}
	if(!strcmp(src, "cpio")) {
		TRACE("mount %s...\n", src);
		mount_cpio_ramfs(dir);
	}

	return 0;
}

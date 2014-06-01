/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    29.03.2013
 */

#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <embox/cmd.h>

EMBOX_CMD(crash_test_exec);

#define CORE_DUMP "/mnt/hda/core.dump"

static int crash_test_exec(int argc, char *argv[]) {

	int fd = creat(CORE_DUMP, 0755);

	if (0 > fd) {
		return -errno;
	}

	close(fd);

	assert(1 == 0);

	return 0;
}

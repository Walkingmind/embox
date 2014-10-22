/**
 * @file
 *
 * @date 15.11.13
 * @author Anton Bondarev
 */

#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <fs/kfile.h>
#include <fs/index_descriptor.h>
#include <fs/idesc.h>
#include <kernel/task.h>

extern const struct idesc_ops idesc_file_ops;

off_t lseek(int fd, off_t offset, int origin) {
	struct idesc *idesc;
	off_t ret;

	if (!idesc_index_valid(fd)
			|| (NULL == (idesc = index_descriptor_get(fd))) 
			|| (idesc->idesc_ops != &idesc_file_ops)) {
		return SET_ERRNO(EBADF);
	}

	ret = kseek(member_cast_out(idesc, struct file_desc, idesc),
			offset, origin);
	if (ret < 0) {
		return SET_ERRNO(-ret);
	}

	return ret;
}

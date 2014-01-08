/**
 * @file
 * @brief
 *
 * @author  Anton Kozlov
 * @date    31.05.12
 */

#include <unistd.h>
#include <errno.h>
#include <kernel/task.h>
#include <kernel/task/idx.h>

int isatty(int fd) {
	struct idx_desc *desc = task_self_idx_get(fd);

	SET_ERRNO(ENOERR);

	if (!desc) {

		SET_ERRNO(EBADF);

		return 0;
	}

	return task_idx_desc_ops(desc)->type == TASK_RES_OPS_TTY;
}
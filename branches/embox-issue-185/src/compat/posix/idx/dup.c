/**
 * @file
 *
 * @brief
 *
 * @date 05.06.2012
 * @author Anton Bondarev
 * @author Anton Kozlov
 */

#include <unistd.h>
#include <kernel/task.h>
#include <kernel/task/idx.h>
#include <errno.h>

//TODO set errno on every return -1

int dup(int flides) {
	int new_fd;

	if (!task_valid_binded_fd(flides)) {
		SET_ERRNO(EBADF);
		return -1;
	}

	if ((new_fd = task_self_idx_first_unbinded()) < 0) {
		SET_ERRNO(EMFILE);
		return -1;
	}

	return dup2(flides, new_fd);
}

int dup2(int flides, int flides2) {
	int res;
	struct idx_desc *old_idx;

	if (! task_valid_binded_fd(flides)) {
	       return -1;
	}

	if (! task_valid_fd(flides2)) {
		return -1;
	}

	if (flides == flides2) {
		return flides2;
	}

	old_idx = task_self_idx_get(flides);

	if (0 != (res = task_self_idx_set(flides2, task_idx_desc_alloc(old_idx->data)))) {
		return res;
	}

	return flides2;
}

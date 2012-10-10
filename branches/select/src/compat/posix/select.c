/**
 * @file
 *
 * @brief
 *
 * @date 13.09.2011
 * @author Anton Bondarev
 */

#include <sys/time.h>
#include <sys/select.h>
#include <errno.h>
#include <kernel/thread/event.h>
#include <kernel/thread/sched_lock.h>
#include <kernel/task.h>
#include <kernel/task/idx.h>

static void fd_set_copy(fd_set *dst, fd_set *src);

/*
 * @brief Save only descriptors with active op.
 * */
static int find_active(fd_set *set, char op);

/* @brief Update sets with find_active() IF these sets contain at least one
 * active descriptor
 * @return count of active descriptors
 * @retval -EBAFD if some descriptor is invalid */
static int update_sets(fd_set *readfds, fd_set *writefds, fd_set *exceptfd);

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, int t
		/*struct timeval *timeout*/) {
	int res, fd_cnt = 0;
	struct idx_desc *desc;
	struct event_set e_set;
	fd_set tmp_r, tmp_w;

	/* Lock scheduler until we search active descriptor and build event set.*/
	/* First try to find some active descriptor */
	sched_lock();
	{
		fd_set_copy(&tmp_r, readfds);
		fd_set_copy(&tmp_w, writefds);

		fd_cnt = update_sets(&tmp_r, &tmp_w, exceptfds);

		if (fd_cnt < 0) {
			res = fd_cnt;
			goto error_locked;
		} else if (fd_cnt > 0) {
			fd_set_copy(readfds, &tmp_r);
			fd_set_copy(writefds, &tmp_w);
			goto out_locked;
		}

		/* If no active descriptors now, than build set of events corresponding
		 * to each descriptor in fd_set. */
		event_set_init(&e_set);

		for (int fd = 0; fd < MAX_FD_CNT; fd++) {
			if (FD_ISSET(fd, readfds)) {
				desc = task_self_idx_get(fd);
				event_set_add(&e_set, &desc->data->read_state.activate);
			}

			if (FD_ISSET(fd, writefds)) {
				desc = task_self_idx_get(fd);
				event_set_add(&e_set, &desc->data->write_state.activate);
			}
		}
	}
	sched_unlock();

	/* XXX */
	event_wait(&e_set, t);

	event_set_clear(&e_set);

	sched_lock();
	{
		fd_cnt = update_sets(readfds, writefds, exceptfds);
	}
out_locked:
	sched_unlock();
	return fd_cnt;

error_locked:
	sched_unlock();
	SET_ERRNO(-res);
	return -1;
}

static void fd_set_copy(fd_set *dst, fd_set *src) {
	int i;
	for (i = 0; i < _FDSETWORDS; i++) {
		dst->fds_bits[i] = src->fds_bits[i];
	}
}

static int find_active(fd_set *set, char op) {
	int fd, fd_cnt = 0;
	struct idx_desc *desc;
	struct idx_io_op_state *state;

	for (fd = 0; fd < MAX_FD_CNT; fd++) {
		if (FD_ISSET(fd, set)) {
			if (!(desc = task_self_idx_get(fd))) {
				return -EBADF;
			} else {
				switch (op) {
				case 'r':
					state = &desc->data->read_state;
					break;
				case 'w':
					state = &desc->data->write_state;
					break;
				}
				if (state->active) {
					fd_cnt++;
				} else {
					FD_CLR(fd, set);
				}
			}
		}
	}

	return fd_cnt;
}

static int update_sets(fd_set *readfds, fd_set *writefds, fd_set *exceptfd) {
	int fd_cnt = 0, res;

	/* Try to find active fd in readfds*/
	if (readfds != NULL) {
		res = find_active(readfds, 'r');
		if (res < 0) {
			return -EBADF;
		} else {
			fd_cnt += res;
		}
	}

	/* Try to find active fd in writefds*/
	if (writefds != NULL) {
		res = find_active(writefds, 'w');
		if (res < 0) {
			return -EBADF;
		} else {
			fd_cnt += res;
		}
	}

	return fd_cnt;
}

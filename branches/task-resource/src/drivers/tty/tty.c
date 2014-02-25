/**
 * @file
 * @brief
 *
 * @date 05.03.13
 * @author Eldar Abusalimov
 */

#include <drivers/tty.h>
#include <drivers/termios_ops.h>

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>

#include <kernel/irq_lock.h>
#include <fs/idesc_event.h>

#include <util/math.h>
#include <util/member.h>

#define TC_I(t, flag) ((t)->termios.c_iflag & (flag))
#define TC_O(t, flag) ((t)->termios.c_oflag & (flag))
#define TC_C(t, flag) ((t)->termios.c_cflag & (flag))
#define TC_L(t, flag) ((t)->termios.c_lflag & (flag))

extern void tty_task_break_check(struct tty *t, char ch);

static inline void tty_notify(struct tty *t, int mask) {
	assert(t);
	if (t->idesc)
		idesc_notify(t->idesc, mask);
}

static inline void tty_out_wake(struct tty *t) {

	t->ops->out_wake(t);
}

static int tty_output(struct tty *t, char ch) {
	// TODO locks? context? -- Eldar
	return termios_putc(&t->termios, ch, &t->o_ring, t->o_buff, TTY_IO_BUFF_SZ);
	// t->ops->tx_char(t, ch);
}

static void tty_echo(struct tty *t, char ch) {
	termios_gotc(&t->termios, ch, &t->o_ring, t->o_buff, TTY_IO_BUFF_SZ);
	mutex_unlock(&t->lock);
	tty_out_wake(t);
	mutex_lock(&t->lock);
}

static void tty_echo_erase(struct tty *t) {
	cc_t *cc = t->termios.c_cc;

	if (!TC_L(t, ECHO))
		return;

	if (TC_L(t, ECHOE))
		tty_output(t, cc[VERASE]);

	else
		for (char *ch = "\b \b"; *ch; ++ch)
			tty_output(t, *ch);
}

/*
 * Input layout is the following:
 *
 *       i_buff  [     raw-raw-raw-raw-cooked|cooked|cooked|cooked|editing   ]
 *
 * TTY struct manages two internal rings:
 *       i_ring  [-----***************************************************---]
 * i_canon_ring  [---------------------***************************-----------]
 *
 * Two syntetic rings are also constructed from ends of the two rings above:
 *     raw_ring  [-----****************--------------------------------------]
 *    edit_ring  [------------------------------------------------********---]
 */

static struct ring *tty_raw_ring(struct tty *t, struct ring *r) {
	r->tail = t->i_ring.tail;
	r->head = t->i_canon_ring.tail;
	return r;
}

static struct ring *tty_edit_ring(struct tty *t, struct ring *r) {
	r->tail = t->i_canon_ring.head;
	r->head = t->i_ring.head;
	return r;
}

static int tty_input(struct tty *t, char ch, unsigned char flag) {
	cc_t *cc = t->termios.c_cc;
	int ignore_cr;
	int raw_mode;
	int is_eol;
	int got_data;

	raw_mode = !TC_L(t, ICANON);

	/* Newline control: IGNCR, ICRNL, INLCR */
	ignore_cr = TC_I(t, IGNCR) && ch == '\r';
	if (!ignore_cr) {
		if (TC_I(t, ICRNL) && ch == '\r') ch = '\n';
		if (TC_I(t, INLCR) && ch == '\n') ch = '\r';
	}
	is_eol = (ch == '\n' || ch == cc[VEOL]);

	if (ignore_cr)
		goto done;

	/* Handle erase/kill */
	if (!raw_mode) {
		int erase_all = (ch == cc[VKILL]);
		if (erase_all || ch == cc[VERASE] || ch == '\b') {

			struct ring edit_ring;
			size_t erase_len = ring_data_size(
						tty_edit_ring(t, &edit_ring), TTY_IO_BUFF_SZ);

			if (erase_len) {
				if (!erase_all)
					erase_len = 1;

				t->i_ring.head -= erase_len - TTY_IO_BUFF_SZ;
				ring_fixup_head(&t->i_ring, TTY_IO_BUFF_SZ);

				while (erase_len--)
					tty_echo_erase(t);
			}

			goto done;
		}
	}

	/* Finally, store and echo the char.
	 *
	 * When i_ring is near to become full, only raw or a line ending chars are
	 * handled. This lets canonical read to see the line with \n or EOL at the
	 * end, even when some chars are missing. */

	if (ring_room_size(&t->i_ring, TTY_IO_BUFF_SZ) > !(raw_mode || is_eol))
		if (ring_write_all_from(&t->i_ring, t->i_buff, TTY_IO_BUFF_SZ, &ch, 1))
			tty_echo(t, ch);

done:
	got_data = (raw_mode || is_eol || ch == cc[VEOF]);

	if (got_data) {
		t->i_canon_ring.head = t->i_ring.head;

		if (raw_mode)
			/* maintain it empty */
			t->i_canon_ring.tail = t->i_canon_ring.head;
	}

	return got_data;
}

static void tty_rx_do(struct tty *t) {
	int ich;

	while ((ich = tty_rx_dequeue(t)) != -1) {
		irq_unlock();
		tty_input(t, (char) ich, (unsigned char) (ich>>CHAR_BIT));
		irq_lock();
	}
}

static char *tty_read_raw(struct tty *t, char *buff, char *end) {
	struct ring raw_ring;
	size_t block_size;

	while ((block_size = ring_can_read(
				tty_raw_ring(t, &raw_ring), TTY_IO_BUFF_SZ, end - buff))) {

		/* No processing is required to read raw data. */
		memcpy(buff, t->i_buff + raw_ring.tail, block_size);
		buff += block_size;

		ring_just_read(&t->i_ring, TTY_IO_BUFF_SZ, block_size);
	}

	return buff;
}

static size_t find_line_len(cc_t eol, cc_t eof,
		const char *buff, ssize_t size, int *is_eof) {
	size_t offset;

	*is_eof = 0;
	for (offset = 0; offset < size; ++offset) {
		char ch = buff[offset];
		if (ch == '\n' || ch == eol || ch == eof) {
			*is_eof = (ch == eof);
			break;
		}
	}

	return offset;
}

static char *tty_read_cooked(struct tty *t, char *buff, char *end) {
	cc_t eol, eof;
	size_t block_size;

	assert(TC_L(t, ICANON));

	eol = t->termios.c_cc[VEOL];
	eof = t->termios.c_cc[VEOF];

	while ((block_size = ring_can_read(
				&t->i_canon_ring, TTY_IO_BUFF_SZ, end - buff))) {
		const char *line_start = t->i_buff + t->i_canon_ring.tail;
		size_t line_len;
		int got_line;
		int is_eof;

		line_len = find_line_len(eol, eof, line_start, block_size, &is_eof);

		got_line = (line_len < block_size);
		block_size = line_len;

		if (got_line) {
 			++block_size;  /* Line end char is always consumed... */

			if (!is_eof)  /* ...but EOF is discarded and not copied to user. */
	 			++line_len;
		}

		memcpy(buff, line_start, line_len);
		buff += line_len;

		ring_just_read(&t->i_ring, TTY_IO_BUFF_SZ, block_size);
		ring_just_read(&t->i_canon_ring, TTY_IO_BUFF_SZ, block_size);

		if (got_line)
			break;
	}

	return buff;
}

size_t tty_read(struct tty *t, char *buff, size_t size) {
	struct idesc_wait_link iwl;
	int rc;
	cc_t vmin, vtime;
	char *curr, *next, *end;
	unsigned long timeout;
	size_t count;

	vmin = t->termios.c_cc[VMIN];
	vtime = t->termios.c_cc[VTIME];
	curr = buff;
	end = buff + size;

	if (((vmin == 0) && (vtime == 0))) {
		size = 0;
		timeout = 0;
	} else {
		size = vtime == 0 ? min(size, vmin) : 1;
		timeout = vmin > 0 ? SCHED_TIMEOUT_INFINITE
				: vtime * 100; /* deciseconds to milliseconds */
	}

	idesc_wait_init(&iwl, POLLIN | POLLERR);

	threadsig_lock();
	mutex_lock(&t->lock);
	do {
		irq_lock();
		{
			tty_rx_do(t);
			rc = idesc_wait_prepare(t->idesc, &iwl);
		}
		irq_unlock();

		next = tty_read_raw(t, curr, end);

		/* TODO serialize termios access with ioctl. -- Eldar */
		if (TC_L(t, ICANON)) {
			next = tty_read_cooked(t, next, end);
		}

		count = next - curr;
		curr = next;
		if (size <= count) {
			idesc_wait_cleanup(t->idesc, &iwl);
			rc = curr - buff;
			break;
		}
		size -= count;

		if (!rc) {
			mutex_unlock(&t->lock);

			rc = sched_wait_timeout(timeout, NULL);

			mutex_lock(&t->lock);

		}
		idesc_wait_cleanup(t->idesc, &iwl);
	} while (!rc);
	mutex_unlock(&t->lock);
	threadsig_unlock();

	return rc;
}

static int tty_blockin_output(struct tty *t, char ch) {
	struct idesc_wait_link iwl;
	int ret;

	idesc_wait_init(&iwl, POLLOUT | POLLERR);

	do {
		if (tty_output(t, ch))
			return 0;

		if (!t->idesc)
			return -EBADF;

		ret = idesc_wait_prepare(t->idesc, &iwl);
		if (!ret) {
			mutex_unlock(&t->lock);

			tty_out_wake(t);
			ret = sched_wait();

			mutex_lock(&t->lock);
		}
		idesc_wait_cleanup(t->idesc, &iwl);
	} while (!ret);

	return ret;
}

size_t tty_write(struct tty *t, const char *buff, size_t size) {
	size_t count;
	int ret = 0;

	threadsig_lock();
	mutex_lock(&t->lock);

	for (count = size; count > 0; count--, buff++)
		if ((ret = tty_blockin_output(t, *buff)))
			break;

	mutex_unlock(&t->lock);
	threadsig_unlock();

	tty_out_wake(t);

	if (!(size - count)) {
		return ret;
	}
	return size - count;
}

int tty_ioctl(struct tty *t, int request, void *data) {
	int ret = 0;

	mutex_lock(&t->lock);

	switch (request) {
	case TIOCGETA:
		memcpy(data, &t->termios, sizeof(struct termios));
		break;
	case TIOCSETAF:
	case TIOCSETAW:
	case TIOCSETA:
		memcpy(&t->termios, data, sizeof(struct termios));
		if (!TC_L(t,ICANON)) {
			t->i_canon_ring.tail = t->i_canon_ring.head = t->i_ring.head;
		}
		break;
	case TIOCGPGRP:
		memcpy(data, &t->pgrp, sizeof(pid_t));
		break;
	case TIOCSPGRP:
		memcpy(&t->pgrp, data, sizeof(pid_t));
		break;
	default:
		ret = -ENOSYS;
		break;
	}

	mutex_unlock(&t->lock);

	return ret;
}

size_t tty_status(struct tty *t, int status_nr) {
	struct ring raw_ring;
	int res = 0;

	assert(t);

	mutex_lock(&t->lock);
	switch (status_nr) {
	case POLLIN:
		IRQ_LOCKED_DO(tty_rx_do(t));

		res = ring_can_read(tty_raw_ring(t, &raw_ring), TTY_IO_BUFF_SZ, 1) ||
			(TC_L(t, ICANON) 
			 	&& ring_can_read(&t->i_canon_ring, TTY_IO_BUFF_SZ, 1));
		break;
	case POLLOUT:
		res = ring_can_write(&t->o_ring, TTY_IO_BUFF_SZ, 1);
		break;
	case POLLERR:
		res = 0; /* FIXME: HUP isn't implemented */
		break;
	}
	mutex_unlock(&t->lock);

	return res;
}

struct tty *tty_init(struct tty *t, const struct tty_ops *ops) {
	assert(t && ops);

	t->idesc = NULL;
	t->ops = ops;

	{
		struct termios *termios = &t->termios;
		cc_t cc_init[NCCS] = TTY_TERMIOS_CC_INIT;

		memcpy(termios->c_cc, cc_init, sizeof(cc_init));
		termios->c_iflag = TTY_TERMIOS_IFLAG_INIT;
		termios->c_oflag = TTY_TERMIOS_OFLAG_INIT;
		termios->c_cflag = TTY_TERMIOS_CFLAG_INIT;
		termios->c_lflag = TTY_TERMIOS_LFLAG_INIT;
	}

	mutex_init(&t->lock);

	ring_init(&t->rx_ring);

	ring_init(&t->i_ring);
	ring_init(&t->i_canon_ring);

	ring_init(&t->o_ring);

	return t;
}

int tty_rx_locked(struct tty *t, char ch, unsigned char flag) {
	uint16_t *slot = t->rx_buff + t->rx_ring.head;

	/* Some input must be processed immediatly, like Ctrl-C.
	 * All other data will be stored as unprocecessed (raw) data
	 * and will be processed only at tty_read (if called)
	 */

	tty_task_break_check(t, ch);

	if (!ring_write(&t->rx_ring, TTY_RX_BUFF_SZ, 1))
		return -1;

	*slot = (flag<<CHAR_BIT) | (unsigned char) ch;

	tty_notify(t, POLLIN);

	return 0;
}


int tty_rx_dequeue(struct tty *t) {
	uint16_t *slot = t->rx_buff + t->rx_ring.tail;

	if (!ring_read(&t->rx_ring, TTY_RX_BUFF_SZ, 1))
		return -1;

	return (int) *slot;
}

int tty_out_getc(struct tty *t) {
	char ch;
	/* TODO Locks */
	if (!ring_read_all_into(&t->o_ring, t->o_buff, TTY_IO_BUFF_SZ, &ch, 1))
		return -1;

	tty_notify(t, POLLOUT);

	return (int) ch;
}

int tty_out_buf(struct tty *t, void *buf, size_t len) {
	int ret;

	ret = ring_read_all_into(&t->o_ring, t->o_buff, TTY_IO_BUFF_SZ, buf, len);

	tty_notify(t, POLLOUT);

	return ret;
}

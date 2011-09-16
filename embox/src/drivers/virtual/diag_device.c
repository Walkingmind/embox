/**
 * @file
 * @brief Creates diag file in /dev/
 *
 * @date 06.09.11
 * @author Anton Kozlov
 */

#include <types.h>
#include <kernel/file.h>
#include <fs/node.h>
#include <kernel/diag.h>
#include <embox/device.h>
#include <diag/diag_device.h>

static void *diag_open(struct file_desc *desc);
static int diag_close(struct file_desc *desc);
static size_t diag_read(void *buf, size_t size, size_t count, void *file);
static size_t diag_write(const void *buff, size_t size, size_t count, void *file);


static file_operations_t file_op = {
		.fread = diag_read,
		.fopen = diag_open,
		.fclose = diag_close,
		.fwrite = diag_write
};

FILE *diag_device_get(void) {
	struct file_desc *desc = file_desc_alloc();
	return diag_open(desc);
}

/*
 * file_operation
 */
static void *diag_open(struct file_desc *desc) {
	desc->ops = &file_op;
	return (void *) desc;
}

static int diag_close(struct file_desc *desc) {
	return 0;
}

static size_t diag_read(void *buf, size_t size, size_t count, void *file) {
	char *ch_buf = (char *) buf;

	int i = count * size;

	while (i --) {
		*(ch_buf++) = diag_getc();
	}

	return count * size;
}

static size_t diag_write(const void *buff, size_t size, size_t count, void *file) {
	size_t cnt = 0;
	char *b = (char*) buff;

	while (cnt != count * size) {
		diag_putc(b[cnt++]);
	}
	return cnt;
}

/* doesn't matter if we have fs:
if have, dependency added automaticly;
else this have no effect*/
EMBOX_DEVICE("diag", &file_op);

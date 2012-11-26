/**
 * @file
 *
 * @date Nov 23, 2012
 * @author: Anton Bondarev
 */

struct index_descriptor {
	struct node *node;
	size_t cursor;
	void *descriptor_data;
};


socket
timer
file
socket->kfile_open(node=NULL, idx_ops, flags)
int kfile_open(const char *path, int flags) {
	return -1;
}

size_t kfile_write(int idx, const void *buf, size_t size, size_t count) {
	struct index_descriptor *desc;

	assert(idx > 0);
	desc = idx_to_descriptor(idx);
	assert(desc);

	return 0;
}

size_t kfile_read(int idx, void *buf, size_t size, size_t count) {
	return 0;
}

int kfile_close(int idx) {
	return 0;
}

int kfile_seek(struct file_desc *desc, long int offset, int origin) {
	return 0;
}

int kfile_ioctl(struct file_desc *fp, int request, ...) {
	return 0;
}

int kfile_stat(struct file_desc *fp, void *buff) {
	return 0;
}

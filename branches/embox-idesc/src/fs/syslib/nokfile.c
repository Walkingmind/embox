/**
 * @file
 *
 * @date Nov 27, 2012
 * @author: Anton Bondarev
 */

#include <stddef.h>
#include <sys/types.h>
#include <fs/kfile.h>

struct file_desc *kopen(struct node *node, int flag) {
	return NULL;
}

size_t kwrite(const void *buf, size_t size, struct file_desc *file) {
	return -1;
}

size_t kread(void *buf, size_t size, struct file_desc *desc) {
	return -1;
}


int kclose(struct file_desc *desc) {
	return -1;
}

int kseek(struct file_desc *desc, long int offset, int origin) {
	return -1;
}

int kfstat(struct file_desc *desc, struct stat *buff) {
	return -1;
}

int kioctl(struct file_desc *fp, int request, void *data) {
	return -1;
}

struct node;

int ktruncate(struct node *node, off_t length) {
	return -1;
}

/**
 * @file
 *
 * @date 06.08.09
 * @author Anton Bondarev
 */

#include <errno.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include <mem/misc/pool.h>

#include <framework/mod/options.h>



#include <fs/kfile.h>


#define FILE_QUANTITY OPTION_GET(NUMBER,file_quantity)

#define DEFAULT_MODE 0755

POOL_DEF(file_pool, FILE, FILE_QUANTITY);

FILE stdin_struct = {
	.fd = STDIN_FILENO,
};
FILE stdout_struct = {
	.fd = STDOUT_FILENO,
};

FILE stderr_struct = {
	.fd = STDERR_FILENO,
};

FILE *stdin = &stdin_struct;
FILE *stdout = &stdout_struct;
FILE *stderr = &stderr_struct;

static FILE *file_alloc(int fd) {
	FILE *file = pool_alloc(&file_pool);

	if (!file) {
		return NULL;
	}

	file->fd = fd;
	file->has_ungetc = 0;
	return file;
}

void file_free(FILE *file) {
	pool_free(&file_pool, file);
}
	
FILE *fopen(const char *path, const char *mode) {
	int fd;
	FILE *file = NULL;
	int flags = 0;

	if (strchr(mode, 'r')) {
		flags |= O_RDONLY;
	} 

	if (strchr(mode, 'w')) {
		flags |= O_WRONLY | O_TRUNC | O_CREAT;
	} 
	
	if (strchr(mode, 'a')) {
		flags |= O_APPEND | O_WRONLY | O_CREAT;
	} 

	if ((fd = open(path, flags, DEFAULT_MODE)) < 0) {
		/* That's sad, but open sets errno, no need to alter */
		return NULL;
	}

	if (NULL == (file = file_alloc(fd))) {
		close(fd);
		SET_ERRNO(ENOMEM);
		return NULL;
	}

	return file;

}

FILE *fdopen(int fd, const char *mode) {
	/**
	 * FIXME mode ignored now
	 */
	FILE *file;

	file = file_alloc(fd);
	if (file == NULL) {
		SET_ERRNO(ENOMEM);
		return NULL;
	}

	return file;
}

FILE *freopen(const char *path, const char *mode, FILE *file) {
	if (NULL == file) {
		return file;
	}
	return NULL;
}

int feof(FILE *file) {
	//TODO:
	return 0;
}

int ferror(FILE *file) {
	//TODO:
	return 0;
}

size_t fwrite(const void *buf, size_t size, size_t count, FILE *file) {

	if (NULL == file) {
		return -1;
	}

	return write(file->fd, buf, size * count);
}

size_t fread(void *buf, size_t size, size_t count, FILE *file) {
	char *cbuff;
	size_t cnt;

	if (NULL == file) {
		SET_ERRNO(EBADF);
		return -1;
	}

	cnt = 0;
	if (file->has_ungetc) {
		file->has_ungetc = 0;
		cbuff = buf;
		cbuff[0] = (char)file->ungetc;
		count --;
		buf = &cbuff[1];
		cnt++;
	}
	while (cnt != count * size) {
		int tmp = read(file->fd,  buf, size * count);
		if (tmp == 0) {
			break; /* errors */
		}
		cnt += tmp;
	}
	if (cnt % size) {
		/* try to revert some bytes */
//		fpos_t pos;
//
//		fgetpos(file, &pos);
//		pos -= cnt % size;
//		fsetpos(file, &pos);
		cnt -= (cnt % size);
	}

	return cnt / size;
}

int fclose(FILE *file) {
	int res;

	if (NULL == file){
		SET_ERRNO(EBADF);
		return -1;
	}

	res = close(file->fd);
	if (res >= 0) {
		file_free(file);
	}

	return res;
}

int fseek(FILE *file, long int offset, int origin) {
	off_t ret;

	if (origin != SEEK_SET && origin != SEEK_CUR
			&& origin != SEEK_END) {
		SET_ERRNO(EINVAL);
		return -1;
	}

	if (NULL == file) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = lseek(file->fd, offset, origin);
	if (ret == (off_t)-1) {
		return -1;
	}

	return 0;
}

long int ftell(FILE *file) {
	if (NULL == file) {
		SET_ERRNO(EBADF);
		return -1;
	}
	return lseek(file->fd, 0L, SEEK_CUR);
}

int fgetpos(FILE *stream, fpos_t *pos) {
	off_t mypos;

	if (NULL == stream) {
		SET_ERRNO(EBADF);
		return -1;
	}

	mypos = lseek(stream->fd, 0L, SEEK_CUR);

	if (-1 == mypos) {
		return -1;
	}

	*pos = mypos;

	return 0;
}

int fsetpos(FILE *stream, const fpos_t *pos) {
	off_t ret;

	if (NULL == stream) {
		SET_ERRNO(EBADF);
		return -1;
	}

	ret = lseek(stream->fd, *pos, SEEK_SET);
	if (ret == (off_t)-1) {
		return -1;
	}

	return 0;
}

void rewind(FILE *file) {
	fseek(file, 0L, SEEK_SET);
}

int fioctl(FILE *file, int request, ...) {
	va_list args;
	if (NULL == file) {
		SET_ERRNO(EBADF);
		return -1;
	}
	va_start(args, request);
	return ioctl(file->fd, request, args);
}

int ungetc(int ch, FILE *file) {
	if (NULL == file) {
		SET_ERRNO(EBADF);
		return -1;
	}
	file->ungetc = (char) ch;
	file->has_ungetc = 1;
	return ch;
}

int fileno(FILE *stream) {
	assert(stream != NULL);
	return stream->fd;
}


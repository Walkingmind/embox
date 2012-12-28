/**
 * @file
 * @brief
 *
 * @date 27.12.12
 * @author Alexander Kalmuk
 */

#include <javacall_file.h>
#include <javacall_dir.h>
#include <javautil_unicode.h>
#include <javacall_memory.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

static javacall_result emboxErrno2javaErrno(int embox_errno);
/* Same as javautil_unicode_utf16_to_utf8, but allocates memory for
 * pUtf8 */
static javacall_result utf16_to_utf8(const javacall_utf16* pUtf16,
                                               javacall_int32 utf16Len,
                                               unsigned char** pUtf8,
                                               javacall_int32 *utf8Len);

javacall_result javacall_file_open(javacall_const_utf16_string fileName,
                                  int fileNameLen,
                                  int flags,
                                  javacall_handle* /* OUT */ handle) {
	int res;
	javacall_int32 utf8NameLen;
	unsigned char *utf8Name;

	if (0 > (res = utf16_to_utf8(fileName, fileNameLen, &utf8Name, &utf8NameLen))) {
		free(utf8Name);
		return JAVACALL_FAIL;
	}
	handle = (void *)fopen((const char *)utf8Name, "rw");/* FIXME */
	free(utf8Name);

	return emboxErrno2javaErrno(errno);
}

javacall_result javacall_file_close(javacall_handle handle) {
    return emboxErrno2javaErrno(fclose((FILE *)handle));
}

long javacall_file_read(javacall_handle handle,
                         unsigned char *buf,
                         long size) {
	return fread(buf, 1, (size_t)size, (FILE *)handle);
}

long javacall_file_write(javacall_handle handle,
                         const unsigned char* buf,
                         long size) {
	return fwrite(buf, 1, (size_t)size, (FILE *)handle);
}

javacall_int64 javacall_file_sizeof(javacall_const_utf16_string fileName,
                                   int fileNameLen) {
	int res;
	struct stat file_stat;
	javacall_int32 utf8NameLen;
	unsigned char *utf8Name;

	if (0 > (res = utf16_to_utf8(fileName, fileNameLen, &utf8Name, &utf8NameLen))) {
		free(utf8Name);
		return JAVACALL_FAIL;
	}

	stat((const char*)utf8Name, &file_stat);
	free(utf8Name);

	return file_stat.st_size;
}

javacall_int64 javacall_file_sizeofopenfile(javacall_handle handle) {
	struct stat file_stat;
	FILE *file = (FILE*)handle;

	fstat(file->fd, &file_stat);
	return file_stat.st_size;
}

javacall_result javacall_file_exist(const javacall_utf16 * fileName, int fileNameLen) {
	int res;
	FILE *file;
	javacall_int32 utf8NameLen;
	unsigned char *utf8Name;

	if (0 > (res = utf16_to_utf8(fileName, fileNameLen, &utf8Name, &utf8NameLen))) {
		free(utf8Name);
		return JAVACALL_FAIL;
	}
	file = (void *)fopen((const char *)utf8Name, "r");
	free(utf8Name);

	if (file) {
		res = JAVACALL_OK;
	} else {
		res = JAVACALL_FAIL;
	}

	fclose(file);
	return res;
}

javacall_int64 javacall_file_seek(javacall_handle handle, javacall_int64 offset,
                                  javacall_file_seek_flags flag) {
	return fseek((FILE*)handle, offset, flag);
}

static javacall_result utf16_to_utf8(const javacall_utf16* pUtf16,
                                               javacall_int32 utf16Len,
                                               unsigned char** pUtf8,
                                               javacall_int32 *utf8Len) {
	int res;

	if (0 > (res = javautil_unicode_utf16_utf8length(pUtf16, utf8Len))) {
		return res;
	}

	if ((*pUtf8 = malloc(*utf8Len)) == NULL) {
		return JAVACALL_FAIL;
	}

	if (0 > (res = javautil_unicode_utf16_to_utf8(pUtf16, utf16Len,
			*pUtf8, *utf8Len, utf8Len))) {
		free(*pUtf8);
		return res;
	}

	return res;
}

/* TODO */
static javacall_result emboxErrno2javaErrno(int embox_errno) {
	switch (errno) {
	case ENOERR:
		return JAVACALL_OK;
	case EBADF:
		return JAVACALL_BAD_FILE_NAME;
	case ENOMEM:
		return JAVACALL_OUT_OF_MEMORY;
	}

	return JAVACALL_OK;
}

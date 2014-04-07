#ifndef TAR_UNISTD_H_
#define TAR_UNISTD_H_

#include <stddef.h>
#include <sys/types.h>

extern int link(const char *oldpath, const char *newpath);
extern ssize_t readlink(const char *path, char *buf,
		       size_t bufsize);
extern ssize_t readlinkat(int fd, const char *path,
		       char *buf, size_t bufsize);

#include_next <unistd.h>

#endif /* TAR_UNISTD_H_ */

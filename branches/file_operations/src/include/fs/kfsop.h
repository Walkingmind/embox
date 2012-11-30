/**
 * @file
 *
 * @date Nov 29, 2012
 * @author: Anton Bondarev
 */

#ifndef FS_KFSOP_H_
#define FS_KFSOP_H_

#include <sys/types.h>

struct stat;

extern int kcreate(const char *pathname, mode_t mode);

extern int kmkdir(const char *pathname, mode_t mode);

extern int kremove(const char *pathname);

extern int kunlink(const char *pathname);

extern int krmdir(const char *pathname);

extern int klstat(const char *path, struct stat *buf);

extern int kmount(char *dev,  char *dir, char *fs_type);

#endif /* FS_KFSOP_H_ */

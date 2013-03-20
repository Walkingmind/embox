/**
 * @file
 *
 * @date 26.12.12
 * @author Alexander Kalmuk
 */

#ifndef PWD_H_
#define PWD_H_

#include <stddef.h>
#include <sys/types.h>

struct passwd {
	char *pw_name;
	char *pw_passwd;
	uid_t pw_uid;
	gid_t pw_gid;
	char *pw_gecos;
	char *pw_dir;
	char *pw_shell;
};

extern int fgetpwent_r(FILE *file, struct passwd *pwd, char *buf, 
		size_t buflen, struct passwd **result);

extern int getpwnam_r(const char *name, struct passwd *pwd,
		char *buf, size_t buflen, struct passwd **result);

extern int getpwuid_r(uid_t uid, struct passwd *pwd,
		char *buf, size_t buflen, struct passwd **result);

static inline struct passwd *getpwuid(uid_t uid) { return NULL; }
static inline void endpwent(void) { }
static inline struct passwd * getpwent(void) { return NULL; }
static inline void setpwent(void) { }

#endif /* PWD_H_ */

/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    06.02.2013
 */

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include <pwd.h>
#include <grp.h>
#include <shadow.h>

#include <pwd_db.h>

static int open_db(const char *db_path, FILE **result) {
	FILE *f;
	if (NULL == (f = fopen(db_path, "r"))) {
		return errno;
	}

	*result = f;
	return 0;
}

static int read_field(FILE *stream, char **buf, size_t *buflen, char **field, 
		int delim) {
	int ch = fgetc(stream);

	*field = *buf;

	while (ch != delim) {
		if (ch == EOF) {
			return EOF;
		}

		if (ch == ':' || ch == '\n') {
			return EIO;
		}

		if (*buflen <= 0) {
			return ERANGE;
		}

		*((*buf)++) = (char) ch;
		(*buflen)--;
		
		ch = fgetc(stream);
	}

	if (*buflen <= 0) {
		return -ERANGE;
	}

	*((*buf)++) = '\0';
	(*buflen)--;

	return 0;
}

static int read_int_field(FILE *stream, const char *format, void *field, int delim) {
	int val;
	int ret = fscanf(stream, format, field);

	if (0 > ret) {
		return -ret;
	}
	
	if (delim != (val = fgetc(stream))) {
		/* fscanf can eat blank charactes, so if it used as delim, here we beleive it
 		 * was on place, but stolen. Otherwise, report inproper stream format
		 */
		if (isspace(delim)) {
			ungetc(val, stream);
		} else {
			return EIO;
		}
	}

	return 0;
}

static int read_pwd(FILE *stream, char *buf, size_t buflen, struct passwd *pwd) {
	int res;
	char *p = buf;
	size_t llen = buflen;

	if (0 != (res = read_field(stream, &p, &llen, &pwd->pw_name, ':'))) {
		return res;
	}

	if (0 != (res = read_field(stream, &p, &llen, &pwd->pw_passwd, ':'))) {
		return res;
	}

	if (0 != (res = read_int_field(stream, "%d", &pwd->pw_uid, ':'))) {
		return res;
	}

	if (0 != (res = read_int_field(stream, "%d", &pwd->pw_gid, ':'))) {
		return res;
	}

	if (0 != (res = read_field(stream, &p, &llen, &pwd->pw_gecos, ':'))) {
		return res;
	}

	if (0 != (res = read_field(stream, &p, &llen, &pwd->pw_dir, ':'))) {
		return res;
	}

	if (0 != (res = read_field(stream, &p, &llen, &pwd->pw_shell, '\n'))) {
		return res;
	}

	return 0;
}

int fgetpwent_r(FILE *file, struct passwd *pwd, char *buf, size_t buflen,
		struct passwd **result) {

	int res = read_pwd(file, buf, buflen, pwd);

	if (res == EOF) {
		*result = NULL;
		return ENOENT;
	}

	*result = pwd;
	return res;

}

int getpwnam_r(const char *name, struct passwd *pwd,
		char *buf, size_t buflen, struct passwd **result) {
	int res;
	FILE *file;

	if (0 != (res = open_db(PASSWD_FILE, &file))) {
		*result = NULL;
		return res;
	}

	while (0 == (res = fgetpwent_r(file, pwd, buf, buflen, result))) {
		if (0 == strcmp(pwd->pw_name, name)) {
			break;
		}
	}

	fclose(file);

	if (0 != res) {
		result = NULL;
		return res == ENOENT ? 0 : -1;
	}

	return 0;
}

struct passwd *getpwnam(const char *name) {
	static struct passwd getpwnam_buffer;
	static char buff[0x80];
	struct passwd *res;

	if (0 != getpwnam_r(name, &getpwnam_buffer, buff, 0x80,  &res)) {
		return NULL;
	}

	return res;
}

int getpwuid_r(uid_t uid, struct passwd *pwd,
		char *buf, size_t buflen, struct passwd **result) {
	int res;
	FILE *file;

	if (0 != (res = open_db(PASSWD_FILE, &file))) {
		*result = NULL;
		return res;
	}

	while (0 == (res = fgetpwent_r(file, pwd, buf, buflen, result))) {
		if (pwd->pw_uid == uid) {
			break;
		}
	}

	fclose(file);

	if (0 != res) {
		result = NULL;
		return res == ENOENT ? 0 : -1;
	}

	return 0;
}

struct passwd *getpwuid(uid_t uid) {
	static struct passwd getpwuid_buffer;
	static char buff[0x80];
	struct passwd *res;

	if (0 != getpwuid_r(uid, &getpwuid_buffer, buff, 80, &res)) {
		//TODO errno must be set
		return NULL;
	}

	return res;
}

int fgetgrent_r(FILE *fp, struct group *gbuf, char *tbuf,
		size_t buflen, struct group **gbufp) {
	int res; 
	char *buf = tbuf;
	size_t buf_len = buflen;
	char *ch, **pmem;

	*gbufp = NULL;

	if (0 != (res = read_field(fp, &buf, &buf_len, &gbuf->gr_name, ':'))) {
		return res;
	}

	if (0 != (res = read_field(fp, &buf, &buf_len, &gbuf->gr_passwd, ':'))) {
		return res;
	}

	if (0 != (res = read_int_field(fp, "%d", &gbuf->gr_gid, ':'))) {
		return res;
	}
	
	if (0 != (res = read_field(fp, &buf, &buf_len, &ch, '\n'))) {
		return res;
	}

	gbuf->gr_mem = pmem = (char **) buf;

	*pmem = ch;

	while (NULL != (ch = strchr(ch, ','))) {
		
		if (buf_len < sizeof(char *)) {
			return -ERANGE;
		}

		buf_len -= sizeof(char *);

		*ch++ = '\0';
	
		*(++pmem) = ch;

	}

	if (buf_len < sizeof(char *)) {
		return -ERANGE;
	}
	*(++pmem) = NULL;

	*gbufp = gbuf;

	return 0;
}
			       
int getgrnam_r(const char *name, struct group *grp,
	char *buf, size_t buflen, struct group **result) {
	int res;
	FILE *file;

	if (0 != (res = open_db(GROUP_FILE, &file))) {
		return res;
	}

	while (0 == (res = fgetgrent_r(file, grp, buf, buflen, result))) {
		if (0 == strcmp((*result)->gr_name, name)) {
			break;
		}
	}

	fclose(file);

	if (0 != res) {
		result = NULL;
		return res == ENOENT ? 0 : -1;
	}
	return 0;

}

struct group * getgrgid(gid_t gid) {
	struct group grp, *result;
	char buf[64];
	int ret;

	ret = getgrgid_r(gid, &grp, buf, sizeof buf, &result);
	if (ret != 0) {
		SET_ERRNO(-ret);
		return NULL;
	}

	return result;
}

int getgrgid_r(gid_t gid, struct group *grp,
	char *buf, size_t buflen, struct group **result) {
	int res;
	FILE *file;

	if (0 != (res = open_db(GROUP_FILE, &file))) {
		return res;
	}

	while (0 == (res = fgetgrent_r(file, grp, buf, buflen, result))) {
		if ((*result)->gr_gid == gid) {
			break;
		}
	}

	fclose(file);

	if (0 != res) {
		result = NULL;
		return res == ENOENT ? 0 : -1;
	}

	return 0;
}

int getmaxuid() {
	int res, curmax = 0;
	FILE *file;
	static char buff[0x80];
	struct passwd *result, pwd;

	if (0 != (res = open_db(PASSWD_FILE, &file))) {
		return res;
	}

	while (0 == (res = fgetpwent_r(file, &pwd, buff, 80, &result))) {
		if (pwd.pw_uid > curmax) {
			curmax = pwd.pw_uid;
		}
	}

	fclose(file);

	return curmax;
}

#define SHADOW_NAME_BUF_LEN 64
#define SHADOW_PSWD_BUF_LEN 128

static struct spwd spwd;
static char spwd_buf[SHADOW_NAME_BUF_LEN + SHADOW_PSWD_BUF_LEN];

struct spwd *fgetspent(FILE *file) {
	int res; 
	char *buf = spwd_buf;
	size_t buf_len = SHADOW_NAME_BUF_LEN + SHADOW_PSWD_BUF_LEN;

	if (0 != (res = read_field(file, &buf, &buf_len, &spwd.sp_namp, ':'))) {
		return NULL;
	}

	if (0 != (res = read_field(file, &buf, &buf_len, &spwd.sp_pwdp, ':'))) {
		return NULL;
	}

	if (0 != (res = read_int_field(file, "%ld", &spwd.sp_lstchg, ':'))) {
		return NULL;
	}

	if (0 != (res = read_int_field(file, "%ld", &spwd.sp_min, ':'))) {
		return NULL;
	}

	if (0 != (res = read_int_field(file, "%ld", &spwd.sp_max, ':'))) {
		return NULL;
	}

	if (0 != (res = read_int_field(file, "%ld", &spwd.sp_warn, ':'))) {
		return NULL;
	}

	if (0 != (res = read_int_field(file, "%ld", &spwd.sp_inact, ':'))) {
		return NULL;
	}

	if (0 != (res = read_int_field(file, "%ld", &spwd.sp_expire, ':'))) {
		return NULL;
	}

	if (0 != (res = read_int_field(file, "%ld", &spwd.sp_expire, '\n'))) {
		return NULL;
	}

	return &spwd;
}

static struct spwd *spwd_find(const char *spwd_path, const char *name) {
	struct spwd *spwd;
	FILE *shdwf;

	if (NULL == (shdwf = fopen(spwd_path, "r"))) {
		return NULL;
	}

	while (NULL != (spwd = fgetspent(shdwf))) {
		if (0 == strcmp(spwd->sp_namp, name)) {
			break;
		}
	}

	fclose(shdwf);

	return spwd;
}

struct spwd *getspnam_f(const char *name) {
	return spwd_find(SHADOW_FILE, name);
}

int get_defpswd(struct passwd *passwd, char *buf, size_t buf_len) {
	FILE *passwdf;
	char *temp;
	int res = 0;

	if (NULL == (passwdf = fopen(ADDUSER_FILE, "r"))) {
		return errno;
	}

	while (read_field(passwdf, &buf, &buf_len, &temp, '=') != EOF) {
		if(0 == strcmp(temp, "GROUP")) {
			if (0 != read_int_field(passwdf, "%d", &passwd->pw_gid, '\n')) {
				res = -1;
				goto out;
			}
			continue;
		}

		if(0 == strcmp(temp, "HOME")) {
			if (0 != read_field(passwdf, &buf, &buf_len,
					&passwd->pw_dir, '\n')) {
				res = -1;
				goto out;
			}
			continue;
		}

		if(0 == strcmp(temp, "SHELL")) {
			if (0 != read_field(passwdf, &buf, &buf_len,
					&passwd->pw_shell, '\n')) {
				res = -1;
				goto out;
			}
			continue;
		}
	}

out:
	fclose(passwdf);
	return res;
}

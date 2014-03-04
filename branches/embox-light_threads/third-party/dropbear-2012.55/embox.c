/**
 * @file
 *
 * @brief
 * @date 23.11.2012
 * @author Alexander Kalmuk
 */


#include "includes.h"
#include <shadow.h>


char *crypt(char *key, const char *salt) {
	static char buff[0x20];
	return strncpy(buff, key, 0x20);
#if 0
	struct passwd *pwd;
	struct spwd *spwd;

	pwd = getpwuid(geteuid());

	buff[0] = '\0';

	if (pwd == NULL) {
		return buff;
	}

	if (!(spwd = getspnam_f(pwd->pw_name))) {
		return buff;
	}

	if (!strcmp(key, spwd->sp_pwdp)) {
		memcpy(buff, pwd->pw_passwd, sizeof(buff));
	}

	return buff;
#endif
}

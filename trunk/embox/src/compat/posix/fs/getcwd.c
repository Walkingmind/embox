/**
 * @file
 * @brief
 *
 * @author Ilia Vaprol
 * @date 31.03.13
 */

#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char * getcwd(char *buff, size_t size) {
	const char *dir;

	if ((buff == NULL) || (size == 0)) {
		SET_ERRNO(EINVAL);
		return NULL;
	}

	dir = getenv("PWD");
	if (dir == NULL) {
		dir = "/"; /* FIXME use default value if PWD not set */
	}

	if (strlen(dir) + 1 >= size) {
		SET_ERRNO(ERANGE);
		return NULL;
	}

	strcpy(buff, dir);

	return buff;
}

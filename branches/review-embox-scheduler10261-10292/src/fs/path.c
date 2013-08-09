/**
 * @file
 * @brief
 *
 * @date 19.11.2012
 * @author Andrey Gazukin
 *          - Initial implementation.
 * @author Eldar Abusalimov
 *          - path_next
 */
#include <stdio.h>
#include <string.h>

#include <fs/path.h>
#include <assert.h>


/*
 * remove the top directory name from path
 */
void path_cut_mount_dir(char *path, char *mount_dir) {
	char *p;

	p = path;
	while (*mount_dir && (*mount_dir == *p)) {
		mount_dir++;
		p++;
	}
	strcpy((char *) path, (const char *) p);
}

/*
 *  move the last name of the whole directory to the top of tail
 */
int path_nip_tail(char *head, char *tail) {
	char *p_tail;
	char *p;

	p = p_tail = head + strlen(head);
	strcat(head, tail);

	do {
		p_tail--;
		if (head > p_tail) {
			*p = '\0';
			return -1;
		}
	} while ('/' != *p_tail);

	strcpy (tail, p_tail);
	*p_tail = '\0';

	return 0;
}

/*
 * move the top of tail as the last name of the head
 */
int path_increase_tail(char *head, char *tail) {
	char *p_tail;

		p_tail = head + strlen(head);
		strcat(head, tail);

		do {
			if ('\0' == *p_tail) {
				break;
			}
			p_tail++;
		} while ('/' != *p_tail);

		strcpy (tail, p_tail);
		*p_tail = '\0';

		return 0;
}

/*
 * Save first node name in path into node_name parameter.
 * Return the remaining part of path.
 */
char *path_get_next_name(const char *path, char *node_name, int buff_len) {
	char *p = (char *) path;
	char *nm = node_name;

	*nm = '\0'; /* empty node_name */

	/* we must pass '/' symbol */
	if ('/' == *p) {
		p++;
	}

	/* we copy chars while not appear end of string or we don't find next item
	 * or don't fill the buffer*/
	while (('/' != *p) && ('\0' != *p) && (buff_len-- > 0)) {
		*nm++ = *p++;
	}

	/* we must setup terminate symbol to the end of node_name */
	*nm = '\0';

	/* if we found some symbols it's a correct node_name  */
	if (nm != node_name) {
		return p;
	}

	return NULL;
}

const char *path_next(const char *path, size_t *p_len) {

	if (!path) {
		return NULL;
	}

	/* Skip leading slashes. */
	while (*path == '/') {
		++path;
	}

	if (!*path) {
		return NULL;
	}

	if (p_len) {
		const char *end = path;

		while (*end && *end != '/') {
			++end;
		}

		*p_len = end - path;
	}

	return path;
}

#include <fs/fat.h>
/*
 *	Convert a filename element from canonical (8.3) to directory entry (11)
 *	form src must point to the first non-separator character.
 *	dest must point to a 12-byte buffer.
 */
char *path_canonical_to_dir(char *dest, char *src) {

	memset(dest, (int)' ', MSDOS_NAME);
	dest[MSDOS_NAME] = 0;

	for (int i = 0; i <= 11; i++) {
		if (!*src) {
			break;
		}
		if (*src == '/') {
			break;
		}
		if (*src == '.') {
			i = 7;
			src++;
			continue;
		}
		if (*src >= 'a' && *src <='z') {
			*src = (*src - 'a') + 'A';
		}

		*(dest + i) = *src;
		src++;
	}

	return dest;
}

/*
 *	Convert a filename element from directory entry (11) to canonical (8.3)
 */
char *path_dir_to_canonical(char *dest, char *src, char dir) {
        int i;
        char *dst;

        dst = dest;
        memset(dest, 0, MSDOS_NAME + 2);
        for (i = 0; i < 8; i++) {
			if (*src != ' ') {
				*dst = *src;
				if ((0 == dir) && (*dst >= 'A' && *dst <='Z')) {
					*dst = (*dst - 'A') + 'a';
				}
				dst++;
			}
			src++;
        }
        if ((*src != ' ') && (0 == dir)) {
        	*dst++ = '.';
        }
        for (i = 0; i < 3; i++) {
			if (*src != ' ') {
				*dst = *src;
				if ((0 == dir) && (*dst >= 'A' && *dst <='Z')) {
					*dst = (*dst - 'A') + 'a';
				}
				dst++;
			}
			src++;
        }
        return dest;
}

int path_is_dotname(const char *name, size_t name_len) {
	if (name_len - 1 <= 1 && name[0] == '.' && name[name_len - 1] == '.') {
		return name_len;
	} else {
		return 0;
	}
}

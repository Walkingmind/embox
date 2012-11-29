/**
 * @file
 * @brief
 *
 * @date 19.11.2012
 * @author Andrey Gazukin
 */
#include <stdio.h>
#include <string.h>

#include <fs/path.h>

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
			if('\0' == *p_tail) {
				break;
			}
			p_tail++;
		} while ('/' != *p_tail);

		strcpy (tail, p_tail);
		*p_tail = '\0';

		return 0;
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
		if (*src >= 'a' && *dest <='z') {
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


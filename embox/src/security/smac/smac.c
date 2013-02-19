/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    18.02.2013
 */

#include <errno.h>
#include <string.h>
#include <assert.h>
#include <fs/node.h>
#include <kernel/task.h>
#include <embox/unit.h>
#include <fs/xattr.h>

#include <security/smac.h>
#include <security/security.h>

EMBOX_UNIT_INIT(smac_init);

static const char *smac_floor = "_";
static const char *smac_star  = "*";
static const char *smac_hat   = "^";
/*static const char *smac_huh   = "?";*/
/*static const char *smac_web   = "@";*/

const char *smac_xattrkey = "SMAC32LABEL";

#define SMAC_MAX_ENTS OPTION_GET(NUMBER, max_entries)

static struct smac_entry smac_env[SMAC_MAX_ENTS];
static int smac_env_n;

/*
 * steps below is from smack deciding order
 */
static int security_access(const char *s_subject, const char *s_object, 
		int access) {

	/* 1 */
	if (0 == strcmp(s_subject, smac_star)) {
		return -EACCES;
	}
	
	/* 2 */
	if (0 == strcmp(s_subject, smac_hat)
		&& 0 == (~(FS_MAY_READ | FS_MAY_EXEC) & access)) {
		return 0;
	}

	/* 3 */
	if (0 == strcmp(s_object, smac_floor)
		&& 0 == (~(FS_MAY_READ | FS_MAY_EXEC) & access)) {
		return 0;
	}

	/* 4 */
	if (0 == strcmp(s_object, smac_star)) {
		return 0;
	}

	/* 5 */
	if (0 == strcmp(s_subject, s_object)) {
		return 0;
	}

	/* 6 */
	for (int i = 0; i < smac_env_n; i++) {
		if (0 == strcmp(s_subject, smac_env[i].subject)
				&& 0 == strcmp(s_object, smac_env[i].object)) {
			if (~smac_env[i].flags & access) {
				return -EACCES;
			}

			return 0;
		}
	}

	/* 7 */
	return -EACCES;
}

int smac_setenv(struct smac_entry *entries, int n, 
		struct smac_entry *backup, size_t backup_len, int *wasn) {

	if (backup || backup_len || wasn) {
		assert(backup);
		assert(backup_len);
		assert(wasn);

		if (backup_len < (smac_env_n * sizeof(struct smac_entry))) {
			return -ERANGE;
		}

		*wasn = smac_env_n;
		memcpy(backup, smac_env, smac_env_n * sizeof(struct smac_entry));
	}

	if (n > SMAC_MAX_ENTS) {
		return -ENOMEM;
	}

	memcpy(smac_env, entries, n * sizeof(struct smac_entry));
	smac_env_n = n;

	return 0;
}

int smac_labelset(const char *label) {
	int res, newlen;
	
	if (0 != (res = security_access(task_self_security(), smac_floor, 
					FS_MAY_WRITE))) {
		return res;
	}
	
	if ((newlen = strlen(label)) > SMAC_LABELLEN) {
		return -ERANGE;
	}

	strcpy(((struct smac_task *) task_self_security())->label, label);

	return 0;
}

int smac_labelget(char *label, size_t len) {
	int res, thislen;

	if (0 != (res = security_access(task_self_security(), smac_floor, 
					FS_MAY_READ))) {
		return res;
	}
	
	if (len < (thislen = strlen(task_self_security()))) {
		return -ERANGE;
	}

	strcpy(label, ((struct smac_task *) task_self_security())->label);

	return 0;
}

int security_node_create(struct node *dir, mode_t mode) {
	char label[SMAC_LABELLEN];
	int res;

	if (0 > (res = kfile_xattr_get(dir, smac_xattrkey, label, SMAC_LABELLEN))) {
		return 0;
	}

	return security_access(task_self_security(), label, FS_MAY_WRITE);
}

int security_node_permissions(struct node *node, int flags) {
	char label[SMAC_LABELLEN];
	int res;

	if (0 > (res = kfile_xattr_get(node, smac_xattrkey, label, SMAC_LABELLEN))) {
		return 0;
	}

	return security_access(task_self_security(), label, flags);
}

static int smac_init(void) {
	strcpy(((struct smac_task *) task_self_security())->label, smac_floor);

	return 0;
}

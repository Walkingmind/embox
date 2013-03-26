/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    26.03.2013
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <embox/cmd.h>

#include <lib/linenoise_1.h>
#include <cmd/shell.h>
#include <pwd.h>
#include <shadow.h>
#include <utmp.h>

#include <kernel/task/u_area.h>

EMBOX_CMD(su_exec);

static int passw_prompt(const char *prompt, char *buf, int buflen) {
	int ch;
	printf("%s", prompt);

	ch = fgetc(stdin);

	while ('\n' != ch && '\r' != ch) {

		/* Avoid strange symbols in stdin.
		 * Actually, telnet sends \r as \r\0,
		 * so trying bypass it.
		 */
		if (ch == '\0') {
			ch = fgetc(stdin);
			continue;
		}

		if (buflen-- <= 0) {
			return -ERANGE;
		}

		*buf++ = ch;
		ch = fgetc(stdin);
	}

	if (buflen-- <= 0) {
		return -ERANGE;
	}

	*buf++ = '\0';

	printf("\n");

	return 0;
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

#define SHADOW_FILE "/shadow"

#define PASSBUF_LEN 64


static int su_exec(int argc, char *argv[]) {
	struct spwd *spwd;
	struct task_u_area *uarea = task_self_u_area();
	uid_t euid = geteuid();
	uid_t reuid = getuid();
	char passwd[PASSBUF_LEN];
	int ret;

	uarea->reuid = uarea->euid = 0;

	spwd = spwd_find(SHADOW_FILE, "root");

	if (!spwd) {
		ret = -EIO;
		goto out_err;
	}

	if (0 > (ret = passw_prompt("Password: ", passwd, PASSBUF_LEN))) {
		goto out_err;
	}

	if (strcmp(spwd->sp_pwdp, passwd)) {
		ret = -EACCES;
		goto out_err;
	}

	shell_run(shell_lookup("tish"));

	ret = 0;

out_err:
	uarea->reuid = reuid;
	uarea->euid = euid;
	return ret;
}


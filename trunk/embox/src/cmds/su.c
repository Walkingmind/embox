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
#include <framework/cmd/api.h>

#include <kernel/task/u_area.h>
#include <security/smac.h>

EMBOX_CMD(su_exec);

static int su_exec(int argc, char *argv[]) {
	struct task_u_area *uarea = task_self_u_area();
	const struct cmd *login_cmd = cmd_lookup("login");
	uid_t euid = geteuid();
	uid_t reuid = getuid();
	char old_smac_label[SMAC_LABELLEN];
	char *defargv[] = {"", "root"};
	int ret;

	if (argc == 1) {
		argv = defargv;
		argc++;
	}

	uarea->reuid = uarea->euid = 0;
	strcpy(old_smac_label, task_self_security());
	strcpy(task_self_security(), smac_admin);

	ret = cmd_exec(login_cmd, argc, argv);

	strcpy(task_self_security(), old_smac_label);
	uarea->reuid = reuid;
	uarea->euid = euid;

	return ret;

}


/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    16.07.2013
 */

#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <cmd/shell.h>
#include <embox/cmd.h>
#include <cmd/smac_test.h>

EMBOX_CMD(smac_test_piece);
struct test_res __zrv_smac_read;
struct test_res __zrv_smac_write;

static const struct shell *sh;

static int do_test(struct test_res *tr, const char *cmd) {
	int ecode;

	printf("\n[Mandatory] Running '%s'\n", cmd);

	ecode = shell_exec(sh, cmd);

	tr->tr_ecode[tr->tr_pos++] = ecode ? -EACCES : 0;

	if (!ecode) {
		printf("Command returned with code %d: %s\n",
				ecode, strerror(-ecode));
	}

	return ecode;
}

static int smac_test_piece(int argc, char *argv[]) {

	sh = shell_lookup("tish");

	printf("\n[Mandatory] Starting write tests for current user\n");

	do_test(&__zrv_smac_write, "echo \"hello\" >> /mandatory_test/unclassified");
	do_test(&__zrv_smac_write, "echo \"hello\" >> /mandatory_test/service");
	do_test(&__zrv_smac_write, "echo \"hello\" >> /mandatory_test/secret");
	do_test(&__zrv_smac_write, "echo \"hello\" >> /mandatory_test/confidentially");

	printf("\n[Mandatory] Starting read tests for current user\n");

	do_test(&__zrv_smac_read, "cat /mandatory_test/unclassified");
	do_test(&__zrv_smac_read, "cat /mandatory_test/service");
	do_test(&__zrv_smac_read, "cat /mandatory_test/secret");
	do_test(&__zrv_smac_read, "cat /mandatory_test/confidentially");

	printf("\n[Mandatory] Tests for current user done\n");

	return 0;
}





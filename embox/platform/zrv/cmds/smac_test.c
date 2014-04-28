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
#include <embox/cmd.h>

#include <cmd/shell.h>
#include <cmd/smac_test.h>

EMBOX_CMD(smac_test);

static struct test_res ref_read = {
	.tr_ecode = {
                0,       -EACCES, -EACCES, -EACCES, 
                0,       0,       -EACCES, -EACCES, 
                0,       0,       0,       -EACCES, 
                0,       0,       0,       0,
	},
	.tr_pos = NFILES * NUSERS,
};

static struct test_res ref_write = {
	.tr_ecode = {
                0,       -EACCES, -EACCES, -EACCES, 
                -EACCES, 0,       -EACCES, -EACCES, 
                -EACCES, -EACCES, 0,       -EACCES, 
                -EACCES, -EACCES, -EACCES, 0,
	},
	.tr_pos = NFILES * NUSERS,
};

static void init_test(struct test_res *tr) {
	tr->tr_pos = 0;

}

static int smac_test(int argc, char *argv[]) {
	const struct shell *sh = shell_lookup("tish");
	int cmp;

	printf("\nStarting mandatory testsuite\n");

	init_test(&__zrv_smac_write);
	init_test(&__zrv_smac_read);

	shell_exec(sh, "su -c smac_test_piece unclassified");
	shell_exec(sh, "su -c smac_test_piece service");
	shell_exec(sh, "su -c smac_test_piece secret");
	shell_exec(sh, "su -c smac_test_piece confidentially");

	cmp = memcmp(&__zrv_smac_read, &ref_read, sizeof(struct test_res)) || 
		memcmp(&__zrv_smac_write, &ref_write, sizeof(struct test_res));

	printf("Mandatory testsuite finished. Result: %s\n",
			cmp ? "Failure" : "Success");

	return cmp;
}


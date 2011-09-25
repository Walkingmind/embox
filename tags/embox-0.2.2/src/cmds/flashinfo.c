/**
 * @file
 * @brief Reads flash info.
 *
 * @date 14.07.09
 * @author Alexandr Batyukov
 */

#include <embox/cmd.h>
#include <getopt.h>
#include <drivers/flash_template.h>
#include <drivers/flash_if.h>
//#include <fs/mbfs.h>  // mbfs_format_flash
#include <drivers/flash_drv_wrap.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: flashinfo [-h] [-i;f;u;a;e;l;s;r;w]\n");
}

static int showdevinfo(void) {
	return 0;
}

static int exec(int argc, char **argv) {
	int opt;
	getopt_init();
	do {
		opt = getopt(argc, argv, "hi");
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		case 'i':
			showdevinfo();
			return 0;
		case -1:
			break;
		default:
			return 0;
		}
	} while (-1 != opt);

	return 0;
}

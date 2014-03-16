/**
 * @file
 *
 * @date 15.10.10
 * @author Nikolay Korotky
 */

#include <embox/cmd.h>
#include <unistd.h>
#include <stdio.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: version [-h]\n");
}

static int exec(int argc, char **argv) {
#ifdef CONFIG_SVN_REV
	unsigned int rev = CONFIG_SVN_REV;
#endif
	int opt;
	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "h"))) {
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		default:
			return 0;
		}
	}

			printf("\n");
	        printf(" _____                      ______     __\n");
	        printf("|__  /__ _ _ __ _   _  __ _|  _ \\ \\   / /\n");
	        printf("  / // _` | '__| | | |/ _` | |_) \\ \\ / / \n");
	        printf(" / /| (_| | |  | |_| | (_| |  _ < \\ V /  \n");
	        printf("/____\\__,_|_|   \\__, |\\__,_|_| \\_\\ \\_/\n");
	        printf("                |___/      				 \n");
	        printf("\n");

	printf("Date: %12s\n", __DATE__);
	printf("Time: %9s\n", __TIME__);
	printf("Compiler: %s\n", __VERSION__);
#ifdef CONFIG_SVN_REV
	printf("Revision: r%d\n", rev);
#endif
	return 0;
}

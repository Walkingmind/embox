/**
 * @file
 * @brief
 *
 * @date 21.11.2012
 * @author Anton Bulychev
 */

#include <embox/cmd.h>

#include <getopt.h>

#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <kernel/task.h>

EMBOX_CMD(exec);

static void *new_task_entry(void *file);

static int exec(int argc, char **argv) {
	char *filename = malloc(strlen(argv[argc-1]));
	strcpy(filename, argv[argc - 1]);
	return new_task(new_task_entry, filename);
}

extern int elf_exec(char *filename);

static void *new_task_entry(void *filename) {
	char s_filename[255];
	strcpy(s_filename, filename);
	free(filename);

	elf_exec(s_filename);

	return NULL;
}

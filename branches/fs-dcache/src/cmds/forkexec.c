/**
 * @file
 * @brief
 *
 * @date 21.11.2012
 * @author Anton Bulychev
 */

#include <embox/cmd.h>

#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include <kernel/task.h>

EMBOX_CMD(exec);

static void *new_task_entry(void *file);

static int exec(int argc, char **argv) {
	char *filename;
	int pid;

	filename = malloc(strlen(argv[argc-1]));
	strcpy(filename, argv[argc - 1]);
	pid = new_task(filename, new_task_entry, filename);

	task_waitpid(pid);

	free(filename);

	return 0;
}

extern int execve_syscall(const char *filename, char *const argv[], char *const envp[]);

static void *new_task_entry(void *filename) {
	char *argv[2] = {filename, NULL};
	char *envp[1] = {NULL};

	execve_syscall(filename, argv, envp);

	return NULL;
}

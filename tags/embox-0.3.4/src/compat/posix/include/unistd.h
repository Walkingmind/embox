/**
 * @file
 * @brief POSIX Standard: 2.10 Symbolic Constants.
 * @details This file defines miscellaneous symbolic constants and types,
 *        and declares miscellaneous function. Now only sleep functions.
 *
 * @date 24.11.09
 * @author Anton Bondarev
 */

#ifndef COMPAT_POSIX_UNISTD_H_
#define COMPAT_POSIX_UNISTD_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/cdefs.h>

#include <posix_environ.h>

#include <kernel/task.h>

__BEGIN_DECLS

/* Standard file descriptors. */
#define STDIN_FILENO    0   /* Standard input. */
#define STDOUT_FILENO   1   /* Standard output. */
#define STDERR_FILENO   2   /* Standard error output. */

/* Values for the WHENCE argument to lseek. */
#define SEEK_SET        0   /* Seek from beginning of file. */
#define SEEK_CUR        1   /* Seek from current position. */
#define SEEK_END        2   /* Seek from end of file. */

/**
 * suspend execution for an interval of time
 * @param seconds interval in seconds
 * @return 0 if time has elapsed if was error then return -1
 */
extern int sleep(unsigned int seconds);

/**
 * suspend execution for an interval of time
 * @param useconds interval in microseconds
 * @return 0 if time has elapsed if was error then return -1
 */
extern int usleep(useconds_t useconds);

extern ssize_t write(int fd, const void *buf, size_t nbyte);

extern ssize_t read(int fd, void *buf, size_t nbyte);

extern off_t lseek(int fd, off_t offset, int origin);

extern int close(int fd);

extern int fsync(int);

extern pid_t fork(void);

extern int nice(int incr);

extern int execv(const char *path, char *const argv[]);
extern int execve(const char *filename, char *const argv[], char *const envp[]);

extern int unlink(const char *pathname);

extern int rmdir(const char *pathname);

static inline pid_t getpid(void) {
	return task_getid();
}

extern int isatty(int fd);

extern int dup(int flides);
extern int dup2(int flides, int flides2);

extern int pipe(int pipefd[2]/*, int flags: O_NONBLOCK */);
extern void _exit(int status);

extern uid_t getuid(void);
extern uid_t geteuid(void);

extern uid_t getgid(void);
extern uid_t getegid(void);

extern int setreuid(uid_t ruid, uid_t euid);
extern int setuid(uid_t uid);
extern int seteuid(uid_t uid);

extern int setregid(gid_t rgid, gid_t egid);
extern int setgid(gid_t gid);
extern int setegid(gid_t gid);

extern int truncate(const char *path, off_t length);
extern int ftruncate(int fd, off_t length);

extern char * getcwd(char *buff, size_t size);
extern int chdir(const char *path);

#define R_OK 4
#define W_OK 2
#define X_OK 1
#define F_OK 0
static inline int access(const char *path, int amode) { return 0; }

/**
 * @param argc is the number of arguments on cmdline
 * @param argv is the pointer to array of cmdline arguments
 * @param opts is the string of all valid options
 * each char case must be given; options taking an arg are followed by = ':'
 */
extern int getopt(int argc, char **argv, const char *opts);

extern char *optarg; /**< argument to optopt */
extern int optind;   /**< last touched cmdline argument */
extern int optopt;   /**< last returned option */
extern int opterr;   /**< flag:error message on unrecognzed options */

/** setup optind and opterr */
extern void getopt_init(void); /* TODO remove this */

#ifndef environ
/**
 * FIXME environ MUST have follow declaration:
 * but then how to do it different for all tasks
 */
extern char **environ;
#endif

#define PASS_MAX 32
extern char *getpass(const char *prompt);

int gethostname(char *name, size_t len);

__END_DECLS

#endif /* COMPAT_POSIX_UNISTD_H_ */
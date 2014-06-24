/*
 * ntfs-3g_embox_compat.h
 *
 *  Created on: 02 juillet 2013
 *      Author: fsulima
 */

#ifndef QPID_EMBOX_COMPAT_H_
#define QPID_EMBOX_COMPAT_H_


#ifdef linux
#undef linux
#endif

#ifdef __linux__
#undef __linux__
#endif

#include <stdio.h>
#include <string.h>
#include <time.h>

#if 1
#define DPRINT() printf(">>> qpid CALL %s\n", __FUNCTION__)
#else
#define DPRINT()
#endif

#include <ctype.h>
//extern int toupper(int c);

#include <pthread.h>

#include <errno.h>

__BEGIN_DECLS

static inline int pthread_rwlock_destroy(pthread_rwlock_t *rwlock) {
	(void)rwlock;
	DPRINT();
	return -ENOSYS;
}

static inline int pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr) {
	(void)rwlock;
	(void)attr;
	DPRINT();
	return -ENOSYS;
}

static inline int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock) {
	(void)rwlock;
	return -ENOSYS;
}

static inline int pthread_rwlock_unlock(pthread_rwlock_t *rwlock) {
	(void)rwlock;
	DPRINT();
	return -ENOSYS;
}

static inline int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock) {
	(void)rwlock;
	DPRINT();
	return -ENOSYS;
}

static inline int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock) {
	(void)rwlock;
	DPRINT();
	return -ENOSYS;
}

static inline int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock) {
	(void)rwlock;
	DPRINT();
	return -ENOSYS;
}

static inline
int alphasort(const struct dirent **a, const struct dirent **b) {
	(void)a;
	(void)b;
	DPRINT();
	return 0;
}
static inline
int scandir(const char *dirp, struct dirent ***namelist,
              int (*filter)(const struct dirent *),
              int (*compar)(const struct dirent **, const struct dirent **)) {
	(void)dirp;
	(void)namelist;
	(void)filter;
	(void)compar;
	DPRINT();
	errno = ENOMEM;
	return -1;
}

#define O_NOFOLLOW 0
#define F_TLOCK 1
#define F_ULOCK 2
static inline
int lockf(int fd, int cmd, off_t len) {
	(void)fd;
	(void)cmd;
	(void)len;
	DPRINT();
	errno = ENOLCK;
	return -1;
}

static inline
pid_t fork() {
	printf(">>> fork()\n");
	errno = ENOSYS;
	return -1;
}

#include <sys/mman.h>


#define MS_ASYNC 1
static inline
int msync(void *addr, size_t length, int flags) {
	(void)addr;
	(void)length;
	(void)flags;
	printf(">>> msync(%p)\n",addr);
	errno = ENOMEM;
	return -1;
}

static inline
int socketpair(int domain, int type, int protocol, int sv[2]) {
	(void)domain;
	(void)type;
	(void)protocol;
	(void)sv;
	DPRINT();
	errno = -EPROTONOSUPPORT;
	return -1;
}
__END_DECLS

#include <netinet/in.h>

#define IPV6_V6ONLY 0
#define TCP_NODELAY 0

#define NI_MAXHOST	1025
#define NI_MAXSERV	32

#include <arpa/inet.h>

static inline
char *strerror_r(int errnum, char *buf, size_t buflen) {
	(void)errnum;
	(void)buf;
	(void)buflen;
	DPRINT();
	return strerror(errnum);
}

#include <sys/types.h>
#include <unistd.h>

static inline
pid_t getppid(void) {
	DPRINT();
	return 0;
}

typedef unsigned int uint;

#define SIG_SETMASK 2

#include <signal.h>
static inline
int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset) {
	(void)how;
	(void)set;
	(void)oldset;
	DPRINT();
	return 0;
}

static inline pid_t setsid(void) {
	DPRINT();
	return -1;
}

#define __thread

#ifdef __cplusplus

#endif // __cplusplus

#endif /* QPID_EMBOX_COMPAT_H_ */

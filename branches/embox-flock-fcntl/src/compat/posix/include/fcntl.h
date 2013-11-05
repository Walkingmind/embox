/**
 * @file
 *
 * @brief
 *
 * @date 07.09.2011
 * @author Anton Bondarev
 */

#ifndef FCNTL_H_
#define FCNTL_H_

#include <sys/stat.h>
#include <sys/cdefs.h>

#include <stdio.h>

#undef TRACE_FS

#ifdef TRACE_FS
#define DPRINTF(a)	printf a
#else
#define DPRINTF(a)	do {} while (0)
#endif

__BEGIN_DECLS

/* int open (const char *path, int __oflag);
 * int open (const char *path, int __oflag, mode_t mode);
 */
extern int open(const char *path, int __oflag, ...);

/*
 * shall be equivalent to: open(path, O_WRONLY|O_CREAT|O_TRUNC, mode)
 */
extern int creat(const char *pathname, mode_t mode);

extern int fcntl(int fd, int cmd, ...);

/* fcntl commands */
#define F_GETFD            0
#define F_SETFD            1
#define F_GETPIPE_SZ       2
#define F_SETPIPE_SZ       3

#define F_GETFL     F_GETFD
#define F_SETFL     F_SETFD

#define F_GETLK            4 /* Get record locking information. */
#define F_SETLK            5 /* Set record locking information. */
#define F_SETLKW           6 /* Set record locking information; wait if blocked. */

/* Values for l_type used for record locking with fcntl() (the following values are unique) are as follows: */
#define F_RDLCK            7 /* Shared or read lock. */
#define F_UNLCK            8 /* Unlock. */
#define F_WRLCK            9 /* Exclusive or write lock. */

/* fcntl flags */
#define O_RDONLY           0x0000  /* Open for reading only */
#define O_WRONLY           0x0001  /* Open for writing only */
#define O_RDWR             0x0002  /* Open for reading and writing */
#define O_SPECIAL          0x0004  /* Open for special access */
#define O_APPEND           0x0008  /* Writes done at EOF */

#define O_CREAT            0x0100  /* Create and open file */
#define O_TRUNC            0x0200  /* Truncate file */
#define O_EXCL             0x0400  /* Open only if file doesn't already exist */
#define O_DIRECT           0x0800  /* Do not use cache for reads and writes */
#define O_NONBLOCK         0x1000  /* Non-blocking mode */

struct flock {
	short  l_type;   /* Type of lock; F_RDLCK, F_WRLCK, F_UNLCK. */
	short  l_whence; /* Flag for starting offset. */
	off_t  l_start;  /* Relative offset in bytes. */
	off_t  l_len;    /* Size; if 0 then until EOF. */
	pid_t  l_pid;    /* Process ID of the process holding the lock; returned with F_GETLK. */
};

/* Temporary structures, should be moved later */

#include <kernel/thread/sync/mutex.h>
#include <sched.h>
/*
typedef struct kflock_exclusive {
	struct mutex      lock;
	struct dlist_head kflock_link;
	short             whence;
	off_t             start;
	off_t             len;
	pid_t             pid;
} kflock_exclusive_t;

typedef struct kflock_shared {
	struct dlist_head kflock_link;
	short             whence;
	off_t             start;
	off_t             len;
	pid_t             pid;
} kflock_shared_t;

typedef union kflock_both {
	kflock_exclusive_t exlock;
	kflock_shared_t    shlock;
} kflock_both_t;

typedef struct kflock {
	struct dlist_head exlock_list;
	long              exlock_count;
	struct dlist_head shlock_list;
	long              shlock_count;
	spinlock_t        flock_guard;
} kflock_t;
*/

typedef struct kflock_lock {
	/*short             type;
	short             whence;
	off_t             start;
	off_t             len;
	pid_t             pid;*/
	struct flock      flock;
	struct dlist_head kflock_link;
	struct wait_queue wq;
} kflock_lock_t;

typedef struct kflock {
	struct dlist_head locks;
	spinlock_t        kflock_guard;
} kflock_t;

/* Remove till here */
__END_DECLS

#endif /* FCNTL_H_ */

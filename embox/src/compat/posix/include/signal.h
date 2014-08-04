/**
 * @file
 *
 * @brief
 *
 * @date 15.05.2012
 * @author Anton Bondarev
 */

#ifndef SIGNAL_H_
#define SIGNAL_H_

#include <errno.h>
#include <sys/types.h>
#include <util/bitmap.h>
#include <sys/cdefs.h>

#define SIG_DFL ((sighandler_t) 0x1)
#define SIG_IGN ((sighandler_t) 0x3)
#define SIG_ERR ((sighandler_t) 0x5)

/* Signals.  */
#define SIGHUP      1       /* (POSIX)    Hangup.  */
#define SIGINT      2       /* (ANSI)     Interrupt.  */
#define SIGQUIT     3       /* (POSIX)    Quit.  */
#define SIGILL      4       /* (ANSI)     Illegal instruction.  */
#define SIGTRAP     5       /* (POSIX)    Trace trap.  */
#define SIGABRT     6       /* (ANSI)     Abort.  */
#define SIGIOT      6       /* (4.2 BSD)  IOT trap.  */
#define SIGBUS      7       /* (4.2 BSD)  BUS error.  */
#define SIGFPE      8       /* (ANSI)     Floating-point exception.  */
#define SIGKILL     9       /* (POSIX)    Kill, unblockable.  */
#define SIGUSR1     10      /* (POSIX)    User-defined signal 1.  */
#define SIGSEGV     11      /* (ANSI)     Segmentation violation.  */
#define SIGUSR2     12      /* (POSIX)    User-defined signal 2.  */
#define SIGPIPE     13      /* (POSIX)    Broken pipe.  */
#define SIGALRM     14      /* (POSIX)    Alarm clock.  */
#define SIGTERM     15      /* (ANSI)     Termination.  */
#define SIGSTKFLT   16      /*            Stack fault.  */
#define SIGCLD      SIGCHLD /* (System V) Same as SIGCHLD.  */
#define SIGCHLD     17      /* (POSIX)    Child status has changed.  */
#define SIGCONT     18      /* (POSIX)    Continue.  */
#define SIGSTOP     19      /* (POSIX)    Stop, unblockable.  */
#define SIGTSTP     20      /* (POSIX)    Keyboard stop.  */
#define SIGTTIN     21      /* (POSIX)    Background read from tty.  */
#define SIGTTOU     22      /* (POSIX)    Background write to tty.  */
#define SIGURG      23      /* (4.2 BSD)  Urgent condition on socket.  */
#define SIGXCPU     24      /* (4.2 BSD)  CPU limit exceeded.  */
#define SIGXFSZ     25      /* (4.2 BSD)  File size limit exceeded.  */
#define SIGVTALRM   26      /* (4.2 BSD)  Virtual alarm clock.  */
#define SIGPROF     27      /* (4.2 BSD)  Profiling alarm clock.  */
#define SIGWINCH    28      /* (4.3 BSD, Sun) Window size change.  */
#define SIGPOLL     SIGIO   /* (System V) Pollable event occurred.  */
#define SIGIO       29      /* (4.2 BSD)  I/O now possible.  */
#define SIGPWR      30      /* (System V) Power failure restart.  */
#define SIGSYS      31      /*            Bad system call.  */
#define SIGUNUSED   31

#define SIGRTMIN    32
#define SIGRTMAX    63

#define _SIG_TOTAL  64

#define SA_NOCLDSTOP  (0x1ul << 0)
#define SA_NOCLDWAIT  (0x1ul << 1)
#define SA_SIGINFO    (0x1ul << 2)
#define SA_ONSTACK    (0x1ul << 3)
#define SA_RESTART    (0x1ul << 4)
#define SA_NODEFER    (0x1ul << 5)
#define SA_RESETHAND  (0x1ul << 6)

__BEGIN_DECLS

typedef int sig_atomic_t;

#define NSIG _SIG_TOTAL
typedef struct {
	BITMAP_DECL(bitmap, _SIG_TOTAL);
} sigset_t;

union sigval {
	int   sival_int;
	void *sival_ptr;
};

typedef struct {
	int           si_signo;
	int           si_code;
	union sigval  si_value;
	int           si_errno;
	pid_t         si_pid;
	uid_t         si_uid;
	void         *si_addr;
	int           si_status;
	int           si_band;
} siginfo_t;

struct sigaction {
	int        sa_flags;
	sigset_t   sa_mask;
	/* The storage occupied by sa_handler and sa_sigaction may overlap,
	 * and a conforming application shall not use both simultaneously.  */
	union {
		void (*sa_handler)(int);
		void (*sa_sigaction)(int, siginfo_t *, void *);
	} /* unnamed */;
};

// TODO Consider moving the following two types into ucontext.h -- Eldar

typedef int mcontext_t; // XXX stub

typedef struct {
	void     *ss_sp;       /* stack base or pointer */
	size_t    ss_size;     /* stack size */
	int       ss_flags;    /* flags */
} stack_t;

struct _ucontext {
	struct _ucontext *uc_link;     /* resumed when this context returns */
	sigset_t    uc_sigmask;  /* blocked when this context is active */
	stack_t     uc_stack;    /* the stack used by this context */
	mcontext_t  uc_mcontext; /* machine-specific representation */
};
typedef struct _ucontext ucontext_t;

/* Non-standard GNU extension. */
typedef void (*sighandler_t)(int);

extern int sigemptyset(sigset_t *);
extern int sigfillset(sigset_t *);
extern int sigismember(const sigset_t *, int signo);
extern int sigaddset(sigset_t *, int signo);
extern int sigdelset(sigset_t *, int signo);

#define SIG_BLOCK   0
#define SIG_SETMASK 1
#define SIG_UNBLOCK 1
static inline int sigprocmask(int how, const sigset_t *set, sigset_t *oldset) {
	(void)how; (void)set; (void)oldset;
	return -ENOSYS;
}

extern sighandler_t signal(int signo, sighandler_t fn);
extern int sigaction(int signo, const struct sigaction * /*restrict*/ act,
		struct sigaction * /*restrict*/ oact);

extern int kill(int tid, int signo);
extern int sigqueue(int tid, int signo, const union sigval value);
extern int raise(int signo);

//static inline int sigaction(int sig, const struct sigaction *act,
		//struct sigaction *oact) { return -1; }
//static inline int sigfillset(sigset_t *set)

extern const char *const sys_siglist[];

#define MINSIGSTKSZ	2048
extern int sigaltstack(const stack_t *ss, stack_t *oss);

__END_DECLS

#endif /* SIGNAL_H_ */

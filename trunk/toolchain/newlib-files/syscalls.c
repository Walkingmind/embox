#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>

char *__env[1] = { 0 };
char **environ = __env;

#define NR_exit      1
#define NR_fork      2
#define NR_read      3
#define NR_write     4
#define NR_open      5
#define NR_close     6
#define NR_waitpid   7
#define NR_link      9
#define NR_unlink    10
#define NR_execve    11
#define NR_lseek     19
#define NR_getpid    20
#define NR_kill      37
#define NR_times     43
#define NR_brk       45
#define NR_stat      106
#define NR_fstat     108

#define __syscall_return(type, res) \
do { \
        if ((unsigned long)(res) >= (unsigned long)(-(128 + 1))) { \
                errno = -(res); \
                res = -1; \
        } \
        return (type) (res); \
} while (0)

#define _syscall0(NR,type,name) \
type name(void) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
         : "=a" (__res) \
         : "0" (NR)); \
__syscall_return(type,__res); \
}

#define _syscall1(NR,type,name,type1,arg1) \
type name(type1 arg1) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
        : "=a" (__res) \
        : "0" (NR),"b" ((long)(arg1))); \
__syscall_return(type,__res); \
}

#define _syscall2(NR,type,name,type1,arg1,type2,arg2) \
type name(type1 arg1,type2 arg2) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
        : "=a" (__res) \
        : "0" (NR),"b" ((long)(arg1)),"c" ((long)(arg2))); \
__syscall_return(type,__res); \
}

#define _syscall3(NR,type,name,type1,arg1,type2,arg2,type3,arg3) \
type name(type1 arg1,type2 arg2,type3 arg3) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
        : "=a" (__res) \
        : "0" (NR),"b" ((long)(arg1)),"c" ((long)(arg2)), \
                  "d" ((long)(arg3))); \
__syscall_return(type,__res); \
}

#define _syscall4(NR,type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4) \
type name (type1 arg1, type2 arg2, type3 arg3, type4 arg4) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
        : "=a" (__res) \
        : "0" (NR),"b" ((long)(arg1)),"c" ((long)(arg2)), \
          "d" ((long)(arg3)),"S" ((long)(arg4))); \
__syscall_return(type,__res); \
} 

#define _syscall5(NR,type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, \
          type5,arg5) \
type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
        : "=a" (__res) \
        : "0" (NR),"b" ((long)(arg1)),"c" ((long)(arg2)), \
          "d" ((long)(arg3)),"S" ((long)(arg4)),"D" ((long)(arg5))); \
__syscall_return(type,__res); \
}

#define _syscall6(NR,type,name,type1,arg1,type2,arg2,type3,arg3,type4,arg4, \
          type5,arg5,type6,arg6) \
type name (type1 arg1,type2 arg2,type3 arg3,type4 arg4,type5 arg5,type6 arg6) \
{ \
long __res; \
__asm__ volatile ("push %%ebp ; movl %%eax,%%ebp ; movl %1,%%eax ; int $0x80 ; pop %%ebp" \
        : "=a" (__res) \
        : "i" (NR),"b" ((long)(arg1)),"c" ((long)(arg2)), \
          "d" ((long)(arg3)),"S" ((long)(arg4)),"D" ((long)(arg5)), \
          "" ((long)(arg6))); \
__syscall_return(type,__res); \
}

_syscall0(NR_exit,void,_exit);
_syscall3(NR_write,int,write,int,file,char *,ptr,int,len);
_syscall1(NR_brk,void *,__brk,void *,end_data_segment);
_syscall2(NR_fstat,int,fstat,int,file,struct stat *,st);
_syscall3(NR_execve,int,execve,char *,name,char **,argv,char **,env);
_syscall0(NR_fork,int,fork);
_syscall1(NR_close,int,close,int,file);
_syscall0(NR_getpid,int,getpid);
_syscall2(NR_kill,int,kill,int,pid,int,sig);
_syscall2(NR_link,int,link,char *,old,char *,new);
_syscall3(NR_lseek,int,lseek,int,file,int,ptr,int,dir);
_syscall3(NR_read,int,read,int,file,char *,ptr,int,len);
_syscall2(NR_stat,int,stat,const char *,file,struct stat *,st);
_syscall1(NR_times,clock_t,times,struct tms *,buf)
_syscall1(NR_unlink,int,unlink,char *,name);
_syscall3(NR_waitpid,int,waitpid,int,pid,int *,status,int,options);
//_syscall3(NR_open,int,open,const char *,name,int,flags,int,mode);

int open(const char *name, int flags, ...) {
	return -1;
}

int isatty(int file) {
	return 1;
}

static char *curr_brk = NULL;

void *sbrk(int increment) {
        char *old_brk,*new_brk;

        if (!curr_brk) curr_brk = __brk(NULL);
        new_brk = __brk(curr_brk+increment);
        if (new_brk != curr_brk+increment) {
                errno = ENOMEM;
                return (void *) -1;
        }
        old_brk = curr_brk;
        curr_brk = new_brk;
        return old_brk;
}

int wait(int *status) {
	return waitpid(-1, status, 0);
}


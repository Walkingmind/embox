# 1 "deflate.c"
# 1 "/home/user/workspace/embox/third-party/lib/zlib-1.2.8//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "deflate.c"
# 52 "deflate.c"
# 1 "deflate.h" 1
# 16 "deflate.h"
# 1 "zutil.h" 1
# 22 "zutil.h"
# 1 "zlib.h" 1
# 34 "zlib.h"
# 1 "zconf.h" 1
# 368 "zconf.h"
typedef unsigned char Byte;

typedef unsigned int uInt;
typedef unsigned long uLong;





   typedef Byte Bytef;

typedef char charf;
typedef int intf;
typedef uInt uIntf;
typedef uLong uLongf;


   typedef void const *voidpc;
   typedef void *voidpf;
   typedef void *voidp;







# 1 "/home/user/workspace/embox/./src/include/limits.h" 1
# 396 "zconf.h" 2
# 406 "zconf.h"
   typedef unsigned z_crc_t;
# 421 "zconf.h"
# 1 "/home/user/workspace/embox/./src/compat/posix/include/sys/types.h" 1
# 14 "/home/user/workspace/embox/./src/compat/posix/include/sys/types.h"
# 1 "/home/user/workspace/embox/./src/arch/x86/include/asm/types.h" 1
# 12 "/home/user/workspace/embox/./src/arch/x86/include/asm/types.h"
# 1 "/home/user/workspace/embox/./src/include/asm-generic/types32.h" 1
# 16 "/home/user/workspace/embox/./src/include/asm-generic/types32.h"
typedef signed char __s8;
typedef unsigned char __u8;
typedef signed short __s16;
typedef unsigned short __u16;
typedef signed int __s32;
typedef unsigned int __u32;
typedef long long __s64;
typedef unsigned long long __u64;
# 32 "/home/user/workspace/embox/./src/include/asm-generic/types32.h"
typedef unsigned int __size_t;
typedef signed int __ptrdiff_t;
# 13 "/home/user/workspace/embox/./src/arch/x86/include/asm/types.h" 2
# 15 "/home/user/workspace/embox/./src/compat/posix/include/sys/types.h" 2



typedef unsigned int size_t;






typedef int ssize_t;


typedef unsigned long clock_t;


typedef unsigned long useconds_t;


typedef long suseconds_t;

typedef unsigned long spinlock_t;

typedef __u32 gfp_t;

typedef struct {
 volatile int counter;
} atomic_t;

typedef long time_t;

typedef int id_t;

typedef int pid_t;

typedef int dev_t;

typedef int clockid_t;

typedef unsigned int ino_t;

typedef unsigned short nlink_t;

typedef unsigned int mode_t;

typedef unsigned short uid_t;
typedef unsigned short gid_t;

typedef unsigned int blkno_t;

typedef int off_t;

typedef long long loff_t;

typedef unsigned long fsblkcnt_t;
typedef unsigned long fsfilcnt_t;
# 422 "zconf.h" 2





# 1 "/home/user/workspace/embox/./src/include/stdarg.h" 1
# 45 "/home/user/workspace/embox/./src/include/stdarg.h"
typedef __builtin_va_list va_list;
# 428 "zconf.h" 2
# 452 "zconf.h"
# 1 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h" 1
# 15 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h"
# 1 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h" 1
# 13 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h"
# 1 "/home/user/workspace/embox/./src/include/sys/cdefs.h" 1
# 14 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h" 2



# 82 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h"
typedef struct stat {
 int st_dev;
 int st_ino;
 int st_mode;
 int st_nlink;
 int st_uid;
 int st_gid;
 int st_rdev;
 size_t st_size;
 size_t st_blksize;
 int st_blocks;
 unsigned st_atime;
 unsigned st_mtime;
 unsigned st_ctime;
} stat_t;
# 114 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h"
static inline int chmod(const char *path, mode_t mode) {
 return -1;
}

extern int stat(const char *, struct stat *);
extern int lstat(const char *, struct stat *);
extern int fstat(int fd, struct stat *);
extern int mkfifo(const char *, mode_t);
extern int mknod(const char *, mode_t, dev_t);
extern int mkdir (const char *, mode_t );
static inline mode_t umask(mode_t mode) {
 return 0;
}


# 16 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h" 2


# 1 "/home/user/workspace/embox/./src/compat/posix/include/posix_environ.h" 1
# 12 "/home/user/workspace/embox/./src/compat/posix/include/posix_environ.h"
# 1 "/home/user/workspace/embox/./src/include/kernel/task/env.h" 1
# 12 "/home/user/workspace/embox/./src/include/kernel/task/env.h"
# 1 "/home/user/workspace/embox/./src/include/framework/mod/options.h" 1
# 13 "/home/user/workspace/embox/./src/include/framework/mod/options.h"
# 1 "/home/user/workspace/embox/./src/include/util/macro.h" 1
# 14 "/home/user/workspace/embox/./src/include/framework/mod/options.h" 2
# 13 "/home/user/workspace/embox/./src/include/kernel/task/env.h" 2
# 1 "/home/user/workspace/embox/./src/include/stddef.h" 1
# 40 "/home/user/workspace/embox/./src/include/stddef.h"
typedef unsigned short wchar_t;





typedef __ptrdiff_t ptrdiff_t;
# 14 "/home/user/workspace/embox/./src/include/kernel/task/env.h" 2


# 1 "/home/user/workspace/embox/./src/include/kernel/task.h" 1
# 12 "/home/user/workspace/embox/./src/include/kernel/task.h"
# 1 "/home/user/workspace/embox/./src/include/util/dlist.h" 1
# 20 "/home/user/workspace/embox/./src/include/util/dlist.h"
# 1 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/util/DList.h" 1






# 1 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h" 1
# 22 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
# 1 "/home/user/workspace/embox/./src/include/assert.h" 1
# 14 "/home/user/workspace/embox/./src/include/assert.h"
# 1 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/lib/LibCDiagnostic.h" 1






# 1 "/home/user/workspace/embox/./src/include/../lib/assert_impl.h" 1
# 12 "/home/user/workspace/embox/./src/include/../lib/assert_impl.h"
# 1 "/home/user/workspace/embox/./src/include/util/location.h" 1
# 13 "/home/user/workspace/embox/./src/include/util/location.h"
struct location {
 const char *file;
 int line;
};

struct location_func {
 struct location at;
 const char *func;
};
# 13 "/home/user/workspace/embox/./src/include/../lib/assert_impl.h" 2
# 1 "/home/user/workspace/embox/./src/compat/linux/include/linux/compiler.h" 1
# 14 "/home/user/workspace/embox/./src/include/../lib/assert_impl.h" 2
# 31 "/home/user/workspace/embox/./src/include/../lib/assert_impl.h"
struct __assertion_point {
 struct location_func location;
 const char *expression;
};




extern

void __attribute__ ((noreturn)) __assertion_handle_failure(
  const struct __assertion_point *point);
# 8 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/lib/LibCDiagnostic.h" 2
# 15 "/home/user/workspace/embox/./src/include/assert.h" 2
# 23 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h" 2






struct dlist_head {
 struct dlist_head *next;
 struct dlist_head *prev;




 struct dlist_head *list_id;
};





static inline void __dlist_add(struct dlist_head *_new, struct dlist_head *next,
  struct dlist_head *prev) {
 _new->prev = prev;
 _new->next = next;
 next->prev = _new;
 prev->next = _new;
}




static inline int __is_linked(struct dlist_head *head) {
 return (((void *)0) != head->list_id);
}





static inline struct dlist_head *dlist_head_init(struct dlist_head *head) {
 head->next = head->prev = head;
 head->list_id = (struct dlist_head *)((void *)0);

 return head;
}
# 77 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
static inline struct dlist_head *dlist_init(struct dlist_head *list_head) {

 list_head->list_id = list_head;
 list_head->next = list_head->prev = list_head;

 return list_head;
}
# 92 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
static inline void dlist_add_next(struct dlist_head *_new,
  struct dlist_head *list) {


 ({do { if (!((__builtin_constant_p(!__is_linked(_new)) ? !!(!__is_linked(_new)) : __builtin_expect(!!(!__is_linked(_new)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/user/workspace/embox/./src/include/../util/dlist_debug.h", .line = 96, }, .func = __func__, }, .expression = "!__is_linked(_new)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});



 ({do { if (!((__builtin_constant_p(__is_linked(list)) ? !!(__is_linked(list)) : __builtin_expect(!!(__is_linked(list)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/user/workspace/embox/./src/include/../util/dlist_debug.h", .line = 100, }, .func = __func__, }, .expression = "__is_linked(list)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});

 _new->list_id = list->list_id;





 __dlist_add(_new, list->next, list);
}
# 119 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
static inline void dlist_add_prev(struct dlist_head *_new,
  struct dlist_head *list) {


 ({do { if (!((__builtin_constant_p(!__is_linked(_new)) ? !!(!__is_linked(_new)) : __builtin_expect(!!(!__is_linked(_new)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/user/workspace/embox/./src/include/../util/dlist_debug.h", .line = 123, }, .func = __func__, }, .expression = "!__is_linked(_new)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});



 ({do { if (!((__builtin_constant_p(__is_linked(list)) ? !!(__is_linked(list)) : __builtin_expect(!!(__is_linked(list)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/user/workspace/embox/./src/include/../util/dlist_debug.h", .line = 127, }, .func = __func__, }, .expression = "__is_linked(list)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});

 _new->list_id = list->list_id;





 __dlist_add(_new, list, list->prev);
}
# 145 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
static inline void dlist_del(struct dlist_head *head) {
 ({do { if (!((__builtin_constant_p(__is_linked(head)) ? !!(__is_linked(head)) : __builtin_expect(!!(__is_linked(head)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/user/workspace/embox/./src/include/../util/dlist_debug.h", .line = 146, }, .func = __func__, }, .expression = "__is_linked(head)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});




 head->prev->next = head->next;
 head->next->prev = head->prev;

 head->list_id = (struct dlist_head *)((void *)0);
}
# 8 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/util/DList.h" 2
# 21 "/home/user/workspace/embox/./src/include/util/dlist.h" 2






struct dlist_head;
# 60 "/home/user/workspace/embox/./src/include/util/dlist.h"
extern struct dlist_head *dlist_init(struct dlist_head *list_head);
# 73 "/home/user/workspace/embox/./src/include/util/dlist.h"
extern struct dlist_head *dlist_head_init(struct dlist_head *item_head);
# 84 "/home/user/workspace/embox/./src/include/util/dlist.h"
extern void dlist_add_next(struct dlist_head *_new, struct dlist_head *list);
# 94 "/home/user/workspace/embox/./src/include/util/dlist.h"
extern void dlist_add_prev(struct dlist_head *_new, struct dlist_head *list);







extern void dlist_del(struct dlist_head *item_head);







static inline void dlist_move(struct dlist_head *head, struct dlist_head *list) {
 dlist_del(head);
 dlist_add_next(head, list);
}







static inline int dlist_empty(struct dlist_head *head) {
 return head == head->next;
}
# 13 "/home/user/workspace/embox/./src/include/kernel/task.h" 2
# 1 "/home/user/workspace/embox/./src/include/util/array.h" 1
# 34 "/home/user/workspace/embox/./src/include/util/array.h"
# 1 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/util/Array.h" 1






# 1 "/home/user/workspace/embox/./src/include/../util/array_impl.h" 1
# 8 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/util/Array.h" 2
# 35 "/home/user/workspace/embox/./src/include/util/array.h" 2
# 14 "/home/user/workspace/embox/./src/include/kernel/task.h" 2




# 1 "/home/user/workspace/embox/./src/include/kernel/task/task_priority.h" 1
# 18 "/home/user/workspace/embox/./src/include/kernel/task/task_priority.h"
typedef short task_priority_t;
# 19 "/home/user/workspace/embox/./src/include/kernel/task.h" 2







struct task_signal_table;
struct task_idx_table;
struct thread;
struct emmap;
struct task_u_area;
struct task_env;





struct task {
 struct dlist_head task_link;

 int tid;

 char task_name[20];

 struct task *parent;

 struct dlist_head children_tasks;

 struct thread *main_thread;

 struct task_idx_table *idx_table;

 struct task_signal_table *signal_table;

 struct emmap *mmap;



 struct task_u_area *u_area;

 struct task_env *env;

 task_priority_t priority;

 void *security;

 int err;

 clock_t per_cpu;

 struct wait_queue *waitq;

 unsigned int affinity;
};

struct task_resource_desc {
 void (*init)(struct task *task, void *resource_space);
 int (*inherit)(struct task *task, struct task *parent_task);
 void (*deinit)(struct task *task);
 size_t resource_size;
};

typedef int (*task_notifing_resource_hnd)(struct thread *prev, struct thread *next);

extern const struct task_resource_desc *task_resource_desc_array[];

extern const task_notifing_resource_hnd task_notifing_resource[];
# 100 "/home/user/workspace/embox/./src/include/kernel/task.h"
static inline struct task_idx_table *task_idx_table(struct task *task) {
 return task->idx_table;
}


extern int new_task(const char *name, void *(*run)(void *), void *arg);


extern int task_add_thread(struct task *, struct thread *);

extern int task_remove_thread(struct task *, struct thread *);






extern struct task *task_self(void);


static inline int task_getid(void) {
 return task_self()->tid;
}


extern int task_set_priority(struct task *task, task_priority_t priority);


extern task_priority_t task_get_priority(struct task *task);


static inline void task_set_affinity(struct task *task, unsigned int affinity) {
 task->affinity = affinity;
}
static inline unsigned int task_get_affinity(struct task *task) {
 return task->affinity;
}

static inline void *task_self_security(void) {
 return task_self()->security;
}






extern void __attribute__((noreturn)) task_exit(void *res);






extern struct task *task_kernel_task(void);

extern int task_notify_switch(struct thread *prev, struct thread *next);

extern int task_waitpid(pid_t pid);

# 1 "/home/user/workspace/embox/./src/include/kernel/task/task_table.h" 1
# 12 "/home/user/workspace/embox/./src/include/kernel/task/task_table.h"
# 1 "/home/user/workspace/embox/./src/include/kernel/task.h" 1
# 13 "/home/user/workspace/embox/./src/include/kernel/task/task_table.h" 2
# 21 "/home/user/workspace/embox/./src/include/kernel/task/task_table.h"
extern int task_table_add(struct task *task);
# 30 "/home/user/workspace/embox/./src/include/kernel/task/task_table.h"
extern struct task *task_table_get(int n);






extern void task_table_del(int n);






extern int task_table_has_space(void);
# 54 "/home/user/workspace/embox/./src/include/kernel/task/task_table.h"
extern int task_table_get_first(int since);
# 161 "/home/user/workspace/embox/./src/include/kernel/task.h" 2
# 181 "/home/user/workspace/embox/./src/include/kernel/task.h"

# 17 "/home/user/workspace/embox/./src/include/kernel/task/env.h" 2

# 1 "/home/user/workspace/embox/./build/base/src-gen/include/module/embox/kernel/task/env.h" 1
# 19 "/home/user/workspace/embox/./src/include/kernel/task/env.h" 2









struct task_env {
 char **envs;
 size_t next;
 char *vals[8 + 1];
 char storage[8][32];
 char buff[32];
};

static inline struct task_env * task_self_env(void) {
 return task_self()->env;
}

static inline char *** task_self_environ_ptr(void) {
 return &task_self()->env->envs;
}


# 13 "/home/user/workspace/embox/./src/compat/posix/include/posix_environ.h" 2
# 19 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h" 2




# 39 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h"
extern int sleep(unsigned int seconds);






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

extern int pipe(int pipefd[2] );
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





static inline int access(const char *path, int amode) { return 0; }







extern int getopt(int argc, char **argv, const char *opts);

extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;


extern void getopt_init(void);
# 132 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h"
extern char *getpass(const char *prompt);

int gethostname(char *name, size_t len);


# 453 "zconf.h" 2
# 35 "zlib.h" 2
# 80 "zlib.h"
typedef voidpf (*alloc_func) (voidpf opaque, uInt items, uInt size);
typedef void (*free_func) (voidpf opaque, voidpf address);

struct internal_state;

typedef struct z_stream_s {
    Bytef *next_in;
    uInt avail_in;
    uLong total_in;

    Bytef *next_out;
    uInt avail_out;
    uLong total_out;

    char *msg;
    struct internal_state *state;

    alloc_func zalloc;
    free_func zfree;
    voidpf opaque;

    int data_type;
    uLong adler;
    uLong reserved;
} z_stream;

typedef z_stream *z_streamp;





typedef struct gz_header_s {
    int text;
    uLong time;
    int xflags;
    int os;
    Bytef *extra;
    uInt extra_len;
    uInt extra_max;
    Bytef *name;
    uInt name_max;
    Bytef *comment;
    uInt comm_max;
    int hcrc;
    int done;

} gz_header;

typedef gz_header *gz_headerp;
# 216 "zlib.h"
extern const char * zlibVersion (void);
# 246 "zlib.h"
extern int deflate (z_streamp strm, int flush);
# 353 "zlib.h"
extern int deflateEnd (z_streamp strm);
# 392 "zlib.h"
extern int inflate (z_streamp strm, int flush);
# 508 "zlib.h"
extern int inflateEnd (z_streamp strm);
# 587 "zlib.h"
extern int deflateSetDictionary (z_streamp strm, const Bytef *dictionary, uInt dictLength)

                                                               ;
# 631 "zlib.h"
extern int deflateCopy (z_streamp dest, z_streamp source)
                                                      ;
# 649 "zlib.h"
extern int deflateReset (z_streamp strm);
# 660 "zlib.h"
extern int deflateParams (z_streamp strm, int level, int strategy)

                                                    ;
# 681 "zlib.h"
extern int deflateTune (z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain)



                                                   ;
# 698 "zlib.h"
extern uLong deflateBound (z_streamp strm, uLong sourceLen)
                                                        ;
# 713 "zlib.h"
extern int deflatePending (z_streamp strm, unsigned *pending, int *bits)

                                                  ;
# 728 "zlib.h"
extern int deflatePrime (z_streamp strm, int bits, int value)

                                                ;
# 745 "zlib.h"
extern int deflateSetHeader (z_streamp strm, gz_headerp head)
                                                          ;
# 819 "zlib.h"
extern int inflateSetDictionary (z_streamp strm, const Bytef *dictionary, uInt dictLength)

                                                               ;
# 842 "zlib.h"
extern int inflateGetDictionary (z_streamp strm, Bytef *dictionary, uInt *dictLength)

                                                                ;
# 857 "zlib.h"
extern int inflateSync (z_streamp strm);
# 876 "zlib.h"
extern int inflateCopy (z_streamp dest, z_streamp source)
                                                      ;
# 892 "zlib.h"
extern int inflateReset (z_streamp strm);
# 902 "zlib.h"
extern int inflateReset2 (z_streamp strm, int windowBits)
                                                      ;
# 914 "zlib.h"
extern int inflatePrime (z_streamp strm, int bits, int value)

                                                ;
# 935 "zlib.h"
extern long inflateMark (z_streamp strm);
# 963 "zlib.h"
extern int inflateGetHeader (z_streamp strm, gz_headerp head)
                                                          ;
# 1025 "zlib.h"
typedef unsigned (*in_func) (void *, unsigned char * *)
                                                                   ;
typedef int (*out_func) (void *, unsigned char *, unsigned);

extern int inflateBack (z_streamp strm, in_func in, void *in_desc, out_func out, void *out_desc)

                                                                      ;
# 1099 "zlib.h"
extern int inflateBackEnd (z_streamp strm);







extern uLong zlibCompileFlags (void);
# 1160 "zlib.h"
extern int compress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
                                                                       ;
# 1174 "zlib.h"
extern int compress2 (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level)

                                             ;
# 1190 "zlib.h"
extern uLong compressBound (uLong sourceLen);






extern int uncompress (Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen)
                                                                         ;
# 1224 "zlib.h"
typedef struct gzFile_s *gzFile;
# 1264 "zlib.h"
extern gzFile gzdopen (int fd, const char *mode);
# 1287 "zlib.h"
extern int gzbuffer (gzFile file, unsigned size);
# 1304 "zlib.h"
extern int gzsetparams (gzFile file, int level, int strategy);
# 1313 "zlib.h"
extern int gzread (gzFile file, voidp buf, unsigned len);
# 1341 "zlib.h"
extern int gzwrite (gzFile file, voidpc buf, unsigned len)
                                                          ;






extern int gzprintf (gzFile file, const char *format, ...);
# 1364 "zlib.h"
extern int gzputs (gzFile file, const char *s);







extern char * gzgets (gzFile file, char *buf, int len);
# 1385 "zlib.h"
extern int gzputc (gzFile file, int c);





extern int gzgetc (gzFile file);
# 1400 "zlib.h"
extern int gzungetc (int c, gzFile file);
# 1412 "zlib.h"
extern int gzflush (gzFile file, int flush);
# 1447 "zlib.h"
extern int gzrewind (gzFile file);
# 1475 "zlib.h"
extern int gzeof (gzFile file);
# 1490 "zlib.h"
extern int gzdirect (gzFile file);
# 1511 "zlib.h"
extern int gzclose (gzFile file);
# 1524 "zlib.h"
extern int gzclose_r (gzFile file);
extern int gzclose_w (gzFile file);
# 1536 "zlib.h"
extern const char * gzerror (gzFile file, int *errnum);
# 1552 "zlib.h"
extern void gzclearerr (gzFile file);
# 1569 "zlib.h"
extern uLong adler32 (uLong adler, const Bytef *buf, uInt len);
# 1600 "zlib.h"
extern uLong crc32 (uLong crc, const Bytef *buf, uInt len);
# 1633 "zlib.h"
extern int deflateInit_ (z_streamp strm, int level, const char *version, int stream_size)
                                                                           ;
extern int inflateInit_ (z_streamp strm, const char *version, int stream_size)
                                                                           ;
extern int deflateInit2_ (z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size)


                                                       ;
extern int inflateInit2_ (z_streamp strm, int windowBits, const char *version, int stream_size)
                                                                            ;
extern int inflateBackInit_ (z_streamp strm, int windowBits, unsigned char *window, const char *version, int stream_size)


                                                          ;
# 1670 "zlib.h"
struct gzFile_s {
    unsigned have;
    unsigned char *next;
    off_t pos;
};
extern int gzgetc_ (gzFile file);
# 1725 "zlib.h"
   extern gzFile gzopen (const char *, const char *);
   extern off_t gzseek (gzFile, off_t, int);
   extern off_t gztell (gzFile);
   extern off_t gzoffset (gzFile);
   extern uLong adler32_combine (uLong, uLong, off_t);
   extern uLong crc32_combine (uLong, uLong, off_t);
# 1746 "zlib.h"
extern const char * zError (int);
extern int inflateSyncPoint (z_streamp);
extern const z_crc_t * get_crc_table (void);
extern int inflateUndermine (z_streamp, int);
extern int inflateResetKeep (z_streamp);
extern int deflateResetKeep (z_streamp);






extern int gzvprintf (gzFile file, const char *format, va_list va)

                                                              ;
# 23 "zutil.h" 2





# 1 "/home/user/workspace/embox/./src/include/string.h" 1
# 22 "/home/user/workspace/embox/./src/include/string.h"

# 33 "/home/user/workspace/embox/./src/include/string.h"
extern size_t strlen(const char *str);
# 47 "/home/user/workspace/embox/./src/include/string.h"
extern char *strcpy(char *dst, const char *src);
# 66 "/home/user/workspace/embox/./src/include/string.h"
extern char *strncpy(char *dst, const char *src, size_t n);
# 78 "/home/user/workspace/embox/./src/include/string.h"
extern char *strcat(char *dst, const char *src);
# 94 "/home/user/workspace/embox/./src/include/string.h"
extern char *strncat(char *dst, const char *src, size_t n);
# 114 "/home/user/workspace/embox/./src/include/string.h"
extern int strcmp(const char *str1, const char *str2);
# 137 "/home/user/workspace/embox/./src/include/string.h"
extern int strncmp(const char *str1, const char *str2, size_t n);
# 152 "/home/user/workspace/embox/./src/include/string.h"
extern char *strchr(const char *str, int ch);
# 169 "/home/user/workspace/embox/./src/include/string.h"
extern char *strrchr(const char *str, int ch);
# 185 "/home/user/workspace/embox/./src/include/string.h"
extern char *strstr(const char *haystack, const char *needle);
# 195 "/home/user/workspace/embox/./src/include/string.h"
extern char *strerror(int err);
# 215 "/home/user/workspace/embox/./src/include/string.h"
extern void *memcpy(void *dst, const void *src, size_t n);
# 230 "/home/user/workspace/embox/./src/include/string.h"
extern void *memmove(void *dst, const void *src, size_t n);
# 245 "/home/user/workspace/embox/./src/include/string.h"
extern void *memset(void *ptr, int c, size_t n);
# 266 "/home/user/workspace/embox/./src/include/string.h"
extern int memcmp(const void *ptr1, const void *ptr2, size_t n);
# 282 "/home/user/workspace/embox/./src/include/string.h"
extern void *memchr(const void *s, int c, size_t n);
# 292 "/home/user/workspace/embox/./src/include/string.h"
extern char *strlwr(char *str);
# 302 "/home/user/workspace/embox/./src/include/string.h"
extern char *strupr(char *str);
# 315 "/home/user/workspace/embox/./src/include/string.h"
extern size_t strspn(const char *s, const char *accept);
# 328 "/home/user/workspace/embox/./src/include/string.h"
extern size_t strcspn(const char *s, const char *reject);
# 342 "/home/user/workspace/embox/./src/include/string.h"
extern char *strpbrk(const char *s, const char *accept);
# 352 "/home/user/workspace/embox/./src/include/string.h"
extern char *strdup(const char *s);






extern int ffs(int i);


# 29 "zutil.h" 2
# 1 "/home/user/workspace/embox/./src/include/stdlib.h" 1
# 18 "/home/user/workspace/embox/./src/include/stdlib.h"
# 1 "/home/user/workspace/embox/./src/include/stdint.h" 1
# 18 "/home/user/workspace/embox/./src/include/stdint.h"
typedef __s8 int8_t;
typedef __s16 int16_t;
typedef __s32 int32_t;
typedef __s64 int64_t;

typedef __u8 uint8_t;
typedef __u16 uint16_t;
typedef __u32 uint32_t;
typedef __u64 uint64_t;

typedef __s8 int_least8_t;
typedef __s16 int_least16_t;
typedef __s32 int_least32_t;
typedef __s64 int_least64_t;

typedef __u8 uint_least8_t;
typedef __u16 uint_least16_t;
typedef __u32 uint_least32_t;
typedef __u64 uint_least64_t;


typedef __s32 __s_fast;
typedef __u32 __u_fast;







typedef __s_fast int_fast8_t;
typedef __s_fast int_fast16_t;
typedef __s_fast int_fast32_t;
typedef __s_fast int_fast64_t;

typedef __u_fast uint_fast8_t;
typedef __u_fast uint_fast16_t;
typedef __u_fast uint_fast32_t;
typedef __u_fast uint_fast64_t;

typedef int64_t intmax_t;
typedef uint64_t uintmax_t;


typedef int intptr_t;
typedef unsigned int uintptr_t;
# 19 "/home/user/workspace/embox/./src/include/stdlib.h" 2
# 1 "/home/user/workspace/embox/./src/compat/posix/include/sys/wait.h" 1
# 15 "/home/user/workspace/embox/./src/compat/posix/include/sys/wait.h"
extern pid_t waitpid(pid_t pid, int *status, int options);
# 20 "/home/user/workspace/embox/./src/include/stdlib.h" 2

typedef struct ldiv {
   long int quot;
   long int rem;
} ldiv_t;

typedef struct div {
   int quot;
   int rem;
} div_t;




# 63 "/home/user/workspace/embox/./src/include/stdlib.h"
extern long int strtol(const char *nptr, char **endptr, int base);

extern unsigned long int strtoul(const char *nptr, char **endptr, int base);

extern double strtod(const char *nptr, char **endptr);
# 78 "/home/user/workspace/embox/./src/include/stdlib.h"
extern char *itoa( int num, char *buf, unsigned short int base );


extern void *calloc(size_t nmemb, size_t size);
extern void *malloc(size_t size);
extern void free(void *ptr);
extern void *realloc(void *ptr, size_t size);
extern void *memalign(size_t boundary, size_t size);


extern void qsort(void *base, size_t nmemb, size_t size,
  int(*compar)(const void *, const void *));

extern void *bsearch(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));


extern void *lower_bound(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));


extern void *upper_bound(const void *key, const void *base,
              size_t nmemb, size_t size,
              int (*compar)(const void *, const void *));


extern int rand(void);
extern int rand_r(unsigned int *seedp);
extern void srand(unsigned int seed);

extern long int random(void);
extern void srandom(unsigned int seed);
extern char *initstate(unsigned int seed, char *state, size_t n);
extern char *setstate(char *state);

struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r(struct random_data *buf, int32_t *result);
extern int srandom_r(unsigned int seed, struct random_data *buf);
extern int initstate_r(unsigned int seed, char *statebuf,
                       size_t statelen, struct random_data *buf);
extern int setstate_r(char *statebuf, struct random_data *buf);

extern ldiv_t ldiv(long num, long denom);
extern div_t div(int num, int denom);


extern double atof(const char *nptr);
extern int atoi(const char *nptr);
extern long atol(const char *nptr);
extern long long atoll(const char *nptr);
extern long long atoq(const char *nptr);
extern double strtod(const char *nptr, char **endptr);
extern float strtof(const char *nptr, char **endptr);
extern long double strtold(const char *nptr, char **endptr);
extern void abort(void);



extern void exit(int status);
# 159 "/home/user/workspace/embox/./src/include/stdlib.h"
static inline int abs(int x) { return x < 0 ? -x : x; }
static inline long labs(long x) { return x < 0 ? -x : x; }


extern char * getenv(const char *name);
extern int putenv(char *string);
extern int setenv(const char *envname, const char *envval, int overwrite);
extern int unsetenv(const char *name);
extern int clearenv(void);
extern int system(const char *command);

static inline int mkstemp(char *path_template) { return -1; }
static inline int mbtowc(wchar_t *pwc, const char *s, size_t n) { return 0; }
static inline int wctomb(char *s, wchar_t wchar) { return 0; }


# 30 "zutil.h" 2
# 41 "zutil.h"
typedef unsigned char uch;
typedef uch uchf;
typedef unsigned short ush;
typedef ush ushf;
typedef unsigned long ulg;

extern char * const z_errmsg[10];
# 173 "zutil.h"
    extern uLong adler32_combine64 (uLong, uLong, off_t);
    extern uLong crc32_combine64 (uLong, uLong, off_t);
# 239 "zutil.h"
   voidpf __attribute__((visibility ("hidden"))) zcalloc (voidpf opaque, unsigned items, unsigned size)
                                                   ;
   void __attribute__((visibility ("hidden"))) zcfree (voidpf opaque, voidpf ptr);
# 17 "deflate.h" 2
# 65 "deflate.h"
typedef struct ct_data_s {
    union {
        ush freq;
        ush code;
    } fc;
    union {
        ush dad;
        ush len;
    } dl;
} ct_data;






typedef struct static_tree_desc_s static_tree_desc;

typedef struct tree_desc_s {
    ct_data *dyn_tree;
    int max_code;
    static_tree_desc *stat_desc;
} tree_desc;

typedef ush Pos;
typedef Pos Posf;
typedef unsigned IPos;





typedef struct internal_state {
    z_streamp strm;
    int status;
    Bytef *pending_buf;
    ulg pending_buf_size;
    Bytef *pending_out;
    uInt pending;
    int wrap;
    gz_headerp gzhead;
    uInt gzindex;
    Byte method;
    int last_flush;



    uInt w_size;
    uInt w_bits;
    uInt w_mask;

    Bytef *window;
# 126 "deflate.h"
    ulg window_size;




    Posf *prev;





    Posf *head;

    uInt ins_h;
    uInt hash_size;
    uInt hash_bits;
    uInt hash_mask;

    uInt hash_shift;






    long block_start;




    uInt match_length;
    IPos prev_match;
    int match_available;
    uInt strstart;
    uInt match_start;
    uInt lookahead;

    uInt prev_length;




    uInt max_chain_length;





    uInt max_lazy_match;
# 185 "deflate.h"
    int level;
    int strategy;

    uInt good_match;


    int nice_match;



    struct ct_data_s dyn_ltree[(2*(256 +1+29)+1)];
    struct ct_data_s dyn_dtree[2*30 +1];
    struct ct_data_s bl_tree[2*19 +1];

    struct tree_desc_s l_desc;
    struct tree_desc_s d_desc;
    struct tree_desc_s bl_desc;

    ush bl_count[15 +1];


    int heap[2*(256 +1+29)+1];
    int heap_len;
    int heap_max;




    uch depth[2*(256 +1+29)+1];



    uchf *l_buf;

    uInt lit_bufsize;
# 239 "deflate.h"
    uInt last_lit;

    ushf *d_buf;





    ulg opt_len;
    ulg static_len;
    uInt matches;
    uInt insert;






    ush bi_buf;



    int bi_valid;




    ulg high_water;






} deflate_state;
# 296 "deflate.h"
void __attribute__((visibility ("hidden"))) _tr_init (deflate_state *s);
int __attribute__((visibility ("hidden"))) _tr_tally (deflate_state *s, unsigned dist, unsigned lc);
void __attribute__((visibility ("hidden"))) _tr_flush_block (deflate_state *s, charf *buf, ulg stored_len, int last)
                                                  ;
void __attribute__((visibility ("hidden"))) _tr_flush_bits (deflate_state *s);
void __attribute__((visibility ("hidden"))) _tr_align (deflate_state *s);
void __attribute__((visibility ("hidden"))) _tr_stored_block (deflate_state *s, charf *buf, ulg stored_len, int last)
                                                  ;
# 319 "deflate.h"
  extern const uch __attribute__((visibility ("hidden"))) _length_code[];
  extern const uch __attribute__((visibility ("hidden"))) _dist_code[];
# 53 "deflate.c" 2

const char deflate_copyright[] =
   " deflate 1.2.8 Copyright 1995-2013 Jean-loup Gailly and Mark Adler ";
# 66 "deflate.c"
typedef enum {
    need_more,
    block_done,
    finish_started,
    finish_done
} block_state;

typedef block_state (*compress_func) (deflate_state *s, int flush);


static void fill_window (deflate_state *s);
static block_state deflate_stored (deflate_state *s, int flush);
static block_state deflate_fast (deflate_state *s, int flush);

static block_state deflate_slow (deflate_state *s, int flush);

static block_state deflate_rle (deflate_state *s, int flush);
static block_state deflate_huff (deflate_state *s, int flush);
static void lm_init (deflate_state *s);
static void putShortMSB (deflate_state *s, uInt b);
static void flush_pending (z_streamp strm);
static int read_buf (z_streamp strm, Bytef *buf, unsigned size);




static uInt longest_match (deflate_state *s, IPos cur_match);
# 117 "deflate.c"
typedef struct config_s {
   ush good_length;
   ush max_lazy;
   ush nice_length;
   ush max_chain;
   compress_func func;
} config;







static const config configuration_table[10] = {

        {0, 0, 0, 0, deflate_stored},
        {4, 4, 8, 4, deflate_fast},
        {4, 5, 16, 8, deflate_fast},
        {4, 6, 32, 32, deflate_fast},

        {4, 4, 16, 16, deflate_slow},
        {8, 16, 32, 32, deflate_slow},
        {8, 16, 128, 128, deflate_slow},
        {8, 32, 128, 256, deflate_slow},
        {32, 128, 258, 1024, deflate_slow},
        {32, 258, 258, 4096, deflate_slow}};
# 155 "deflate.c"
struct static_tree_desc_s {int dummy;};
# 201 "deflate.c"
int deflateInit_(strm, level, version, stream_size)
    z_streamp strm;
    int level;
    const char *version;
    int stream_size;
{
    return deflateInit2_(strm, level, 8, 15, 8,
                         0, version, stream_size);

}


int deflateInit2_(strm, level, method, windowBits, memLevel, strategy,
                  version, stream_size)
    z_streamp strm;
    int level;
    int method;
    int windowBits;
    int memLevel;
    int strategy;
    const char *version;
    int stream_size;
{
    deflate_state *s;
    int wrap = 1;
    static const char my_version[] = "1.2.8";

    ushf *overlay;




    if (version == 0 || version[0] != my_version[0] ||
        stream_size != sizeof(z_stream)) {
        return (-6);
    }
    if (strm == 0) return (-2);

    strm->msg = 0;
    if (strm->zalloc == (alloc_func)0) {



        strm->zalloc = zcalloc;
        strm->opaque = (voidpf)0;

    }
    if (strm->zfree == (free_func)0)



        strm->zfree = zcfree;





    if (level == (-1)) level = 6;


    if (windowBits < 0) {
        wrap = 0;
        windowBits = -windowBits;
    }

    else if (windowBits > 15) {
        wrap = 2;
        windowBits -= 16;
    }

    if (memLevel < 1 || memLevel > 9 || method != 8 ||
        windowBits < 8 || windowBits > 15 || level < 0 || level > 9 ||
        strategy < 0 || strategy > 4) {
        return (-2);
    }
    if (windowBits == 8) windowBits = 9;
    s = (deflate_state *) (*((strm)->zalloc))((strm)->opaque, (1), (sizeof(deflate_state)));
    if (s == 0) return (-4);
    strm->state = (struct internal_state *)s;
    s->strm = strm;

    s->wrap = wrap;
    s->gzhead = 0;
    s->w_bits = windowBits;
    s->w_size = 1 << s->w_bits;
    s->w_mask = s->w_size - 1;

    s->hash_bits = memLevel + 7;
    s->hash_size = 1 << s->hash_bits;
    s->hash_mask = s->hash_size - 1;
    s->hash_shift = ((s->hash_bits+3 -1)/3);

    s->window = (Bytef *) (*((strm)->zalloc))((strm)->opaque, (s->w_size), (2*sizeof(Byte)));
    s->prev = (Posf *) (*((strm)->zalloc))((strm)->opaque, (s->w_size), (sizeof(Pos)));
    s->head = (Posf *) (*((strm)->zalloc))((strm)->opaque, (s->hash_size), (sizeof(Pos)));

    s->high_water = 0;

    s->lit_bufsize = 1 << (memLevel + 6);

    overlay = (ushf *) (*((strm)->zalloc))((strm)->opaque, (s->lit_bufsize), (sizeof(ush)+2));
    s->pending_buf = (uchf *) overlay;
    s->pending_buf_size = (ulg)s->lit_bufsize * (sizeof(ush)+2L);

    if (s->window == 0 || s->prev == 0 || s->head == 0 ||
        s->pending_buf == 0) {
        s->status = 666;
        strm->msg = z_errmsg[2 -((-4))];
        deflateEnd (strm);
        return (-4);
    }
    s->d_buf = overlay + s->lit_bufsize/sizeof(ush);
    s->l_buf = s->pending_buf + (1+sizeof(ush))*s->lit_bufsize;

    s->level = level;
    s->strategy = strategy;
    s->method = (Byte)method;

    return deflateReset(strm);
}


int deflateSetDictionary (strm, dictionary, dictLength)
    z_streamp strm;
    const Bytef *dictionary;
    uInt dictLength;
{
    deflate_state *s;
    uInt str, n;
    int wrap;
    unsigned avail;
    unsigned char *next;

    if (strm == 0 || strm->state == 0 || dictionary == 0)
        return (-2);
    s = strm->state;
    wrap = s->wrap;
    if (wrap == 2 || (wrap == 1 && s->status != 42) || s->lookahead)
        return (-2);


    if (wrap == 1)
        strm->adler = adler32(strm->adler, dictionary, dictLength);
    s->wrap = 0;


    if (dictLength >= s->w_size) {
        if (wrap == 0) {
            s->head[s->hash_size-1] = 0; memset((Bytef *)s->head, 0, (unsigned)(s->hash_size-1)*sizeof(*s->head));;
            s->strstart = 0;
            s->block_start = 0L;
            s->insert = 0;
        }
        dictionary += dictLength - s->w_size;
        dictLength = s->w_size;
    }


    avail = strm->avail_in;
    next = strm->next_in;
    strm->avail_in = dictLength;
    strm->next_in = ( Bytef *)dictionary;
    fill_window(s);
    while (s->lookahead >= 3) {
        str = s->strstart;
        n = s->lookahead - (3 -1);
        do {
            (s->ins_h = (((s->ins_h)<<s->hash_shift) ^ (s->window[str + 3 -1])) & s->hash_mask);

            s->prev[str & s->w_mask] = s->head[s->ins_h];

            s->head[s->ins_h] = (Pos)str;
            str++;
        } while (--n);
        s->strstart = str;
        s->lookahead = 3 -1;
        fill_window(s);
    }
    s->strstart += s->lookahead;
    s->block_start = (long)s->strstart;
    s->insert = s->lookahead;
    s->lookahead = 0;
    s->match_length = s->prev_length = 3 -1;
    s->match_available = 0;
    strm->next_in = next;
    strm->avail_in = avail;
    s->wrap = wrap;
    return 0;
}


int deflateResetKeep (strm)
    z_streamp strm;
{
    deflate_state *s;

    if (strm == 0 || strm->state == 0 ||
        strm->zalloc == (alloc_func)0 || strm->zfree == (free_func)0) {
        return (-2);
    }

    strm->total_in = strm->total_out = 0;
    strm->msg = 0;
    strm->data_type = 2;

    s = (deflate_state *)strm->state;
    s->pending = 0;
    s->pending_out = s->pending_buf;

    if (s->wrap < 0) {
        s->wrap = -s->wrap;
    }
    s->status = s->wrap ? 42 : 113;
    strm->adler =

        s->wrap == 2 ? crc32(0L, 0, 0) :

        adler32(0L, 0, 0);
    s->last_flush = 0;

    _tr_init(s);

    return 0;
}


int deflateReset (strm)
    z_streamp strm;
{
    int ret;

    ret = deflateResetKeep(strm);
    if (ret == 0)
        lm_init(strm->state);
    return ret;
}


int deflateSetHeader (strm, head)
    z_streamp strm;
    gz_headerp head;
{
    if (strm == 0 || strm->state == 0) return (-2);
    if (strm->state->wrap != 2) return (-2);
    strm->state->gzhead = head;
    return 0;
}


int deflatePending (strm, pending, bits)
    unsigned *pending;
    int *bits;
    z_streamp strm;
{
    if (strm == 0 || strm->state == 0) return (-2);
    if (pending != 0)
        *pending = strm->state->pending;
    if (bits != 0)
        *bits = strm->state->bi_valid;
    return 0;
}


int deflatePrime (strm, bits, value)
    z_streamp strm;
    int bits;
    int value;
{
    deflate_state *s;
    int put;

    if (strm == 0 || strm->state == 0) return (-2);
    s = strm->state;
    if ((Bytef *)(s->d_buf) < s->pending_out + ((16 + 7) >> 3))
        return (-5);
    do {
        put = 16 - s->bi_valid;
        if (put > bits)
            put = bits;
        s->bi_buf |= (ush)((value & ((1 << put) - 1)) << s->bi_valid);
        s->bi_valid += put;
        _tr_flush_bits(s);
        value >>= put;
        bits -= put;
    } while (bits);
    return 0;
}


int deflateParams(strm, level, strategy)
    z_streamp strm;
    int level;
    int strategy;
{
    deflate_state *s;
    compress_func func;
    int err = 0;

    if (strm == 0 || strm->state == 0) return (-2);
    s = strm->state;




    if (level == (-1)) level = 6;

    if (level < 0 || level > 9 || strategy < 0 || strategy > 4) {
        return (-2);
    }
    func = configuration_table[s->level].func;

    if ((strategy != s->strategy || func != configuration_table[level].func) &&
        strm->total_in != 0) {

        err = deflate(strm, 5);
        if (err == (-5) && s->pending == 0)
            err = 0;
    }
    if (s->level != level) {
        s->level = level;
        s->max_lazy_match = configuration_table[level].max_lazy;
        s->good_match = configuration_table[level].good_length;
        s->nice_match = configuration_table[level].nice_length;
        s->max_chain_length = configuration_table[level].max_chain;
    }
    s->strategy = strategy;
    return err;
}


int deflateTune(strm, good_length, max_lazy, nice_length, max_chain)
    z_streamp strm;
    int good_length;
    int max_lazy;
    int nice_length;
    int max_chain;
{
    deflate_state *s;

    if (strm == 0 || strm->state == 0) return (-2);
    s = strm->state;
    s->good_match = good_length;
    s->max_lazy_match = max_lazy;
    s->nice_match = nice_length;
    s->max_chain_length = max_chain;
    return 0;
}
# 566 "deflate.c"
uLong deflateBound(strm, sourceLen)
    z_streamp strm;
    uLong sourceLen;
{
    deflate_state *s;
    uLong complen, wraplen;
    Bytef *str;


    complen = sourceLen +
              ((sourceLen + 7) >> 3) + ((sourceLen + 63) >> 6) + 5;


    if (strm == 0 || strm->state == 0)
        return complen + 6;


    s = strm->state;
    switch (s->wrap) {
    case 0:
        wraplen = 0;
        break;
    case 1:
        wraplen = 6 + (s->strstart ? 4 : 0);
        break;
    case 2:
        wraplen = 18;
        if (s->gzhead != 0) {
            if (s->gzhead->extra != 0)
                wraplen += 2 + s->gzhead->extra_len;
            str = s->gzhead->name;
            if (str != 0)
                do {
                    wraplen++;
                } while (*str++);
            str = s->gzhead->comment;
            if (str != 0)
                do {
                    wraplen++;
                } while (*str++);
            if (s->gzhead->hcrc)
                wraplen += 2;
        }
        break;
    default:
        wraplen = 6;
    }


    if (s->w_bits != 15 || s->hash_bits != 8 + 7)
        return complen + wraplen;


    return sourceLen + (sourceLen >> 12) + (sourceLen >> 14) +
           (sourceLen >> 25) + 13 - 6 + wraplen;
}






static void putShortMSB (s, b)
    deflate_state *s;
    uInt b;
{
    {s->pending_buf[s->pending++] = ((Byte)(b >> 8));};
    {s->pending_buf[s->pending++] = ((Byte)(b & 0xff));};
}







static void flush_pending(strm)
    z_streamp strm;
{
    unsigned len;
    deflate_state *s = strm->state;

    _tr_flush_bits(s);
    len = s->pending;
    if (len > strm->avail_out) len = strm->avail_out;
    if (len == 0) return;

    memcpy(strm->next_out, s->pending_out, len);
    strm->next_out += len;
    s->pending_out += len;
    strm->total_out += len;
    strm->avail_out -= len;
    s->pending -= len;
    if (s->pending == 0) {
        s->pending_out = s->pending_buf;
    }
}


int deflate (strm, flush)
    z_streamp strm;
    int flush;
{
    int old_flush;
    deflate_state *s;

    if (strm == 0 || strm->state == 0 ||
        flush > 5 || flush < 0) {
        return (-2);
    }
    s = strm->state;

    if (strm->next_out == 0 ||
        (strm->next_in == 0 && strm->avail_in != 0) ||
        (s->status == 666 && flush != 4)) {
        return (strm->msg = z_errmsg[2 -((-2))], ((-2)));
    }
    if (strm->avail_out == 0) return (strm->msg = z_errmsg[2 -((-5))], ((-5)));

    s->strm = strm;
    old_flush = s->last_flush;
    s->last_flush = flush;


    if (s->status == 42) {

        if (s->wrap == 2) {
            strm->adler = crc32(0L, 0, 0);
            {s->pending_buf[s->pending++] = (31);};
            {s->pending_buf[s->pending++] = (139);};
            {s->pending_buf[s->pending++] = (8);};
            if (s->gzhead == 0) {
                {s->pending_buf[s->pending++] = (0);};
                {s->pending_buf[s->pending++] = (0);};
                {s->pending_buf[s->pending++] = (0);};
                {s->pending_buf[s->pending++] = (0);};
                {s->pending_buf[s->pending++] = (0);};
                {s->pending_buf[s->pending++] = (s->level == 9 ? 2 : (s->strategy >= 2 || s->level < 2 ? 4 : 0));}

                                    ;
                {s->pending_buf[s->pending++] = (0x03);};
                s->status = 113;
            }
            else {
                {s->pending_buf[s->pending++] = ((s->gzhead->text ? 1 : 0) + (s->gzhead->hcrc ? 2 : 0) + (s->gzhead->extra == 0 ? 0 : 4) + (s->gzhead->name == 0 ? 0 : 8) + (s->gzhead->comment == 0 ? 0 : 16));}




                         ;
                {s->pending_buf[s->pending++] = ((Byte)(s->gzhead->time & 0xff));};
                {s->pending_buf[s->pending++] = ((Byte)((s->gzhead->time >> 8) & 0xff));};
                {s->pending_buf[s->pending++] = ((Byte)((s->gzhead->time >> 16) & 0xff));};
                {s->pending_buf[s->pending++] = ((Byte)((s->gzhead->time >> 24) & 0xff));};
                {s->pending_buf[s->pending++] = (s->level == 9 ? 2 : (s->strategy >= 2 || s->level < 2 ? 4 : 0));}

                                    ;
                {s->pending_buf[s->pending++] = (s->gzhead->os & 0xff);};
                if (s->gzhead->extra != 0) {
                    {s->pending_buf[s->pending++] = (s->gzhead->extra_len & 0xff);};
                    {s->pending_buf[s->pending++] = ((s->gzhead->extra_len >> 8) & 0xff);};
                }
                if (s->gzhead->hcrc)
                    strm->adler = crc32(strm->adler, s->pending_buf,
                                        s->pending);
                s->gzindex = 0;
                s->status = 69;
            }
        }
        else

        {
            uInt header = (8 + ((s->w_bits-8)<<4)) << 8;
            uInt level_flags;

            if (s->strategy >= 2 || s->level < 2)
                level_flags = 0;
            else if (s->level < 6)
                level_flags = 1;
            else if (s->level == 6)
                level_flags = 2;
            else
                level_flags = 3;
            header |= (level_flags << 6);
            if (s->strstart != 0) header |= 0x20;
            header += 31 - (header % 31);

            s->status = 113;
            putShortMSB(s, header);


            if (s->strstart != 0) {
                putShortMSB(s, (uInt)(strm->adler >> 16));
                putShortMSB(s, (uInt)(strm->adler & 0xffff));
            }
            strm->adler = adler32(0L, 0, 0);
        }
    }

    if (s->status == 69) {
        if (s->gzhead->extra != 0) {
            uInt beg = s->pending;

            while (s->gzindex < (s->gzhead->extra_len & 0xffff)) {
                if (s->pending == s->pending_buf_size) {
                    if (s->gzhead->hcrc && s->pending > beg)
                        strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                            s->pending - beg);
                    flush_pending(strm);
                    beg = s->pending;
                    if (s->pending == s->pending_buf_size)
                        break;
                }
                {s->pending_buf[s->pending++] = (s->gzhead->extra[s->gzindex]);};
                s->gzindex++;
            }
            if (s->gzhead->hcrc && s->pending > beg)
                strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                    s->pending - beg);
            if (s->gzindex == s->gzhead->extra_len) {
                s->gzindex = 0;
                s->status = 73;
            }
        }
        else
            s->status = 73;
    }
    if (s->status == 73) {
        if (s->gzhead->name != 0) {
            uInt beg = s->pending;
            int val;

            do {
                if (s->pending == s->pending_buf_size) {
                    if (s->gzhead->hcrc && s->pending > beg)
                        strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                            s->pending - beg);
                    flush_pending(strm);
                    beg = s->pending;
                    if (s->pending == s->pending_buf_size) {
                        val = 1;
                        break;
                    }
                }
                val = s->gzhead->name[s->gzindex++];
                {s->pending_buf[s->pending++] = (val);};
            } while (val != 0);
            if (s->gzhead->hcrc && s->pending > beg)
                strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                    s->pending - beg);
            if (val == 0) {
                s->gzindex = 0;
                s->status = 91;
            }
        }
        else
            s->status = 91;
    }
    if (s->status == 91) {
        if (s->gzhead->comment != 0) {
            uInt beg = s->pending;
            int val;

            do {
                if (s->pending == s->pending_buf_size) {
                    if (s->gzhead->hcrc && s->pending > beg)
                        strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                            s->pending - beg);
                    flush_pending(strm);
                    beg = s->pending;
                    if (s->pending == s->pending_buf_size) {
                        val = 1;
                        break;
                    }
                }
                val = s->gzhead->comment[s->gzindex++];
                {s->pending_buf[s->pending++] = (val);};
            } while (val != 0);
            if (s->gzhead->hcrc && s->pending > beg)
                strm->adler = crc32(strm->adler, s->pending_buf + beg,
                                    s->pending - beg);
            if (val == 0)
                s->status = 103;
        }
        else
            s->status = 103;
    }
    if (s->status == 103) {
        if (s->gzhead->hcrc) {
            if (s->pending + 2 > s->pending_buf_size)
                flush_pending(strm);
            if (s->pending + 2 <= s->pending_buf_size) {
                {s->pending_buf[s->pending++] = ((Byte)(strm->adler & 0xff));};
                {s->pending_buf[s->pending++] = ((Byte)((strm->adler >> 8) & 0xff));};
                strm->adler = crc32(0L, 0, 0);
                s->status = 113;
            }
        }
        else
            s->status = 113;
    }



    if (s->pending != 0) {
        flush_pending(strm);
        if (strm->avail_out == 0) {






            s->last_flush = -1;
            return 0;
        }





    } else if (strm->avail_in == 0 && (((flush) << 1) - ((flush) > 4 ? 9 : 0)) <= (((old_flush) << 1) - ((old_flush) > 4 ? 9 : 0)) &&
               flush != 4) {
        return (strm->msg = z_errmsg[2 -((-5))], ((-5)));
    }


    if (s->status == 666 && strm->avail_in != 0) {
        return (strm->msg = z_errmsg[2 -((-5))], ((-5)));
    }



    if (strm->avail_in != 0 || s->lookahead != 0 ||
        (flush != 0 && s->status != 666)) {
        block_state bstate;

        bstate = s->strategy == 2 ? deflate_huff(s, flush) :
                    (s->strategy == 3 ? deflate_rle(s, flush) :
                        (*(configuration_table[s->level].func))(s, flush));

        if (bstate == finish_started || bstate == finish_done) {
            s->status = 666;
        }
        if (bstate == need_more || bstate == finish_started) {
            if (strm->avail_out == 0) {
                s->last_flush = -1;
            }
            return 0;







        }
        if (bstate == block_done) {
            if (flush == 1) {
                _tr_align(s);
            } else if (flush != 5) {
                _tr_stored_block(s, (char*)0, 0L, 0);



                if (flush == 3) {
                    s->head[s->hash_size-1] = 0; memset((Bytef *)s->head, 0, (unsigned)(s->hash_size-1)*sizeof(*s->head));;
                    if (s->lookahead == 0) {
                        s->strstart = 0;
                        s->block_start = 0L;
                        s->insert = 0;
                    }
                }
            }
            flush_pending(strm);
            if (strm->avail_out == 0) {
              s->last_flush = -1;
              return 0;
            }
        }
    }
    ;

    if (flush != 4) return 0;
    if (s->wrap <= 0) return 1;



    if (s->wrap == 2) {
        {s->pending_buf[s->pending++] = ((Byte)(strm->adler & 0xff));};
        {s->pending_buf[s->pending++] = ((Byte)((strm->adler >> 8) & 0xff));};
        {s->pending_buf[s->pending++] = ((Byte)((strm->adler >> 16) & 0xff));};
        {s->pending_buf[s->pending++] = ((Byte)((strm->adler >> 24) & 0xff));};
        {s->pending_buf[s->pending++] = ((Byte)(strm->total_in & 0xff));};
        {s->pending_buf[s->pending++] = ((Byte)((strm->total_in >> 8) & 0xff));};
        {s->pending_buf[s->pending++] = ((Byte)((strm->total_in >> 16) & 0xff));};
        {s->pending_buf[s->pending++] = ((Byte)((strm->total_in >> 24) & 0xff));};
    }
    else

    {
        putShortMSB(s, (uInt)(strm->adler >> 16));
        putShortMSB(s, (uInt)(strm->adler & 0xffff));
    }
    flush_pending(strm);



    if (s->wrap > 0) s->wrap = -s->wrap;
    return s->pending != 0 ? 0 : 1;
}


int deflateEnd (strm)
    z_streamp strm;
{
    int status;

    if (strm == 0 || strm->state == 0) return (-2);

    status = strm->state->status;
    if (status != 42 &&
        status != 69 &&
        status != 73 &&
        status != 91 &&
        status != 103 &&
        status != 113 &&
        status != 666) {
      return (-2);
    }


    {if (strm->state->pending_buf) (*((strm)->zfree))((strm)->opaque, (voidpf)(strm->state->pending_buf));};
    {if (strm->state->head) (*((strm)->zfree))((strm)->opaque, (voidpf)(strm->state->head));};
    {if (strm->state->prev) (*((strm)->zfree))((strm)->opaque, (voidpf)(strm->state->prev));};
    {if (strm->state->window) (*((strm)->zfree))((strm)->opaque, (voidpf)(strm->state->window));};

    (*((strm)->zfree))((strm)->opaque, (voidpf)(strm->state));
    strm->state = 0;

    return status == 113 ? (-3) : 0;
}






int deflateCopy (dest, source)
    z_streamp dest;
    z_streamp source;
{



    deflate_state *ds;
    deflate_state *ss;
    ushf *overlay;


    if (source == 0 || dest == 0 || source->state == 0) {
        return (-2);
    }

    ss = source->state;

    memcpy((voidpf)dest, (voidpf)source, sizeof(z_stream));

    ds = (deflate_state *) (*((dest)->zalloc))((dest)->opaque, (1), (sizeof(deflate_state)));
    if (ds == 0) return (-4);
    dest->state = (struct internal_state *) ds;
    memcpy((voidpf)ds, (voidpf)ss, sizeof(deflate_state));
    ds->strm = dest;

    ds->window = (Bytef *) (*((dest)->zalloc))((dest)->opaque, (ds->w_size), (2*sizeof(Byte)));
    ds->prev = (Posf *) (*((dest)->zalloc))((dest)->opaque, (ds->w_size), (sizeof(Pos)));
    ds->head = (Posf *) (*((dest)->zalloc))((dest)->opaque, (ds->hash_size), (sizeof(Pos)));
    overlay = (ushf *) (*((dest)->zalloc))((dest)->opaque, (ds->lit_bufsize), (sizeof(ush)+2));
    ds->pending_buf = (uchf *) overlay;

    if (ds->window == 0 || ds->prev == 0 || ds->head == 0 ||
        ds->pending_buf == 0) {
        deflateEnd (dest);
        return (-4);
    }

    memcpy(ds->window, ss->window, ds->w_size * 2 * sizeof(Byte));
    memcpy((voidpf)ds->prev, (voidpf)ss->prev, ds->w_size * sizeof(Pos));
    memcpy((voidpf)ds->head, (voidpf)ss->head, ds->hash_size * sizeof(Pos));
    memcpy(ds->pending_buf, ss->pending_buf, (uInt)ds->pending_buf_size);

    ds->pending_out = ds->pending_buf + (ss->pending_out - ss->pending_buf);
    ds->d_buf = overlay + ds->lit_bufsize/sizeof(ush);
    ds->l_buf = ds->pending_buf + (1+sizeof(ush))*ds->lit_bufsize;

    ds->l_desc.dyn_tree = ds->dyn_ltree;
    ds->d_desc.dyn_tree = ds->dyn_dtree;
    ds->bl_desc.dyn_tree = ds->bl_tree;

    return 0;

}
# 1076 "deflate.c"
static int read_buf(strm, buf, size)
    z_streamp strm;
    Bytef *buf;
    unsigned size;
{
    unsigned len = strm->avail_in;

    if (len > size) len = size;
    if (len == 0) return 0;

    strm->avail_in -= len;

    memcpy(buf, strm->next_in, len);
    if (strm->state->wrap == 1) {
        strm->adler = adler32(strm->adler, buf, len);
    }

    else if (strm->state->wrap == 2) {
        strm->adler = crc32(strm->adler, buf, len);
    }

    strm->next_in += len;
    strm->total_in += len;

    return (int)len;
}




static void lm_init (s)
    deflate_state *s;
{
    s->window_size = (ulg)2L*s->w_size;

    s->head[s->hash_size-1] = 0; memset((Bytef *)s->head, 0, (unsigned)(s->hash_size-1)*sizeof(*s->head));;



    s->max_lazy_match = configuration_table[s->level].max_lazy;
    s->good_match = configuration_table[s->level].good_length;
    s->nice_match = configuration_table[s->level].nice_length;
    s->max_chain_length = configuration_table[s->level].max_chain;

    s->strstart = 0;
    s->block_start = 0L;
    s->lookahead = 0;
    s->insert = 0;
    s->match_length = s->prev_length = 3 -1;
    s->match_available = 0;
    s->ins_h = 0;





}
# 1148 "deflate.c"
static uInt longest_match(s, cur_match)
    deflate_state *s;
    IPos cur_match;
{
    unsigned chain_length = s->max_chain_length;
    register Bytef *scan = s->window + s->strstart;
    register Bytef *match;
    register int len;
    int best_len = s->prev_length;
    int nice_match = s->nice_match;
    IPos limit = s->strstart > (IPos)((s)->w_size-(258 +3 +1)) ?
        s->strstart - (IPos)((s)->w_size-(258 +3 +1)) : 0;



    Posf *prev = s->prev;
    uInt wmask = s->w_mask;
# 1174 "deflate.c"
    register Bytef *strend = s->window + s->strstart + 258;
    register Byte scan_end1 = scan[best_len-1];
    register Byte scan_end = scan[best_len];





    ;


    if (s->prev_length >= s->good_match) {
        chain_length >>= 2;
    }



    if ((uInt)nice_match > s->lookahead) nice_match = s->lookahead;

    ;

    do {
        ;
        match = s->window + cur_match;
# 1242 "deflate.c"
        if (match[best_len] != scan_end ||
            match[best_len-1] != scan_end1 ||
            *match != *scan ||
            *++match != scan[1]) continue;







        scan += 2, match++;
        ;




        do {
        } while (*++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 *++scan == *++match && *++scan == *++match &&
                 scan < strend);

        ;

        len = 258 - (int)(strend - scan);
        scan = strend - 258;



        if (len > best_len) {
            s->match_start = cur_match;
            best_len = len;
            if (len >= nice_match) break;



            scan_end1 = scan[best_len-1];
            scan_end = scan[best_len];

        }
    } while ((cur_match = prev[cur_match & wmask]) > limit
             && --chain_length != 0);

    if ((uInt)best_len <= s->lookahead) return (uInt)best_len;
    return s->lookahead;
}
# 1390 "deflate.c"
static void fill_window(s)
    deflate_state *s;
{
    register unsigned n, m;
    register Posf *p;
    unsigned more;
    uInt wsize = s->w_size;

    ;

    do {
        more = (unsigned)(s->window_size -(ulg)s->lookahead -(ulg)s->strstart);


        if (sizeof(int) <= 2) {
            if (more == 0 && s->strstart == 0 && s->lookahead == 0) {
                more = wsize;

            } else if (more == (unsigned)(-1)) {



                more--;
            }
        }




        if (s->strstart >= wsize+((s)->w_size-(258 +3 +1))) {

            memcpy(s->window, s->window+wsize, (unsigned)wsize);
            s->match_start -= wsize;
            s->strstart -= wsize;
            s->block_start -= (long) wsize;







            n = s->hash_size;
            p = &s->head[n];
            do {
                m = *--p;
                *p = (Pos)(m >= wsize ? m-wsize : 0);
            } while (--n);

            n = wsize;

            p = &s->prev[n];
            do {
                m = *--p;
                *p = (Pos)(m >= wsize ? m-wsize : 0);



            } while (--n);

            more += wsize;
        }
        if (s->strm->avail_in == 0) break;
# 1465 "deflate.c"
        ;

        n = read_buf(s->strm, s->window + s->strstart + s->lookahead, more);
        s->lookahead += n;


        if (s->lookahead + s->insert >= 3) {
            uInt str = s->strstart - s->insert;
            s->ins_h = s->window[str];
            (s->ins_h = (((s->ins_h)<<s->hash_shift) ^ (s->window[str + 1])) & s->hash_mask);



            while (s->insert) {
                (s->ins_h = (((s->ins_h)<<s->hash_shift) ^ (s->window[str + 3 -1])) & s->hash_mask);

                s->prev[str & s->w_mask] = s->head[s->ins_h];

                s->head[s->ins_h] = (Pos)str;
                str++;
                s->insert--;
                if (s->lookahead + s->insert < 3)
                    break;
            }
        }




    } while (s->lookahead < (258 +3 +1) && s->strm->avail_in != 0);
# 1503 "deflate.c"
    if (s->high_water < s->window_size) {
        ulg curr = s->strstart + (ulg)(s->lookahead);
        ulg init;

        if (s->high_water < curr) {



            init = s->window_size - curr;
            if (init > 258)
                init = 258;
            memset(s->window + curr, 0, (unsigned)init);
            s->high_water = curr + init;
        }
        else if (s->high_water < (ulg)curr + 258) {




            init = (ulg)curr + 258 - s->high_water;
            if (init > s->window_size - s->high_water)
                init = s->window_size - s->high_water;
            memset(s->window + s->high_water, 0, (unsigned)init);
            s->high_water += init;
        }
    }

   
                                        ;
}
# 1564 "deflate.c"
static block_state deflate_stored(s, flush)
    deflate_state *s;
    int flush;
{



    ulg max_block_size = 0xffff;
    ulg max_start;

    if (max_block_size > s->pending_buf_size - 5) {
        max_block_size = s->pending_buf_size - 5;
    }


    for (;;) {

        if (s->lookahead <= 1) {

           
                                                                       ;

            fill_window(s);
            if (s->lookahead == 0 && flush == 0) return need_more;

            if (s->lookahead == 0) break;
        }
        ;

        s->strstart += s->lookahead;
        s->lookahead = 0;


        max_start = s->block_start + max_block_size;
        if (s->strstart == 0 || (ulg)s->strstart >= max_start) {

            s->lookahead = (uInt)(s->strstart - max_start);
            s->strstart = (uInt)max_start;
            { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };
        }



        if (s->strstart - (uInt)s->block_start >= ((s)->w_size-(258 +3 +1))) {
            { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };
        }
    }
    s->insert = 0;
    if (flush == 4) {
        { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (1)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (1) ? finish_started : need_more; };
        return finish_done;
    }
    if ((long)s->strstart > s->block_start)
        { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };
    return block_done;
}
# 1628 "deflate.c"
static block_state deflate_fast(s, flush)
    deflate_state *s;
    int flush;
{
    IPos hash_head;
    int bflush;

    for (;;) {





        if (s->lookahead < (258 +3 +1)) {
            fill_window(s);
            if (s->lookahead < (258 +3 +1) && flush == 0) {
                return need_more;
            }
            if (s->lookahead == 0) break;
        }




        hash_head = 0;
        if (s->lookahead >= 3) {
            ((s->ins_h = (((s->ins_h)<<s->hash_shift) ^ (s->window[(s->strstart) + (3 -1)])) & s->hash_mask), hash_head = s->prev[(s->strstart) & s->w_mask] = s->head[s->ins_h], s->head[s->ins_h] = (Pos)(s->strstart));
        }




        if (hash_head != 0 && s->strstart - hash_head <= ((s)->w_size-(258 +3 +1))) {




            s->match_length = longest_match (s, hash_head);

        }
        if (s->match_length >= 3) {
            ;

            { uch len = (s->match_length - 3); ush dist = (s->strstart - s->match_start); s->d_buf[s->last_lit] = dist; s->l_buf[s->last_lit++] = len; dist--; s->dyn_ltree[_length_code[len]+256 +1].fc.freq++; s->dyn_dtree[((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)])].fc.freq++; bflush = (s->last_lit == s->lit_bufsize-1); }
                                                               ;

            s->lookahead -= s->match_length;





            if (s->match_length <= s->max_lazy_match &&
                s->lookahead >= 3) {
                s->match_length--;
                do {
                    s->strstart++;
                    ((s->ins_h = (((s->ins_h)<<s->hash_shift) ^ (s->window[(s->strstart) + (3 -1)])) & s->hash_mask), hash_head = s->prev[(s->strstart) & s->w_mask] = s->head[s->ins_h], s->head[s->ins_h] = (Pos)(s->strstart));



                } while (--s->match_length != 0);
                s->strstart++;
            } else

            {
                s->strstart += s->match_length;
                s->match_length = 0;
                s->ins_h = s->window[s->strstart];
                (s->ins_h = (((s->ins_h)<<s->hash_shift) ^ (s->window[s->strstart+1])) & s->hash_mask);






            }
        } else {

            ;
            { uch cc = (s->window[s->strstart]); s->d_buf[s->last_lit] = 0; s->l_buf[s->last_lit++] = cc; s->dyn_ltree[cc].fc.freq++; bflush = (s->last_lit == s->lit_bufsize-1); };
            s->lookahead--;
            s->strstart++;
        }
        if (bflush) { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };
    }
    s->insert = s->strstart < 3 -1 ? s->strstart : 3 -1;
    if (flush == 4) {
        { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (1)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (1) ? finish_started : need_more; };
        return finish_done;
    }
    if (s->last_lit)
        { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };
    return block_done;
}







static block_state deflate_slow(s, flush)
    deflate_state *s;
    int flush;
{
    IPos hash_head;
    int bflush;


    for (;;) {





        if (s->lookahead < (258 +3 +1)) {
            fill_window(s);
            if (s->lookahead < (258 +3 +1) && flush == 0) {
                return need_more;
            }
            if (s->lookahead == 0) break;
        }




        hash_head = 0;
        if (s->lookahead >= 3) {
            ((s->ins_h = (((s->ins_h)<<s->hash_shift) ^ (s->window[(s->strstart) + (3 -1)])) & s->hash_mask), hash_head = s->prev[(s->strstart) & s->w_mask] = s->head[s->ins_h], s->head[s->ins_h] = (Pos)(s->strstart));
        }



        s->prev_length = s->match_length, s->prev_match = s->match_start;
        s->match_length = 3 -1;

        if (hash_head != 0 && s->prev_length < s->max_lazy_match &&
            s->strstart - hash_head <= ((s)->w_size-(258 +3 +1))) {




            s->match_length = longest_match (s, hash_head);


            if (s->match_length <= 5 && (s->strategy == 1

                || (s->match_length == 3 &&
                    s->strstart - s->match_start > 4096)

                )) {




                s->match_length = 3 -1;
            }
        }



        if (s->prev_length >= 3 && s->match_length <= s->prev_length) {
            uInt max_insert = s->strstart + s->lookahead - 3;


            ;

            { uch len = (s->prev_length - 3); ush dist = (s->strstart -1 - s->prev_match); s->d_buf[s->last_lit] = dist; s->l_buf[s->last_lit++] = len; dist--; s->dyn_ltree[_length_code[len]+256 +1].fc.freq++; s->dyn_dtree[((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)])].fc.freq++; bflush = (s->last_lit == s->lit_bufsize-1); }
                                                              ;






            s->lookahead -= s->prev_length-1;
            s->prev_length -= 2;
            do {
                if (++s->strstart <= max_insert) {
                    ((s->ins_h = (((s->ins_h)<<s->hash_shift) ^ (s->window[(s->strstart) + (3 -1)])) & s->hash_mask), hash_head = s->prev[(s->strstart) & s->w_mask] = s->head[s->ins_h], s->head[s->ins_h] = (Pos)(s->strstart));
                }
            } while (--s->prev_length != 0);
            s->match_available = 0;
            s->match_length = 3 -1;
            s->strstart++;

            if (bflush) { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };

        } else if (s->match_available) {




            ;
            { uch cc = (s->window[s->strstart-1]); s->d_buf[s->last_lit] = 0; s->l_buf[s->last_lit++] = cc; s->dyn_ltree[cc].fc.freq++; bflush = (s->last_lit == s->lit_bufsize-1); };
            if (bflush) {
                { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; };
            }
            s->strstart++;
            s->lookahead--;
            if (s->strm->avail_out == 0) return need_more;
        } else {



            s->match_available = 1;
            s->strstart++;
            s->lookahead--;
        }
    }
    ;
    if (s->match_available) {
        ;
        { uch cc = (s->window[s->strstart-1]); s->d_buf[s->last_lit] = 0; s->l_buf[s->last_lit++] = cc; s->dyn_ltree[cc].fc.freq++; bflush = (s->last_lit == s->lit_bufsize-1); };
        s->match_available = 0;
    }
    s->insert = s->strstart < 3 -1 ? s->strstart : 3 -1;
    if (flush == 4) {
        { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (1)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (1) ? finish_started : need_more; };
        return finish_done;
    }
    if (s->last_lit)
        { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };
    return block_done;
}







static block_state deflate_rle(s, flush)
    deflate_state *s;
    int flush;
{
    int bflush;
    uInt prev;
    Bytef *scan, *strend;

    for (;;) {




        if (s->lookahead <= 258) {
            fill_window(s);
            if (s->lookahead <= 258 && flush == 0) {
                return need_more;
            }
            if (s->lookahead == 0) break;
        }


        s->match_length = 0;
        if (s->lookahead >= 3 && s->strstart > 0) {
            scan = s->window + s->strstart - 1;
            prev = *scan;
            if (prev == *++scan && prev == *++scan && prev == *++scan) {
                strend = s->window + s->strstart + 258;
                do {
                } while (prev == *++scan && prev == *++scan &&
                         prev == *++scan && prev == *++scan &&
                         prev == *++scan && prev == *++scan &&
                         prev == *++scan && prev == *++scan &&
                         scan < strend);
                s->match_length = 258 - (int)(strend - scan);
                if (s->match_length > s->lookahead)
                    s->match_length = s->lookahead;
            }
            ;
        }


        if (s->match_length >= 3) {
            ;

            { uch len = (s->match_length - 3); ush dist = (1); s->d_buf[s->last_lit] = dist; s->l_buf[s->last_lit++] = len; dist--; s->dyn_ltree[_length_code[len]+256 +1].fc.freq++; s->dyn_dtree[((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)])].fc.freq++; bflush = (s->last_lit == s->lit_bufsize-1); };

            s->lookahead -= s->match_length;
            s->strstart += s->match_length;
            s->match_length = 0;
        } else {

            ;
            { uch cc = (s->window[s->strstart]); s->d_buf[s->last_lit] = 0; s->l_buf[s->last_lit++] = cc; s->dyn_ltree[cc].fc.freq++; bflush = (s->last_lit == s->lit_bufsize-1); };
            s->lookahead--;
            s->strstart++;
        }
        if (bflush) { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };
    }
    s->insert = 0;
    if (flush == 4) {
        { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (1)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (1) ? finish_started : need_more; };
        return finish_done;
    }
    if (s->last_lit)
        { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };
    return block_done;
}





static block_state deflate_huff(s, flush)
    deflate_state *s;
    int flush;
{
    int bflush;

    for (;;) {

        if (s->lookahead == 0) {
            fill_window(s);
            if (s->lookahead == 0) {
                if (flush == 0)
                    return need_more;
                break;
            }
        }


        s->match_length = 0;
        ;
        { uch cc = (s->window[s->strstart]); s->d_buf[s->last_lit] = 0; s->l_buf[s->last_lit++] = cc; s->dyn_ltree[cc].fc.freq++; bflush = (s->last_lit == s->lit_bufsize-1); };
        s->lookahead--;
        s->strstart++;
        if (bflush) { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };
    }
    s->insert = 0;
    if (flush == 4) {
        { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (1)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (1) ? finish_started : need_more; };
        return finish_done;
    }
    if (s->last_lit)
        { { _tr_flush_block(s, (s->block_start >= 0L ? (charf *)&s->window[(unsigned)s->block_start] : (charf *)0), (ulg)((long)s->strstart - s->block_start), (0)); s->block_start = s->strstart; flush_pending(s->strm); ; }; if (s->strm->avail_out == 0) return (0) ? finish_started : need_more; };
    return block_done;
}

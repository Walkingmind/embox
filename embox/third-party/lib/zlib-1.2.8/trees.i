# 1 "trees.c"
# 1 "/home/user/workspace/embox/third-party/lib/zlib-1.2.8//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "trees.c"
# 37 "trees.c"
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
# 38 "trees.c" 2
# 62 "trees.c"
static const int extra_lbits[29]
   = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0};

static const int extra_dbits[30]
   = {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};

static const int extra_blbits[19]
   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7};

static const uch bl_order[19]
   = {16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15};
# 114 "trees.c"
# 1 "trees.h" 1


static const ct_data static_ltree[(256 +1+29)+2] = {
{{ 12},{ 8}}, {{140},{ 8}}, {{ 76},{ 8}}, {{204},{ 8}}, {{ 44},{ 8}},
{{172},{ 8}}, {{108},{ 8}}, {{236},{ 8}}, {{ 28},{ 8}}, {{156},{ 8}},
{{ 92},{ 8}}, {{220},{ 8}}, {{ 60},{ 8}}, {{188},{ 8}}, {{124},{ 8}},
{{252},{ 8}}, {{ 2},{ 8}}, {{130},{ 8}}, {{ 66},{ 8}}, {{194},{ 8}},
{{ 34},{ 8}}, {{162},{ 8}}, {{ 98},{ 8}}, {{226},{ 8}}, {{ 18},{ 8}},
{{146},{ 8}}, {{ 82},{ 8}}, {{210},{ 8}}, {{ 50},{ 8}}, {{178},{ 8}},
{{114},{ 8}}, {{242},{ 8}}, {{ 10},{ 8}}, {{138},{ 8}}, {{ 74},{ 8}},
{{202},{ 8}}, {{ 42},{ 8}}, {{170},{ 8}}, {{106},{ 8}}, {{234},{ 8}},
{{ 26},{ 8}}, {{154},{ 8}}, {{ 90},{ 8}}, {{218},{ 8}}, {{ 58},{ 8}},
{{186},{ 8}}, {{122},{ 8}}, {{250},{ 8}}, {{ 6},{ 8}}, {{134},{ 8}},
{{ 70},{ 8}}, {{198},{ 8}}, {{ 38},{ 8}}, {{166},{ 8}}, {{102},{ 8}},
{{230},{ 8}}, {{ 22},{ 8}}, {{150},{ 8}}, {{ 86},{ 8}}, {{214},{ 8}},
{{ 54},{ 8}}, {{182},{ 8}}, {{118},{ 8}}, {{246},{ 8}}, {{ 14},{ 8}},
{{142},{ 8}}, {{ 78},{ 8}}, {{206},{ 8}}, {{ 46},{ 8}}, {{174},{ 8}},
{{110},{ 8}}, {{238},{ 8}}, {{ 30},{ 8}}, {{158},{ 8}}, {{ 94},{ 8}},
{{222},{ 8}}, {{ 62},{ 8}}, {{190},{ 8}}, {{126},{ 8}}, {{254},{ 8}},
{{ 1},{ 8}}, {{129},{ 8}}, {{ 65},{ 8}}, {{193},{ 8}}, {{ 33},{ 8}},
{{161},{ 8}}, {{ 97},{ 8}}, {{225},{ 8}}, {{ 17},{ 8}}, {{145},{ 8}},
{{ 81},{ 8}}, {{209},{ 8}}, {{ 49},{ 8}}, {{177},{ 8}}, {{113},{ 8}},
{{241},{ 8}}, {{ 9},{ 8}}, {{137},{ 8}}, {{ 73},{ 8}}, {{201},{ 8}},
{{ 41},{ 8}}, {{169},{ 8}}, {{105},{ 8}}, {{233},{ 8}}, {{ 25},{ 8}},
{{153},{ 8}}, {{ 89},{ 8}}, {{217},{ 8}}, {{ 57},{ 8}}, {{185},{ 8}},
{{121},{ 8}}, {{249},{ 8}}, {{ 5},{ 8}}, {{133},{ 8}}, {{ 69},{ 8}},
{{197},{ 8}}, {{ 37},{ 8}}, {{165},{ 8}}, {{101},{ 8}}, {{229},{ 8}},
{{ 21},{ 8}}, {{149},{ 8}}, {{ 85},{ 8}}, {{213},{ 8}}, {{ 53},{ 8}},
{{181},{ 8}}, {{117},{ 8}}, {{245},{ 8}}, {{ 13},{ 8}}, {{141},{ 8}},
{{ 77},{ 8}}, {{205},{ 8}}, {{ 45},{ 8}}, {{173},{ 8}}, {{109},{ 8}},
{{237},{ 8}}, {{ 29},{ 8}}, {{157},{ 8}}, {{ 93},{ 8}}, {{221},{ 8}},
{{ 61},{ 8}}, {{189},{ 8}}, {{125},{ 8}}, {{253},{ 8}}, {{ 19},{ 9}},
{{275},{ 9}}, {{147},{ 9}}, {{403},{ 9}}, {{ 83},{ 9}}, {{339},{ 9}},
{{211},{ 9}}, {{467},{ 9}}, {{ 51},{ 9}}, {{307},{ 9}}, {{179},{ 9}},
{{435},{ 9}}, {{115},{ 9}}, {{371},{ 9}}, {{243},{ 9}}, {{499},{ 9}},
{{ 11},{ 9}}, {{267},{ 9}}, {{139},{ 9}}, {{395},{ 9}}, {{ 75},{ 9}},
{{331},{ 9}}, {{203},{ 9}}, {{459},{ 9}}, {{ 43},{ 9}}, {{299},{ 9}},
{{171},{ 9}}, {{427},{ 9}}, {{107},{ 9}}, {{363},{ 9}}, {{235},{ 9}},
{{491},{ 9}}, {{ 27},{ 9}}, {{283},{ 9}}, {{155},{ 9}}, {{411},{ 9}},
{{ 91},{ 9}}, {{347},{ 9}}, {{219},{ 9}}, {{475},{ 9}}, {{ 59},{ 9}},
{{315},{ 9}}, {{187},{ 9}}, {{443},{ 9}}, {{123},{ 9}}, {{379},{ 9}},
{{251},{ 9}}, {{507},{ 9}}, {{ 7},{ 9}}, {{263},{ 9}}, {{135},{ 9}},
{{391},{ 9}}, {{ 71},{ 9}}, {{327},{ 9}}, {{199},{ 9}}, {{455},{ 9}},
{{ 39},{ 9}}, {{295},{ 9}}, {{167},{ 9}}, {{423},{ 9}}, {{103},{ 9}},
{{359},{ 9}}, {{231},{ 9}}, {{487},{ 9}}, {{ 23},{ 9}}, {{279},{ 9}},
{{151},{ 9}}, {{407},{ 9}}, {{ 87},{ 9}}, {{343},{ 9}}, {{215},{ 9}},
{{471},{ 9}}, {{ 55},{ 9}}, {{311},{ 9}}, {{183},{ 9}}, {{439},{ 9}},
{{119},{ 9}}, {{375},{ 9}}, {{247},{ 9}}, {{503},{ 9}}, {{ 15},{ 9}},
{{271},{ 9}}, {{143},{ 9}}, {{399},{ 9}}, {{ 79},{ 9}}, {{335},{ 9}},
{{207},{ 9}}, {{463},{ 9}}, {{ 47},{ 9}}, {{303},{ 9}}, {{175},{ 9}},
{{431},{ 9}}, {{111},{ 9}}, {{367},{ 9}}, {{239},{ 9}}, {{495},{ 9}},
{{ 31},{ 9}}, {{287},{ 9}}, {{159},{ 9}}, {{415},{ 9}}, {{ 95},{ 9}},
{{351},{ 9}}, {{223},{ 9}}, {{479},{ 9}}, {{ 63},{ 9}}, {{319},{ 9}},
{{191},{ 9}}, {{447},{ 9}}, {{127},{ 9}}, {{383},{ 9}}, {{255},{ 9}},
{{511},{ 9}}, {{ 0},{ 7}}, {{ 64},{ 7}}, {{ 32},{ 7}}, {{ 96},{ 7}},
{{ 16},{ 7}}, {{ 80},{ 7}}, {{ 48},{ 7}}, {{112},{ 7}}, {{ 8},{ 7}},
{{ 72},{ 7}}, {{ 40},{ 7}}, {{104},{ 7}}, {{ 24},{ 7}}, {{ 88},{ 7}},
{{ 56},{ 7}}, {{120},{ 7}}, {{ 4},{ 7}}, {{ 68},{ 7}}, {{ 36},{ 7}},
{{100},{ 7}}, {{ 20},{ 7}}, {{ 84},{ 7}}, {{ 52},{ 7}}, {{116},{ 7}},
{{ 3},{ 8}}, {{131},{ 8}}, {{ 67},{ 8}}, {{195},{ 8}}, {{ 35},{ 8}},
{{163},{ 8}}, {{ 99},{ 8}}, {{227},{ 8}}
};

static const ct_data static_dtree[30] = {
{{ 0},{ 5}}, {{16},{ 5}}, {{ 8},{ 5}}, {{24},{ 5}}, {{ 4},{ 5}},
{{20},{ 5}}, {{12},{ 5}}, {{28},{ 5}}, {{ 2},{ 5}}, {{18},{ 5}},
{{10},{ 5}}, {{26},{ 5}}, {{ 6},{ 5}}, {{22},{ 5}}, {{14},{ 5}},
{{30},{ 5}}, {{ 1},{ 5}}, {{17},{ 5}}, {{ 9},{ 5}}, {{25},{ 5}},
{{ 5},{ 5}}, {{21},{ 5}}, {{13},{ 5}}, {{29},{ 5}}, {{ 3},{ 5}},
{{19},{ 5}}, {{11},{ 5}}, {{27},{ 5}}, {{ 7},{ 5}}, {{23},{ 5}}
};

const uch __attribute__((visibility ("hidden"))) _dist_code[512] = {
 0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8,
 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10,
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13,
13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15,
15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 16, 17,
18, 18, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22,
23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27,
27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29
};

const uch __attribute__((visibility ("hidden"))) _length_code[258 -3 +1]= {
 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12,
13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16,
17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19,
19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22,
22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23,
23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28
};

static const int base_length[29] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 20, 24, 28, 32, 40, 48, 56,
64, 80, 96, 112, 128, 160, 192, 224, 0
};

static const int base_dist[30] = {
    0, 1, 2, 3, 4, 6, 8, 12, 16, 24,
   32, 48, 64, 96, 128, 192, 256, 384, 512, 768,
 1024, 1536, 2048, 3072, 4096, 6144, 8192, 12288, 16384, 24576
};
# 115 "trees.c" 2


struct static_tree_desc_s {
    const ct_data *static_tree;
    const intf *extra_bits;
    int extra_base;
    int elems;
    int max_length;
};

static static_tree_desc static_l_desc =
{static_ltree, extra_lbits, 256 +1, (256 +1+29), 15};

static static_tree_desc static_d_desc =
{static_dtree, extra_dbits, 0, 30, 15};

static static_tree_desc static_bl_desc =
{(const ct_data *)0, extra_blbits, 0, 19, 7};





static void tr_static_init (void);
static void init_block (deflate_state *s);
static void pqdownheap (deflate_state *s, ct_data *tree, int k);
static void gen_bitlen (deflate_state *s, tree_desc *desc);
static void gen_codes (ct_data *tree, int max_code, ushf *bl_count);
static void build_tree (deflate_state *s, tree_desc *desc);
static void scan_tree (deflate_state *s, ct_data *tree, int max_code);
static void send_tree (deflate_state *s, ct_data *tree, int max_code);
static int build_bl_tree (deflate_state *s);
static void send_all_trees (deflate_state *s, int lcodes, int dcodes, int blcodes)
                                           ;
static void compress_block (deflate_state *s, const ct_data *ltree, const ct_data *dtree)
                                                    ;
static int detect_data_type (deflate_state *s);
static unsigned bi_reverse (unsigned value, int length);
static void bi_windup (deflate_state *s);
static void bi_flush (deflate_state *s);
static void copy_block (deflate_state *s, charf *buf, unsigned len, int header)
                                          ;
# 234 "trees.c"
static void tr_static_init()
{
# 314 "trees.c"
}
# 381 "trees.c"
void __attribute__((visibility ("hidden"))) _tr_init(s)
    deflate_state *s;
{
    tr_static_init();

    s->l_desc.dyn_tree = s->dyn_ltree;
    s->l_desc.stat_desc = &static_l_desc;

    s->d_desc.dyn_tree = s->dyn_dtree;
    s->d_desc.stat_desc = &static_d_desc;

    s->bl_desc.dyn_tree = s->bl_tree;
    s->bl_desc.stat_desc = &static_bl_desc;

    s->bi_buf = 0;
    s->bi_valid = 0;






    init_block(s);
}




static void init_block(s)
    deflate_state *s;
{
    int n;


    for (n = 0; n < (256 +1+29); n++) s->dyn_ltree[n].fc.freq = 0;
    for (n = 0; n < 30; n++) s->dyn_dtree[n].fc.freq = 0;
    for (n = 0; n < 19; n++) s->bl_tree[n].fc.freq = 0;

    s->dyn_ltree[256].fc.freq = 1;
    s->opt_len = s->static_len = 0L;
    s->last_lit = s->matches = 0;
}
# 453 "trees.c"
static void pqdownheap(s, tree, k)
    deflate_state *s;
    ct_data *tree;
    int k;
{
    int v = s->heap[k];
    int j = k << 1;
    while (j <= s->heap_len) {

        if (j < s->heap_len &&
            (tree[s->heap[j+1]].fc.freq < tree[s->heap[j]].fc.freq || (tree[s->heap[j+1]].fc.freq == tree[s->heap[j]].fc.freq && s->depth[s->heap[j+1]] <= s->depth[s->heap[j]]))) {
            j++;
        }

        if ((tree[v].fc.freq < tree[s->heap[j]].fc.freq || (tree[v].fc.freq == tree[s->heap[j]].fc.freq && s->depth[v] <= s->depth[s->heap[j]]))) break;


        s->heap[k] = s->heap[j]; k = j;


        j <<= 1;
    }
    s->heap[k] = v;
}
# 488 "trees.c"
static void gen_bitlen(s, desc)
    deflate_state *s;
    tree_desc *desc;
{
    ct_data *tree = desc->dyn_tree;
    int max_code = desc->max_code;
    const ct_data *stree = desc->stat_desc->static_tree;
    const intf *extra = desc->stat_desc->extra_bits;
    int base = desc->stat_desc->extra_base;
    int max_length = desc->stat_desc->max_length;
    int h;
    int n, m;
    int bits;
    int xbits;
    ush f;
    int overflow = 0;

    for (bits = 0; bits <= 15; bits++) s->bl_count[bits] = 0;




    tree[s->heap[s->heap_max]].dl.len = 0;

    for (h = s->heap_max+1; h < (2*(256 +1+29)+1); h++) {
        n = s->heap[h];
        bits = tree[tree[n].dl.dad].dl.len + 1;
        if (bits > max_length) bits = max_length, overflow++;
        tree[n].dl.len = (ush)bits;


        if (n > max_code) continue;

        s->bl_count[bits]++;
        xbits = 0;
        if (n >= base) xbits = extra[n-base];
        f = tree[n].fc.freq;
        s->opt_len += (ulg)f * (bits + xbits);
        if (stree) s->static_len += (ulg)f * (stree[n].dl.len + xbits);
    }
    if (overflow == 0) return;

    ;



    do {
        bits = max_length-1;
        while (s->bl_count[bits] == 0) bits--;
        s->bl_count[bits]--;
        s->bl_count[bits+1] += 2;
        s->bl_count[max_length]--;



        overflow -= 2;
    } while (overflow > 0);






    for (bits = max_length; bits != 0; bits--) {
        n = s->bl_count[bits];
        while (n != 0) {
            m = s->heap[--h];
            if (m > max_code) continue;
            if ((unsigned) tree[m].dl.len != (unsigned) bits) {
                ;
                s->opt_len += ((long)bits - (long)tree[m].dl.len)
                              *(long)tree[m].fc.freq;
                tree[m].dl.len = (ush)bits;
            }
            n--;
        }
    }
}
# 575 "trees.c"
static void gen_codes (tree, max_code, bl_count)
    ct_data *tree;
    int max_code;
    ushf *bl_count;
{
    ush next_code[15 +1];
    ush code = 0;
    int bits;
    int n;




    for (bits = 1; bits <= 15; bits++) {
        next_code[bits] = code = (code + bl_count[bits-1]) << 1;
    }



   
                                      ;
    ;

    for (n = 0; n <= max_code; n++) {
        int len = tree[n].dl.len;
        if (len == 0) continue;

        tree[n].fc.code = bi_reverse(next_code[len]++, len);

       
                                                                             ;
    }
}
# 617 "trees.c"
static void build_tree(s, desc)
    deflate_state *s;
    tree_desc *desc;
{
    ct_data *tree = desc->dyn_tree;
    const ct_data *stree = desc->stat_desc->static_tree;
    int elems = desc->stat_desc->elems;
    int n, m;
    int max_code = -1;
    int node;





    s->heap_len = 0, s->heap_max = (2*(256 +1+29)+1);

    for (n = 0; n < elems; n++) {
        if (tree[n].fc.freq != 0) {
            s->heap[++(s->heap_len)] = max_code = n;
            s->depth[n] = 0;
        } else {
            tree[n].dl.len = 0;
        }
    }






    while (s->heap_len < 2) {
        node = s->heap[++(s->heap_len)] = (max_code < 2 ? ++max_code : 0);
        tree[node].fc.freq = 1;
        s->depth[node] = 0;
        s->opt_len--; if (stree) s->static_len -= stree[node].dl.len;

    }
    desc->max_code = max_code;




    for (n = s->heap_len/2; n >= 1; n--) pqdownheap(s, tree, n);




    node = elems;
    do {
        { n = s->heap[1]; s->heap[1] = s->heap[s->heap_len--]; pqdownheap(s, tree, 1); };
        m = s->heap[1];

        s->heap[--(s->heap_max)] = n;
        s->heap[--(s->heap_max)] = m;


        tree[node].fc.freq = tree[n].fc.freq + tree[m].fc.freq;
        s->depth[node] = (uch)((s->depth[n] >= s->depth[m] ?
                                s->depth[n] : s->depth[m]) + 1);
        tree[n].dl.dad = tree[m].dl.dad = (ush)node;







        s->heap[1] = node++;
        pqdownheap(s, tree, 1);

    } while (s->heap_len >= 2);

    s->heap[--(s->heap_max)] = s->heap[1];




    gen_bitlen(s, (tree_desc *)desc);


    gen_codes ((ct_data *)tree, max_code, s->bl_count);
}





static void scan_tree (s, tree, max_code)
    deflate_state *s;
    ct_data *tree;
    int max_code;
{
    int n;
    int prevlen = -1;
    int curlen;
    int nextlen = tree[0].dl.len;
    int count = 0;
    int max_count = 7;
    int min_count = 4;

    if (nextlen == 0) max_count = 138, min_count = 3;
    tree[max_code+1].dl.len = (ush)0xffff;

    for (n = 0; n <= max_code; n++) {
        curlen = nextlen; nextlen = tree[n+1].dl.len;
        if (++count < max_count && curlen == nextlen) {
            continue;
        } else if (count < min_count) {
            s->bl_tree[curlen].fc.freq += count;
        } else if (curlen != 0) {
            if (curlen != prevlen) s->bl_tree[curlen].fc.freq++;
            s->bl_tree[16].fc.freq++;
        } else if (count <= 10) {
            s->bl_tree[17].fc.freq++;
        } else {
            s->bl_tree[18].fc.freq++;
        }
        count = 0; prevlen = curlen;
        if (nextlen == 0) {
            max_count = 138, min_count = 3;
        } else if (curlen == nextlen) {
            max_count = 6, min_count = 3;
        } else {
            max_count = 7, min_count = 4;
        }
    }
}





static void send_tree (s, tree, max_code)
    deflate_state *s;
    ct_data *tree;
    int max_code;
{
    int n;
    int prevlen = -1;
    int curlen;
    int nextlen = tree[0].dl.len;
    int count = 0;
    int max_count = 7;
    int min_count = 4;


    if (nextlen == 0) max_count = 138, min_count = 3;

    for (n = 0; n <= max_code; n++) {
        curlen = nextlen; nextlen = tree[n+1].dl.len;
        if (++count < max_count && curlen == nextlen) {
            continue;
        } else if (count < min_count) {
            do { { int len = s->bl_tree[curlen].dl.len; if (s->bi_valid > (int)16 - len) { int val = s->bl_tree[curlen].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[curlen].fc.code) << s->bi_valid; s->bi_valid += len; }}; } while (--count != 0);

        } else if (curlen != 0) {
            if (curlen != prevlen) {
                { int len = s->bl_tree[curlen].dl.len; if (s->bi_valid > (int)16 - len) { int val = s->bl_tree[curlen].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[curlen].fc.code) << s->bi_valid; s->bi_valid += len; }}; count--;
            }
            ;
            { int len = s->bl_tree[16].dl.len; if (s->bi_valid > (int)16 - len) { int val = s->bl_tree[16].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[16].fc.code) << s->bi_valid; s->bi_valid += len; }}; { int len = 2; if (s->bi_valid > (int)16 - len) { int val = count-3; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(count-3) << s->bi_valid; s->bi_valid += len; }};

        } else if (count <= 10) {
            { int len = s->bl_tree[17].dl.len; if (s->bi_valid > (int)16 - len) { int val = s->bl_tree[17].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[17].fc.code) << s->bi_valid; s->bi_valid += len; }}; { int len = 3; if (s->bi_valid > (int)16 - len) { int val = count-3; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(count-3) << s->bi_valid; s->bi_valid += len; }};

        } else {
            { int len = s->bl_tree[18].dl.len; if (s->bi_valid > (int)16 - len) { int val = s->bl_tree[18].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[18].fc.code) << s->bi_valid; s->bi_valid += len; }}; { int len = 7; if (s->bi_valid > (int)16 - len) { int val = count-11; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(count-11) << s->bi_valid; s->bi_valid += len; }};
        }
        count = 0; prevlen = curlen;
        if (nextlen == 0) {
            max_count = 138, min_count = 3;
        } else if (curlen == nextlen) {
            max_count = 6, min_count = 3;
        } else {
            max_count = 7, min_count = 4;
        }
    }
}





static int build_bl_tree(s)
    deflate_state *s;
{
    int max_blindex;


    scan_tree(s, (ct_data *)s->dyn_ltree, s->l_desc.max_code);
    scan_tree(s, (ct_data *)s->dyn_dtree, s->d_desc.max_code);


    build_tree(s, (tree_desc *)(&(s->bl_desc)));
# 820 "trees.c"
    for (max_blindex = 19 -1; max_blindex >= 3; max_blindex--) {
        if (s->bl_tree[bl_order[max_blindex]].dl.len != 0) break;
    }

    s->opt_len += 3*(max_blindex+1) + 5+5+4;
   
                                       ;

    return max_blindex;
}






static void send_all_trees(s, lcodes, dcodes, blcodes)
    deflate_state *s;
    int lcodes, dcodes, blcodes;
{
    int rank;

    ;
   
                             ;
    ;
    { int len = 5; if (s->bi_valid > (int)16 - len) { int val = lcodes-257; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(lcodes-257) << s->bi_valid; s->bi_valid += len; }};
    { int len = 5; if (s->bi_valid > (int)16 - len) { int val = dcodes-1; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(dcodes-1) << s->bi_valid; s->bi_valid += len; }};
    { int len = 4; if (s->bi_valid > (int)16 - len) { int val = blcodes-4; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(blcodes-4) << s->bi_valid; s->bi_valid += len; }};
    for (rank = 0; rank < blcodes; rank++) {
        ;
        { int len = 3; if (s->bi_valid > (int)16 - len) { int val = s->bl_tree[bl_order[rank]].dl.len; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[bl_order[rank]].dl.len) << s->bi_valid; s->bi_valid += len; }};
    }
    ;

    send_tree(s, (ct_data *)s->dyn_ltree, lcodes-1);
    ;

    send_tree(s, (ct_data *)s->dyn_dtree, dcodes-1);
    ;
}




void __attribute__((visibility ("hidden"))) _tr_stored_block(s, buf, stored_len, last)
    deflate_state *s;
    charf *buf;
    ulg stored_len;
    int last;
{
    { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (0<<1)+last; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)((0<<1)+last) << s->bi_valid; s->bi_valid += len; }};




    copy_block(s, buf, (unsigned)stored_len, 1);
}




void __attribute__((visibility ("hidden"))) _tr_flush_bits(s)
    deflate_state *s;
{
    bi_flush(s);
}





void __attribute__((visibility ("hidden"))) _tr_align(s)
    deflate_state *s;
{
    { int len = 3; if (s->bi_valid > (int)16 - len) { int val = 1<<1; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(1<<1) << s->bi_valid; s->bi_valid += len; }};
    { int len = static_ltree[256].dl.len; if (s->bi_valid > (int)16 - len) { int val = static_ltree[256].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(static_ltree[256].fc.code) << s->bi_valid; s->bi_valid += len; }};



    bi_flush(s);
}





void __attribute__((visibility ("hidden"))) _tr_flush_block(s, buf, stored_len, last)
    deflate_state *s;
    charf *buf;
    ulg stored_len;
    int last;
{
    ulg opt_lenb, static_lenb;
    int max_blindex = 0;


    if (s->level > 0) {


        if (s->strm->data_type == 2)
            s->strm->data_type = detect_data_type(s);


        build_tree(s, (tree_desc *)(&(s->l_desc)));
       
                               ;

        build_tree(s, (tree_desc *)(&(s->d_desc)));
       
                               ;







        max_blindex = build_bl_tree(s);


        opt_lenb = (s->opt_len+3+7)>>3;
        static_lenb = (s->static_len+3+7)>>3;

       

                             ;

        if (static_lenb <= opt_lenb) opt_lenb = static_lenb;

    } else {
        ;
        opt_lenb = static_lenb = stored_len + 5;
    }




    if (stored_len+4 <= opt_lenb && buf != (char*)0) {
# 967 "trees.c"
        _tr_stored_block(s, buf, stored_len, last);




    } else if (s->strategy == 4 || static_lenb == opt_lenb) {

        { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (1<<1)+last; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)((1<<1)+last) << s->bi_valid; s->bi_valid += len; }};
        compress_block(s, (const ct_data *)static_ltree,
                       (const ct_data *)static_dtree);



    } else {
        { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (2<<1)+last; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)((2<<1)+last) << s->bi_valid; s->bi_valid += len; }};
        send_all_trees(s, s->l_desc.max_code+1, s->d_desc.max_code+1,
                       max_blindex+1);
        compress_block(s, (const ct_data *)s->dyn_ltree,
                       (const ct_data *)s->dyn_dtree);



    }
    ;



    init_block(s);

    if (last) {
        bi_windup(s);



    }
   
                                     ;
}





int __attribute__((visibility ("hidden"))) _tr_tally (s, dist, lc)
    deflate_state *s;
    unsigned dist;
    unsigned lc;
{
    s->d_buf[s->last_lit] = (ush)dist;
    s->l_buf[s->last_lit++] = (uch)lc;
    if (dist == 0) {

        s->dyn_ltree[lc].fc.freq++;
    } else {
        s->matches++;

        dist--;
       

                                                                         ;

        s->dyn_ltree[_length_code[lc]+256 +1].fc.freq++;
        s->dyn_dtree[((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)])].fc.freq++;
    }
# 1050 "trees.c"
    return (s->last_lit == s->lit_bufsize-1);




}




static void compress_block(s, ltree, dtree)
    deflate_state *s;
    const ct_data *ltree;
    const ct_data *dtree;
{
    unsigned dist;
    int lc;
    unsigned lx = 0;
    unsigned code;
    int extra;

    if (s->last_lit != 0) do {
        dist = s->d_buf[lx];
        lc = s->l_buf[lx++];
        if (dist == 0) {
            { int len = ltree[lc].dl.len; if (s->bi_valid > (int)16 - len) { int val = ltree[lc].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(ltree[lc].fc.code) << s->bi_valid; s->bi_valid += len; }};
            ;
        } else {

            code = _length_code[lc];
            { int len = ltree[code+256 +1].dl.len; if (s->bi_valid > (int)16 - len) { int val = ltree[code+256 +1].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(ltree[code+256 +1].fc.code) << s->bi_valid; s->bi_valid += len; }};
            extra = extra_lbits[code];
            if (extra != 0) {
                lc -= base_length[code];
                { int len = extra; if (s->bi_valid > (int)16 - len) { int val = lc; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(lc) << s->bi_valid; s->bi_valid += len; }};
            }
            dist--;
            code = ((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)]);
            ;

            { int len = dtree[code].dl.len; if (s->bi_valid > (int)16 - len) { int val = dtree[code].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(dtree[code].fc.code) << s->bi_valid; s->bi_valid += len; }};
            extra = extra_dbits[code];
            if (extra != 0) {
                dist -= base_dist[code];
                { int len = extra; if (s->bi_valid > (int)16 - len) { int val = dist; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(dist) << s->bi_valid; s->bi_valid += len; }};
            }
        }


       
                                     ;

    } while (lx < s->last_lit);

    { int len = ltree[256].dl.len; if (s->bi_valid > (int)16 - len) { int val = ltree[256].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(ltree[256].fc.code) << s->bi_valid; s->bi_valid += len; }};
}
# 1120 "trees.c"
static int detect_data_type(s)
    deflate_state *s;
{




    unsigned long black_mask = 0xf3ffc07fUL;
    int n;


    for (n = 0; n <= 31; n++, black_mask >>= 1)
        if ((black_mask & 1) && (s->dyn_ltree[n].fc.freq != 0))
            return 0;


    if (s->dyn_ltree[9].fc.freq != 0 || s->dyn_ltree[10].fc.freq != 0
            || s->dyn_ltree[13].fc.freq != 0)
        return 1;
    for (n = 32; n < 256; n++)
        if (s->dyn_ltree[n].fc.freq != 0)
            return 1;




    return 0;
}






static unsigned bi_reverse(code, len)
    unsigned code;
    int len;
{
    register unsigned res = 0;
    do {
        res |= code & 1;
        code >>= 1, res <<= 1;
    } while (--len > 0);
    return res >> 1;
}




static void bi_flush(s)
    deflate_state *s;
{
    if (s->bi_valid == 16) {
        { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; };
        s->bi_buf = 0;
        s->bi_valid = 0;
    } else if (s->bi_valid >= 8) {
        {s->pending_buf[s->pending++] = ((Byte)s->bi_buf);};
        s->bi_buf >>= 8;
        s->bi_valid -= 8;
    }
}




static void bi_windup(s)
    deflate_state *s;
{
    if (s->bi_valid > 8) {
        { {s->pending_buf[s->pending++] = ((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)(s->bi_buf) >> 8));}; };
    } else if (s->bi_valid > 0) {
        {s->pending_buf[s->pending++] = ((Byte)s->bi_buf);};
    }
    s->bi_buf = 0;
    s->bi_valid = 0;



}





static void copy_block(s, buf, len, header)
    deflate_state *s;
    charf *buf;
    unsigned len;
    int header;
{
    bi_windup(s);

    if (header) {
        { {s->pending_buf[s->pending++] = ((uch)(((ush)len) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)((ush)len) >> 8));}; };
        { {s->pending_buf[s->pending++] = ((uch)(((ush)~len) & 0xff));}; {s->pending_buf[s->pending++] = ((uch)((ush)((ush)~len) >> 8));}; };



    }



    while (len--) {
        {s->pending_buf[s->pending++] = (*buf++);};
    }
}

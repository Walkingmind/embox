# 1 "gzwrite.c"
# 1 "/home/user/workspace/embox/third-party/lib/zlib-1.2.8//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "gzwrite.c"





# 1 "gzguts.h" 1
# 21 "gzguts.h"
# 1 "/home/user/workspace/embox/./src/include/stdio.h" 1
# 14 "/home/user/workspace/embox/./src/include/stdio.h"
# 1 "/home/user/workspace/embox/./src/include/stdarg.h" 1
# 45 "/home/user/workspace/embox/./src/include/stdarg.h"
typedef __builtin_va_list va_list;
# 15 "/home/user/workspace/embox/./src/include/stdio.h" 2
# 1 "/home/user/workspace/embox/./src/include/stddef.h" 1
# 14 "/home/user/workspace/embox/./src/include/stddef.h"
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
# 15 "/home/user/workspace/embox/./src/include/stddef.h" 2
# 34 "/home/user/workspace/embox/./src/include/stddef.h"
typedef __size_t size_t;





typedef unsigned short wchar_t;





typedef __ptrdiff_t ptrdiff_t;
# 16 "/home/user/workspace/embox/./src/include/stdio.h" 2
# 1 "/home/user/workspace/embox/./src/include/kernel/printk.h" 1
# 12 "/home/user/workspace/embox/./src/include/kernel/printk.h"
extern int printk(const char *format, ...) __attribute__ ((format
    (printf, 1, 2)));
# 17 "/home/user/workspace/embox/./src/include/stdio.h" 2
# 36 "/home/user/workspace/embox/./src/include/stdio.h"
typedef struct file_struct {
 int fd;
 char has_ungetc;
 int ungetc;
} FILE;


struct stat;

# 1 "/home/user/workspace/embox/./src/include/sys/cdefs.h" 1
# 46 "/home/user/workspace/embox/./src/include/stdio.h" 2



extern int putc(int c, FILE *f);
extern int fputc(int c, FILE *f);

extern int getc(FILE *f);
extern int fgetc(FILE *f);




extern int puts(const char *s);
extern int fputs(const char *s, FILE *f);

extern int putchar(int c);





extern char *gets(char *s);

extern char *fgets(char *s, int n, FILE *stream);

extern int getchar(void);

extern int ungetc(int c, FILE *stream);


int ungetchar(int ch);

extern void perror(const char *s);




extern int printf(const char *format, ...);

extern int vprintf(const char *format, va_list args);




extern int fprintf(FILE *f, const char *format, ...);

extern int vfprintf(FILE *f, const char *format, va_list args);




extern int sprintf(char *s, const char *format, ...);

extern int vsprintf(char *s, const char *format, va_list args);




extern int snprintf(char *s, size_t n, const char *format, ...);

extern int vsnprintf(char *s, size_t n, const char *format, va_list args);




extern int scanf(const char *format, ...);

extern int fscanf(FILE *stream, const char *format, ...);




extern int sscanf(const char *out, const char *format, ...);





extern FILE *fopen(const char *path, const char *mode);






extern FILE *fdopen(int fd, const char *mode);





extern FILE *freopen(const char *path, const char *mode, FILE *stream);





extern size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);





extern size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);





extern int fclose(FILE *fp);

static inline int fflush(FILE *fp) { return (-1); }




extern int remove(const char *pathname);
# 171 "/home/user/workspace/embox/./src/include/stdio.h"
extern int fseek(FILE *stream, long int offset, int origin);

extern long int ftell(FILE *stream);

typedef long int fpos_t;

extern int fgetpos(FILE *stream, fpos_t *pos);

extern int fsetpos(FILE *stream, const fpos_t *pos);




extern void rewind(FILE *stream);




extern int rename(const char *oldpath, const char *newpath);




extern int fioctl(FILE *fp, int request, ...);

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;



extern void clearerr(FILE *stream);

extern int feof(FILE *stream);

extern int ferror(FILE *stream);

static inline int fileno(FILE *stream) {

 return stream->fd;
}


# 22 "gzguts.h" 2
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
# 25 "/home/user/workspace/embox/./src/compat/posix/include/sys/types.h"
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
# 452 "zconf.h"
# 1 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h" 1
# 15 "/home/user/workspace/embox/./src/compat/posix/include/unistd.h"
# 1 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h" 1
# 16 "/home/user/workspace/embox/./src/compat/posix/include/sys/stat.h"

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
# 1742 "zlib.h"
    struct internal_state {int dummy;};



extern const char * zError (int);
extern int inflateSyncPoint (z_streamp);
extern const z_crc_t * get_crc_table (void);
extern int inflateUndermine (z_streamp, int);
extern int inflateResetKeep (z_streamp);
extern int deflateResetKeep (z_streamp);






extern int gzvprintf (gzFile file, const char *format, va_list va)

                                                              ;
# 23 "gzguts.h" 2

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


# 25 "gzguts.h" 2
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


# 26 "gzguts.h" 2


# 1 "/home/user/workspace/embox/./src/compat/posix/include/fcntl.h" 1
# 26 "/home/user/workspace/embox/./src/compat/posix/include/fcntl.h"





extern int open(const char *path, int __oflag, ...);




extern int creat(const char *pathname, mode_t mode);

extern int fcntl(int fd, int cmd, ...);
# 71 "/home/user/workspace/embox/./src/compat/posix/include/fcntl.h"
struct flock {
 short l_type;
 short l_whence;
 off_t l_start;
 off_t l_len;
 pid_t l_pid;
};


# 29 "gzguts.h" 2
# 1 "/home/user/workspace/embox/./src/compat/posix/include/posix_errno.h" 1
# 12 "/home/user/workspace/embox/./src/compat/posix/include/posix_errno.h"
# 1 "/home/user/workspace/embox/./src/include/kernel/task/errno.h" 1
# 14 "/home/user/workspace/embox/./src/include/kernel/task/errno.h"


extern int * task_self_errno_ptr(void);

struct task;

int task_errno(struct task *task);

void task_errno_set(struct task *task, int errno);


# 13 "/home/user/workspace/embox/./src/compat/posix/include/posix_errno.h" 2
# 30 "gzguts.h" 2
# 124 "gzguts.h"
# 1 "/home/user/workspace/embox/./src/include/errno.h" 1
# 125 "gzguts.h" 2
# 133 "gzguts.h"
    extern gzFile gzopen64 (const char *, const char *);
    extern off_t gzseek64 (gzFile, off_t, int);
    extern off_t gztell64 (gzFile);
    extern off_t gzoffset64 (gzFile);
# 162 "gzguts.h"
typedef struct {

    struct gzFile_s x;




    int mode;
    int fd;
    char *path;
    unsigned size;
    unsigned want;
    unsigned char *in;
    unsigned char *out;
    int direct;

    int how;
    off_t start;
    int eof;
    int past;

    int level;
    int strategy;

    off_t skip;
    int seek;

    int err;
    char *msg;

    z_stream strm;
} gz_state;
typedef gz_state *gz_statep;


void __attribute__((visibility ("hidden"))) gz_error (gz_statep, int, const char *);
# 7 "gzwrite.c" 2


static int gz_init (gz_statep);
static int gz_comp (gz_statep, int);
static int gz_zero (gz_statep, off_t);



static int gz_init(state)
    gz_statep state;
{
    int ret;
    z_streamp strm = &(state->strm);


    state->in = (unsigned char *)malloc(state->want);
    if (state->in == ((void *)0)) {
        gz_error(state, (-4), "out of memory");
        return -1;
    }


    if (!state->direct) {

        state->out = (unsigned char *)malloc(state->want);
        if (state->out == ((void *)0)) {
            free(state->in);
            gz_error(state, (-4), "out of memory");
            return -1;
        }


        strm->zalloc = 0;
        strm->zfree = 0;
        strm->opaque = 0;
        ret = deflateInit2_((strm),(state->level),(8),(15 + 16),(8), (state->strategy), "1.2.8", (int)sizeof(z_stream))
                                                                          ;
        if (ret != 0) {
            free(state->out);
            free(state->in);
            gz_error(state, (-4), "out of memory");
            return -1;
        }
    }


    state->size = state->want;


    if (!state->direct) {
        strm->avail_out = state->size;
        strm->next_out = state->out;
        state->x.next = strm->next_out;
    }
    return 0;
}







static int gz_comp(state, flush)
    gz_statep state;
    int flush;
{
    int ret, got;
    unsigned have;
    z_streamp strm = &(state->strm);


    if (state->size == 0 && gz_init(state) == -1)
        return -1;


    if (state->direct) {
        got = write(state->fd, strm->next_in, strm->avail_in);
        if (got < 0 || (unsigned)got != strm->avail_in) {
            gz_error(state, (-1), strerror((* task_self_errno_ptr())));
            return -1;
        }
        strm->avail_in = 0;
        return 0;
    }


    ret = 0;
    do {


        if (strm->avail_out == 0 || (flush != 0 &&
            (flush != 4 || ret == 1))) {
            have = (unsigned)(strm->next_out - state->x.next);
            if (have && ((got = write(state->fd, state->x.next, have)) < 0 ||
                         (unsigned)got != have)) {
                gz_error(state, (-1), strerror((* task_self_errno_ptr())));
                return -1;
            }
            if (strm->avail_out == 0) {
                strm->avail_out = state->size;
                strm->next_out = state->out;
            }
            state->x.next = strm->next_out;
        }


        have = strm->avail_out;
        ret = deflate(strm, flush);
        if (ret == (-2)) {
            gz_error(state, (-2),
                      "internal error: deflate stream corrupt");
            return -1;
        }
        have -= strm->avail_out;
    } while (have);


    if (flush == 4)
        deflateReset(strm);


    return 0;
}


static int gz_zero(state, len)
    gz_statep state;
    off_t len;
{
    int first;
    unsigned n;
    z_streamp strm = &(state->strm);


    if (strm->avail_in && gz_comp(state, 0) == -1)
        return -1;


    first = 1;
    while (len) {
        n = (sizeof(int) == sizeof(off_t) && (state->size) > 2147483647) || (off_t)state->size > len ?
            (unsigned)len : state->size;
        if (first) {
            memset(state->in, 0, n);
            first = 0;
        }
        strm->avail_in = n;
        strm->next_in = state->in;
        state->x.pos += n;
        if (gz_comp(state, 0) == -1)
            return -1;
        len -= n;
    }
    return 0;
}


int gzwrite(file, buf, len)
    gzFile file;
    voidpc buf;
    unsigned len;
{
    unsigned put = len;
    gz_statep state;
    z_streamp strm;


    if (file == ((void *)0))
        return 0;
    state = (gz_statep)file;
    strm = &(state->strm);


    if (state->mode != 31153 || state->err != 0)
        return 0;



    if ((int)len < 0) {
        gz_error(state, (-3), "requested length does not fit in int");
        return 0;
    }


    if (len == 0)
        return 0;


    if (state->size == 0 && gz_init(state) == -1)
        return 0;


    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            return 0;
    }


    if (len < state->size) {

        do {
            unsigned have, copy;

            if (strm->avail_in == 0)
                strm->next_in = state->in;
            have = (unsigned)((strm->next_in + strm->avail_in) - state->in);
            copy = state->size - have;
            if (copy > len)
                copy = len;
            memcpy(state->in + have, buf, copy);
            strm->avail_in += copy;
            state->x.pos += copy;
            buf = (const char *)buf + copy;
            len -= copy;
            if (len && gz_comp(state, 0) == -1)
                return 0;
        } while (len);
    }
    else {

        if (strm->avail_in && gz_comp(state, 0) == -1)
            return 0;


        strm->avail_in = len;
        strm->next_in = ( Bytef *)buf;
        state->x.pos += len;
        if (gz_comp(state, 0) == -1)
            return 0;
    }


    return (int)put;
}


int gzputc(file, c)
    gzFile file;
    int c;
{
    unsigned have;
    unsigned char buf[1];
    gz_statep state;
    z_streamp strm;


    if (file == ((void *)0))
        return -1;
    state = (gz_statep)file;
    strm = &(state->strm);


    if (state->mode != 31153 || state->err != 0)
        return -1;


    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            return -1;
    }



    if (state->size) {
        if (strm->avail_in == 0)
            strm->next_in = state->in;
        have = (unsigned)((strm->next_in + strm->avail_in) - state->in);
        if (have < state->size) {
            state->in[have] = c;
            strm->avail_in++;
            state->x.pos++;
            return c & 0xff;
        }
    }


    buf[0] = c;
    if (gzwrite(file, buf, 1) != 1)
        return -1;
    return c & 0xff;
}


int gzputs(file, str)
    gzFile file;
    const char *str;
{
    int ret;
    unsigned len;


    len = (unsigned)strlen(str);
    ret = gzwrite(file, str, len);
    return ret == 0 && len != 0 ? -1 : ret;
}





int gzvprintf(gzFile file, const char *format, va_list va)
{
    int size, len;
    gz_statep state;
    z_streamp strm;


    if (file == ((void *)0))
        return -1;
    state = (gz_statep)file;
    strm = &(state->strm);


    if (state->mode != 31153 || state->err != 0)
        return 0;


    if (state->size == 0 && gz_init(state) == -1)
        return 0;


    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            return 0;
    }


    if (strm->avail_in && gz_comp(state, 0) == -1)
        return 0;


    size = (int)(state->size);
    state->in[size - 1] = 0;
# 357 "gzwrite.c"
    len = vsnprintf((char *)(state->in), size, format, va);




    if (len <= 0 || len >= (int)size || state->in[size - 1] != 0)
        return 0;


    strm->avail_in = (unsigned)len;
    strm->next_in = state->in;
    state->x.pos += len;
    return len;
}

int gzprintf(gzFile file, const char *format, ...)
{
    va_list va;
    int ret;

    __builtin_va_start(va,format);
    ret = gzvprintf(file, format, va);
    __builtin_va_end(va);
    return ret;
}
# 465 "gzwrite.c"
int gzflush(file, flush)
    gzFile file;
    int flush;
{
    gz_statep state;


    if (file == ((void *)0))
        return -1;
    state = (gz_statep)file;


    if (state->mode != 31153 || state->err != 0)
        return (-2);


    if (flush < 0 || flush > 4)
        return (-2);


    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            return -1;
    }


    gz_comp(state, flush);
    return state->err;
}


int gzsetparams(file, level, strategy)
    gzFile file;
    int level;
    int strategy;
{
    gz_statep state;
    z_streamp strm;


    if (file == ((void *)0))
        return (-2);
    state = (gz_statep)file;
    strm = &(state->strm);


    if (state->mode != 31153 || state->err != 0)
        return (-2);


    if (level == state->level && strategy == state->strategy)
        return 0;


    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            return -1;
    }


    if (state->size) {

        if (strm->avail_in && gz_comp(state, 1) == -1)
            return state->err;
        deflateParams(strm, level, strategy);
    }
    state->level = level;
    state->strategy = strategy;
    return 0;
}


int gzclose_w(file)
    gzFile file;
{
    int ret = 0;
    gz_statep state;


    if (file == ((void *)0))
        return (-2);
    state = (gz_statep)file;


    if (state->mode != 31153)
        return (-2);


    if (state->seek) {
        state->seek = 0;
        if (gz_zero(state, state->skip) == -1)
            ret = state->err;
    }


    if (gz_comp(state, 4) == -1)
        ret = state->err;
    if (state->size) {
        if (!state->direct) {
            (void)deflateEnd(&(state->strm));
            free(state->out);
        }
        free(state->in);
    }
    gz_error(state, 0, ((void *)0));
    free(state->path);
    if (close(state->fd) == -1)
        ret = (-1);
    free(state);
    return ret;
}

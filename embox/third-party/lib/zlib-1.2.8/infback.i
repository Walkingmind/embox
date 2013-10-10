# 1 "infback.c"
# 1 "/home/anton/workspace/embox-trunk/third-party/lib/zlib-1.2.8//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "infback.c"
# 13 "infback.c"
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







# 1 "/home/anton/workspace/embox-trunk/./src/include/limits.h" 1
# 14 "/home/anton/workspace/embox-trunk/./src/include/limits.h"
# 1 "/home/anton/workspace/embox-trunk/./src/arch/x86/include/asm/limits.h" 1
# 12 "/home/anton/workspace/embox-trunk/./src/arch/x86/include/asm/limits.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/asm-generic/limits32.h" 1
# 13 "/home/anton/workspace/embox-trunk/./src/arch/x86/include/asm/limits.h" 2
# 15 "/home/anton/workspace/embox-trunk/./src/include/limits.h" 2
# 396 "zconf.h" 2
# 406 "zconf.h"
   typedef unsigned z_crc_t;
# 421 "zconf.h"
# 1 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h" 1
# 14 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h"
# 1 "/home/anton/workspace/embox-trunk/./src/arch/x86/include/asm/types.h" 1
# 12 "/home/anton/workspace/embox-trunk/./src/arch/x86/include/asm/types.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/asm-generic/types32.h" 1
# 16 "/home/anton/workspace/embox-trunk/./src/include/asm-generic/types32.h"
typedef signed char __s8;
typedef unsigned char __u8;
typedef signed short __s16;
typedef unsigned short __u16;
typedef signed int __s32;
typedef unsigned int __u32;
typedef long long __s64;
typedef unsigned long long __u64;

typedef unsigned int __size_t;
typedef signed int __ptrdiff_t;

typedef unsigned long int __uintptr_t;
typedef long int __intptr_t;

typedef __s32 __s_fast;
typedef __u32 __u_fast;
# 13 "/home/anton/workspace/embox-trunk/./src/arch/x86/include/asm/types.h" 2
# 15 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h" 2

# 1 "/home/anton/workspace/embox-trunk/./src/include/defines/size_t.h" 1
# 12 "/home/anton/workspace/embox-trunk/./src/include/defines/size_t.h"
 typedef unsigned int size_t;
# 17 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h" 2





typedef int ssize_t;


# 1 "/home/anton/workspace/embox-trunk/./src/include/defines/clock_t.h" 1
# 14 "/home/anton/workspace/embox-trunk/./src/include/defines/clock_t.h"
 typedef unsigned long clock_t;
# 26 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h" 2



typedef unsigned long useconds_t;


# 1 "/home/anton/workspace/embox-trunk/./src/include/defines/suseconds_t.h" 1
# 13 "/home/anton/workspace/embox-trunk/./src/include/defines/suseconds_t.h"
typedef long suseconds_t;
# 33 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h" 2

typedef unsigned long spinlock_t;

typedef __u32 gfp_t;

typedef struct {
 volatile int counter;
} atomic_t;


# 1 "/home/anton/workspace/embox-trunk/./src/include/defines/time_t.h" 1
# 13 "/home/anton/workspace/embox-trunk/./src/include/defines/time_t.h"
 typedef long time_t;
# 44 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h" 2
# 1 "/home/anton/workspace/embox-trunk/./src/include/defines/timer_t.h" 1
# 45 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h" 2

typedef int id_t;

typedef int pid_t;

typedef int dev_t;


# 1 "/home/anton/workspace/embox-trunk/./src/include/defines/clockid_t.h" 1
# 14 "/home/anton/workspace/embox-trunk/./src/include/defines/clockid_t.h"
 typedef int clockid_t;
# 54 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h" 2


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





# 1 "/home/anton/workspace/embox-trunk/./src/include/stdarg.h" 1
# 45 "/home/anton/workspace/embox-trunk/./src/include/stdarg.h"
typedef __builtin_va_list va_list;
# 428 "zconf.h" 2
# 452 "zconf.h"
# 1 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/unistd.h" 1
# 15 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/unistd.h"
# 1 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/stat.h" 1
# 13 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/stat.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/sys/cdefs.h" 1
# 14 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/stat.h" 2



# 82 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/stat.h"
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
# 114 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/stat.h"
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


# 16 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/unistd.h" 2


# 1 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/posix_environ.h" 1
# 12 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/posix_environ.h"
extern char *** task_self_environ_ptr(void);
# 19 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/unistd.h" 2

# 1 "/home/anton/workspace/embox-trunk/./src/include/kernel/task.h" 1
# 12 "/home/anton/workspace/embox-trunk/./src/include/kernel/task.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/util/dlist.h" 1
# 20 "/home/anton/workspace/embox-trunk/./src/include/util/dlist.h"
# 1 "/home/anton/workspace/embox-trunk/./build/base/src-gen/include/module/embox/util/DList.h" 1






# 1 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h" 1
# 21 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/stddef.h" 1
# 24 "/home/anton/workspace/embox-trunk/./src/include/stddef.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/defines/null.h" 1
# 25 "/home/anton/workspace/embox-trunk/./src/include/stddef.h" 2



# 1 "/home/anton/workspace/embox-trunk/./src/include/defines/wchar_t.h" 1
# 13 "/home/anton/workspace/embox-trunk/./src/include/defines/wchar_t.h"
 typedef int wchar_t;
# 29 "/home/anton/workspace/embox-trunk/./src/include/stddef.h" 2

typedef __ptrdiff_t ptrdiff_t;
# 22 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h" 2
# 1 "/home/anton/workspace/embox-trunk/./src/include/assert.h" 1
# 14 "/home/anton/workspace/embox-trunk/./src/include/assert.h"
# 1 "/home/anton/workspace/embox-trunk/./build/base/src-gen/include/module/embox/lib/LibCAssert.h" 1






# 1 "/home/anton/workspace/embox-trunk/./src/include/../lib/assert_impl.h" 1
# 12 "/home/anton/workspace/embox-trunk/./src/include/../lib/assert_impl.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/util/location.h" 1
# 13 "/home/anton/workspace/embox-trunk/./src/include/util/location.h"
struct location {
 const char *file;
 int line;
};

struct location_func {
 struct location at;
 const char *func;
};
# 13 "/home/anton/workspace/embox-trunk/./src/include/../lib/assert_impl.h" 2
# 1 "/home/anton/workspace/embox-trunk/./src/compat/linux/include/linux/compiler.h" 1
# 14 "/home/anton/workspace/embox-trunk/./src/include/../lib/assert_impl.h" 2
# 31 "/home/anton/workspace/embox-trunk/./src/include/../lib/assert_impl.h"
struct __assertion_point {
 struct location_func location;
 const char *expression;
};




extern

void __attribute__ ((noreturn)) __assertion_handle_failure(
  const struct __assertion_point *point);
# 8 "/home/anton/workspace/embox-trunk/./build/base/src-gen/include/module/embox/lib/LibCAssert.h" 2
# 15 "/home/anton/workspace/embox-trunk/./src/include/assert.h" 2
# 23 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h" 2






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
# 77 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h"
static inline struct dlist_head *dlist_init(struct dlist_head *list_head) {

 list_head->list_id = list_head;
 list_head->next = list_head->prev = list_head;

 return list_head;
}
# 92 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h"
static inline void dlist_add_next(struct dlist_head *_new,
  struct dlist_head *list) {


 ({do { if (!((__builtin_constant_p(!__is_linked(_new)) ? !!(!__is_linked(_new)) : __builtin_expect(!!(!__is_linked(_new)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h", .line = 96, }, .func = __func__, }, .expression = "!__is_linked(_new)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});



 ({do { if (!((__builtin_constant_p(__is_linked(list)) ? !!(__is_linked(list)) : __builtin_expect(!!(__is_linked(list)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h", .line = 100, }, .func = __func__, }, .expression = "__is_linked(list)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});

 _new->list_id = list->list_id;





 __dlist_add(_new, list->next, list);
}
# 119 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h"
static inline void dlist_add_prev(struct dlist_head *_new,
  struct dlist_head *list) {


 ({do { if (!((__builtin_constant_p(!__is_linked(_new)) ? !!(!__is_linked(_new)) : __builtin_expect(!!(!__is_linked(_new)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h", .line = 123, }, .func = __func__, }, .expression = "!__is_linked(_new)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});



 ({do { if (!((__builtin_constant_p(__is_linked(list)) ? !!(__is_linked(list)) : __builtin_expect(!!(__is_linked(list)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h", .line = 127, }, .func = __func__, }, .expression = "__is_linked(list)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});

 _new->list_id = list->list_id;





 __dlist_add(_new, list, list->prev);
}
# 145 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h"
static inline void dlist_del(struct dlist_head *head) {
 ({do { if (!((__builtin_constant_p(__is_linked(head)) ? !!(__is_linked(head)) : __builtin_expect(!!(__is_linked(head)), 1)))) { extern char __assertion_message_buff[]; static const struct __assertion_point __assertion_point = { .location = { .at = { .file = "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h", .line = 146, }, .func = __func__, }, .expression = "__is_linked(head)", }; extern int sprintf(char *s, const char *format, ...); sprintf(__assertion_message_buff, "" ); __assertion_handle_failure(&__assertion_point); } } while(0);});




 head->prev->next = head->next;
 head->next->prev = head->prev;

 head->list_id = (struct dlist_head *)((void *)0);
}
# 8 "/home/anton/workspace/embox-trunk/./build/base/src-gen/include/module/embox/util/DList.h" 2
# 21 "/home/anton/workspace/embox-trunk/./src/include/util/dlist.h" 2






struct dlist_head;
# 60 "/home/anton/workspace/embox-trunk/./src/include/util/dlist.h"
extern struct dlist_head *dlist_init(struct dlist_head *list_head);
# 73 "/home/anton/workspace/embox-trunk/./src/include/util/dlist.h"
extern struct dlist_head *dlist_head_init(struct dlist_head *item_head);
# 84 "/home/anton/workspace/embox-trunk/./src/include/util/dlist.h"
extern void dlist_add_next(struct dlist_head *_new, struct dlist_head *list);
# 94 "/home/anton/workspace/embox-trunk/./src/include/util/dlist.h"
extern void dlist_add_prev(struct dlist_head *_new, struct dlist_head *list);







extern void dlist_del(struct dlist_head *item_head);







static inline void dlist_move(struct dlist_head *head, struct dlist_head *list) {
 dlist_del(head);
 dlist_add_next(head, list);
}







static inline int dlist_empty(struct dlist_head *head) {
 return head == head->next;
}
# 13 "/home/anton/workspace/embox-trunk/./src/include/kernel/task.h" 2
# 1 "/home/anton/workspace/embox-trunk/./src/include/util/array.h" 1
# 34 "/home/anton/workspace/embox-trunk/./src/include/util/array.h"
# 1 "/home/anton/workspace/embox-trunk/./build/base/src-gen/include/module/embox/util/Array.h" 1






# 1 "/home/anton/workspace/embox-trunk/./src/include/../util/array_impl.h" 1
# 16 "/home/anton/workspace/embox-trunk/./src/include/../util/array_impl.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/util/macro.h" 1
# 17 "/home/anton/workspace/embox-trunk/./src/include/../util/array_impl.h" 2
# 8 "/home/anton/workspace/embox-trunk/./build/base/src-gen/include/module/embox/util/Array.h" 2
# 35 "/home/anton/workspace/embox-trunk/./src/include/util/array.h" 2
# 14 "/home/anton/workspace/embox-trunk/./src/include/kernel/task.h" 2




# 1 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/task_priority.h" 1
# 18 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/task_priority.h"
typedef short task_priority_t;
# 19 "/home/anton/workspace/embox-trunk/./src/include/kernel/task.h" 2
# 1 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/thread_key_table.h" 1
# 11 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/thread_key_table.h"
struct task;

# 1 "/home/anton/workspace/embox-trunk/./build/base/src-gen/include/module/embox/kernel/task/task_key_table.h" 1
# 11 "/home/anton/workspace/embox-trunk/./build/base/src-gen/include/module/embox/kernel/task/task_key_table.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/../kernel/task/task_thread_key.h" 1
# 13 "/home/anton/workspace/embox-trunk/./src/include/../kernel/task/task_thread_key.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/framework/mod/options.h" 1
# 14 "/home/anton/workspace/embox-trunk/./src/include/../kernel/task/task_thread_key.h" 2
# 1 "/home/anton/workspace/embox-trunk/./src/include/util/indexator.h" 1
# 19 "/home/anton/workspace/embox-trunk/./src/include/util/indexator.h"
enum index_type {
 INDEX_RANDOM,
 INDEX_MIN,
 INDEX_MAX,
 INDEX_PREV,
 INDEX_NEXT
};




struct indexator {
 size_t last;

 size_t min;
 size_t max;
 size_t prev;
 size_t next;

 unsigned long *mask;
 size_t start;
 size_t end;
 size_t clamp_min;
 size_t clamp_max;
};

typedef unsigned long index_data_t;
# 108 "/home/anton/workspace/embox-trunk/./src/include/util/indexator.h"
extern void index_init(struct indexator *ind, size_t start,
  size_t capacity, void *data);
# 118 "/home/anton/workspace/embox-trunk/./src/include/util/indexator.h"
extern void index_clamp(struct indexator *ind, size_t min,
  size_t max);






extern void index_clean(struct indexator *ind);







extern size_t index_start(struct indexator *ind);







extern size_t index_end(struct indexator *ind);







extern size_t index_capacity(struct indexator *ind);







extern size_t index_clamp_min(struct indexator *ind);







extern size_t index_clamp_max(struct indexator *ind);
# 175 "/home/anton/workspace/embox-trunk/./src/include/util/indexator.h"
extern size_t index_find(struct indexator *ind,
  enum index_type type);
# 185 "/home/anton/workspace/embox-trunk/./src/include/util/indexator.h"
extern int index_try_lock(struct indexator *ind, size_t idx);







extern void index_lock(struct indexator *ind, size_t idx);
# 202 "/home/anton/workspace/embox-trunk/./src/include/util/indexator.h"
extern int index_locked(struct indexator *ind, size_t idx);







extern void index_unlock(struct indexator *ind, size_t idx);
# 219 "/home/anton/workspace/embox-trunk/./src/include/util/indexator.h"
extern size_t index_alloc(struct indexator *ind,
  enum index_type type);
# 229 "/home/anton/workspace/embox-trunk/./src/include/util/indexator.h"
extern void index_free(struct indexator *ind, size_t idx);
# 15 "/home/anton/workspace/embox-trunk/./src/include/../kernel/task/task_thread_key.h" 2
# 1 "/home/anton/workspace/embox-trunk/./src/include/kernel/thread/sync/mutex.h" 1
# 13 "/home/anton/workspace/embox-trunk/./src/include/kernel/thread/sync/mutex.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/kernel/sched/wait_queue.h" 1
# 14 "/home/anton/workspace/embox-trunk/./src/include/kernel/sched/wait_queue.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/kernel/work.h" 1
# 14 "/home/anton/workspace/embox-trunk/./src/include/kernel/work.h"
struct work;

struct work_queue {
 struct dlist_head list;
};

struct work {
 struct dlist_head link;
 unsigned int state;

 struct work_queue *wq;
 int (*handler)(struct work *);
};



extern void work_init(struct work *w, int (*handler)(struct work *),
  unsigned int flags);

extern void work_queue_init(struct work_queue *wq);


extern void work_post(struct work *w , struct work_queue *wq);
extern void work_cancel(struct work *w);

extern void work_disable(struct work *w);
extern void work_enable(struct work *w);

extern void work_queue_run(struct work_queue *wq);
# 15 "/home/anton/workspace/embox-trunk/./src/include/kernel/sched/wait_queue.h" 2

struct wait_queue {
 struct dlist_head list;
 int flag;
};

struct thread;
struct wait_link {
 struct dlist_head link;
 struct thread *thread;
};





static inline void wait_queue_init(struct wait_queue *wait_queue) {
 dlist_init(&wait_queue->list);
}

static inline int wait_queue_empty(struct wait_queue *wait_queue) {
 return dlist_empty(&wait_queue->list);
}

extern void wait_queue_insert(struct wait_queue *wait_queue,
  struct wait_link *wait_link);
extern void wait_queue_prepare(struct wait_link *wait_link);
extern void wait_queue_cleanup(struct wait_link *wait_link);

extern int wait_queue_wait(struct wait_queue *wait_queue, int timeout);
extern int wait_queue_wait_locked(struct wait_queue *wait_queue, int timeout);
extern void wait_queue_notify(struct wait_queue *wait_queue);
extern void wait_queue_notify_all_err(struct wait_queue *wait_queue, int error);

static inline void wait_queue_notify_all(struct wait_queue *wait_queue) {
 wait_queue_notify_all_err(wait_queue, 0);
}


# 14 "/home/anton/workspace/embox-trunk/./src/include/kernel/thread/sync/mutex.h" 2
# 1 "/home/anton/workspace/embox-trunk/./src/include/kernel/thread/sync/mutexattr.h" 1
# 28 "/home/anton/workspace/embox-trunk/./src/include/kernel/thread/sync/mutexattr.h"
struct mutexattr {
 int type;
};





extern int mutexattr_init(struct mutexattr *attr);





extern int mutexattr_copy(const struct mutexattr *source_attr,
  struct mutexattr *dest_attr);




extern int mutexattr_destroy(struct mutexattr *attr);





extern int mutexattr_gettype(const struct mutexattr *attr, int *type);





extern int mutexattr_settype(struct mutexattr *attr, int type);
# 15 "/home/anton/workspace/embox-trunk/./src/include/kernel/thread/sync/mutex.h" 2

struct thread;




struct mutex {
 struct wait_queue wq;
 struct thread *holder;
 struct mutexattr attr;

 int lock_count;
};
# 57 "/home/anton/workspace/embox-trunk/./src/include/kernel/thread/sync/mutex.h"







extern void mutex_init_default(struct mutex *m, const struct mutexattr *attr);





extern void mutex_init(struct mutex *mutex);
# 80 "/home/anton/workspace/embox-trunk/./src/include/kernel/thread/sync/mutex.h"
extern int mutex_lock(struct mutex *free_mutex);







extern int mutex_unlock(struct mutex *locked_mutex);







extern int mutex_trylock(struct mutex *free_mutex);


# 16 "/home/anton/workspace/embox-trunk/./src/include/../kernel/task/task_thread_key.h" 2






struct thread_key_table {
 struct indexator indexator;
 char ind_buff[64 / 8 + 1];
 void *destructor_table[64];
 struct mutex mutex;
};
typedef struct thread_key_table __thread_key_table_t;
# 12 "/home/anton/workspace/embox-trunk/./build/base/src-gen/include/module/embox/kernel/task/task_key_table.h" 2
# 14 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/thread_key_table.h" 2

typedef __thread_key_table_t thread_key_table_t;

extern void task_thread_key_init(struct task *task);

extern int task_thread_key_exist(struct task *task, size_t idx);

extern int task_thread_key_create(struct task *task, size_t *idx);

extern int task_thread_key_destroy(struct task *task, size_t idx);
# 20 "/home/anton/workspace/embox-trunk/./src/include/kernel/task.h" 2







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

 thread_key_table_t key_table;
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
# 101 "/home/anton/workspace/embox-trunk/./src/include/kernel/task.h"
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

# 1 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/task_table.h" 1
# 12 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/task_table.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/kernel/task.h" 1
# 13 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/task_table.h" 2
# 21 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/task_table.h"
extern int task_table_add(struct task *task);
# 30 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/task_table.h"
extern struct task *task_table_get(int n);






extern void task_table_del(int n);






extern int task_table_has_space(void);
# 54 "/home/anton/workspace/embox-trunk/./src/include/kernel/task/task_table.h"
extern int task_table_get_first(int since);
# 162 "/home/anton/workspace/embox-trunk/./src/include/kernel/task.h" 2
# 182 "/home/anton/workspace/embox-trunk/./src/include/kernel/task.h"

# 21 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/unistd.h" 2


# 39 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/unistd.h"
extern int sleep(unsigned int seconds);






extern int usleep(useconds_t useconds);

extern ssize_t write(int fd, const void *buf, size_t nbyte);

extern ssize_t read(int fd, void *buf, size_t nbyte);

extern off_t lseek(int fd, off_t offset, int origin);

extern int close(int fd);

extern int fsync(int);

extern void sync(void);

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
# 134 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/unistd.h"
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





# 1 "/home/anton/workspace/embox-trunk/./src/include/string.h" 1
# 23 "/home/anton/workspace/embox-trunk/./src/include/string.h"

# 34 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern size_t strlen(const char *str);
# 48 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strcpy(char *dst, const char *src);
# 67 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strncpy(char *dst, const char *src, size_t n);
# 79 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strcat(char *dst, const char *src);
# 95 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strncat(char *dst, const char *src, size_t n);
# 115 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern int strcmp(const char *str1, const char *str2);
# 138 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern int strncmp(const char *str1, const char *str2, size_t n);
# 153 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strchr(const char *str, int ch);
# 170 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strrchr(const char *str, int ch);
# 186 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strstr(const char *haystack, const char *needle);
# 196 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strerror(int err);
# 216 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern void *memcpy(void *dst, const void *src, size_t n);
# 231 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern void *memmove(void *dst, const void *src, size_t n);
# 246 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern void *memset(void *ptr, int c, size_t n);
# 267 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern int memcmp(const void *ptr1, const void *ptr2, size_t n);
# 283 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern void *memchr(const void *s, int c, size_t n);
# 293 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strlwr(char *str);
# 303 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strupr(char *str);
# 316 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern size_t strspn(const char *s, const char *accept);
# 329 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern size_t strcspn(const char *s, const char *reject);
# 343 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strpbrk(const char *s, const char *accept);
# 353 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strdup(const char *s);
# 374 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strtok_r(char *str, const char *delim, char **saveptr);
# 403 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strtok(char *str, const char *delim);
# 417 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern size_t strnlen(const char *s, size_t maxlen);
# 434 "/home/anton/workspace/embox-trunk/./src/include/string.h"
extern char *strndup(const char *s, size_t size);
# 501 "/home/anton/workspace/embox-trunk/./src/include/string.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/string_bsd.h" 1
# 12 "/home/anton/workspace/embox-trunk/./src/include/string_bsd.h"
extern size_t strlcpy(char *dst, const char *src, size_t size);
# 502 "/home/anton/workspace/embox-trunk/./src/include/string.h" 2


# 29 "zutil.h" 2
# 1 "/home/anton/workspace/embox-trunk/./src/include/stdlib.h" 1
# 23 "/home/anton/workspace/embox-trunk/./src/include/stdlib.h"
# 1 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/wait.h" 1
# 15 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/wait.h"
extern pid_t waitpid(pid_t pid, int *status, int options);
# 24 "/home/anton/workspace/embox-trunk/./src/include/stdlib.h" 2

typedef struct ldiv {
   long int quot;
   long int rem;
} ldiv_t;

typedef struct div {
   int quot;
   int rem;
} div_t;



# 66 "/home/anton/workspace/embox-trunk/./src/include/stdlib.h"
extern long int strtol(const char *nptr, char **endptr, int base);

extern unsigned long int strtoul(const char *nptr, char **endptr, int base);

extern double strtod(const char *nptr, char **endptr);
# 81 "/home/anton/workspace/embox-trunk/./src/include/stdlib.h"
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


# 1 "/home/anton/workspace/embox-trunk/./src/include/stdint.h" 1
# 20 "/home/anton/workspace/embox-trunk/./src/include/stdint.h"
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


typedef __intptr_t intptr_t;

typedef __uintptr_t uintptr_t;
# 68 "/home/anton/workspace/embox-trunk/./src/include/stdint.h"
# 1 "/home/anton/workspace/embox-trunk/./src/include/stdint-gcc.h" 1
# 69 "/home/anton/workspace/embox-trunk/./src/include/stdint.h" 2
# 120 "/home/anton/workspace/embox-trunk/./src/include/stdlib.h" 2
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
# 164 "/home/anton/workspace/embox-trunk/./src/include/stdlib.h"
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
# 14 "infback.c" 2
# 1 "inftrees.h" 1
# 24 "inftrees.h"
typedef struct {
    unsigned char op;
    unsigned char bits;
    unsigned short val;
} code;
# 54 "inftrees.h"
typedef enum {
    CODES,
    LENS,
    DISTS
} codetype;

int __attribute__((visibility ("hidden"))) inflate_table (codetype type, unsigned short *lens, unsigned codes, code * *table, unsigned *bits, unsigned short *work)

                                                                           ;
# 15 "infback.c" 2
# 1 "inflate.h" 1
# 20 "inflate.h"
typedef enum {
    HEAD,
    FLAGS,
    TIME,
    OS,
    EXLEN,
    EXTRA,
    NAME,
    COMMENT,
    HCRC,
    DICTID,
    DICT,
        TYPE,
        TYPEDO,
        STORED,
        COPY_,
        COPY,
        TABLE,
        LENLENS,
        CODELENS,
            LEN_,
            LEN,
            LENEXT,
            DIST,
            DISTEXT,
            MATCH,
            LIT,
    CHECK,
    LENGTH,
    DONE,
    BAD,
    MEM,
    SYNC
} inflate_mode;
# 81 "inflate.h"
struct inflate_state {
    inflate_mode mode;
    int last;
    int wrap;
    int havedict;
    int flags;
    unsigned dmax;
    unsigned long check;
    unsigned long total;
    gz_headerp head;

    unsigned wbits;
    unsigned wsize;
    unsigned whave;
    unsigned wnext;
    unsigned char *window;

    unsigned long hold;
    unsigned bits;

    unsigned length;
    unsigned offset;

    unsigned extra;

    code const *lencode;
    code const *distcode;
    unsigned lenbits;
    unsigned distbits;

    unsigned ncode;
    unsigned nlen;
    unsigned ndist;
    unsigned have;
    code *next;
    unsigned short lens[320];
    unsigned short work[288];
    code codes[(852 +592)];
    int sane;
    int back;
    unsigned was;
};
# 16 "infback.c" 2
# 1 "inffast.h" 1
# 11 "inffast.h"
void __attribute__((visibility ("hidden"))) inflate_fast (z_streamp strm, unsigned start);
# 17 "infback.c" 2


static void fixedtables (struct inflate_state *state);
# 28 "infback.c"
int inflateBackInit_(strm, windowBits, window, version, stream_size)
z_streamp strm;
int windowBits;
unsigned char *window;
const char *version;
int stream_size;
{
    struct inflate_state *state;

    if (version == 0 || version[0] != "1.2.8"[0] ||
        stream_size != (int)(sizeof(z_stream)))
        return (-6);
    if (strm == 0 || window == 0 ||
        windowBits < 8 || windowBits > 15)
        return (-2);
    strm->msg = 0;
    if (strm->zalloc == (alloc_func)0) {



        strm->zalloc = zcalloc;
        strm->opaque = (voidpf)0;

    }
    if (strm->zfree == (free_func)0)



    strm->zfree = zcfree;

    state = (struct inflate_state *)(*((strm)->zalloc))((strm)->opaque, (1), (sizeof(struct inflate_state)))
                                                                            ;
    if (state == 0) return (-4);
    ;
    strm->state = (struct internal_state *)state;
    state->dmax = 32768U;
    state->wbits = windowBits;
    state->wsize = 1U << windowBits;
    state->window = window;
    state->wnext = 0;
    state->whave = 0;
    return 0;
}
# 82 "infback.c"
static void fixedtables(state)
struct inflate_state *state;
{
# 117 "infback.c"
# 1 "inffixed.h" 1
# 10 "inffixed.h"
    static const code lenfix[512] = {
        {96,7,0},{0,8,80},{0,8,16},{20,8,115},{18,7,31},{0,8,112},{0,8,48},
        {0,9,192},{16,7,10},{0,8,96},{0,8,32},{0,9,160},{0,8,0},{0,8,128},
        {0,8,64},{0,9,224},{16,7,6},{0,8,88},{0,8,24},{0,9,144},{19,7,59},
        {0,8,120},{0,8,56},{0,9,208},{17,7,17},{0,8,104},{0,8,40},{0,9,176},
        {0,8,8},{0,8,136},{0,8,72},{0,9,240},{16,7,4},{0,8,84},{0,8,20},
        {21,8,227},{19,7,43},{0,8,116},{0,8,52},{0,9,200},{17,7,13},{0,8,100},
        {0,8,36},{0,9,168},{0,8,4},{0,8,132},{0,8,68},{0,9,232},{16,7,8},
        {0,8,92},{0,8,28},{0,9,152},{20,7,83},{0,8,124},{0,8,60},{0,9,216},
        {18,7,23},{0,8,108},{0,8,44},{0,9,184},{0,8,12},{0,8,140},{0,8,76},
        {0,9,248},{16,7,3},{0,8,82},{0,8,18},{21,8,163},{19,7,35},{0,8,114},
        {0,8,50},{0,9,196},{17,7,11},{0,8,98},{0,8,34},{0,9,164},{0,8,2},
        {0,8,130},{0,8,66},{0,9,228},{16,7,7},{0,8,90},{0,8,26},{0,9,148},
        {20,7,67},{0,8,122},{0,8,58},{0,9,212},{18,7,19},{0,8,106},{0,8,42},
        {0,9,180},{0,8,10},{0,8,138},{0,8,74},{0,9,244},{16,7,5},{0,8,86},
        {0,8,22},{64,8,0},{19,7,51},{0,8,118},{0,8,54},{0,9,204},{17,7,15},
        {0,8,102},{0,8,38},{0,9,172},{0,8,6},{0,8,134},{0,8,70},{0,9,236},
        {16,7,9},{0,8,94},{0,8,30},{0,9,156},{20,7,99},{0,8,126},{0,8,62},
        {0,9,220},{18,7,27},{0,8,110},{0,8,46},{0,9,188},{0,8,14},{0,8,142},
        {0,8,78},{0,9,252},{96,7,0},{0,8,81},{0,8,17},{21,8,131},{18,7,31},
        {0,8,113},{0,8,49},{0,9,194},{16,7,10},{0,8,97},{0,8,33},{0,9,162},
        {0,8,1},{0,8,129},{0,8,65},{0,9,226},{16,7,6},{0,8,89},{0,8,25},
        {0,9,146},{19,7,59},{0,8,121},{0,8,57},{0,9,210},{17,7,17},{0,8,105},
        {0,8,41},{0,9,178},{0,8,9},{0,8,137},{0,8,73},{0,9,242},{16,7,4},
        {0,8,85},{0,8,21},{16,8,258},{19,7,43},{0,8,117},{0,8,53},{0,9,202},
        {17,7,13},{0,8,101},{0,8,37},{0,9,170},{0,8,5},{0,8,133},{0,8,69},
        {0,9,234},{16,7,8},{0,8,93},{0,8,29},{0,9,154},{20,7,83},{0,8,125},
        {0,8,61},{0,9,218},{18,7,23},{0,8,109},{0,8,45},{0,9,186},{0,8,13},
        {0,8,141},{0,8,77},{0,9,250},{16,7,3},{0,8,83},{0,8,19},{21,8,195},
        {19,7,35},{0,8,115},{0,8,51},{0,9,198},{17,7,11},{0,8,99},{0,8,35},
        {0,9,166},{0,8,3},{0,8,131},{0,8,67},{0,9,230},{16,7,7},{0,8,91},
        {0,8,27},{0,9,150},{20,7,67},{0,8,123},{0,8,59},{0,9,214},{18,7,19},
        {0,8,107},{0,8,43},{0,9,182},{0,8,11},{0,8,139},{0,8,75},{0,9,246},
        {16,7,5},{0,8,87},{0,8,23},{64,8,0},{19,7,51},{0,8,119},{0,8,55},
        {0,9,206},{17,7,15},{0,8,103},{0,8,39},{0,9,174},{0,8,7},{0,8,135},
        {0,8,71},{0,9,238},{16,7,9},{0,8,95},{0,8,31},{0,9,158},{20,7,99},
        {0,8,127},{0,8,63},{0,9,222},{18,7,27},{0,8,111},{0,8,47},{0,9,190},
        {0,8,15},{0,8,143},{0,8,79},{0,9,254},{96,7,0},{0,8,80},{0,8,16},
        {20,8,115},{18,7,31},{0,8,112},{0,8,48},{0,9,193},{16,7,10},{0,8,96},
        {0,8,32},{0,9,161},{0,8,0},{0,8,128},{0,8,64},{0,9,225},{16,7,6},
        {0,8,88},{0,8,24},{0,9,145},{19,7,59},{0,8,120},{0,8,56},{0,9,209},
        {17,7,17},{0,8,104},{0,8,40},{0,9,177},{0,8,8},{0,8,136},{0,8,72},
        {0,9,241},{16,7,4},{0,8,84},{0,8,20},{21,8,227},{19,7,43},{0,8,116},
        {0,8,52},{0,9,201},{17,7,13},{0,8,100},{0,8,36},{0,9,169},{0,8,4},
        {0,8,132},{0,8,68},{0,9,233},{16,7,8},{0,8,92},{0,8,28},{0,9,153},
        {20,7,83},{0,8,124},{0,8,60},{0,9,217},{18,7,23},{0,8,108},{0,8,44},
        {0,9,185},{0,8,12},{0,8,140},{0,8,76},{0,9,249},{16,7,3},{0,8,82},
        {0,8,18},{21,8,163},{19,7,35},{0,8,114},{0,8,50},{0,9,197},{17,7,11},
        {0,8,98},{0,8,34},{0,9,165},{0,8,2},{0,8,130},{0,8,66},{0,9,229},
        {16,7,7},{0,8,90},{0,8,26},{0,9,149},{20,7,67},{0,8,122},{0,8,58},
        {0,9,213},{18,7,19},{0,8,106},{0,8,42},{0,9,181},{0,8,10},{0,8,138},
        {0,8,74},{0,9,245},{16,7,5},{0,8,86},{0,8,22},{64,8,0},{19,7,51},
        {0,8,118},{0,8,54},{0,9,205},{17,7,15},{0,8,102},{0,8,38},{0,9,173},
        {0,8,6},{0,8,134},{0,8,70},{0,9,237},{16,7,9},{0,8,94},{0,8,30},
        {0,9,157},{20,7,99},{0,8,126},{0,8,62},{0,9,221},{18,7,27},{0,8,110},
        {0,8,46},{0,9,189},{0,8,14},{0,8,142},{0,8,78},{0,9,253},{96,7,0},
        {0,8,81},{0,8,17},{21,8,131},{18,7,31},{0,8,113},{0,8,49},{0,9,195},
        {16,7,10},{0,8,97},{0,8,33},{0,9,163},{0,8,1},{0,8,129},{0,8,65},
        {0,9,227},{16,7,6},{0,8,89},{0,8,25},{0,9,147},{19,7,59},{0,8,121},
        {0,8,57},{0,9,211},{17,7,17},{0,8,105},{0,8,41},{0,9,179},{0,8,9},
        {0,8,137},{0,8,73},{0,9,243},{16,7,4},{0,8,85},{0,8,21},{16,8,258},
        {19,7,43},{0,8,117},{0,8,53},{0,9,203},{17,7,13},{0,8,101},{0,8,37},
        {0,9,171},{0,8,5},{0,8,133},{0,8,69},{0,9,235},{16,7,8},{0,8,93},
        {0,8,29},{0,9,155},{20,7,83},{0,8,125},{0,8,61},{0,9,219},{18,7,23},
        {0,8,109},{0,8,45},{0,9,187},{0,8,13},{0,8,141},{0,8,77},{0,9,251},
        {16,7,3},{0,8,83},{0,8,19},{21,8,195},{19,7,35},{0,8,115},{0,8,51},
        {0,9,199},{17,7,11},{0,8,99},{0,8,35},{0,9,167},{0,8,3},{0,8,131},
        {0,8,67},{0,9,231},{16,7,7},{0,8,91},{0,8,27},{0,9,151},{20,7,67},
        {0,8,123},{0,8,59},{0,9,215},{18,7,19},{0,8,107},{0,8,43},{0,9,183},
        {0,8,11},{0,8,139},{0,8,75},{0,9,247},{16,7,5},{0,8,87},{0,8,23},
        {64,8,0},{19,7,51},{0,8,119},{0,8,55},{0,9,207},{17,7,15},{0,8,103},
        {0,8,39},{0,9,175},{0,8,7},{0,8,135},{0,8,71},{0,9,239},{16,7,9},
        {0,8,95},{0,8,31},{0,9,159},{20,7,99},{0,8,127},{0,8,63},{0,9,223},
        {18,7,27},{0,8,111},{0,8,47},{0,9,191},{0,8,15},{0,8,143},{0,8,79},
        {0,9,255}
    };

    static const code distfix[32] = {
        {16,5,1},{23,5,257},{19,5,17},{27,5,4097},{17,5,5},{25,5,1025},
        {21,5,65},{29,5,16385},{16,5,3},{24,5,513},{20,5,33},{28,5,8193},
        {18,5,9},{26,5,2049},{22,5,129},{64,5,0},{16,5,2},{23,5,385},
        {19,5,25},{27,5,6145},{17,5,7},{25,5,1537},{21,5,97},{29,5,24577},
        {16,5,4},{24,5,769},{20,5,49},{28,5,12289},{18,5,13},{26,5,3073},
        {22,5,193},{64,5,0}
    };
# 118 "infback.c" 2

    state->lencode = lenfix;
    state->lenbits = 9;
    state->distcode = distfix;
    state->distbits = 5;
}
# 250 "infback.c"
int inflateBack(strm, in, in_desc, out, out_desc)
z_streamp strm;
in_func in;
void *in_desc;
out_func out;
void *out_desc;
{
    struct inflate_state *state;
    unsigned char *next;
    unsigned char *put;
    unsigned have, left;
    unsigned long hold;
    unsigned bits;
    unsigned copy;
    unsigned char *from;
    code here;
    code last;
    unsigned len;
    int ret;
    static const unsigned short order[19] =
        {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};


    if (strm == 0 || strm->state == 0)
        return (-2);
    state = (struct inflate_state *)strm->state;


    strm->msg = 0;
    state->mode = TYPE;
    state->last = 0;
    state->whave = 0;
    next = strm->next_in;
    have = next != 0 ? strm->avail_in : 0;
    hold = 0;
    bits = 0;
    put = state->window;
    left = state->wsize;


    for (;;)
        switch (state->mode) {
        case TYPE:

            if (state->last) {
                do { hold >>= bits & 7; bits -= bits & 7; } while (0);
                state->mode = DONE;
                break;
            }
            do { while (bits < (unsigned)(3)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
            state->last = ((unsigned)hold & ((1U << (1)) - 1));
            do { hold >>= (1); bits -= (unsigned)(1); } while (0);
            switch (((unsigned)hold & ((1U << (2)) - 1))) {
            case 0:
               
                                                      ;
                state->mode = STORED;
                break;
            case 1:
                fixedtables(state);
               
                                                      ;
                state->mode = LEN;
                break;
            case 2:
               
                                                      ;
                state->mode = TABLE;
                break;
            case 3:
                strm->msg = (char *)"invalid block type";
                state->mode = BAD;
            }
            do { hold >>= (2); bits -= (unsigned)(2); } while (0);
            break;

        case STORED:

            do { hold >>= bits & 7; bits -= bits & 7; } while (0);
            do { while (bits < (unsigned)(32)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
            if ((hold & 0xffff) != ((hold >> 16) ^ 0xffff)) {
                strm->msg = (char *)"invalid stored block lengths";
                state->mode = BAD;
                break;
            }
            state->length = (unsigned)hold & 0xffff;
           
                                   ;
            do { hold = 0; bits = 0; } while (0);


            while (state->length != 0) {
                copy = state->length;
                do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0);
                do { if (left == 0) { put = state->window; left = state->wsize; state->whave = left; if (out(out_desc, put, left)) { ret = (-5); goto inf_leave; } } } while (0);
                if (copy > have) copy = have;
                if (copy > left) copy = left;
                memcpy(put, next, copy);
                have -= copy;
                next += copy;
                left -= copy;
                put += copy;
                state->length -= copy;
            }
            ;
            state->mode = TYPE;
            break;

        case TABLE:

            do { while (bits < (unsigned)(14)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
            state->nlen = ((unsigned)hold & ((1U << (5)) - 1)) + 257;
            do { hold >>= (5); bits -= (unsigned)(5); } while (0);
            state->ndist = ((unsigned)hold & ((1U << (5)) - 1)) + 1;
            do { hold >>= (5); bits -= (unsigned)(5); } while (0);
            state->ncode = ((unsigned)hold & ((1U << (4)) - 1)) + 4;
            do { hold >>= (4); bits -= (unsigned)(4); } while (0);

            if (state->nlen > 286 || state->ndist > 30) {
                strm->msg = (char *)"too many length or distance symbols";
                state->mode = BAD;
                break;
            }

            ;


            state->have = 0;
            while (state->have < state->ncode) {
                do { while (bits < (unsigned)(3)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                state->lens[order[state->have++]] = (unsigned short)((unsigned)hold & ((1U << (3)) - 1));
                do { hold >>= (3); bits -= (unsigned)(3); } while (0);
            }
            while (state->have < 19)
                state->lens[order[state->have++]] = 0;
            state->next = state->codes;
            state->lencode = (code const *)(state->next);
            state->lenbits = 7;
            ret = inflate_table(CODES, state->lens, 19, &(state->next),
                                &(state->lenbits), state->work);
            if (ret) {
                strm->msg = (char *)"invalid code lengths set";
                state->mode = BAD;
                break;
            }
            ;


            state->have = 0;
            while (state->have < state->nlen + state->ndist) {
                for (;;) {
                    here = state->lencode[((unsigned)hold & ((1U << (state->lenbits)) - 1))];
                    if ((unsigned)(here.bits) <= bits) break;
                    do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
                }
                if (here.val < 16) {
                    do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                    state->lens[state->have++] = here.val;
                }
                else {
                    if (here.val == 16) {
                        do { while (bits < (unsigned)(here.bits + 2)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                        do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                        if (state->have == 0) {
                            strm->msg = (char *)"invalid bit length repeat";
                            state->mode = BAD;
                            break;
                        }
                        len = (unsigned)(state->lens[state->have - 1]);
                        copy = 3 + ((unsigned)hold & ((1U << (2)) - 1));
                        do { hold >>= (2); bits -= (unsigned)(2); } while (0);
                    }
                    else if (here.val == 17) {
                        do { while (bits < (unsigned)(here.bits + 3)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                        do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                        len = 0;
                        copy = 3 + ((unsigned)hold & ((1U << (3)) - 1));
                        do { hold >>= (3); bits -= (unsigned)(3); } while (0);
                    }
                    else {
                        do { while (bits < (unsigned)(here.bits + 7)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                        do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                        len = 0;
                        copy = 11 + ((unsigned)hold & ((1U << (7)) - 1));
                        do { hold >>= (7); bits -= (unsigned)(7); } while (0);
                    }
                    if (state->have + copy > state->nlen + state->ndist) {
                        strm->msg = (char *)"invalid bit length repeat";
                        state->mode = BAD;
                        break;
                    }
                    while (copy--)
                        state->lens[state->have++] = (unsigned short)len;
                }
            }


            if (state->mode == BAD) break;


            if (state->lens[256] == 0) {
                strm->msg = (char *)"invalid code -- missing end-of-block";
                state->mode = BAD;
                break;
            }




            state->next = state->codes;
            state->lencode = (code const *)(state->next);
            state->lenbits = 9;
            ret = inflate_table(LENS, state->lens, state->nlen, &(state->next),
                                &(state->lenbits), state->work);
            if (ret) {
                strm->msg = (char *)"invalid literal/lengths set";
                state->mode = BAD;
                break;
            }
            state->distcode = (code const *)(state->next);
            state->distbits = 6;
            ret = inflate_table(DISTS, state->lens + state->nlen, state->ndist,
                            &(state->next), &(state->distbits), state->work);
            if (ret) {
                strm->msg = (char *)"invalid distances set";
                state->mode = BAD;
                break;
            }
            ;
            state->mode = LEN;

        case LEN:

            if (have >= 6 && left >= 258) {
                do { strm->next_out = put; strm->avail_out = left; strm->next_in = next; strm->avail_in = have; state->hold = hold; state->bits = bits; } while (0);
                if (state->whave < state->wsize)
                    state->whave = state->wsize - left;
                inflate_fast(strm, state->wsize);
                do { put = strm->next_out; left = strm->avail_out; next = strm->next_in; have = strm->avail_in; hold = state->hold; bits = state->bits; } while (0);
                break;
            }


            for (;;) {
                here = state->lencode[((unsigned)hold & ((1U << (state->lenbits)) - 1))];
                if ((unsigned)(here.bits) <= bits) break;
                do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
            }
            if (here.op && (here.op & 0xf0) == 0) {
                last = here;
                for (;;) {
                    here = state->lencode[last.val +
                            (((unsigned)hold & ((1U << (last.bits + last.op)) - 1)) >> last.bits)];
                    if ((unsigned)(last.bits + here.bits) <= bits) break;
                    do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
                }
                do { hold >>= (last.bits); bits -= (unsigned)(last.bits); } while (0);
            }
            do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
            state->length = (unsigned)here.val;


            if (here.op == 0) {
               

                                                                       ;
                do { if (left == 0) { put = state->window; left = state->wsize; state->whave = left; if (out(out_desc, put, left)) { ret = (-5); goto inf_leave; } } } while (0);
                *put++ = (unsigned char)(state->length);
                left--;
                state->mode = LEN;
                break;
            }


            if (here.op & 32) {
                ;
                state->mode = TYPE;
                break;
            }


            if (here.op & 64) {
                strm->msg = (char *)"invalid literal/length code";
                state->mode = BAD;
                break;
            }


            state->extra = (unsigned)(here.op) & 15;
            if (state->extra != 0) {
                do { while (bits < (unsigned)(state->extra)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                state->length += ((unsigned)hold & ((1U << (state->extra)) - 1));
                do { hold >>= (state->extra); bits -= (unsigned)(state->extra); } while (0);
            }
            ;


            for (;;) {
                here = state->distcode[((unsigned)hold & ((1U << (state->distbits)) - 1))];
                if ((unsigned)(here.bits) <= bits) break;
                do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
            }
            if ((here.op & 0xf0) == 0) {
                last = here;
                for (;;) {
                    here = state->distcode[last.val +
                            (((unsigned)hold & ((1U << (last.bits + last.op)) - 1)) >> last.bits)];
                    if ((unsigned)(last.bits + here.bits) <= bits) break;
                    do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
                }
                do { hold >>= (last.bits); bits -= (unsigned)(last.bits); } while (0);
            }
            do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
            if (here.op & 64) {
                strm->msg = (char *)"invalid distance code";
                state->mode = BAD;
                break;
            }
            state->offset = (unsigned)here.val;


            state->extra = (unsigned)(here.op) & 15;
            if (state->extra != 0) {
                do { while (bits < (unsigned)(state->extra)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                state->offset += ((unsigned)hold & ((1U << (state->extra)) - 1));
                do { hold >>= (state->extra); bits -= (unsigned)(state->extra); } while (0);
            }
            if (state->offset > state->wsize - (state->whave < state->wsize ?
                                                left : 0)) {
                strm->msg = (char *)"invalid distance too far back";
                state->mode = BAD;
                break;
            }
            ;


            do {
                do { if (left == 0) { put = state->window; left = state->wsize; state->whave = left; if (out(out_desc, put, left)) { ret = (-5); goto inf_leave; } } } while (0);
                copy = state->wsize - state->offset;
                if (copy < left) {
                    from = put + copy;
                    copy = left - copy;
                }
                else {
                    from = put - state->offset;
                    copy = left;
                }
                if (copy > state->length) copy = state->length;
                state->length -= copy;
                left -= copy;
                do {
                    *put++ = *from++;
                } while (--copy);
            } while (state->length != 0);
            break;

        case DONE:

            ret = 1;
            if (left < state->wsize) {
                if (out(out_desc, state->window, state->wsize - left))
                    ret = (-5);
            }
            goto inf_leave;

        case BAD:
            ret = (-3);
            goto inf_leave;

        default:
            ret = (-2);
            goto inf_leave;
        }


  inf_leave:
    strm->next_in = next;
    strm->avail_in = have;
    return ret;
}

int inflateBackEnd(strm)
z_streamp strm;
{
    if (strm == 0 || strm->state == 0 || strm->zfree == (free_func)0)
        return (-2);
    (*((strm)->zfree))((strm)->opaque, (voidpf)(strm->state));
    strm->state = 0;
    ;
    return 0;
}

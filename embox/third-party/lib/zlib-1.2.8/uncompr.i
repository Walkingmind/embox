# 1 "uncompr.c"
# 1 "/home/anton/workspace/embox-trunk/third-party/lib/zlib-1.2.8//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "uncompr.c"
# 9 "uncompr.c"
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
# 10 "uncompr.c" 2
# 24 "uncompr.c"
int uncompress (dest, destLen, source, sourceLen)
    Bytef *dest;
    uLongf *destLen;
    const Bytef *source;
    uLong sourceLen;
{
    z_stream stream;
    int err;

    stream.next_in = ( Bytef *)source;
    stream.avail_in = (uInt)sourceLen;

    if ((uLong)stream.avail_in != sourceLen) return (-5);

    stream.next_out = dest;
    stream.avail_out = (uInt)*destLen;
    if ((uLong)stream.avail_out != *destLen) return (-5);

    stream.zalloc = (alloc_func)0;
    stream.zfree = (free_func)0;

    err = inflateInit_((&stream), "1.2.8", (int)sizeof(z_stream));
    if (err != 0) return err;

    err = inflate(&stream, 4);
    if (err != 1) {
        inflateEnd(&stream);
        if (err == 2 || (err == (-5) && stream.avail_in == 0))
            return (-3);
        return err;
    }
    *destLen = stream.total_out;

    err = inflateEnd(&stream);
    return err;
}

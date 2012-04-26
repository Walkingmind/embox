/**
 * @file
 * @brief
 *
 * @date 26.11.11
 * @author Anton Kozlov 
 */

#ifndef TASK_RESOURCES_H_
#define TASK_RESOURCES_H_

#define CONFIG_TASKS_RES_QUANTITY 16

#include <assert.h>
#include <stdarg.h>

/**
 * @brief Enum for supported idx descriptors (numerated task resources)
 */
enum {
	TASK_IDX_TYPE_FILE = 0, 
	TASK_IDX_TYPE_SOCKET = 1
};

/**
 * Specify operations with task's resources, which be called POSIX compat lib
 */
struct task_res_ops {
	int	type;
	int	(*open)(const char *path, int __oflag, va_list args); 
	int	(*close)(int idx);
	int	(*read) (int fd, const void *buf, size_t nbyte);
	int	(*write)(int fd, const void *buf, size_t nbyte);
	int	(*ioctl)(int fd, int request, va_list args);
	int (*fseek)(int fd, long int offset, int origin);
};

/**
 * Descriptor for numerated item for resource (int flides / int socket)
 * Task stores resources in this form, dynamically resolve operations 
 * with resources by type
 */
struct idx_desc {
	void *data;     /**< @brief Pointer for actual struct */
	int link_count; /**< @brief Count of links in all tasks */
	int type;	/**< @brief Type of resource */
};

/**
 * @brief idx utillity: get resource by idx 
 * @param desc idx descriptor to get
 * @return resource in idx
 */
static inline void *task_idx_desc_get_res(struct idx_desc *desc) {
	assert(desc);
	return desc->data;
}

/**
 * @brief idx utillity: get type by idx 
 * @param desc idx descriptor to get
 * @return type in idx
 */
static inline int task_idx_desc_get_type(struct idx_desc *desc) {
	assert(desc);
	return desc->type;
}

/**
 * @brief idx utillity: get reference count by idx 
 * @param desc idx descriptor to get
 * @return count of references to idx resource
 */
static inline int task_idx_desc_link_count(struct idx_desc *desc) {
	assert(desc);
	return desc->link_count;
}

/**
 * @brief idx utillity: update reference count by idx 
 * @param desc idx descriptor to update 
 * @param d references count delta 
 * @return new count of references to idx resource
 */
static inline int task_idx_desc_link_count_add(struct idx_desc *desc, int d) {
	assert(desc);
	return (desc->link_count += d);
}	

/**
 * @brief Task resources container
 */
struct task_resources {
	// heap desc
	struct idx_desc *idx[CONFIG_TASKS_RES_QUANTITY];
};

/**
 * @brief Get idx descriptor from task resources by idx number
 *
 * @param res Task resources to get idx from
 * @param idx idx number
 *
 * @return Pointer to idx 
 */
static inline struct idx_desc *task_res_idx_get(struct task_resources *res, int idx) {
	assert(res);
	return res->idx[idx]; 
}

/**
 * @brief Set task resource's 'number' resource to idx
 *
 * @param res Task resource
 * @param idx number to set
 * @param desc idx descriptor to store in task resources
 */
static inline void task_res_idx_set(struct task_resources *res, int idx, struct idx_desc *desc) {
	assert(res);
	res->idx[idx] = desc;
}

/**
 * @brief Allocate idx descriptor structure with type and data
 *
 * @param type idx descriptor type
 * @param data pointer for idx descriptor data
 *
 * @return 
 */
extern struct idx_desc *task_idx_desc_alloc(int type, void *data);
extern void task_idx_desc_free(struct idx_desc *desc);

extern int task_res_idx_alloc(struct task_resources *res, int type, void *data);
extern void task_res_idx_free(struct task_resources *res, int idx);

/**
 * @brief Check if task resource number is occupied 
 *
 * @param res Task resource to check
 * @param idx Number to check
 *
 * @return 
 */
static inline int task_res_idx_is_binded(struct task_resources *res, int idx) {
	return task_res_idx_get(res, idx) != NULL;
}

/**
 * @brief Mark task resource's number as free. Use with care, old resource should
 * be properly freed
 *
 * @param res Task resource to deal with
 * @param idx idx number
 */
static inline void task_res_idx_unbind(struct task_resources *res, int idx) {
	task_res_idx_set(res, idx, NULL);
}

#endif


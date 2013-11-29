/**
 * @file
 *
 * @date Nov 11, 2013
 * @author: Anton Bondarev
 */

#ifndef IDESC_TABLE_H_
#define IDESC_TABLE_H_

#include <framework/mod/options.h>
#include <config/embox/kernel/task/idx_table.h>

#define IDESC_QUANTITY \
	OPTION_MODULE_GET(embox__kernel__task__idx_table,NUMBER,task_res_quantity)

#define idesc_index_valid(idx) ((idx >=0) && (idx < IDESC_QUANTITY))

#include <util/indexator.h>

struct idesc;

struct idesc_table {
	struct idesc *idesc_table[IDESC_QUANTITY];

	struct indexator indexator;
	index_data_t index_buffer[INDEX_DATA_LEN(IDESC_QUANTITY)];
};

typedef struct idesc_table idesc_table_t;

//TODO
#include <stdint.h>
#define idesc_cloexec_set(desc) \
	desc = (struct idesc *)(((uintptr_t)desc) | 0x1)

#define idesc_cloexec_clear(desc) \
	desc = (struct idesc *)(((uintptr_t)desc) & ~0x1)

#define idesc_is_cloexeced(idesc)  ((uintptr_t)idesc & 0x1)


#include <sys/cdefs.h>

__BEGIN_DECLS

extern int idesc_table_add(struct idesc_table *t, struct idesc *idesc,
		int cloexec);

extern int idesc_table_del(struct idesc_table *t, int idx);

extern int idesc_table_lock(struct idesc_table *t, struct idesc *idesc, int idx,
		int cloexec);

extern int idesc_table_locked(struct idesc_table *t, int idx);

extern int idesc_table_init(struct idesc_table *t);

extern int idesc_table_finit(struct idesc_table *t);

extern int idesc_table_fork(struct idesc_table *t, struct idesc_table *par_tab);

extern struct idesc *idesc_table_get(struct idesc_table *t, int idx);


__END_DECLS

#endif /* IDESC_TABLE_H_ */

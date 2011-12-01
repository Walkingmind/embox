/**
 * @file
 * @brief Test dynamic memory allocation
 *
 * @date 12.05.10
 * @author Michail Skorginskii
 */

#include <stdio.h>

#include <embox/test.h>
#include <mem/kmalloc.h>
#include <lib/list.h>
#include <mem/pagealloc/mpallocator.h>

EMBOX_EXAMPLE(run);

/**
 * The test itself.
 *
 * @return the test result
 * @retval 0 on success
 * @retval nonzero on failure
 */
struct list {
	struct list_head *next, *prev;
	int p;
};

static LIST_HEAD(int_list);

static int run(int argc, char **argv) {
	int result = 0;

	int i;
	struct list_head *tmp_h;
	struct list *tmp;

	putchar('\n');
	TRACE("\t\t = Allocate list =\n");
	for (i = 0; i <= 10; i++) {
		tmp = (struct list *) kmalloc(sizeof(struct list));
		if (tmp == 0) {
			return -1;
		}
		tmp->p = i;
		list_add((struct list_head*) tmp, &int_list);
		TRACE("tmp[%d] = %d \n ", i, tmp->p);
	}

	TRACE("\n\n\t\t = Test our list =\n");
	list_for_each(tmp_h, &int_list) {
		tmp = (struct list *) tmp_h;
		TRACE("tmp[%d] = %d \n ", tmp->p, tmp->p);
	}

	TRACE("\n\n\t\t = Test free =\n");
	list_for_each(tmp_h, &int_list) {
		tmp = (struct list *) tmp_h;
		TRACE("now tmp[%d] is free \n ", tmp->p);
	}
	TRACE("\ntest ");

	return result;
}

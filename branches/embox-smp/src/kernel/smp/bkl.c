/**
 * @file
 * @brief TODO
 *
 * @date 08.02.2012
 * @author Anton Bulychev
 */

#include <kernel/percpu.h>
#include <kernel/spinlock.h>
#include <hal/ipl.h>

static SPINLOCK_DEFINE(bkl);

static unsigned int owner_id, nested;

void bkl_lock(void) {
	ipl_t ipl;
	int cpu_id, tmp;

	while (1) {
		spin_lock(&bkl);

		ipl = ipl_save();

		cpu_id = cpu_get_id();

		if (!nested || cpu_id == owner_id) {
			owner_id = cpu_id;
			nested++;

			tmp = 1;
		}

		ipl_restore(ipl);
		spin_unlock(&bkl);

		if (tmp) break;
	}
}

void bkl_unlock(void) {
	spin_lock(&bkl);

	nested--;

	spin_unlock(&bkl);
}

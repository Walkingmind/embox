/**
 * @file
 * @brief	test file for object pool allocator
 *
 * @date	14.11.11
 * @author	Gleb Efimov
 *
 */

#include <framework/example/self.h>
#include <mem/misc/pool2.h>

/**
 * This macro is used for registration of this example at system
 * run - function which describe work of example
 */
EMBOX_EXAMPLE(run);


struct example_type {
	int temp;
};

#define MY_POOL_SZ 100

POOL_DEF(my_pool, struct example_type, MY_POOL_SZ);

static int run(int argc, char **argv) {
	struct example_type* temp;
	temp = pool2_alloc(&my_pool);
	temp->temp = 0;
	pool2_free(&my_pool, temp);
	return 0;
}

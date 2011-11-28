/**
 * @file
 *
 * @brief
 *
 * @date 25.11.2011
 * @author Anton Bondarev
 */

#include <embox/test.h>
#include <mem/misc/pool2.h>

#define OBJECTS_QUANTITY 0x10

struct test_obj {
	int a;
	char b;
};

POOL_DEF(pool, struct test_obj, OBJECTS_QUANTITY);

EMBOX_TEST_SUITE("fixed size pool test");
#include <stdio.h>
TEST_CASE("single object allocation") {
	struct test_obj *obj;
	obj = pool2_alloc(&pool);
	test_assert_not_null(obj);
	pool2_free(&pool, obj);
}

TEST_CASE("test object freeing") {
	struct test_obj* objs[OBJECTS_QUANTITY + 1];
	int i;
	for(i = 0; i < sizeof(objs); i ++) {
		if(NULL == (objs[i] = pool2_alloc(&pool))) {
			break;
		}
	}
	pool2_free(&pool, objs[0]);
	objs[i] = pool2_alloc(&pool);
	test_assert_not_null(objs[i]);
	while( 0 > i --) {
		pool2_free(&pool, objs[i]);
	}

}

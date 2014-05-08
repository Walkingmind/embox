/**
 * @file
 *
 * @brief
 *
 * @date 25.11.2011
 * @author Anton Bondarev
 */
#include <embox/test.h>
#include <stdlib.h>
#include <mem/page.h>
#include <mem/heap.h>

#define HEAP_SIZE OPTION_MODULE_GET(embox__mem__heap_api,NUMBER,heap_size)

EMBOX_TEST_SUITE("heap allocation test");

struct small_struct {
	int data;
};

struct big_struct {
	int data[0x10];
};

struct unaligned_struct {
	char data;
};

TEST_CASE("Allocates small object") {
	void *obj = malloc(sizeof(struct small_struct));
	test_assert_not_null(obj);
	free(obj);
}

TEST_CASE("Allocates big object") {
	void *obj = malloc(sizeof(struct big_struct));
	test_assert_not_null(obj);
	free(obj);
}

#define MAX_MALLOC_SIZE (HEAP_SIZE/2 - 8) //XXX based on current impl
#define BIG_MALLOC_SIZE (1024 * 1024)

#if BIG_MALLOC_SIZE + 100 <= MAX_MALLOC_SIZE
/* + align */

TEST_CASE("Allocate really big size with align, fill 0's, free, allocate again") {
		void *big = memalign(8,BIG_MALLOC_SIZE);
		test_assert_not_null(big);
		memset(big, 0, BIG_MALLOC_SIZE); // comment this out, and everything is OK
		free(big);

		big = malloc(BIG_MALLOC_SIZE);
		test_assert_not_null(big);
		free(big);
}
#endif


TEST_CASE("Allocates unaligned object") {
	void *obj = malloc(sizeof(struct unaligned_struct));
	test_assert_not_null(obj);
	free(obj);
}

TEST_CASE("Allocates several objects with different size") {
	void *obj;

	obj = malloc(sizeof(struct unaligned_struct));
	test_assert_not_null(obj);
	free(obj);

	obj = malloc(sizeof(struct big_struct));
	test_assert_not_null(obj);
	free(obj);

	obj = malloc(sizeof(struct small_struct));
	test_assert_not_null(obj);
	free(obj);
}

TEST_CASE("Allocates several objects with different size and fill them than free them") {
	struct small_struct *small;
	struct unaligned_struct *unaligned;
	struct big_struct *big;
	int i;

	unaligned = memalign(8, sizeof(struct unaligned_struct));
	test_assert_not_null(unaligned);

	big = memalign(8, sizeof(struct big_struct));
	test_assert_not_null(big);

	small = malloc(sizeof(struct small_struct));
	test_assert_not_null(small);


	unaligned->data = 0x55;
	small->data = 0x12345678;
	for(i = 0; i < ARRAY_SIZE(big->data); i ++) {
		big->data[i] = 0x87654321;
	}

	test_assert_equal(unaligned->data, 0x55);
	test_assert_equal(small->data, 0x12345678);
	for(i = 0; i < ARRAY_SIZE(big->data); i ++) {
		test_assert_equal(big->data[i], 0x87654321);
	}

	free(big);
	free(small);
	free(unaligned);
}

#define ALLOC_FROM 2000
#define ALLOC_STEP 7
#define ALLOC_TO   4000
#define ALLOC_COUNT ((ALLOC_TO - ALLOC_FROM) / ALLOC_STEP + 1)
TEST_CASE("Allocates many objects with different size") {
	int i, alloc_sz;
	void **arr;

	arr = malloc(ALLOC_COUNT * sizeof *arr);
	test_assert_not_null(arr);

	for (alloc_sz = ALLOC_FROM, i = 0; alloc_sz < ALLOC_TO;
			alloc_sz += ALLOC_STEP, ++i) {
		assert(i < ALLOC_COUNT);
		arr[i] = malloc(alloc_sz);
		if (arr[i] == NULL)
			break;
	}

	while (--i >= 0) {
		test_assert_not_null(arr[i]);
		free(arr[i]);
	}
	free(arr);
}

TEST_CASE("malloc fails when trying to allocate a very large"
		" chunk of memory") {
	test_assert_null(malloc(4294966160));
}

/**
 * @file
 *
 * @brief
 *
 * @date 13.12.2011
 * @author Anton Bondarev
 */

#include <embox/test.h>
#include <util/ring_buff.h>

EMBOX_TEST_SUITE("util/ring_buff test");

#define BUFF_LENGTH (0x10)
RING_BUFFER_DEF(test_rbuff, int, BUFF_LENGTH);

TEST_CASE("Write/read single element to ring buffer") {
	int rd = 5;
	int wr = 0;

	ring_buff_enqueue(&test_rbuff, &rd, 1);
	ring_buff_dequeue(&test_rbuff, &wr, 1);

	test_assert_equal(wr, rd);
}

TEST_CASE("Test capacity of buffer") {
	int rd = 5;
	int wr = 0;
	int cnt = BUFF_LENGTH;

	while(0 != ring_buff_enqueue(&test_rbuff, &rd, 1)) {
		cnt --;
	}
	test_assert_zero(cnt);
	while(0 != ring_buff_dequeue(&test_rbuff, &wr, 1)) {
		cnt ++;
	}

	test_assert_equal(cnt, BUFF_LENGTH);
}
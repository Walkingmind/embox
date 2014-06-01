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
		test_assert_equal(wr, rd);
		cnt ++;
	}

	test_assert_equal(cnt, BUFF_LENGTH);
}

TEST_CASE("Ringbuffer should be able write all one piece") {
	int rd[BUFF_LENGTH] = { 5,5,5,5, 5,5,5,5, 5,5,5,5, 5,5,5,5,};
	int wr;
	int cnt = BUFF_LENGTH;

	test_assert_equal(BUFF_LENGTH, 
			ring_buff_enqueue(&test_rbuff, &rd, BUFF_LENGTH));

	while (cnt--) {
		test_assert_equal(1, ring_buff_dequeue(&test_rbuff, &wr, 1));

		test_assert_equal(wr, 5);
	}

	test_assert_equal(0, ring_buff_dequeue(&test_rbuff, &wr, 1));
}

#define SMALL_BUFLEN 4
RING_BUFFER_DEF(test_small_buf, int, SMALL_BUFLEN);

TEST_CASE("Ringbuffer enqueue should respect bounds") {
	int rd = 0;
	int wr;

	rd++;
	test_assert_equal(1, ring_buff_enqueue(&test_small_buf, &(rd), 1));
	rd++;
	test_assert_equal(1, ring_buff_enqueue(&test_small_buf, &(rd), 1));
	rd++;
	test_assert_equal(1, ring_buff_enqueue(&test_small_buf, &(rd), 1));
	rd++;
	test_assert_equal(1, ring_buff_enqueue(&test_small_buf, &(rd), 1));
	rd++;
	test_assert_equal(0, ring_buff_enqueue(&test_small_buf, &(rd), 1));
	rd++;
	test_assert_equal(0, ring_buff_enqueue(&test_small_buf, &(rd), 1));

	test_assert_equal(1, ring_buff_dequeue(&test_small_buf, &wr, 1));
	test_assert_equal(1, wr);

	test_assert_equal(1, ring_buff_dequeue(&test_small_buf, &wr, 1));
	test_assert_equal(2, wr);

	test_assert_equal(1, ring_buff_dequeue(&test_small_buf, &wr, 1));
	test_assert_equal(3, wr);

	test_assert_equal(1, ring_buff_dequeue(&test_small_buf, &wr, 1));
	test_assert_equal(4, wr);

	test_assert_equal(0, ring_buff_dequeue(&test_small_buf, &wr, 1));
}

TEST_CASE("Ringbuffer enqueueover shouldn't respect bounds") {
	int rd = 0;
	int wr;

	rd++;
	test_assert_equal(1, ring_buff_enqueueover(&test_small_buf, &(rd), 1));
	rd++;
	test_assert_equal(1, ring_buff_enqueueover(&test_small_buf, &(rd), 1));
	rd++;
	test_assert_equal(1, ring_buff_enqueueover(&test_small_buf, &(rd), 1));
	rd++;
	test_assert_equal(1, ring_buff_enqueueover(&test_small_buf, &(rd), 1));
	rd++;
	test_assert_equal(1, ring_buff_enqueueover(&test_small_buf, &(rd), 1));
	rd++;
	test_assert_equal(1, ring_buff_enqueueover(&test_small_buf, &(rd), 1));

	test_assert_equal(1, ring_buff_dequeue(&test_small_buf, &wr, 1));
	test_assert_equal(3, wr);

	test_assert_equal(1, ring_buff_dequeue(&test_small_buf, &wr, 1));
	test_assert_equal(4, wr);

	test_assert_equal(1, ring_buff_dequeue(&test_small_buf, &wr, 1));
	test_assert_equal(5, wr);

	test_assert_equal(1, ring_buff_dequeue(&test_small_buf, &wr, 1));
	test_assert_equal(6, wr);

	test_assert_equal(0, ring_buff_dequeue(&test_small_buf, &wr, 1));
}

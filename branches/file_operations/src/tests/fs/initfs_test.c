/**
 * @file
 *
 * @date Nov 28, 2012
 * @author: Anton Bondarev
 */


#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <embox/test.h>

EMBOX_TEST_SUITE("fs/initfs test");

TEST_SETUP_SUITE(setup_suite);

TEST_TEARDOWN_SUITE(teardown_suite);

#define TEST_FILE_NAME "/initfs_test_file.txt"

static int test_fd;
static const char test_file_contains[] = { "\""
      #include "initfs_test_file.txt"
		"\""
};

#define SIZE_OF_FILE sizeof(test_file_contains)

static char test_buff[SIZE_OF_FILE];

TEST_CASE("Write data to a read only file on a initfs file system") {
	test_assert_equal(-EPERM, write(test_fd, test_buff, 1));
}

TEST_CASE("Read data from a file") {
	int res;
//	char full_file[SIZE_OF_FILE + 2];
//	full_file[0] = '\"';
//	memcpy(full_file, )

	res = read(test_fd, test_buff, SIZE_OF_FILE);
	test_assert_equal(SIZE_OF_FILE, res);
	res = strncmp(test_buff, test_file_contains, SIZE_OF_FILE);
}

TEST_CASE("Call stat from a file") {

}

TEST_CASE("Call fstat from a file") {

}

TEST_CASE("Try to remove file from initfs") {

}

TEST_CASE("Call fcntl") {

}

static int setup_suite(void) {
	test_assert(0 <= (test_fd = open(TEST_FILE_NAME, O_RDONLY)));
	return 0;
}

static int teardown_suite(void) {
	test_assert_zero(close(test_fd));
	return 0;
}

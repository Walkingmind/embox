/**
 * @file
 * @brief test for allocation static variables in icebrick gcc
 * @details At first array of char's allocates.
 * Then we write " " to the string.
 * At last we check value recorded to the string.
 * This problem has not relevant to string,
 * possible it connected with memory allocation.
 *
 * @date 10.03.2010
 * @author Alexander Batyukov
 */

#include <types.h>
#include <embox/test.h>
#include <string.h>

EMBOX_TEST(run);

static int run(void) {
	char buf[2];
	static char space = ' ';
/*      static char space1 = ' ';*/ /* with this line works correctly */
	static char* proposals[64];
	proposals[0] = "a"; /* for mem allocation only */
	buf[0] = space;
	buf[1] = '\0';
/*	printf("%s\n", buf);*/

	return strcmp(buf, " ");
}

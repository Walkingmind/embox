/**
 * @file
 *
 * @date Jun 25, 2013
 * @author: Anton Bondarev
 */
#include <stdio.h>

int main(void) {
	int i;

	i = OPTION_GET(NUMBER, iteration);
	for(; i > 0; i--) {
		printf("hello mybuild v 0.5");
	}

	return 0;
}

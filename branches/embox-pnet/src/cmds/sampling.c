/**
 * @file
 * @brief
 *
 * @author  Alexander Kalmuk
 * @date    16.05.2013
 */

#include <stdio.h>
#include <embox/cmd.h>
#include <profiler/sampling.h>

EMBOX_CMD(sampling_cmd);

static int sampling_cmd(int argc, char **argv) {
	struct sample buf[SYMBOL_CNT_UPPERBOUND];
	int i, len;

	len = sampling_copy_sample(buf, SYMBOL_CNT_UPPERBOUND);

	printf("\n\n");
	for(i = 0; i < len; i++) {
		printf("(%d)%s - %d\n", i, buf[i].name, buf[i].cnt);
	}
	printf("\n\n");

	return 0;
}

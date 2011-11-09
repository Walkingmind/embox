/**
 * @file
 * @brief store memory area to flash
 *
 * @date 06.05.10
 * @author Alexander Batyukov
 */

#include <embox/cmd.h>
#include <getopt.h>
#include <drivers/flash_if.h>

EMBOX_CMD(exec);

static void print_usage(void) {
	printf("Usage: store [-h] -f <src_addr> -t <dst_addr> -n <numbytes>\n");
}

#define SIZE_OF_TEST_ARRAY  0x100

static uint32_t test_array[SIZE_OF_TEST_ARRAY];

static int store_area(uint32_t src_addr, uint32_t start_block_num, int numwords) {
	int i;
	uint32_t curr_block_num = start_block_num;
	uint32_t curr_block_size;
	uint32_t block_addr;
	uint32_t curr_addr = src_addr;

	FLASH_STATUS flash_status;

/*
 *	flash_status = UNLOCK_ALL_BLOCKS(flash_devices_table[0]);
 */

	while (numwords > 0) {
		curr_block_size = flash_if_get_block_size(&flash_devices_table[0], curr_block_num);

		printf("unlock\n");
		flash_status = UNLOCK_BLOCK(flash_devices_table[0], curr_block_num);

		printf("erase\n");
		flash_status = ERASE_BLOCK(flash_devices_table[0], curr_block_num);

		GET_BLOCK_OFFSET(flash_devices_table[0], curr_block_num, &block_addr);

		printf("program\n");
		for (i = 0; i < curr_block_size / sizeof(uint32_t); i++) {
			flash_status = PROGRAM_FLASH(flash_devices_table[0],
				block_addr + sizeof(uint32_t) * i, *((uint32_t *) curr_addr + i));
			if (--numwords <= 0) {
				break;
			}
			printf(".");
		}

		printf("lock\n");
		flash_status = LOCK_BLOCK(flash_devices_table[0], curr_block_num);

		curr_addr += curr_block_size;
		curr_block_num++;
	}

/*
	flash_status = LOCK_ALL_BLOCKS(flash_devices_table[0]);
*/

	printf("\nok!\n");
	return 0;
}


static int exec(int argc, char **argv) {
	int i;
	int opt;
	uint32_t src_addr;
	int start_block_num;
	int numwords;

	for (i = 0; i < SIZE_OF_TEST_ARRAY; i++) {
		test_array[i] = i;
	}

	src_addr = (uint32_t)&test_array;
	numwords = SIZE_OF_TEST_ARRAY;

	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "hf:t:n:"))) {
		switch(opt) {
		case 'h':
			print_usage();
			return 0;
		case 'f':
			if (1 != sscanf(optarg, "0x%x", &src_addr)) {
				return -1;
			}
			break;
		case 't':
			if (1 != sscanf(optarg, "%d", &start_block_num)) {
				return -1;
			}
			break;
		case 'n':
			if (1 != sscanf(optarg, "%d", &numwords)) {
				return -1;
			}
			break;
		default:
			return 0;
		}
	}

	store_area(src_addr, start_block_num, numwords);

	return 0;
}

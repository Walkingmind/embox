/**
 * @file
 *
 * @date 16.10.2009
 * @author Alexander Batyukov
 */
#include <drivers/flash_if.h>
#include <drivers/flash_template.h>
#include <common.h>
#include <string.h>
#if 0
static FLASH_DEV flash_dev;
#endif

FLASH_DEV flash_devices_table[MAX_FLASH_DEVS];

static int flash_if_read_id(uint32_t address, uint32_t *mcode, uint32_t *device_id) {
	uint32_t * fptr;
	*((volatile uint32_t*)0x80000000) |= (1<<11);

	fptr = (uint32_t *) address;
	*fptr = 0x00900090;

	*((volatile uint32_t*)0x80000000) &= ~(1<<11);

	*mcode = *fptr;

	fptr = (uint32_t *) address + 0x1;

	*device_id = *fptr;

	*((volatile uint32_t*)0x80000000) |= (1<<11);

	fptr = (uint32_t *) address;
	*fptr = 0x00ff00ff;

	*((volatile uint32_t*)0x80000000) &= ~(1<<11);
	return 0;
}

static int flash_alloc_slot(int flash_device_id) {
	int i;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		if (flash_devices_table[i].number == 0) {
			flash_devices_table[i].number = flash_device_id;
			return i;
		}
	}
	return -1;
}

int flash_if_init(void) {
	int i;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		flash_devices_table[i].dev = -1;
	}
	return 0;
}

int flash_if_device_init(uint32_t address, int num) {
	uint32_t mcode, device_id;
	int slot_number;
	printf("Initializing flash devs, address 0x%8x...\t", address);
	flash_if_read_id(address, &mcode, &device_id);

	/*allocation*/
	slot_number = flash_alloc_slot(num);

	flash_devices_table[slot_number].manuf = mcode;
	flash_devices_table[slot_number].dev = device_id;
	flash_devices_table[slot_number].start_address = address;
	flash_devices_table[slot_number].number = num;

	switch (device_id)
		{
			case 0x891C891C:
				printf("Intel P30 bottom\n");
				flash_devices_table[slot_number].flash_if_erase_all_blocks = flash_erase_all_blocks;
				flash_devices_table[slot_number].flash_if_erase_block = flash_erase_block;
				flash_devices_table[slot_number].flash_if_get_block_address = flash_get_block_address;
				flash_devices_table[slot_number].flash_if_lock_block = flash_lock_block;
				flash_devices_table[slot_number].flash_if_lock_block_down = flash_lock_block_down;
				flash_devices_table[slot_number].flash_if_program_flash = flash_program_flash;
				flash_devices_table[slot_number].flash_if_program_flash_buffered = flash_program_flash_buffered;
				flash_devices_table[slot_number].flash_if_query = flash_query;
				flash_devices_table[slot_number].flash_if_read_block_status = flash_read_block_status;
				flash_devices_table[slot_number].flash_if_read_device_id = flash_read_device_ID;
				flash_devices_table[slot_number].flash_if_read_flash = flash_read_flash;
				flash_devices_table[slot_number].flash_if_read_status = flash_read_status;
				flash_devices_table[slot_number].flash_if_unlock_all_blocks = flash_unlock_all_blocks;
				flash_devices_table[slot_number].flash_if_unlock_block = flash_unlock_block;
				flash_devices_table[slot_number].param_block_nums[0] = 0;
				flash_devices_table[slot_number].param_block_nums[1] = 1;
				flash_devices_table[slot_number].param_block_nums[2] = 2;
				flash_devices_table[slot_number].param_block_nums[3] = 3;
				flash_devices_table[slot_number].is_top = 0;

				flash_devices_table[slot_number].total_numblocks = FLASH_TOTAL_NUMBLOCKS;
				flash_devices_table[slot_number].total_size = FLASH_TOTAL_SIZE;
				flash_devices_table[slot_number].buffer_size = FLASH_BUFFER_SIZE;
				break;
			case 0x89198919:
				printf("Intel P30 top??\n");
				flash_devices_table[slot_number].flash_if_erase_all_blocks = flash_erase_all_blocks;
				flash_devices_table[slot_number].flash_if_erase_block = flash_erase_block;
				flash_devices_table[slot_number].flash_if_get_block_address = flash_get_block_address;
				flash_devices_table[slot_number].flash_if_lock_block = flash_lock_block;
				flash_devices_table[slot_number].flash_if_lock_block_down = flash_lock_block_down;
				flash_devices_table[slot_number].flash_if_program_flash = flash_program_flash;
				flash_devices_table[slot_number].flash_if_program_flash_buffered = flash_program_flash_buffered;
				flash_devices_table[slot_number].flash_if_query = flash_query;
				flash_devices_table[slot_number].flash_if_read_block_status = flash_read_block_status;
				flash_devices_table[slot_number].flash_if_read_device_id = flash_read_device_ID;
				flash_devices_table[slot_number].flash_if_read_flash = flash_read_flash;
				flash_devices_table[slot_number].flash_if_read_status = flash_read_status;
				flash_devices_table[slot_number].flash_if_unlock_all_blocks = flash_unlock_all_blocks;
				flash_devices_table[slot_number].flash_if_unlock_block = flash_unlock_block;
				flash_devices_table[slot_number].param_block_nums[0] = FLASH_TOTAL_NUMBLOCKS - 4;
				flash_devices_table[slot_number].param_block_nums[1] = FLASH_TOTAL_NUMBLOCKS - 3;
				flash_devices_table[slot_number].param_block_nums[2] = FLASH_TOTAL_NUMBLOCKS - 2;
				flash_devices_table[slot_number].param_block_nums[3] = FLASH_TOTAL_NUMBLOCKS - 1;
				flash_devices_table[slot_number].is_top = 1;

				flash_devices_table[slot_number].total_numblocks = FLASH_TOTAL_NUMBLOCKS;
				flash_devices_table[slot_number].total_size = FLASH_TOTAL_SIZE;
				flash_devices_table[slot_number].buffer_size = FLASH_BUFFER_SIZE;
				break;
			default:
				printf("unknown flash device, device_id = 0x%x\n", device_id);
				break;
		}
	return slot_number;
}

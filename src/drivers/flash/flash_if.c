/**
 * @file
 *
 * @date 16.10.2009
 * @author Alexander Batyukov
 */
#include <drivers/flash_if.h>
#include <drivers/flash_template.h>
#include <embox/kernel.h>
#include <string.h>
#include <embox/unit.h>

EMBOX_UNIT_INIT(unit_init);


int flash_if_read_id(uint32_t address, uint32_t *mcode, uint32_t *device_id)
								__attribute__ ((section (".reloc.flash_utils")));
/*
int flash_if_write(FLASH_DEV *flash_dev, uint32_t addr, void *buff, uint32_t size)
								__attribute__ ((section (".reloc.flash_utils")));
*/

/**
 * Reads flash id and manufacturer using standard flash interface
 * @param address	flash start address
 * @param mcode		manufacturer code (out param)
 * @param device_id	device code (out param)
 * @return read result
 * @retval 0 on success
 */
int flash_if_read_id(uint32_t address, uint32_t *mcode, uint32_t *device_id) {
	uint32_t *fptr;

	FLASH_WRITE_ENABLE;

	fptr = (uint32_t *) address;
	*fptr = FLASH_READ_ID_CODES;

	FLASH_WRITE_DISABLE;

	*mcode = *fptr;

	fptr = (uint32_t *) address + 0x1;

	*device_id = *fptr;

	FLASH_WRITE_ENABLE;

	fptr = (uint32_t *) address;
	*fptr = FLASH_READ_ARRAY;

	FLASH_WRITE_DISABLE;

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

static int flash_if_device_init(uint32_t address, int num) {
	uint32_t mcode, device_id;
	int slot_number;
	printf("Address 0x%8x...\t", address);
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
				flash_devices_table[slot_number].erase_all_blocks = flash_erase_all_blocks;
				flash_devices_table[slot_number].erase_block = flash_erase_block;
				flash_devices_table[slot_number].get_block_offset = flash_get_block_offset;
				flash_devices_table[slot_number].lock_block = flash_lock_block;
				flash_devices_table[slot_number].lock_block_down = flash_lock_block_down;
				flash_devices_table[slot_number].program_flash = flash_program_flash;
				flash_devices_table[slot_number].program_flash_buffered = flash_program_flash_buffered;
				flash_devices_table[slot_number].query = flash_query;
				flash_devices_table[slot_number].read_block_status = flash_read_block_status;
				flash_devices_table[slot_number].read_device_id = flash_read_device_ID;
				flash_devices_table[slot_number].read_flash = flash_read_flash;
				flash_devices_table[slot_number].read_status = flash_read_status;
				flash_devices_table[slot_number].lock_all_blocks = flash_lock_all_blocks;
				flash_devices_table[slot_number].unlock_all_blocks = flash_unlock_all_blocks;
				flash_devices_table[slot_number].unlock_block = flash_unlock_block;
				flash_devices_table[slot_number].param_block_nums[0] = 0;
				flash_devices_table[slot_number].param_block_nums[1] = 1;
				flash_devices_table[slot_number].param_block_nums[2] = 2;
				flash_devices_table[slot_number].param_block_nums[3] = 3;
				flash_devices_table[slot_number].is_top = 0;
				flash_devices_table[slot_number].param_block_size = FLASH_PARM_BLOCK_NUMBYTES;
				flash_devices_table[slot_number].main_block_size = FLASH_MAIN_BLOCK_NUMBYTES;

				flash_devices_table[slot_number].total_numblocks = FLASH_TOTAL_NUMBLOCKS;
				flash_devices_table[slot_number].total_size = FLASH_TOTAL_SIZE;
				flash_devices_table[slot_number].buffer_size = FLASH_BUFFER_SIZE;
				break;
			case 0x89198919:
				printf("Intel P30 top\n");
				flash_devices_table[slot_number].erase_all_blocks = flash_erase_all_blocks;
				flash_devices_table[slot_number].erase_block = flash_erase_block;
				flash_devices_table[slot_number].get_block_offset = flash_get_block_offset;
				flash_devices_table[slot_number].lock_block = flash_lock_block;
				flash_devices_table[slot_number].lock_block_down = flash_lock_block_down;
				flash_devices_table[slot_number].program_flash = flash_program_flash;
				flash_devices_table[slot_number].program_flash_buffered = flash_program_flash_buffered;
				flash_devices_table[slot_number].query = flash_query;
				flash_devices_table[slot_number].read_block_status = flash_read_block_status;
				flash_devices_table[slot_number].read_device_id = flash_read_device_ID;
				flash_devices_table[slot_number].read_flash = flash_read_flash;
				flash_devices_table[slot_number].read_status = flash_read_status;
				flash_devices_table[slot_number].lock_all_blocks = flash_lock_all_blocks;
				flash_devices_table[slot_number].unlock_all_blocks = flash_unlock_all_blocks;
				flash_devices_table[slot_number].unlock_block = flash_unlock_block;
				flash_devices_table[slot_number].param_block_nums[0] = FLASH_TOTAL_NUMBLOCKS - 4;
				flash_devices_table[slot_number].param_block_nums[1] = FLASH_TOTAL_NUMBLOCKS - 3;
				flash_devices_table[slot_number].param_block_nums[2] = FLASH_TOTAL_NUMBLOCKS - 2;
				flash_devices_table[slot_number].param_block_nums[3] = FLASH_TOTAL_NUMBLOCKS - 1;
				flash_devices_table[slot_number].is_top = 1;
				flash_devices_table[slot_number].param_block_size = FLASH_PARM_BLOCK_NUMBYTES;
				flash_devices_table[slot_number].main_block_size = FLASH_MAIN_BLOCK_NUMBYTES;

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

int flash_if_get_block_size(FLASH_DEV *flash_dev, uint32_t blocknum)
				__attribute__ ((section (".reloc.flash_utils")));

int flash_if_get_block_size(FLASH_DEV *flash_dev, uint32_t blocknum) {
	if (blocknum > flash_dev->total_numblocks) {
		return -1;
	}

	if ((blocknum == flash_dev->param_block_nums[0]) ||
		(blocknum == flash_dev->param_block_nums[1]) ||
		(blocknum == flash_dev->param_block_nums[2]) ||
		(blocknum == flash_dev->param_block_nums[3])) {
		return flash_dev->param_block_size;
	}

	return flash_dev->main_block_size;
}

int flash_if_get_start_block(FLASH_DEV *flash_dev, uint32_t addr)
					__attribute__ ((section (".reloc.flash_utils")));

int flash_if_get_start_block(FLASH_DEV *flash_dev, uint32_t addr) {
	size_t i;
	uint32_t block_addr;

	if ((addr > flash_dev->total_size) || (addr < flash_dev->start_address)) {
		return -1;
	}

	for (i = 0; i < flash_dev->total_numblocks; i++) {
		flash_dev->get_block_offset(flash_dev, i, &block_addr);
		if (addr < block_addr) {
			break;
		}
	}
	return i - 1;
}

static int unit_init() {
	int i;
	for (i = 0; i < MAX_FLASH_DEVS; i++) {
		flash_devices_table[i].dev = -1;
	}
	flash_if_device_init(0x0, 1);
	return 0;
}

/* temporary.. it is really bullshit. My mistake. -- SunnyA */

static uint32_t flash_buff[0x20000];

int flash_if_write(FLASH_DEV *flash_dev, uint32_t addr, void *buff, uint32_t size)
					__attribute__ ((section (".reloc.flash_utils")));

int flash_if_write(FLASH_DEV *flash_dev, uint32_t addr, void *buff, uint32_t size) {
	uint32_t block_num;
	uint32_t start_block_addr;
	uint32_t block_offset;
	uint32_t block_size;
	size_t i;
	uint32_t curr_offset;

	block_num = flash_if_get_start_block(flash_dev, addr);
	block_size = flash_if_get_block_size(flash_dev, block_num);
	flash_dev->get_block_offset(flash_dev, block_num, &start_block_addr);
	block_offset = addr - start_block_addr;

	flash_dev->read_flash(flash_dev, start_block_addr, &flash_buff, size);
	memcpy(flash_buff + block_offset, buff, size);
	flash_dev->erase_block(flash_dev, block_num);
	for (i = 0, curr_offset = 0; i < block_size; i++, curr_offset+= 4) {
		printf(".");
		flash_dev->program_flash(flash_dev, curr_offset, *(flash_buff + i));
	}
	return 0;
}

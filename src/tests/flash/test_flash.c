/**
 * @file
 * @brief flash info test
 * @author Alexander Batyukov
 */

#include <embox/test.h>

EMBOX_TEST(run);

/** memory controller base */
#define MEM_CTRLR_BASE  0x80000000

#define FLASH_WRITE_ENABLE	*((volatile uint32_t*) MEM_CTRLR_BASE) |= (1<<11)
#define FLASH_WRITE_DISABLE	*((volatile uint32_t*) MEM_CTRLR_BASE) &= ~(1<<11)

/** opcodes */
#define FLASH_READ_STATUS_REGISTER	0x00900090
#define FLASH_READ_ARRAY			0x00ff00ff

#define FLASH_BASE_ADDRESS			0x04000000

/**
 * Reads flash id and manufacturer using standard flash interface
 * @param address	flash start address
 * @param mcode		manufacturer code (out param)
 * @param device_id	device code (out param)
 * @return read result
 * @retval 0 on success
 */
int flash_read_id(uint32_t address, uint32_t *mcode, uint32_t *device_id) {
	uint32_t *fptr;

	FLASH_WRITE_ENABLE;

	fptr = (uint32_t *) address;
	*fptr = FLASH_READ_STATUS_REGISTER;

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

/**
 * Prints flash memory info.
 *
 * @return the test result
 * @retval 0 on success
 * @retval nonzero on failure
 */
static int run(void) {
	int result = 0;

	uint32_t mcode;
	uint32_t device_id;

	result = flash_read_id(FLASH_BASE_ADDRESS, &mcode, &device_id);

	TRACE("\n\t\t\tflash info\n");
	TRACE("\tmanuf.: 0x%04X\t\t0x%04X\n",
		  ((mcode >> 16)& 0xFFFF), (mcode & 0xFFFF));
	TRACE("\ttype  : 0x%04X\t\t0x%04X\n\n",
		  ((device_id >> 16)& 0xFFFF), (device_id & 0xFFFF));

	return result;
}

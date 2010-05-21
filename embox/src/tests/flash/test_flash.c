/**
 * @file
 * @brief flash info test
 * @author Alexander Batyukov
 */

#include <embox/test.h>
#include <drivers/flash_if.h>

EMBOX_TEST(run);

#if 0
#define FLASH_BASE_ADDRESS			0x04000000
#else
#define FLASH_BASE_ADDRESS			0x00000000
#endif


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

	result = flash_if_read_id(FLASH_BASE_ADDRESS, &mcode, &device_id);

	TRACE("\n\t\t\tflash info\n");
	TRACE("\tmanuf.: 0x%04X\t\t0x%04X\n",
		  ((mcode >> 16)& 0xFFFF), (mcode & 0xFFFF));
	TRACE("\ttype  : 0x%04X\t\t0x%04X\n\n",
		  ((device_id >> 16)& 0xFFFF), (device_id & 0xFFFF));

	return result;
}

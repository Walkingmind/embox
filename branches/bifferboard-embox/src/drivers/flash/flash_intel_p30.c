/**
 * @file
 * @details
 *  Intel Confidential
 * Copyright (C) Intel Corporation 2003-2005
 * All Rights Reserved.
 * --------------------------------------------------------------------
 *
 * Project Name: Flash Templates
 *
 * Module Name: Device
 *
 * File: Device.C - P30 device specific template source file
 *
 * File Revision: $Revision: 2 $, $JustDate:  1/20/03 $, $Author: Garotg $
 *
 * Purpose:
 *
 *    The purpose of this file is to implement the P30 device specific
 *    functionality for the P30 template package.  This module
 *    implements only those functions which have P30 device specific
 *    implementations.  The remaining functions which complete
 *    the template application programmers interface are implemented
 *    by the template.c source module.
 *
 * @date 09.07.09
 * @author Garotg
 * @author Alexander Batyukov
 */

/*
*****************************************************************
* NOTICE OF LICENSE AGREEMENT
*
* This code is provided by Intel Corp., and the use is governed
* under the terms of a license agreement. See license agreement
* for complete terms of license.
*
* YOU MAY ONLY USE THE SOFTWARE WITH INTEL FLASH PRODUCTS.  YOUR
* USE OF THE SOFTWARE WITH ANY OTHER FLASH PRODUCTS IS EXPRESSLY
* PROHIBITED UNLESS AND UNTIL YOU APPLY FOR, AND ARE GRANTED IN
* INTEL'S SOLE DISCRETION, A SEPARATE WRITTEN SOFTWARE LICENSE
* FROM INTEL LICENSING ANY SUCH USE.
*****************************************************************
*/

/* Include Files */

#include <drivers/flash_template.h>

#include <string.h>
#include <embox/kernel.h>
#include <drivers/flash_if.h>

/**
 * This procedure is called to erase all data blocks on the flash
 * device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_erase_all_blocks(FLASH_DEV *flash_dev) {
	int flash_total_numblocks;
	FLASH_STATUS stat;
	uint16_t block;

	flash_total_numblocks = flash_dev->total_numblocks;
	for (block = 0; block < flash_total_numblocks; block++) {
		stat = flash_erase_block(flash_dev, block);

		if (stat.Result != StatCompleted) {
			return (stat);
		}
	}

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return (stat);

}

/**
 * This procedure is called to issue the erase suspend command to
 * the flash device.
 * When this function is called the device is currently in the erase
 * mode for the block identified.
 *
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_erase_suspend(FLASH_DEV *flash_dev) {

	FLASH_STATUS stat;

	flash_writef(flash_dev, 0, FLASH_BLOCK_SUSPEND);

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
	} else {
		stat.Result = StatCompleted;
	}

	stat.SR = flash_read_status(flash_dev);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return (stat);

}

/**
 * This procedure is called to retrieve the extended query
 * data from the flash device.
 * @param (OUT) *extquery - pointer to extended query structure
 * @return FLASH_STATUS
*/
FLASH_STATUS flash_extended_query(FLASH_DEV *flash_dev,
		struct _FLASH_EXTQUERY *extquery) {
	FLASH_STATUS stat;
	struct _FLASH_QUERY_DATA query;
	FLASH_FDATA item;
	uint32_t addr, longitem, i, offset;

	stat = flash_query(flash_dev, &query);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	offset = query.ExtTablePtr;

	flash_writef(flash_dev, 0, FLASH_READ_QUERY);

	/* read extended query string */
	for (i = 0; i < 3; i++) {
		stat = flash_get_query_address(flash_dev, offset, &addr);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, addr);

		item &= 0xff;
		extquery->ExtQueryStr[i] = (char) item;
		offset++;
	}
	extquery->ExtQueryStr[3] = '\0'; /* null terminate string */

	/* read major version number */
	stat = flash_get_query_address(flash_dev, offset, &addr);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, addr);
	item &= 0xff;
	extquery->MajorVersionNum = (uint8_t) item;
	offset++;

	/* read minor version number */
	stat = flash_get_query_address(flash_dev, offset, &addr);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, addr);
	item &= 0xff;
	extquery->MinorVersionNum = (uint8_t) item;
	offset++;

	extquery->OptionalFeature = 0;
	for (i = 0; i < 4; i++) {
		stat = flash_get_query_address(flash_dev, offset, &addr);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, addr);
		item &= 0xff;
		longitem = (uint32_t) ((uint32_t) item << (8 * i));
		extquery->OptionalFeature = (uint32_t) (extquery->OptionalFeature
				| longitem);
		offset++;
	}

	/* read after suspend functions */
	stat = flash_get_query_address(flash_dev, offset, &addr);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, addr);

	item &= 0xff;
	extquery->AfterSuspendFunctions = (uint8_t) item;
	offset++;

	/* read vendor id */
	extquery->BlockLockStatus = 0;
	for (i = 0; i < 2; i++) {
		stat = flash_get_query_address(flash_dev, offset, &addr);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, addr);

		item &= 0xff;
		item = item << (8 * i);
		extquery->BlockLockStatus = (uint16_t) (extquery->BlockLockStatus
				| item);
		offset++;
	}

	/* read vcc optimum */
	stat = flash_get_query_address(flash_dev, offset, &addr);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, addr);

	item &= 0xff;
	extquery->VccOptimum = (uint8_t) item;
	offset++;

	/* read vpp optimum */
	stat = flash_get_query_address(flash_dev, offset, &addr);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, addr);

	item &= 0xff;
	extquery->VppOptimum = (uint8_t) item;
	offset++;

	stat.Result = StatCompleted;

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return (stat);

}

/**
 * This procedure is called to get the flash starting address for the
 * specified block number.
 * @param blocknum - the block number on the device.
 * @param (OUT) address  - the starting flash address for the specified
 *                         block.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_get_block_offset(FLASH_DEV *flash_dev, uint32_t blocknum,
		uint32_t *address) {
	FLASH_STATUS stat;
	int is_top = flash_dev->is_top;

	if (!is_top) { /* Bottom Boot Device */
		if (((blocknum >= FLASH_BOTTOM_BLOCK_LOWER) && (blocknum
				<= FLASH_BOTTOM_BLOCK_UPPER))) {

			*address = (blocknum * FLASH_PARM_BLOCK_NUMBYTES);

			stat.Result = StatCompleted;

		}

		else if ((blocknum >= 4 && blocknum <= FLASH_TOTAL_NUMBLOCKS)) {
			*address = ((blocknum - FLASH_BOTTOM_BLOCK_UPPER)
					* FLASH_MAIN_BLOCK_NUMBYTES);

			stat.Result = StatCompleted;
		}

		else {
			stat.Result = StatBadBlock;
		}

	}

	else { /* Top Boot Device */
		if ((blocknum >= FLASH_TOP_BLOCK_LOWER && blocknum
				<= (FLASH_TOTAL_NUMBLOCKS-1))) {

			*address = (((FLASH_TOP_BLOCK_LOWER) * FLASH_MAIN_BLOCK_NUMBYTES)
					+ ((blocknum - (FLASH_TOP_BLOCK_LOWER))
							* FLASH_PARM_BLOCK_NUMBYTES));

			stat.Result = StatCompleted;
		}

		else if (((blocknum >= 0) && (blocknum <= (FLASH_TOP_BLOCK_LOWER-1)))) {
			*address = (blocknum * FLASH_MAIN_BLOCK_NUMBYTES);

			stat.Result = StatCompleted;
		}

		else {
			stat.Result = StatBadBlock;
		}

	}

	stat.SR = 0;

	return (stat);

}

/**
 * This procedure is called to lock the specified block on the flash
 * device.
 * @param blocknum - the block number on the device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_lock_block(FLASH_DEV *flash_dev, uint16_t blocknum) {
	FLASH_STATUS stat;
	uint32_t block_offset;

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
		return (stat);
	}

	flash_get_block_offset(flash_dev, blocknum, &block_offset);

	flash_writef(flash_dev, block_offset, FLASH_CONFIG_SETUP);
	flash_writef(flash_dev, block_offset, FLASH_LOCK_BIT_SET);

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
	}

	stat.SR = flash_read_status(flash_dev);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return stat;
}

/**
 * This procedure is called to lock down the specified block on the flash
 * device.
 * @param blocknum - the block number on the device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_lock_block_down(FLASH_DEV *flash_dev, uint16_t blocknum) {
	FLASH_STATUS stat;
	uint32_t block_offset;

	stat.SR = 0;

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
		return (stat);
	}

	flash_get_block_offset(flash_dev, blocknum, &block_offset);

	flash_writef(flash_dev, block_offset, FLASH_CONFIG_SETUP);

	flash_writef(flash_dev, block_offset, FLASH_LOCKDOWN_BIT_SET);

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
	}

	stat.SR = flash_read_status(flash_dev);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return stat;

}

/**
 * This procedure is called to program the protection register user lock
 * bit on the flash device.
 * Protection Register number to be locked is valid
 * @param ProtectionRegister - Protection Register number to be locked
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_lock_protection(FLASH_DEV *flash_dev,
		uint32_t ProtectionRegister) {

	uint32_t base_offset;
	FLASH_STATUS stat;
	int is_top = flash_dev->is_top;

	if (!is_top) {

		if (ProtectionRegister == 0) {
			base_offset = FLASH_OTP_BASE + FLASH_BOTTOM_PARTITION_BASE;
		} else {
			base_offset = FLASH_OTP_BASE2 + FLASH_BOTTOM_PARTITION_BASE;
		}

	} else {

		if (ProtectionRegister == 0) {
			base_offset = FLASH_OTP_BASE + FLASH_TOP_PARTITION_BASE;
		} else {
			base_offset = FLASH_OTP_BASE2 + FLASH_TOP_PARTITION_BASE;
		}

	}

	/* Make sure part is ready */
	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {

		stat.Result = StatTimeout;

		stat.SR = flash_read_status(flash_dev);

		return (stat);
	}

	flash_clear_status(flash_dev);

	if (ProtectionRegister == 0) {

		flash_writef(flash_dev, base_offset, FLASH_OTP_PROGRAM);
		flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK);
	}

	else {

		flash_writef(flash_dev, base_offset, FLASH_OTP_PROGRAM);

		switch (ProtectionRegister) {
		case 1:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR1);
			break;
		case 2:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR2);
			break;
		case 3:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR3);
			break;
		case 4:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR4);
			break;
		case 5:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR5);
			break;
		case 6:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR6);
			break;
		case 7:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR7);
			break;
		case 8:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR8);
			break;
		case 9:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR9);
			break;
		case 10:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR10);
			break;
		case 11:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR11);
			break;
		case 12:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR12);
			break;
		case 13:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR13);
			break;
		case 14:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR14);
			break;
		case 15:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR15);
			break;
		case 16:
			flash_writef(flash_dev, base_offset, FLASH_OTP_LOCK_PR16);
			break;
		}

	}

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
	} else {
		stat.Result = StatCompleted;
	}

	stat.SR = flash_read_status(flash_dev);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return (stat);

}

/**
 * This procedure is called to enable or disable page mode read to
 * the device.  If page mode is disabled, device is set to synchronous
 * read mode.
 * Note:  If device is set to synchronous, use TMPL_SetConfiguration function
 *        to set burst sequence, burst length, clock edge, etc.) in the
 *        the Read Configuration Register.
 * @param enable - flag "1" to indicate the page mode is anable and
 *                 flag "0" to indicate the page mode is disable to
 *                 the device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_page_mode(FLASH_DEV *flash_dev, uint16_t enable) {
	FLASH_STATUS stat;
	uint32_t address; /* contains the address to load the
	 Read Configuration Register with */

	if (enable) {
		address = FLASH_PAGE_READ_MODE;
	} else {
		address = FLASH_STD_READ_MODE;
	}

	address = address << 1; /* shift so address is on A16..A1 */

	/* write Read Configuration command */
	flash_writef(flash_dev, 0, FLASH_CONFIG_SETUP);
	flash_writef(flash_dev, address, FLASH_SET_READ_CONFIG);

	stat.Result = StatCompleted;
	stat.SR = 0;

	return (stat);
}

/**
 * This procedure is called to program the flash device at the specified
 * starting address contiguously with the specified buffer data.
 * @param address  - the flash address to be programmed.
 * @param buffer   - the buffer containing data to be programmed.
 * @param numitems - the number of data items contained in the buffer.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_program_flash_buffered(FLASH_DEV *flash_dev,
		uint32_t offset, uint32_t *buffer, uint32_t numwords) {
	FLASH_STATUS stat;
	uint32_t cur_add, expect;

	int flash_buffer_size = flash_dev->buffer_size;

	stat.SR = 0;

	printf("\tin flash_program_flash_buffered\n");

	if (numwords > flash_buffer_size) {
		stat.Result = StatTimeout;
		printf("TT %d\n", numwords);
		stat.SR = flash_read_status(flash_dev);

		return (stat);
	}

	/* Make sure part is ready */
	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {

		stat.Result = StatTimeout;
		stat.SR = flash_read_status(flash_dev);

		return (stat);
	}

	/* Write program command, buffer size and data then wait until done */
	flash_writef(flash_dev, offset, FLASH_WRITE_TO_BUFFER);

	flash_writef(flash_dev, offset, (uint32_t) (numwords - 1));

	for (cur_add = offset; cur_add - offset < (numwords); cur_add
			+= sizeof(uint32_t)) {
		expect = *buffer;
		flash_writef(flash_dev, cur_add, expect);
	}
	cur_add -= sizeof(uint32_t); /* can't advance beyond end of array */
	flash_writef(flash_dev, cur_add, FLASH_CONFIRM);

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;

		stat.SR = flash_read_status(flash_dev);

		return (stat);
	}

	flash_writef(flash_dev, offset, FLASH_READ_ARRAY); /* return to array read mode */

	stat.Result = StatCompleted;
	return (stat);

}

/**
 * This procedure is called to program the protection register on
 * the flash device at the specified location with the specified data
 * value.
 * @param  location - the protection register location on the flash
 *                    device to be programmed.
 * @param value    - the data item to be programmed.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_program_protection(FLASH_DEV *flash_dev, uint32_t location,
		uint32_t value) {
	uint32_t base_offset;
	uint32_t offset;
	FLASH_STATUS stat;
	int is_top = flash_dev->is_top;

	stat.SR = 0;

	if (location > FLASH_OTP_NUMWORDS) {
		stat.Result = StatBadOtp;
		return (stat);
	}

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
		return (stat);
	}

	if (!is_top) {
		base_offset = FLASH_BOTTOM_PARTITION_BASE;
		offset = FLASH_OTP_BASE;
	} else {
		base_offset = FLASH_TOP_PARTITION_BASE;
		offset = FLASH_OTP_BASE + (FLASH_TOP_PARTITION_BASE);
	}

	offset += (location * sizeof(FLASH_FDATA));

	flash_clear_status(flash_dev);

	flash_writef(flash_dev, base_offset, FLASH_OTP_PROGRAM);

	flash_writef(flash_dev, offset, value);

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
	} else {
		stat.Result = StatCompleted;
	}

	stat.SR = flash_read_status(flash_dev);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return (stat);

}

/**
 * This procedure is called to issue the program suspend command to
 * the flash device.
 * When this function is called the device is currently in the program
 * mode for the block identified.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_program_suspend(FLASH_DEV *flash_dev) {

	FLASH_STATUS stat;

	flash_writef(flash_dev, 0, FLASH_BLOCK_SUSPEND);

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
	} else {
		stat.Result = StatCompleted;
	}

	stat.SR = flash_read_status(flash_dev);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return (stat);

}

/**
 * This procedure is called to read the status for the specified block
 * from the flash device.
 * @param blocknum - the block number on the device.
 * @param (OUT) blockstat- the status of the block as: unlocked, locked,
 *                         or locked down.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_read_block_status(FLASH_DEV *flash_dev, uint16_t blocknum,
		uint32_t *blockstat) {
	uint32_t stat_offset, block_offset;
	FLASH_STATUS stat;

	stat = flash_get_block_offset(flash_dev, blocknum, &block_offset);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	stat_offset = (block_offset + (2 * sizeof(FLASH_FDATA)));

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
	} else {
		stat.Result = StatCompleted;
	}

	flash_writef(flash_dev, stat_offset, FLASH_READ_ID_CODES);

	*blockstat = flash_readf(flash_dev, stat_offset);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	stat.Result = StatCompleted;

	return (stat);
}

/**
 * This procedure is called to read the protection register value on
 * the flash device from the specified location.
 * @param location - the protection register location on the flash
 *                   device to be read from.
 * @param (OUT) value - the data item read from the register.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_read_protection(FLASH_DEV *flash_dev, uint32_t location,
		uint32_t *value) {
	uint32_t base_offset;
	uint32_t offset;
	FLASH_STATUS stat;

	stat.SR = 0;

	if (location > FLASH_OTP_NUMWORDS) {
		stat.Result = StatBadOtp;
		return (stat);
	}

	base_offset = FLASH_OTP_BASE;

	offset = FLASH_OTP_BASE;

	offset += (location * sizeof(FLASH_FDATA));

	flash_writef(flash_dev, base_offset, FLASH_OTP_READ);

	*value = flash_readf(flash_dev, offset);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	stat.Result = StatCompleted;

	return (stat);

}

/**
 * This procedure is called to issue the resume command to the flash
 * device for the specified block.
 *    The block indicated was previously program suspended or erase
 *    suspended.
 * @param blocknum - the block number to resume.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_resume(FLASH_DEV *flash_dev) {

	FLASH_STATUS stat;

	flash_writef(flash_dev, 0, FLASH_BLOCK_RESUME);

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
	} else {
		stat.Result = StatCompleted;
	}

	stat.SR = flash_read_status(flash_dev);

	return (stat);

}

/**
 * This function is used to write data to the Read Configuration
 * Register (RCR) on the device.  Use this function to set RCR
 * values such as read mode, latency count, wait polarity, data hold,
 * burst sequence, clock edge, and burst length.
 *    A valid configuration setting.
 * @param data - address of configuration data to be read in
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_set_configuration(FLASH_DEV *flash_dev, uint16_t data) {

	FLASH_STATUS stat;
	uint32_t address; /* contains the address to load the
	 Read Configuration Register with */

	/********************************************************/
	/* Convert the RCR into valid address then write it     */
	/********************************************************/
	address = (uint32_t) data;
	address = address << (sizeof(uint16_t) - 1);

	/* write Read Configuration command */

	flash_writef(flash_dev, 0, FLASH_CONFIG_SETUP);
	flash_writef(flash_dev, address, FLASH_SET_READ_CONFIG);

	stat.Result = StatCompleted;
	stat.SR = 0;

	return (stat);

}


/**
 * This procedure is called to unlock all blocks on the flash device.
 *    The blocks were previously locked.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_unlock_all_blocks(FLASH_DEV *flash_dev) {

	FLASH_STATUS stat;
	uint16_t block;
	int flash_total_numblocks = flash_dev->total_numblocks;

	TRACE("\n");
	for (block = 0; block < flash_total_numblocks; block++) {
		stat = flash_unlock_block(flash_dev, block);
		TRACE("block %d status 0x%x\n", block, stat.SR);

		if (stat.Result != StatCompleted) {
			return (stat);
		}
	}

	stat.SR = flash_read_status(flash_dev);

	return (stat);

}
/**
 * This procedure is called to lock all blocks on the flash device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_lock_all_blocks(FLASH_DEV *flash_dev) {

	FLASH_STATUS stat;
	uint16_t block;
	int flash_total_numblocks = flash_dev->total_numblocks;

	TRACE("\n");
	for (block = 0; block < flash_total_numblocks; block++) {
		stat = flash_lock_block(flash_dev, block);
		printf("block %d status 0x%x\n", block, stat.SR);

		if (stat.Result != StatCompleted) {
			return (stat);
		}
	}

	stat.SR = flash_read_status(flash_dev);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return (stat);

}

/**
 * This procedure is called to unlock the specified block on the flash
 * device.
 *    The block indicated was previously locked.
 * @param blocknum - the block number to unlock.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_unlock_block(FLASH_DEV *flash_dev, uint16_t blocknum) {
	FLASH_STATUS stat;
	uint32_t address;

	stat.SR = 0;

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
		return (stat);
	}

	flash_get_block_offset(flash_dev, blocknum, &address);

	flash_writef(flash_dev, address, FLASH_CONFIG_SETUP);

	flash_writef(flash_dev, address, FLASH_LOCK_BIT_CLEAR);

	if (!flash_wait_until_ready(flash_dev, FLASH_ERASE_TIMEOUT)) {
		stat.Result = StatTimeout;
		return (stat);
	}

	stat.SR = flash_read_status(flash_dev);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	stat.Result = StatCompleted;

	return (stat);
}

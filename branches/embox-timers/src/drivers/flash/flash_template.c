/**
 * @file
 * @details
 * Intel Confidential
 * Copyright (C) Intel Corporation 2003
 * All Rights Reserved.
 * --------------------------------------------------------------------
 *
 * Project Name: Flash Templates
 *
 * Module Name: flash_template
 *
 * File: flash_template.C - Common template C source file
 *
 * File Revision: $Revision: 2 $, $JustDate:  1/20/03 $, $Author: Garotg $
 *
 * Purpose:
 *
 *    The purpose of this file is to implement the common application
 *    programmers interface for flash template software.  This module
 *    implements all flash template subroutines that do not have
 *    a device specific implementation in the device.c module for
 *    the supported device.  Macros are used to determine if
 *    the template.c common implementation or the device.c specific
 *    implementation is used by the template for each subroutine.
 *
 *    Note that some common template functions implemented in this
 *    module will return STATUS_UNSUPPORTED since no common
 *    implementation is possible due to the differences between
 *    supported devices for those functions.  The device.c module
 *    must contain implementations for these particular functions
 *    when the function is in fact supported for that device.
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
#include <drivers/flash_if.h>

#define __ATTR //__attribute__ ((section (".reloc.flash_utils")))

/**
 * This procedure is called to clear the status register on the flash
 * device.
 */
void flash_clear_status(FLASH_DEV *flash_dev) {
	flash_writef(flash_dev, 0, FLASH_CLEAR_STATUS_REGISTER);
}

/**
 * This procedure is called to erase a data block on the flash
 * device.
 * @param blocknum - the block number on the device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_erase_block(FLASH_DEV *flash_dev, uint16_t blocknum) {
	FLASH_STATUS stat;
	uint32_t blockadd;

	stat = flash_get_block_offset(flash_dev, blocknum, &blockadd);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	flash_clear_status(flash_dev);

	flash_writef(flash_dev, blockadd, FLASH_BLOCK_ERASE);
	flash_writef(flash_dev, blockadd, FLASH_CONFIRM);

	if (!flash_wait_until_ready(flash_dev, FLASH_ERASE_TIMEOUT)) {
		stat.Result = StatTimeout;
	} else {
		stat.Result = StatCompleted;
	}

	/* so? */
	stat.SR = flash_readf(flash_dev, 0);

	/* return device to read array mode */

	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);
	return (stat);
}


/**
 * This procedure is called to get the flash address for a given
 * query offset.
 * @param offset   - query offset location
 * @param (OUT) address  - the flash address for the specified query
 *						  offset.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_get_query_address(FLASH_DEV *flash_dev, uint32_t offset,
		uint32_t *address) {
	FLASH_STATUS stat;
	*address = offset << 2;

	stat.Result = StatCompleted;
	stat.SR = 0;

	return (stat);
}

/**
 * This procedure is called to program the flash device at the specified
 * address with the single specified data value.  See the flash device
 * datasheet for specific details on this command.
 * @param address  - the flash address to be programmed.
 * @param item	 - the data value to be programmed.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_program_flash(FLASH_DEV *flash_dev, uint32_t offset,
		uint32_t item) {
	FLASH_STATUS stat;

	int flash_total_size = flash_dev->total_size;

	stat.SR = 0;

	if (offset >= flash_total_size) {
		stat.Result = StatBadAddress;

		return (stat);
	}

	flash_clear_status(flash_dev);

	if ((offset & 0x1) != 0) {
		offset--;
	}

	flash_writef(flash_dev, offset, FLASH_PROGRAM_SETUP);
	flash_writef(flash_dev, offset, item);

	if (!flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT)) {
		stat.Result = StatTimeout;
	} else {
		stat.Result = StatCompleted;
	}

	/* so? */
	stat.SR = flash_readf(flash_dev, 0);

	/* return device to read array mode */
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return (stat);
}

/**
 * This procedure is called to issue the query command to
 * the flash device.
 * @param (OUT) *query - pointer to query structure
 * @return FLASH_STATUS
 * WARNING: overly complex function.
 */
FLASH_STATUS flash_query(FLASH_DEV *flash_dev, struct _FLASH_QUERY_DATA *query) {
	FLASH_STATUS stat;
	uint32_t add, offset, longitem, i;
	FLASH_FDATA item;

	flash_writef(flash_dev, 0, FLASH_READ_QUERY);

	offset = FLASH_QUERY_START_OFFSET;

	/* read query string */
	for (i = 0; i < 3; i++) {
		stat = flash_get_query_address(flash_dev, offset, &add);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, add);

		item &= 0xff;
		query->QueryStr[i] = (char) item;
		offset++;
	}
	query->QueryStr[3] = '\0'; /* null terminate string */

	/* read vendor id */
	query->VendorId = 0;
	for (i = 0; i < 2; i++) {
		stat = flash_get_query_address(flash_dev, offset, &add);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, add);

		item &= 0x00ff;
		item = item << (8 * (1 - i));

		query->VendorId = (uint16_t) (query->VendorId | item);
		offset++;
	}

	/* read extended table ptr */
	query->ExtTablePtr = 0;
	for (i = 0; i < 2; i++) {
		stat = flash_get_query_address(flash_dev, offset, &add);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, add);

		item &= 0x00ff;
		item = item << (8 * (1 - i));

		query->ExtTablePtr = (uint16_t) (query->ExtTablePtr | item);
		offset++;
	}

	/* read alternate vendor id */
	query->AltVendorId = 0;
	for (i = 0; i < 2; i++) {
		stat = flash_get_query_address(flash_dev, offset, &add);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, add);

		item &= 0x00ff;
		item = item << (8 * (1 - i));

		query->AltVendorId = (uint16_t) (query->AltVendorId | item);
		offset++;
	}

	/* read secondary extended table ptr */
	query->SecExtTablePtr = 0;
	for (i = 0; i < 2; i++) {
		stat = flash_get_query_address(flash_dev, offset, &add);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, add);

		item &= 0x00ff;
		item = item << (8 * (1 - i));

		query->SecExtTablePtr = (uint16_t) (query->SecExtTablePtr | item);
		offset++;
	}

	/* read minimum voltage */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->VccMin = (uint8_t) item;
	offset++;

	/* read maximum voltage */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->VccMax = (uint8_t) item;
	offset++;

	/* read supply voltage */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->VppMin = (uint8_t) item;
	offset++;

	/* read supply max voltage */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->VppMax = (uint8_t) item;
	offset++;

	/* read typical program timeout */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->TypicalProgTimeout = (uint8_t) item;
	offset++;

	/* read typical buffer timeout */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->TypicalBufferTimeout = (uint8_t) item;
	offset++;

	/* read block erase timeout */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->BlockEraseTimeout = (uint8_t) item;
	offset++;

	/* read chip erase timeout */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->ChipEraseTimeout = (uint8_t) item;
	offset++;

	/* read max single timeout */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->MaxSingleTimeout = (uint8_t) item;
	offset++;

	/* read max buffer timeout */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->MaxBufferTimeout = (uint8_t) item;
	offset++;

	/* read max block erase timeout */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->MaxBlockEraseTimeout = (uint8_t) item;
	offset++;

	/* read max chip erase timeout */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->MaxChipEraseTimeout = (uint8_t) item;
	offset++;

	/* read device size */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->DeviceSize = (uint8_t) item;
	offset++;

	/* read device interface */
	query->DeviceInterface = 0;
	for (i = 0; i < 2; i++) {
		stat = flash_get_query_address(flash_dev, offset, &add);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, add);

		item &= 0x00ff;
		item = item << (8 * (1 - i));

		query->DeviceInterface = (uint16_t) (query->DeviceInterface | item);
		offset++;
	}

	/* read max write buffer bytes */
	query->MaxWriteBufferBytes = 0;
	for (i = 0; i < 2; i++) {
		stat = flash_get_query_address(flash_dev, offset, &add);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, add);

		item &= 0x00ff;
		item = item << (8 * (1 - i));

		query->MaxWriteBufferBytes = (uint16_t) (query->MaxWriteBufferBytes
				| item);
		offset++;
	}

	/* read num erase blocks */
	stat = flash_get_query_address(flash_dev, offset, &add);

	if (stat.Result != StatCompleted) {
		return (stat);
	}

	item = flash_readf(flash_dev, add);

	item &= 0x00ff;

	query->NumEraseBlocks = (uint8_t) item;
	offset++;

	/* read erase block information */
	query->EraseBlock1Information = 0;
	for (i = 0; i < 4; i++) {
		stat = flash_get_query_address(flash_dev, offset, &add);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, add);

		item &= 0x00ff;
		longitem = (uint32_t) ((uint32_t) item << (8 * (3 - i)));

		query->EraseBlock1Information
				= (uint32_t) (query->EraseBlock1Information | longitem);

		offset++;
	}
	query->EraseBlock2Information = 0;
	for (i = 0; i < 4; i++) {
		stat = flash_get_query_address(flash_dev, offset, &add);

		if (stat.Result != StatCompleted) {
			return (stat);
		}

		item = flash_readf(flash_dev, add);

		item &= 0x00ff;
		longitem = (uint32_t) ((uint32_t) item << (8 * (3 - i)));

		query->EraseBlock2Information
				= (uint32_t) (query->EraseBlock2Information | longitem);
		offset++;
	}

	stat.Result = StatCompleted;

	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	return (stat);
}

/**
 * This procedure is called to read the status for the specified block
 * from the flash device.
 * @param (OUT) mcode	- the manufacturer code.
 * @param (OUT) deviceid - the device id.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_read_device_ID(FLASH_DEV *flash_dev, uint32_t *mcode,
		uint32_t *deviceid) {
	FLASH_STATUS stat;
	uint32_t idaddress;

	idaddress = sizeof(FLASH_FDATA);

	flash_writef(flash_dev, 0, FLASH_READ_ID_CODES);

	*mcode = flash_readf(flash_dev, 0);

	*deviceid = flash_readf(flash_dev, idaddress);

	flash_writef(flash_dev, 0, FLASH_READ_ARRAY); /* o_O magic string*/
	stat.Result = StatCompleted;
	stat.SR = 0;

	return (stat);

}
/**
 * This procedure is called to read a single data item directly from the
 * specified device address.  This function is used internally by the
 * flash template api.  Clients that need to read data to the flash
 * device should use the flash_read_flash() command.
 * @param offset  - the flash address to be written to.
 * @return the flash data from the device.
 */
FLASH_FDATA flash_readf(FLASH_DEV *flash_dev, uint32_t offset) {
	volatile uint32_t tmp;

/*
 * Something strange is happening in this function. Empty cycle and
 * TRACE are necessary for correct execution. Who can tell me why? -- Alexander
 */
	int i;
	for (i = 0; i < 100 ; i++) {
	}

	tmp = *((FLASH_FDATA * volatile)(flash_dev->start_address + offset));

	TRACE("0x%x\n", tmp);

	return tmp;
}

/**
 * This procedure is called to read one or more data items from
 * the flash device at the specified starting address.
 * @param address  - the starting device address.
 * @param (OUT) buffer - the buffer to contain the data items read.
 * @param numbytes - the number of data items to read.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_read_flash(FLASH_DEV *flash_dev, uint32_t offset,
		void *buffer, uint32_t num) {
	FLASH_STATUS stat;
	uint32_t cur_addr;
	uint32_t *ptr;
	int flash_total_size = flash_dev->total_size;

	stat.SR = 0;

	if ((offset + num) > flash_total_size) {
		stat.Result = StatBadAddress;

		return (stat);
	}

	flash_clear_status(flash_dev);
	flash_writef(flash_dev, 0, FLASH_READ_ARRAY);

	for (cur_addr = offset; cur_addr - offset < (num); cur_addr
			+= sizeof(uint32_t)) {
		ptr = (FLASH_FDATA *) ((char *) buffer + cur_addr - offset);
		*ptr = flash_readf(flash_dev, cur_addr);
	}
	stat.Result = StatCompleted;

	stat.SR = flash_read_status(flash_dev);

	return stat;
}

/**
 * This procedure is called to read the status register value from
 * the flash device.
 * @return FLASH_FDATA - the status register value read from the device.
 */
FLASH_FDATA flash_read_status(FLASH_DEV *flash_dev) {
	volatile FLASH_FDATA status = 0;

	flash_writef(flash_dev, 0, FLASH_READ_STATUS_REGISTER);

	status = flash_readf(flash_dev, 0);

	return status;

}

/**
 * This procedure is called to wait until the flash device status
 * indicates a ready state or times out.
 * @param timeout  - timeout value specified as number of times
 *				   to read the status register before giving up.
 * @return uint8_t - boolean flag indicating whether the ready state was
 *                 reached before the timeout number of reads
 *                 occured.
 */
uint8_t flash_wait_until_ready(FLASH_DEV *flash_dev, uint32_t timeout) {
	volatile FLASH_FDATA flash_status;
	while (timeout--) {
		flash_status = flash_read_status(flash_dev);
		if (mIsStatusReady(flash_status))
		{
			TRACE("\nready!\n");
			return true;
		}
		if (timeout % 100000 == 0) {
			TRACE("0x%x\n", flash_status);
		}
	}
	return false;
}

void flash_writef(FLASH_DEV *flash_dev, uint32_t offset,
		volatile FLASH_FDATA value) __ATTR;
/**
 * This procedure is called to write a single data item directly to the
 * specified device address.  This function is used internally by the
 * flash template api.  Clients that need to write data to the flash
 * device should use the TMPL_ProgramFlash or TMPL_ProgramFlashBuffered
 * command.
 * @param offset  - the flash address to be written to.
 * @param value	- the flash data to write to the device.
 */
void flash_writef(FLASH_DEV *flash_dev, uint32_t offset,
		volatile FLASH_FDATA value) {
	uint32_t *ptr;
	ptr = (FLASH_FDATA * volatile) (flash_dev->start_address + offset);
	FLASH_WRITE_ENABLE;
	*ptr = value;
	FLASH_WRITE_DISABLE;
}

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
 * @date 09.07.2009
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

/**
 * This procedure is called to clear the status register on the flash
 * device.
 */
void flash_clear_status ( FLASH_DEV *flash_dev )
{
	int flash_base_address = flash_dev->start_address;
	flash_writef( flash_base_address,  FLASH_CLEAR_STATUS_REGISTER );

}

/**
 * This procedure is called to erase a data block on the flash
 * device.
 * @param blocknum - the block number on the device.
 * @param returnSR - flag to indicate whether the device status register
 *				   value should be returned by this function.
 * @return TMPL_Status
 */
FLASH_STATUS flash_erase_block ( FLASH_DEV *flash_dev, uint16_t blocknum, uint8_t returnSR )
{
	int flash_base_address;
	FLASH_STATUS   stat;
	uint32_t blockadd;

	stat = flash_get_block_address(flash_dev, blocknum, &blockadd );

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	if ( returnSR )
	{
		flash_clear_status(flash_dev);
	}


	flash_writef(blockadd, FLASH_BLOCK_ERASE);
	flash_writef(blockadd, FLASH_CONFIRM );

	if ( !flash_wait_until_ready(flash_dev, FLASH_ERASE_TIMEOUT / 2) )
	{
		stat.Result = StatTimeout;
	} else
	{
		stat.Result = StatCompleted;
	}

	if ( returnSR )
	{
		flash_readf(blockadd, (FLASH_FDATA_PTR)&stat.SR);
	}

	if ( !flash_wait_until_ready(flash_dev, FLASH_ERASE_TIMEOUT) )
	{
		stat.Result = StatTimeout;
	} else
	{
		stat.Result = StatCompleted;
	}

	/* return device to read array mode */

	flash_base_address = flash_dev->start_address;
	flash_writef(flash_base_address, FLASH_READ_ARRAY );
	return( stat );
}

/**
 * This procedure is called to return a flash ptr given a
 * specified device address.  This routine will likely need to be
 * provided externally by the template client in order to properly
 * deal with addressing details that are specific to the HW platform.
 * @param address  - the flash address
 * @return TMPL_FDATA_PTR  - address returned in ptr form
 */
FLASH_FDATA_PTR  flash_get_fptr (uint32_t address )
{
	return( (FLASH_FDATA_PTR)address );
}

/**
 * This procedure is called to get the flash address for a given
 * query offset.
 * @param offset   - query offset location
 * @param (OUT) address  - the flash address for the specified query
 *						  offset.
 * @return TMPL_Status
 */
FLASH_STATUS flash_get_query_address (FLASH_DEV *flash_dev, uint32_t offset, uint32_t *address )
{
	FLASH_STATUS stat;
	int flash_base_address;
	*address = offset << 2;

	flash_base_address = flash_dev->start_address;
	*address += flash_base_address;

	stat.Result = StatCompleted;
	stat.SR = 0;

	return( stat );
}

/**
 * This procedure is called to program the flash device at the specified
 * address with the single specified data value.  See the flash device
 * datasheet for specific details on this command.
 * @param address  - the flash address to be programmed.
 * @param item	 - the data value to be programmed.
 * @param returnSR - flag to indicate whether the device status register
 *				   value should be returned by this function.
 * @return TMPL_Status
 */
FLASH_STATUS flash_program_flash ( FLASH_DEV *flash_dev, uint32_t address, uint32_t item, uint8_t  returnSR )
{
#if 0
	printf("flash_program_flash: flash_dev id = %d, address = 0x%x, item = %d\t\t",
			flash_dev->dev, address, item);
#endif
	FLASH_STATUS stat;
	int flash_base_address;
#if 0
	FLASH_FDATA writedata;
#endif

	int flash_total_size = flash_dev->total_size;

	stat.SR = 0;

	if ( address >= flash_total_size )
	{
		stat.Result = StatBadAddress;

		return( stat );
	}

	if ( returnSR )
	{
		flash_clear_status(flash_dev);
	}

/*	writedata = (FLASH_FDATA)( item );*/

	if ( ( address & 0x1 ) != 0 )
	{
		address--;
/*		writedata |= 0xFF00;*/
	} else
	{
/*	   writedata |= 0x00ff;*/
	}

	flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT);  /*magic*/

	flash_writef(address, FLASH_PROGRAM_SETUP );
	flash_writef(address, item);

	if ( !flash_wait_until_ready(flash_dev, FLASH_PROGRAM_TIMEOUT ) )
	{
		stat.Result = StatTimeout;
	} else
	{
		stat.Result = StatCompleted;
	}

	flash_base_address = flash_dev->start_address;
	if ( returnSR )
	{
		flash_readf(flash_base_address, (FLASH_FDATA_PTR)&stat.SR);
	}

	/* return device to read array mode */
	flash_writef(flash_base_address, FLASH_READ_ARRAY );

	return( stat );
}

/**
 * This procedure is called to issue the query command to
 * the flash device.
 * @param (OUT) *query - pointer to query structure
 * @return TMPL_Status
 */
FLASH_STATUS flash_query (FLASH_DEV *flash_dev, struct _FLASH_QUERY_DATA *query )
{
	FLASH_STATUS stat;
	uint32_t add, offset, longitem, i;
	FLASH_FDATA item;
	int flash_base_address = flash_dev->start_address;

	flash_writef(flash_base_address, FLASH_READ_QUERY );

	offset = FLASH_QUERY_START_OFFSET;

	/* read query string */
	for ( i=0; i < 3; i++ )
	{
		stat = flash_get_query_address(flash_dev,offset, &add);

		if ( stat.Result != StatCompleted )
		{
			return( stat );
		}

		flash_readf(add, &item);

		item &= 0xff;
		query->QueryStr[i] = (char)item;
		offset++;
	}
	query->QueryStr[3] = '\0'; /* null terminate string */

	/* read vendor id */
	query->VendorId = 0;
	for ( i=0; i < 2; i++ )
	{
		stat = flash_get_query_address(flash_dev,offset, &add);

		if ( stat.Result != StatCompleted )
		{
			return( stat );
		}

		flash_readf(add, &item);

		item &= 0x00ff;
		item = item << (8*(1-i) );

		query->VendorId = (uint16_t)( query->VendorId | item );
		offset++;
	}

	/* read extended table ptr */
	query->ExtTablePtr = 0;
	for ( i=0; i < 2; i++ )
	{
		stat = flash_get_query_address(flash_dev,offset, &add);

		if ( stat.Result != StatCompleted )
		{
			return( stat );
		}

		flash_readf(add, &item);

		item &= 0x00ff;
		item = item << (8*(1-i) );

		query->ExtTablePtr = (uint16_t)( query->ExtTablePtr | item );
		offset++;
	}

	/* read alternate vendor id */
	query->AltVendorId = 0;
	for ( i=0; i < 2; i++ )
	{
		stat = flash_get_query_address(flash_dev,offset, &add);

		if ( stat.Result != StatCompleted )
		{
			return( stat );
		}

		flash_readf(add, &item);

		item &= 0x00ff;
		item = item << (8*(1-i) );

		query->AltVendorId = (uint16_t)( query->AltVendorId | item );
		offset++;
	}

	/* read secondary extended table ptr */
	query->SecExtTablePtr = 0;
	for ( i=0; i < 2; i++ )
	{
		stat = flash_get_query_address(flash_dev,offset, &add);

		if ( stat.Result != StatCompleted )
		{
			return( stat );
		}

		flash_readf(add, &item);

		item &= 0x00ff;
		item = item << (8*(1-i) );

		query->SecExtTablePtr = (uint16_t)
								( query->SecExtTablePtr | item );
		offset++;
	}

	/* read minimum voltage */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->VccMin = (uint8_t)item;
	offset++;

	/* read maximum voltage */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->VccMax = (uint8_t)item;
	offset++;

	/* read supply voltage */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->VppMin = (uint8_t)item;
	offset++;

	/* read supply max voltage */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->VppMax = (uint8_t)item;
	offset++;

	/* read typical program timeout */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->TypicalProgTimeout = (uint8_t)item;
	offset++;

	/* read typical buffer timeout */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->TypicalBufferTimeout = (uint8_t)item;
	offset++;

	/* read block erase timeout */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->BlockEraseTimeout = (uint8_t)item;
	offset++;

	/* read chip erase timeout */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->ChipEraseTimeout = (uint8_t)item;
	offset++;

	/* read max single timeout */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->MaxSingleTimeout = (uint8_t)item;
	offset++;

	/* read max buffer timeout */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->MaxBufferTimeout = (uint8_t)item;
	offset++;

	/* read max block erase timeout */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->MaxBlockEraseTimeout = (uint8_t)item;
	offset++;

	/* read max chip erase timeout */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->MaxChipEraseTimeout = (uint8_t)item;
	offset++;

	/* read device size */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->DeviceSize = (uint8_t)item;
	offset++;

	/* read device interface */
	query->DeviceInterface = 0;
	for ( i=0; i < 2; i++ )
	{
		stat = flash_get_query_address(flash_dev,offset, &add);

		if ( stat.Result != StatCompleted )
		{
			return( stat );
		}

		flash_readf(add, &item);

		item &= 0x00ff;
		item = item << (8*(1-i) );

		query->DeviceInterface = (uint16_t)
								 ( query->DeviceInterface | item );
		offset++;
	}

	/* read max write buffer bytes */
	query->MaxWriteBufferBytes = 0;
	for ( i=0; i < 2; i++ )
	{
		stat = flash_get_query_address(flash_dev,offset, &add);

		if ( stat.Result != StatCompleted )
		{
			return( stat );
		}

		flash_readf(add, &item);

		item &= 0x00ff;
		item = item << (8*(1-i) );

		query->MaxWriteBufferBytes = (uint16_t)
									 ( query->MaxWriteBufferBytes | item );
		offset++;
	}

	/* read num erase blocks */
	stat = flash_get_query_address(flash_dev,offset, &add);

	if ( stat.Result != StatCompleted )
	{
		return( stat );
	}

	flash_readf(add, &item);

	item &= 0x00ff;

	query->NumEraseBlocks = (uint8_t)item;
	offset++;

	/* read erase block information */
	query->EraseBlock1Information = 0;
	for ( i=0; i < 4; i++ )
	{
		stat = flash_get_query_address(flash_dev,offset, &add);

		if ( stat.Result != StatCompleted )
		{
			return( stat );
		}

		flash_readf(add, &item);

		item &= 0x00ff;
		longitem = (uint32_t)((uint32_t)item << (8*(3-i) ));

		query->EraseBlock1Information = (uint32_t)
									   ( query->EraseBlock1Information | longitem );

		offset++;
	}
		query->EraseBlock2Information = 0;
		for ( i=0; i < 4; i++ )
		{
			stat = flash_get_query_address(flash_dev,offset, &add);

			if ( stat.Result != StatCompleted )
			{
				return( stat );
			}

			flash_readf(add, &item);

			item &= 0x00ff;
			longitem = (uint32_t)((uint32_t)item << (8*(3-i) ));

			query->EraseBlock2Information = (uint32_t)
										   ( query->EraseBlock2Information | longitem );
			offset++;
	}

	stat.Result = StatCompleted;

	flash_writef(flash_base_address, FLASH_READ_ARRAY );

	return( stat );
}

/**
 * This procedure is called to read the status for the specified block
 * from the flash device.
 * @param (OUT) mcode	- the manufacturer code.
 * @param (OUT) deviceid - the device id.
 * @return TMPL_Status
 */
FLASH_STATUS flash_read_device_ID (FLASH_DEV *flash_dev, uint32_t *mcode, uint32_t *deviceid )
{
	FLASH_STATUS stat;
	uint32_t idaddress;

	int flash_base_address = flash_dev->start_address;
	idaddress = ( flash_base_address + sizeof( FLASH_FDATA ) );

	flash_writef(flash_base_address, FLASH_READ_ID_CODES);

	flash_readf(flash_base_address, mcode );

	flash_readf(idaddress, deviceid);
#if 0
	flash_readf(FLASH_BASE_ADDRESS + 0x80 * sizeof(FLASH_FDATA), &temp);
	flash_readf(FLASH_BASE_ADDRESS + 0x85 * sizeof(FLASH_FDATA), &temp);
	flash_readf(FLASH_BASE_ADDRESS + 0x86 * sizeof(FLASH_FDATA), &temp);
	flash_readf(FLASH_BASE_ADDRESS + 0x87 * sizeof(FLASH_FDATA), &temp);
	flash_readf(FLASH_BASE_ADDRESS + 0x88 * sizeof(FLASH_FDATA), &temp);
	flash_readf(FLASH_BASE_ADDRESS + 0x89 * sizeof(FLASH_FDATA), &temp);
#endif
	flash_writef(flash_base_address, FLASH_READ_ARRAY ); /* o_O magic string*/
	stat.Result = StatCompleted;
	stat.SR = 0;

	return( stat );

}

/**
 * This procedure is called to read a single data item directly from the
 * specified device address.  This function is used internally by the
 * flash template api.  Clients that need to read data from the flash
 * device should use the TMPL_ReadFlash command.
 *	The flash device is in the READ_ARRAY mode when this function is
 *	called.
 * @param address  - the flash address to be read from.
 * @param (OUT) value - the flash data read from the device.
 */
/*volatile */int flash_readf (uint32_t address, FLASH_FDATA_PTR value ) {
	FLASH_FDATA_PTR  fptr;

	fptr = flash_get_fptr(address);

	*value = *fptr;
	return 0;
}

/**
 * This procedure is called to read one or more data items from
 * the flash device at the specified starting address.
 * @param address  - the starting device address.
 * @param (OUT) buffer - the buffer to contain the data items read.
 * @param numbytes - the number of data items to read.
 * @param returnSR - flag to indicate whether the device status register
 *				   value should be returned by this function.
 * @return TMPL_Status
 */
FLASH_STATUS flash_read_flash (FLASH_DEV *flash_dev, uint32_t address, void *buffer, uint32_t num, uint8_t returnSR )
{
	FLASH_STATUS stat;
	uint32_t cur_addr;
	int flash_base_address, flash_total_size = flash_dev->total_size;

	stat.SR = 0;

	if ( ( address + num ) > flash_total_size )
	{
		stat.Result = StatBadAddress;

		return( stat );
	}

	if ( returnSR )
	{
		flash_clear_status(flash_dev);
	}

	flash_base_address = flash_dev->start_address;
	flash_writef(flash_base_address, FLASH_READ_ARRAY );

	for (cur_addr = address;
		 cur_addr - address < (num);
		 cur_addr += sizeof(uint32_t)) {
		flash_readf(cur_addr, (void*)((char *)buffer + cur_addr - address));
	}
	stat.Result = StatCompleted;

	if ( returnSR )
	{
		stat.SR = flash_read_status(flash_dev);
	}

	return( stat );
}

/**
 * This procedure is called to read the status register value from
 * the flash device.
 * @return TMPL_FDATA - the status register value read from the device.
 */
FLASH_FDATA flash_read_status (FLASH_DEV *flash_dev)
{
	FLASH_FDATA status;

	int flash_base_address = flash_dev->start_address;
	flash_writef(flash_base_address, FLASH_READ_STATUS_REGISTER );

	flash_readf(flash_base_address, &status );

	return( status );

}

/**
 * This procedure is called to wait until the flash device status
 * indicates a ready state or times out.
 * @param timeout  - timeout value specified as number of times
 *				   to read the status register before giving up.
 * @return uint8_t - boolean flag indicating whether the ready state was
 *				 reached before the timeout number of reads
 *				 occured.
 */
uint8_t flash_wait_until_ready ( FLASH_DEV *flash_dev, uint32_t timeout )
{

	while ( timeout )
	{

		if ( mIsStatusReady( flash_read_status(flash_dev) ) )
		{
			return( true );
		}
		timeout--;
	}

	return( false );
}

/**
 * This procedure is called to write a single data item directly to the
 * specified device address.  This function is used internally by the
 * flash template api.  Clients that need to write data to the flash
 * device should use the TMPL_ProgramFlash or TMPL_ProgramFlashBuffered
 * command.
 * @param address  - the flash address to be written to.
 * @param value	- the flash data to write to the device.
 */
/*volatile */int flash_writef ( uint32_t address, FLASH_FDATA value )
{
	FLASH_FDATA_PTR  fptr = flash_get_fptr(address);

	*((volatile uint32_t*)0x80000000) |= (1<<11);

	*fptr = value;

	*((volatile uint32_t*)0x80000000) &= ~(1<<11);
	return 0;
}

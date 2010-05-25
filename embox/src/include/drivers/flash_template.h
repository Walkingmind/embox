/**
 * @file
 * @details
 * Intel Confidential
 * Copyright (C) Intel Corporation 2003-2005
 * All Rights Reserved.
 * --------------------------------------------------------------------
 *
 * Project Name: Flash Templates
 *
 * Module Name: flash_template
 *
 * File: flash_template.H - Common template C header
 *
 * File Revision: $Revision: 2 $, $JustDate:  1/20/03 $, $Author: Garotg $
 *
 * Purpose:
 *
 *    The purpose of this file is to define the common application
 *    programmers interface for Flash template software.  This module
 *    defines all flash template subroutines and common definitions.
 *
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

#ifndef __FLASH_TEMPLATE_H  /* ensure this file only gets included once */
#define __FLASH_TEMPLATE_H

#include <types.h>
#include <drivers/flash_intel_p30.h> /* include device specific header */
#include <drivers/flash_if.h>
/* Status Macros */

#define mIsBlockLocked(A) ( ( A & FLASH_SR_BLOCK_LOCKED ) == FLASH_SR_BLOCK_LOCKED )
#define mIsProgramSuspended(A) ( ( A & FLASH_SR_PROGRAM_SUSPENDED ) == FLASH_SR_PROGRAM_SUSPENDED )
#define mIsVppLow(A) ( ( A & FLASH_SR_VPP_LOW ) == FLASH_SR_VPP_LOW )
#define mIsProgramError(A) ( ( A & FLASH_SR_PROGRAM_ERROR ) == FLASH_SR_PROGRAM_ERROR )
#define mIsEraseError(A) ( ( A & FLASH_SR_ERASE_ERROR ) == FLASH_SR_ERASE_ERROR )
#define mIsEraseSuspended(A) ( ( A & FLASH_SR_ERASE_SUSPENDED ) == FLASH_SR_ERASE_SUSPENDED )
#define mIsStatusReady(A) ( ( A & FLASH_SR_STATUS_READY ) == FLASH_SR_STATUS_READY )
#define mIsBlockstatLocked(A) ( ( A & FLASH_BLOCKSTAT_LOCKED ) == FLASH_BLOCKSTAT_LOCKED )
#define mIsBlockstatUnlocked(A) ( A == FLASH_BLOCKSTAT_UNLOCKED )
#define mIsBlockstatLockedDown(A) ( ( A & FLASH_BLOCKSTAT_LOCKEDDOWN ) == FLASH_BLOCKSTAT_LOCKEDDOWN )

#define FLASH_QUERY_START_OFFSET 0x10

/* operation codes */
#define FLASH_PROGRAM_SETUP         0x00400040
#define FLASH_READ_STATUS_REGISTER  0x00700070
#define FLASH_CLEAR_STATUS_REGISTER 0x00500050
#define FLASH_READ_ID_CODES         0x00900090
#define FLASH_READ_QUERY            0x00980098
#define FLASH_BLOCK_ERASE           0x00200020
#define FLASH_CONFIRM               0x00D000D0
#define FLASH_READ_ARRAY            0x00ff00ff
#define FLASH_CONFIG_SETUP          0x00600060

/* Status Register Values */
#define FLASH_SR_BLOCK_LOCKED         0x00020002
#define FLASH_SR_PROGRAM_SUSPENDED    0x00040004
#define FLASH_SR_VPP_LOW              0x00080008
#define FLASH_SR_PROGRAM_ERROR        0x00100010
#define FLASH_SR_ERASE_ERROR          0x00200020
#define FLASH_SR_ERASE_SUSPENDED      0x00400040
#define FLASH_SR_STATUS_READY         0x00800080

typedef uint32_t FLASH_FDATA; /* flash data item */

/*
 *  Flash template function declarations
 */

/**
 * This procedure is called to clear the status register on the flash
 * device.
 */
void flash_clear_status (FLASH_DEV *flash_dev);

/**
 * This procedure is called to erase all data blocks on the flash
 * device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_erase_all_blocks (FLASH_DEV *flash_dev);

/**
 * This procedure is called to erase a data block on the flash
 * device.
 * @param blocknum - the block number on the device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_erase_block (FLASH_DEV *flash_dev, uint16_t blocknum);

/**
 * This procedure is called to issue the erase suspend command to
 * the flash device.
 * When this function is called the device is currently in the erase
 * mode for the block identified.
 *
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_erase_suspend (FLASH_DEV *flash_dev);


/**
 * This procedure is called to retrieve the extended query
 * data from the flash device.
 * @param (OUT) *extquery - pointer to extended query structure
 * @return FLASH_STATUS
*/
FLASH_STATUS flash_extended_query(FLASH_DEV *flash_dev, struct _FLASH_EXTQUERY *extquery );

/**
 * This procedure is called to get the flash starting address for the
 * specified block number.
 * @param blocknum - the block number on the device.
 * @param (OUT) address  - the starting flash address for the specified
 *                         block.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_get_block_offset ( FLASH_DEV *flash_dev, uint32_t blocknum, uint32_t *address );


/**
 * This procedure is called to get the flash address for a given
 * query offset.
 * @param offset   - query offset location
 * @param (OUT) address  - the flash address for the specified query
 *						  offset.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_get_query_address (FLASH_DEV *flash_dev, uint32_t offset, uint32_t *address );

/**
 * This procedure is called to lock the specified block on the flash
 * device.
 * @param blocknum - the block number on the device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_lock_block (FLASH_DEV *flash_dev, uint16_t blocknum);

/**
 * This procedure is called to lock all blocks on the flash device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_lock_all_blocks (FLASH_DEV *flash_dev);

/**
 * This procedure is called to lock down the specified block on the flash
 * device.
 * @param blocknum - the block number on the device.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_lock_block_down (FLASH_DEV *flash_dev, uint16_t blocknum);

/**
 * This procedure is called to program the protection register user lock
 * bit on the flash device.
 * Protection Register number to be locked is valid
 * @param ProtectionRegister - Protection Register number to be locked
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_lock_protection (FLASH_DEV *flash_dev, uint32_t ProtectionRegister);

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
FLASH_STATUS flash_page_mode (FLASH_DEV *flash_dev, uint16_t enable);

/**
 * This procedure is called to program the flash device at the specified
 * address with the single specified data value.  See the flash device
 * datasheet for specific details on this command.
 * @param address  - the flash address to be programmed.
 * @param item	 - the data value to be programmed.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_program_flash (FLASH_DEV *flash_dev, uint32_t address, uint32_t item);

/**
 * This procedure is called to program the flash device at the specified
 * starting address contiguously with the specified buffer data.
 * @param address  - the flash address to be programmed.
 * @param buffer   - the buffer containing data to be programmed.
 * @param numitems - the number of data items contained in the buffer.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_program_flash_buffered (FLASH_DEV *flash_dev, uint32_t address, uint32_t *buffer, uint32_t numbytes);

/**
 * This procedure is called to program the protection register on
 * the flash device at the specified location with the specified data
 * value.
 * @param  location - the protection register location on the flash
 *                    device to be programmed.
 * @param value    - the data item to be programmed.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_program_protection (FLASH_DEV *flash_dev, uint32_t location, FLASH_FDATA value);

/**
 * This procedure is called to issue the program suspend command to
 * the flash device.
 * When this function is called the device is currently in the program
 * mode for the block identified.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_program_suspend (FLASH_DEV *flash_dev);

/**
 * This procedure is called to issue the query command to
 * the flash device.
 * @param (OUT) *query - pointer to query structure
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_query (FLASH_DEV *flash_dev, struct _FLASH_QUERY_DATA *query);

/**
 * This procedure is called to read the status for the specified block
 * from the flash device.
 * @param blocknum - the block number on the device.
 * @param (OUT) blockstat- the status of the block as: unlocked, locked,
 *                         or locked down.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_read_block_status (FLASH_DEV *flash_dev, uint16_t blocknum, FLASH_FDATA *blockstat);

/**
 * This procedure is called to read the status for the specified block
 * from the flash device.
 * @param (OUT) mcode	- the manufacturer code.
 * @param (OUT) deviceid - the device id.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_read_device_ID (FLASH_DEV *flash_dev, uint32_t *mcode, uint32_t *deviceid);

/**
 * This procedure is called to read a single data item directly from the
 * specified device address.  This function is used internally by the
 * flash template api.  Clients that need to read data to the flash
 * device should use the flash_read_flash() command.
 * @param offset  - the flash address to be written to.
 * @return the flash data from the device.
 */
extern volatile FLASH_FDATA flash_readf (FLASH_DEV *flash_dev, uint32_t offset);

/**
 * This procedure is called to read one or more data items from
 * the flash device at the specified starting address.
 * @param address  - the starting device address.
 * @param (OUT) buffer - the buffer to contain the data items read.
 * @param numbytes - the number of data items to read.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_read_flash (FLASH_DEV *flash_dev, uint32_t address, void *buffer, uint32_t numbytes);

/**
 * This procedure is called to read the protection register value on
 * the flash device from the specified location.
 * @param location - the protection register location on the flash
 *                   device to be read from.
 * @param (OUT) value - the data item read from the register.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_read_protection (FLASH_DEV *flash_dev, uint32_t location, uint32_t *value);


/**
 * This procedure is called to read the status register value from
 * the flash device.
 * @return FLASH_FDATA - the status register value read from the device.
 */
uint32_t flash_read_status ( FLASH_DEV *flash_dev );

/**
 * This procedure is called to issue the resume command to the flash
 * device for the specified block.
 *    The block indicated was previously program suspended or erase
 *    suspended.
 * @param blocknum - the block number to resume.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_resume (FLASH_DEV *flash_dev);

/**
 * This function is used to write data to the Read Configuration
 * Register (RCR) on the device.  Use this function to set RCR
 * values such as read mode, latency count, wait polarity, data hold,
 * burst sequence, clock edge, and burst length.
 *    A valid configuration setting.
 * @param data - address of configuration data to be read in
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_set_configuration (FLASH_DEV *flash_dev, uint16_t data);

/**
 * This procedure is called to unlock the specified block on the flash
 * device.
 *    The block indicated was previously locked.
 * @param blocknum - the block number to unlock.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_unlock_block (FLASH_DEV *flash_dev, uint16_t blocknum);

/**
 * This procedure is called to unlock all blocks on the flash device.
 *    The blocks were previously locked.
 * @return FLASH_STATUS
 */
FLASH_STATUS flash_unlock_all_blocks (FLASH_DEV *flash_dev);

/**
 * This procedure is called to wait until the flash device status
 * indicates a ready state or times out.
 * @param timeout  - timeout value specified as number of times
 *                   to read the status register before giving up.
 * @return uint8_t - boolean flag indicating whether the ready state was
 *                 reached before the timeout number of reads
 *                 occured.
 */
uint8_t flash_wait_until_ready (FLASH_DEV *flash_dev, uint32_t timeout);

/**
 * This procedure is called to write a single data item directly to the
 * specified device address.  This function is used internally by the
 * flash template api.  Clients that need to write data to the flash
 * device should use the TMPL_ProgramFlash or TMPL_ProgramFlashBuffered
 * command.
 * @param offset  - the flash address to be written to.
 * @param value	- the flash data to write to the device.
 */
extern void flash_writef (FLASH_DEV *flash_dev, uint32_t offset, FLASH_FDATA value);

#endif  /* __FLASH_TEMPLATE_H */


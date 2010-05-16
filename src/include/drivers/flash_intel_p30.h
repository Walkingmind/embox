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
 * Module Name: Device
 *
 * File: Device.H - P30 device specific template C header
 *
 * File Revision: $Revision: 2 $, $JustDate:  1/20/03 $, $Author: Garotg $
 *
 * Purpose:
 *
 *    The purpose of this file is to establish P30 device specific
 *    constants used at compile time and runtime.  These constants
 *    include device layout parameters, command constants and
 *    function declaration flags.
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
#ifndef __DEVICE_H  /* ensure this file only gets included once */
#define __DEVICE_H

#include <types.h>
/*
 * P30 specific constants
 */

/* set 1 and only 1 PARAMETER to TRUE */
#if 0
#define P30_TOP                         FALSE
#define P30_BOTTOM                      TRUE
#endif


/* ERASE_TIMEOUT_CYCLES = # of times to check for status ready after erase
  commands are issued to the device */
#define FLASH_ERASE_TIMEOUT              50000000L

/* PROGRAM_TIMEOUT_CYCLES = # of times to check for status ready after
 program commands are issued to the device */
#define FLASH_PROGRAM_TIMEOUT            1000000L

#define FLASH_BLOCKSTAT_UNLOCKED         0x0
#define FLASH_BLOCKSTAT_LOCKED           0x1
#define FLASH_BLOCKSTAT_LOCKEDDOWN       0x3

#define FLASH_PROTECTION_LOCK_LOCATION   0x0

/* The device is divided into multiple 8-Mbit partitions. Each device contains
 one parameter partion and several main partitions.

 In top or bottom parameter partition, it contains four 16-KWord blocks
 and the rest are 64-KWord blocks.  Main partitions contain  blocks that
 are 64-Kword in size */

/******************** 256M *******************/
#define FLASH_TOTAL_NUMBLOCKS        0x103
#define FLASH_MAIN_BLOCK_NUMBYTES    0x20000         /* 64 K-Word block size */
#define FLASH_PARM_BLOCK_NUMBYTES    0x8000          /* 16 K-Word block size */

#define FLASH_TOP_PARTITION_BASE     0xFF0000        /* address */
#define FLASH_BOTTOM_PARTITION_BASE  0x0000          /* address */

#define FLASH_TOP_BLOCK_LOWER        0xFF
#define FLASH_TOP_BLOCK_UPPER        0x102

#define FLASH_BOTTOM_BLOCK_LOWER     0x0
#define FLASH_BOTTOM_BLOCK_UPPER     0x3

#define FLASH_TOTAL_SIZE            0x4000000
#define FLASH_BLOCK_MASK            0xFFFF

#define FLASH_OTP_NUMWORDS           0x90
#define FLASH_OTP_BASE               0x200           /* address */
#define FLASH_OTP_BASE2              0x224           /* address */
#define FLASH_OTP_PROGRAM            0x00C000C0
#define FLASH_OTP_READ               0x00900090
#define FLASH_OTP_LOCK               0xFFFDFFFD

/*  OTP Extended PR[1-16] bit settings */
#define FLASH_OTP_LOCK_PR1           0xFFFEFFFE
#define FLASH_OTP_LOCK_PR2           0xFFFDFFFD
#define FLASH_OTP_LOCK_PR3           0xFFFBFFFB
#define FLASH_OTP_LOCK_PR4           0xFFF7FFF7
#define FLASH_OTP_LOCK_PR5           0xFFEFFFEF
#define FLASH_OTP_LOCK_PR6           0xFFDFFFDF
#define FLASH_OTP_LOCK_PR7           0xFFBFFFBF
#define FLASH_OTP_LOCK_PR8           0xFF7FFF7F
#define FLASH_OTP_LOCK_PR9           0xFEFFFEFF
#define FLASH_OTP_LOCK_PR10          0xFDFFFDFF
#define FLASH_OTP_LOCK_PR11          0xFBFFFBFF
#define FLASH_OTP_LOCK_PR12          0xF7FFF7FF
#define FLASH_OTP_LOCK_PR13          0xEFFFEFFF
#define FLASH_OTP_LOCK_PR14          0xDFFFDFFF
#define FLASH_OTP_LOCK_PR15          0xBFFFBFFF
#define FLASH_OTP_LOCK_PR16          0x7FFF7FFF

#define FLASH_LOCKDOWN_BIT_SET       0x002D002F
#define FLASH_LOCK_BIT_SET           0x00010001      /* 2nd cycle lock bit command */
#define FLASH_LOCK_BIT_CLEAR         0x00D000D0      /* 2nd cycle lock bit command */
#define FLASH_BLOCK_SUSPEND          0x00B000B0
#define FLASH_BLOCK_RESUME           0x00D000D0

/********************************************************************
    PRODUCT SPECIFIC DATA DEFINES
********************************************************************/

#define FLASH_BUFFER_SIZE            0x40            /* words */
#define FLASH_WRITE_TO_BUFFER        0x00E800E8
#define FLASH_SET_READ_CONFIG        0x00030003

/* defined for all data widths. added to flash base address. contains A16..A1 */
#define FLASH_STD_READ_MODE              0x7FCF
#define FLASH_PAGE_READ_MODE             0xBFCF

/*
 * device specific typedefs
 */

/* extended query structure */
typedef struct _FLASH_EXTQUERY {
	char    ExtQueryStr[4];        /* 3 bytes + null */
	uint8_t MajorVersionNum;       /* 1 byte */
	uint8_t MinorVersionNum;       /* 1 bytes */
	uint32_t OptionalFeature;       /* 4 bytes */
	uint8_t  AfterSuspendFunctions; /* 1 byte */
	uint16_t BlockLockStatus;       /* 2 bytes */
	uint8_t  VccOptimum;            /* 1 byte */
	uint8_t  VppOptimum;            /* 1 byte */
} FLASH_EXTQUERY;

#endif /* __DEVICE_H */

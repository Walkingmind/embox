/**
 * @file
 * @brief
 *
 * @date 20.08.2013
 * @author Andrey Gazukin
 */

#ifndef FLASH_H_
#define FLASH_H_

#include <embox/block_dev.h>
#include <stddef.h>

/* ======== 0x600 FLASH ===============================
 * Get/Set configuration 'key' values for FLASH drivers
 */
#define GET_CONFIG_FLASH_ERASE            0x600
#define GET_CONFIG_FLASH_QUERY            0x601
#define GET_CONFIG_FLASH_LOCK             0x602
#define GET_CONFIG_FLASH_UNLOCK           0x603
#define GET_CONFIG_FLASH_VERIFY           0x604
#define GET_CONFIG_FLASH_DEVSIZE          0x605
#define GET_CONFIG_FLASH_BLOCKSIZE        0x606
#define GET_CONFIG_FLASH_DEVADDR          0x607

#define SET_CONFIG_FLASH_FIS_NAME         0x680

typedef struct {
	uint32_t offset;
    size_t len;
    int flasherr;
    uint32_t err_address;
} flash_getconfig_erase_t;

typedef struct {
    size_t dev_size;
} flash_getconfig_devsize_t;

typedef struct {
	uint32_t dev_addr;
} flash_getconfig_devaddr_t;

typedef struct {
    size_t block_size;
} flash_getconfig_blocksize_t;


typedef struct flash_block_info
{
	size_t           block_size;
	uint32_t         blocks;
} flash_block_info_t;

// Information about what one device driver drives
typedef struct {
	uint32_t     start;              /* First address */
	uint32_t     end;                /* Last address */
	uint32_t     num_block_infos;    /* Number of entries */
	const flash_block_info_t* block_info;         /* Info about block sizes */
} flash_info_t;

#endif /* FLASH_H_ */

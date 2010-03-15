/**
 * @file
 *
 * @date 29.06.2009
 * @author Anton Bondarev
 */
#ifndef FS_ROMFS_H_
#define FS_ROMFS_H_

#include <fs/rootfs.h>

//#define FLASH_SYS_FDESC_SIZE 0x20
#define FLASH_WRITE_ENABLE      *((volatile uint32_t*)0x80000000) |= (1<<11)
#define FLASH_WRITE_DISABLE     *((volatile uint32_t*)0x80000000) &= ~(1<<11)

typedef struct _ROMFS_CREATE_PARAM {
	unsigned int size;
	char name[CONFIG_MAX_LENGTH_FILE_NAME];
	unsigned int mode;
} ROMFS_CREATE_PARAM;

extern FSOP_DESCRIPTION romfsop;

//typedef enum _FS_TYPE
//{
//	FL_IN_RAM = 0,
//	FL_IN_ROM = 1,
//	FL_IN_FLASH = 2
//}FS_TYPE;

/*typedef struct _FILE_DESC
{
	uint8_t id;//may be free
	uint32_t size;//busy size
	uint8_t check_type;
	uint32_t check_sum;
	uint8_t name[22];//write in flash 32 bytes FLASH_SYS_FDESC_SIZE


	uint32_t offset;

	bool is_lock;//
	uint8_t mode;//'r' or 'w'
	uint8_t location;//in ram in fash in rom
}FILE_DESC;
*/

#endif /* FS_ROMFS_H_ */

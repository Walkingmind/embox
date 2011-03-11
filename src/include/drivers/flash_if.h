/**
 * @file
 *
 * @date 13.10.2009
 * @author Alexander Batyukov
 */
#ifndef FLASH_IF_H_
#define FLASH_IF_H_

#include <types.h>
#include <embox/kernel.h>


/* status return values */
enum FLASH_COMMAND_STAT {
	StatCompleted,  /* the function completed */
	StatTimeout,    /* access to the device timed out */
	StatBadBlock,   /* block # not valid for this device */
	StatBadAddress, /* address not valid for this device */
	StatBadOtp,     /* otp loc not valid for this device */
	StatUnsupported /* this function is not supported */
};

/* status structure */
typedef struct _FLASH_STATUS {
	enum FLASH_COMMAND_STAT Result;  /* subroutine status */
	volatile uint32_t   SR;      /* Flash status register value */
}FLASH_STATUS;


typedef struct _FLASH_QUERY_DATA {
	char   QueryStr[4];             /* 3 bytes + null */
	uint16_t VendorId;              /* 2 bytes */
	uint16_t ExtTablePtr;           /* 2 bytes */
	uint16_t AltVendorId;           /* 2 bytes */
	uint16_t SecExtTablePtr;        /* 2 bytes */
	uint8_t  VccMin;                /* 1 byte */
	uint8_t  VccMax;                /* 1 byte */
	uint8_t  VppMin;                /* 1 byte */
	uint8_t  VppMax;                /* 1 byte */
	uint8_t  TypicalProgTimeout;    /* 1 byte */
	uint8_t  TypicalBufferTimeout;  /* 1 byte */
	uint8_t  BlockEraseTimeout;     /* 1 byte */
	uint8_t  ChipEraseTimeout;      /* 1 byte */
	uint8_t  MaxSingleTimeout;      /* 1 byte */
	uint8_t  MaxBufferTimeout;      /* 1 byte */
	uint8_t  MaxBlockEraseTimeout;  /* 1 byte */
	uint8_t  MaxChipEraseTimeout;   /* 1 byte */
	uint8_t  DeviceSize;            /* 1 byte */
	uint16_t DeviceInterface;       /* 2 bytes */
	uint16_t MaxWriteBufferBytes;   /* 2 bytes */
	uint8_t  NumEraseBlocks;        /* 1 byte */
	uint32_t EraseBlock1Information; /* 4 bytes */
	uint32_t EraseBlock2Information;
}FLASH_QUERY_DATA;


struct _FLASH_DEV;

typedef	void (*FLASH_CLEAR_STATUS) (struct _FLASH_DEV *flash_dev);

typedef FLASH_STATUS (*FLASH_ERASE_ALL_BLOCKS) (struct _FLASH_DEV *flash_dev);

typedef FLASH_STATUS (*FLASH_ERASE_BLOCK) (struct _FLASH_DEV *flash_dev, uint16_t blocknum);

typedef FLASH_STATUS (*FLASH_GET_BLOCK_OFFSET) (struct _FLASH_DEV *flash_dev, uint32_t blocknum, uint32_t *address);

typedef FLASH_STATUS (*FLASH_LOCK_BLOCK) (struct _FLASH_DEV *flash_dev, uint16_t blocknum);

typedef FLASH_STATUS (*FLASH_LOCK_ALL_BLOCKS) (struct _FLASH_DEV *flash_dev);

typedef FLASH_STATUS (*FLASH_LOCK_BLOCK_DOWN) (struct _FLASH_DEV *flash_dev, uint16_t blocknum);

typedef FLASH_STATUS (*FLASH_LOCK_PROTECTION) (struct _FLASH_DEV *flash_dev, uint32_t ProtectionRegister);

typedef FLASH_STATUS (*FLASH_PAGE_MODE) (struct _FLASH_DEV *flash_dev, uint16_t enable);

typedef FLASH_STATUS (*FLASH_PROGRAM_FLASH) (struct _FLASH_DEV *flash_dev, uint32_t address, uint32_t item);

typedef FLASH_STATUS (*FLASH_PROGRAM_FLASH_BUFFERED) (struct _FLASH_DEV *flash_dev, uint32_t address, uint32_t *buffer, uint32_t numbytes);

typedef FLASH_STATUS (*FLASH_PROGRAM_PROTECTION) (struct _FLASH_DEV *flash_dev, uint32_t location, uint32_t value);

typedef FLASH_STATUS (*FLASH_QUERY) (struct _FLASH_DEV *flash_dev, struct _FLASH_QUERY_DATA *query);

typedef FLASH_STATUS (*FLASH_READ_BLOCK_STATUS) (struct _FLASH_DEV *flash_dev, uint16_t blocknum, uint32_t *blockstat);

typedef FLASH_STATUS (*FLASH_READ_DEVICE_ID) (struct _FLASH_DEV *flash_dev, uint32_t *mcode, uint32_t *deviceid);

typedef FLASH_STATUS (*FLASH_READ_FLASH) (struct _FLASH_DEV *flash_dev, uint32_t address, void *buffer, uint32_t numbytes);

typedef FLASH_STATUS (*FLASH_READ_PROTECTION) (struct _FLASH_DEV *flash_dev, uint32_t location, uint32_t *value);

typedef uint32_t (*FLASH_READ_STATUS) (struct _FLASH_DEV *flash_dev);

typedef FLASH_STATUS (*FLASH_RESUME) (struct _FLASH_DEV *flash_dev);

typedef FLASH_STATUS (*FLASH_SET_CONFIGURATION) (struct _FLASH_DEV *flash_dev, uint16_t data);

typedef FLASH_STATUS (*FLASH_UNLOCK_BLOCK) (struct _FLASH_DEV *flash_dev, uint16_t blocknum);

typedef FLASH_STATUS (*FLASH_UNLOCK_ALL_BLOCKS) (struct _FLASH_DEV *flash_dev);

typedef uint8_t (*FLASH_WAIT_UNTIL_READY) (struct _FLASH_DEV *flash_dev, uint32_t timeout);


typedef struct _FLASH_DEV{
	int manuf;
	int dev;
	int start_address;
	int total_numblocks;
	int total_size;
	int buffer_size;
	int param_block_nums[4];
	int number;
	int is_top;
	int param_block_size;
	int main_block_size;
	FLASH_ERASE_ALL_BLOCKS          erase_all_blocks;
	FLASH_ERASE_BLOCK               erase_block;
	FLASH_GET_BLOCK_OFFSET          get_block_offset;
	FLASH_LOCK_BLOCK                lock_block;
	FLASH_LOCK_ALL_BLOCKS           lock_all_blocks;
	FLASH_LOCK_BLOCK_DOWN           lock_block_down;
	FLASH_PROGRAM_FLASH             program_flash;
	FLASH_PROGRAM_FLASH_BUFFERED    program_flash_buffered;
	FLASH_QUERY                     query;
	FLASH_READ_BLOCK_STATUS         read_block_status;
	FLASH_READ_DEVICE_ID            read_device_id;
	FLASH_READ_FLASH                read_flash;
	FLASH_READ_STATUS               read_status;
	FLASH_UNLOCK_BLOCK              unlock_block;
	FLASH_UNLOCK_ALL_BLOCKS         unlock_all_blocks;
}FLASH_DEV;


#define MAX_FLASH_DEVS 2

extern FLASH_DEV flash_devices_table[MAX_FLASH_DEVS];

int flash_if_read_id(uint32_t address, uint32_t *mcode, uint32_t *device_id);
int flash_if_get_block_size(FLASH_DEV *flash_dev, uint32_t blocknum);

#define ERASE_ALL_BLOCKS(flash_dev) \
			flash_dev.erase_all_blocks(&flash_dev)

#define ERASE_BLOCK(flash_dev, block_num) \
			flash_dev.erase_block(&flash_dev, block_num)

#define GET_BLOCK_OFFSET(flash_dev, block_num, address) \
			flash_dev.get_block_offset(&flash_dev, block_num, address)

#define LOCK_BLOCK(flash_dev, block_num) \
			flash_dev.lock_block(&flash_dev, block_num)

#define LOCK_ALL_BLOCKS(flash_dev) \
			flash_dev.lock_all_blocks(&flash_dev)

#define LOCK_BLOCK_DOWN(flash_dev, block_num) \
			flash_dev.lock_block_down(&flash_dev, block_num)

#define PROGRAM_FLASH(flash_dev, address, item) \
			flash_dev.program_flash(&flash_dev, address, item)

#define PROGRAM_FLASH_BUFFERED(flash_dev, address, buffer, numbytes) \
			flash_dev.program_flash_buffered(&flash_dev, address, \
													buffer, nymbytes)

#define QUERY(flash_dev, query) \
			flash_dev.query(&flash_dev, query)

#define READ_BLOCK_STATUS(flash_dev, block_num, block_stat) \
			flash_dev.read_block_status(&flash_dev, block_num, block_stat)

#define READ_DEVICE_ID(flash_dev, mcode, deviceid) \
			flash_dev.read_device_id(&flash_dev, mcode, deviceid)

#define READ_FLASH(flash_dev, address, buffer, numbytes) \
			flash_dev.read_flash(&flash_dev, address, buffer, numbytes)

#define READ_STATUS(flash_dev) flash_dev.read_status(&flash_dev)

#define UNLOCK_BLOCK(flash_dev, block_num) \
			flash_dev.unlock_block(&flash_dev, block_num)

#define UNLOCK_ALL_BLOCKS(flash_dev) \
			flash_dev.unlock_all_blocks(&flash_dev)

/** memory controller base */
#define MEM_CTRLR_BASE  0x80000000

#define FLASH_WRITE_ENABLE	*((volatile uint32_t*) MEM_CTRLR_BASE) |= (1<<11)
#define FLASH_WRITE_DISABLE	*((volatile uint32_t*) MEM_CTRLR_BASE) &= ~(1<<11)

int flash_if_write(FLASH_DEV *flash_dev, uint32_t addr, void *buff, uint32_t size);

#endif /* FLASH_IF_H_ */

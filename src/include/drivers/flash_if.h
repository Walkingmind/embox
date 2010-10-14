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

typedef void (*FLASH_CLEAR_STATUS) (struct _FLASH_DEV *flash_dev);
typedef FLASH_STATUS (*FLASH_ERASE_ALL_BLOCKS) (struct _FLASH_DEV *flash_dev,uint8_t returnSR);
typedef FLASH_STATUS (*FLASH_ERASE_BLOCK) (struct _FLASH_DEV *flash_dev,uint16_t blocknum, uint8_t returnSR);
typedef FLASH_STATUS (*FLASH_GET_BLOCK_ADDRESS) (struct _FLASH_DEV *flash_dev,uint32_t blocknum, uint32_t *address);
typedef FLASH_STATUS (*FLASH_LOCK_BLOCK) (struct _FLASH_DEV *flash_dev,uint16_t blocknum, uint8_t  returnSR);
typedef FLASH_STATUS (*FLASH_LOCK_ALL_BLOCKS) (struct _FLASH_DEV *flash_dev,uint8_t  returnSR);
typedef FLASH_STATUS (*FLASH_LOCK_BLOCK_DOWN) (struct _FLASH_DEV *flash_dev,uint16_t blocknum, uint8_t  returnSR);
typedef FLASH_STATUS (*FLASH_LOCK_PROTECTION) (struct _FLASH_DEV *flash_dev,uint32_t ProtectionRegister, uint8_t returnSR);
typedef FLASH_STATUS (*FLASH_PAGE_MODE) (struct _FLASH_DEV *flash_dev,uint16_t enable);
typedef FLASH_STATUS (*FLASH_PROGRAM_FLASH) (struct _FLASH_DEV *flash_dev,uint32_t address, uint32_t item, uint8_t  returnSR);
typedef FLASH_STATUS (*FLASH_PROGRAM_FLASH_BUFFERED) (struct _FLASH_DEV *flash_dev,uint32_t address, uint32_t *buffer, uint32_t numbytes, uint8_t returnSR);
typedef FLASH_STATUS (*FLASH_PROGRAM_PROTECTION) (struct _FLASH_DEV *flash_dev,uint32_t location, uint32_t value, uint8_t returnSR);
typedef FLASH_STATUS (*FLASH_QUERY) (struct _FLASH_DEV *flash_dev,struct _FLASH_QUERY_DATA *query);
typedef FLASH_STATUS (*FLASH_READ_BLOCK_STATUS) (struct _FLASH_DEV *flash_dev,uint16_t blocknum, uint32_t *blockstat);
typedef FLASH_STATUS (*FLASH_READ_DEVICE_ID) (struct _FLASH_DEV *flash_dev,uint32_t *mcode, uint32_t *deviceid);
typedef FLASH_STATUS (*FLASH_READ_FLASH) (struct _FLASH_DEV *flash_dev,uint32_t address, void *buffer, uint32_t numbytes, uint8_t  returnSR);
typedef FLASH_STATUS (*FLASH_READ_PROTECTION) (struct _FLASH_DEV *flash_dev,uint32_t location, uint32_t *value);
typedef uint32_t (*FLASH_READ_STATUS) (struct _FLASH_DEV *flash_dev);
typedef FLASH_STATUS (*FLASH_RESUME) (struct _FLASH_DEV *flash_dev, uint8_t  returnSR);
typedef FLASH_STATUS (*FLASH_SET_CONFIGURATION) (struct _FLASH_DEV *flash_dev, uint16_t data);
typedef FLASH_STATUS (*FLASH_UNLOCK_BLOCK) (struct _FLASH_DEV *flash_dev, uint16_t blocknum, uint8_t  returnS);
typedef FLASH_STATUS (*FLASH_UNLOCK_ALL_BLOCKS) (struct _FLASH_DEV *flash_dev, uint8_t  returnSR);
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
	FLASH_ERASE_ALL_BLOCKS          flash_if_erase_all_blocks;
	FLASH_ERASE_BLOCK               flash_if_erase_block;
	FLASH_GET_BLOCK_ADDRESS         flash_if_get_block_address;
	FLASH_LOCK_BLOCK                flash_if_lock_block;
	FLASH_LOCK_ALL_BLOCKS           flash_if_lock_all_blocks;
	FLASH_LOCK_BLOCK_DOWN           flash_if_lock_block_down;
	FLASH_PROGRAM_FLASH             flash_if_program_flash;
	FLASH_PROGRAM_FLASH_BUFFERED    flash_if_program_flash_buffered;
	FLASH_QUERY                     flash_if_query;
	FLASH_READ_BLOCK_STATUS         flash_if_read_block_status;
	FLASH_READ_DEVICE_ID            flash_if_read_device_id;
	FLASH_READ_FLASH                flash_if_read_flash;
	FLASH_READ_STATUS               flash_if_read_status;
	FLASH_UNLOCK_BLOCK              flash_if_unlock_block;
	FLASH_UNLOCK_ALL_BLOCKS         flash_if_unlock_all_blocks;
}FLASH_DEV;

#define MAX_FLASH_DEVS 2
extern FLASH_DEV flash_devices_table[MAX_FLASH_DEVS];

int flash_if_init(void);
int flash_if_device_init(uint32_t address, int num);

#endif /* FLASH_IF_H_ */

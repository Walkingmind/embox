/**
 * @file
 *
 * @date Feb 14, 2013
 * @author: Anton Bondarev
 */

#ifndef I8042_H_
#define I8042_H_


#define  I8042_CMD_PORT        0x64
#define  I8042_STS_PORT        0x64
#define  I8042_DATA_PORT       0x60

#define  I8042_CMD_READ_MODE   0x20
#define  I8042_CMD_WRITE_MODE  0x60
#define  I8042_CMD_PORT_DIS    0xAD
#define  I8042_CMD_PORT_EN     0xAE

#define  I8042_MODE_XLATE      0x40
#define  I8042_MODE_DISABLE    0x10


/* Status */
#define I8042_STS_PERR      0x80    /* Parity error */
#define I8042_STS_TMO       0x40    /* Timeout */
#define I8042_STS_AUXOBF    0x20    /* Mouse OBF */
#define I8042_STS_INH       0x10    /* 0: inhibit  1: no-inhibit */
#define I8042_STS_SYS       0x04    /* 0: power up  1:Init comp */
#define I8042_STS_IBF       0x02    /* Input (to kbd) buffer full */
#define I8042_STS_OBF       0x01    /* Output (from kbd) buffer full */


#endif /* I8042_H_ */

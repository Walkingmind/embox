/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    19.07.2013
 */

#ifndef ZRV_CMD_SMAC_TEST_H_
#define ZRV_CMD_SMAC_TEST_H_

#define NFILES 4
#define NUSERS 4

struct test_res {
	int tr_ecode[NFILES * NUSERS];
	int tr_pos;
};


extern struct test_res __zrv_smac_read;
extern struct test_res __zrv_smac_write;

#endif /* ZRV_CMD_SMAC_TEST_H_ */


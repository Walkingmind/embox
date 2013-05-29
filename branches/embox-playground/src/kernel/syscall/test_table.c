#include <stddef.h>

int sys_1(int arg1){
	return arg1;
}

void *const SYSCALL_TABLE[2] = {
		NULL, sys_1
};

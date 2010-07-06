/**
 * @file
 *
 * @date 01.07.10
 * @author Nikolay Korotky
 */

#include "linux/kernel.h"

/* mark as section .img.main.text, to be referenced in linker script */
int __attribute__ ((__section__ (".img.main.text"))) __main(void) {
    void (*kernel)();

    /* call kernel */
    kernel = (void (*)()) CONFIG_KERNEL_BASE_ADDR;
    kernel();
    return 0;
}


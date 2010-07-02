/**
 * @file
 *
 * @date 01.07.10
 * @author Nikolay Korotky
 */

#include "linux/kernel.h"

#if 0
/*                                                                                                                                                                                  
 * Legacy format image header,                                                                                                                                                      
 * all data in network byte order (aka natural aka bigendian).                                                                                                                      
 */                                                                                                                                                                                 
typedef struct image_header {                                                                                                                                                       
        uint32_t        ih_magic;       /* Image Header Magic Number    */                                                                                                          
        uint32_t        ih_hcrc;        /* Image Header CRC Checksum    */                                                                                                          
        uint32_t        ih_time;        /* Image Creation Timestamp     */                                                                                                          
        uint32_t        ih_size;        /* Image Data Size              */                                                                                                          
        uint32_t        ih_load;        /* Data  Load  Address          */                                                                                                          
        uint32_t        ih_ep;          /* Entry Point Address          */                                                                                                          
        uint32_t        ih_dcrc;        /* Image Data CRC Checksum      */                                                                                                          
        uint8_t         ih_os;          /* Operating System             */                                                                                                          
        uint8_t         ih_arch;        /* CPU architecture             */                                                                                                          
        uint8_t         ih_type;        /* Image Type                   */                                                                                                          
        uint8_t         ih_comp;        /* Compression Type             */                                                                                                          
        uint8_t         ih_name[128];      /* Image Name           */                                                                                                          
} image_header_t;
#endif

/* mark as section .img.main.text, to be referenced in linker script */
int __attribute__ ((__section__ (".img.main.text"))) __main(void) {
    void (*kernel)();

    /* call kernel */
    kernel = (void (*)()) CONFIG_KERNEL_BASE_ADDR;
    kernel();
    return 0;
}


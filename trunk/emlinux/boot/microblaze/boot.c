/**
 * @file
 *
 * @date 01.07.10
 * @author Nikolay Korotky
 */

#include <stdio.h>

#define CONFIG_LOAD_ADDR 0x40000000

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

/* STUB */
int main(int argc, char **argv) {
    //unsigned long load_addr = CONFIG_SYS_LOAD_ADDR;
    //static bootm_headers_t images;
    //bootm_start
    //memset ((void *)&images, 0, sizeof (images));
    //bootm_load_os
    //   memmove from flash to memory
    //do_bootm_linux
    //void    (*theKernel) (char *, unsigned long, char*);
    //theKernel = (void (*)(char *, ulong, char*))images->ep;
    //theKernel(commandline, images->rd_start, of_flat_tree);
    return 0;
}


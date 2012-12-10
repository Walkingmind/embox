
#/* memory region*/
lds_region('sdram', '0x20000000', '8K')
lds_region('flash', '0x8000000', '128K')

#/*section placement*/
lds_section('text', 'flash')
lds_section('rodata', 'flash')
lds_section_load('data', 'sdram', 'flash')
lds_section('bss', 'sdram')
lds_section('stack', 'sdram')



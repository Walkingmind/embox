
#/* memory region*/
lds_region('sdram', '0x00100000', '64M')
lds_region('flash', '0x0', '0M')

#/*section placement*/
lds_section('text', 'sdram')
lds_section('rodata', 'sdram')
lds_section('data', 'sdram')
lds_section('bss', 'sdram')
lds_section('stack', 'sdram')

lds_section('heap', 'sdram')


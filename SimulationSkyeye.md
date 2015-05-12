## SKYEYE ##

Targeted to ARM simulation (and maybe LEON2). Used for Atmel AT91 simulation as
that installed in Lego NXT brick. Have UART support.

Install Skyeye:

> [skyeye-1.3.0rc1](http://sourceforge.net/projects/skyeye/files/skyeye/skyeye-1.3.0_rc1.tar.gz/download)

> [skyeye-1.2.6rc1](http://sourceforge.net/projects/skyeye/files/skyeye/skyeye-1.2.6_rc1/skyeye-1.2.6_rc1.tar.bz2/download) (recommended)

  1. Using skyeye.conf
```
arch:arm
cpu: arm7tdmi

mach: at91

mem_bank: map=M, type=RW,  addr=0x00000000,  size=0x10000000
mem_bank: map=I, type=RW,  addr=0xf0000000,  size=0x10000000
uart:mod=term
```
  1. Start simulator
```
skyeye -d -c [path-to-embox]/third-party/conf/skyeye.conf
```
  1. Load Embox into skyeye
```
arm-elf-gdb [path-to-embox-elf]
    (gdb) tar extended-remote :12345
    (gdb) load
```
  1. Now we can debug, e.g. just run
```
    (gdb) c
```
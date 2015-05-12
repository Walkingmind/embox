&lt;wiki:gadget url="http://embox.googlecode.com/svn/wiki/gadgets/userbox-under-construction.xml" width="640" height="100" border="0"/&gt;



# Introduction #
Embox is a multi-platform operationg system, it means this project was ported to several types of processor’s architecture including some open platform: [SPARC](http://ru.wikipedia.org/wiki/SPARC), [micriblaze](http://ru.wikipedia.org/wiki/MicroBlaze), and so on. These architectures often are used in [System-on-chip (SOC)](http://en.wikipedia.org/wiki/System-on-a-chip). You can learn more details about supported architecture on [the project description page](ProjectDescription.md) in the section **supported architectures**.

Most of project’s code was written in C languages and independent on cpu’s platform. There are some architecture specific code it places in folder named **arch**. This folder contains HAL interface implementation, constant and macroses for the architecture, base linker script for this architecture.

This page contains minimal requirements for execution code on a new architecture.

# List of architecture dependent part #
  * [Headers](#Headers.md)
  * [Boot code](#Boot_code.md)
  * [Linker scripts](#Linker_scripts.md)

First of all [Default IO](#Default_IO.md)
Then:
  * [Interrupt handlers](#Interrupt_handlers.md)
  * [System timer](#System_timer.md)
  * [Traps handlers](#Trap_handlers.md)

## Headers ##

### asm/types.h ###

### asm/hal**###**

#### clock.h ####

#### interrupt.h ####

#### arch.h ####

#### reg.h ####

#### ipl.h ####

## Boot code ##
## Linker scripts ##
## Default IO ##
## Interrupt handlers ##
## System timer ##
## Trap handlers ##
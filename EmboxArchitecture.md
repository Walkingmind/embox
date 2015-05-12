**Embox** has base level and module architecture. We can imaging level structure as follow:

![http://embox.googlecode.com/svn/wiki/images/EmboxArchitecture/arch.png](http://embox.googlecode.com/svn/wiki/images/EmboxArchitecture/arch.png)

The lowest level as a hardware abstraction layer ([HAL](Hal.md)). The next is [kernel](Kernel.md) level, usually It supports resources allocation and internal communication. The next is driver and [services](Services.md) level, And the highest is [applications](Applications.md) level. Each level consist of several modules. We can also say that level is compound module.

# [HAL](Hal.md) #
[this intesface](Hal.md) supports following platform specific operations and utilities as virtual memory primitives, atomic operations
clock sources and etc.
It is this interface implementation that need to porting Embox to a new architecture.

# [Kernel](Kernel.md) #
[Kernel](Kernel.md) provides time scheduling, protection address space, IPC and so on.

# [Drivers](Drivers.md) #
[Drivers](Drivers.md) provide unify program interface to hardware devices and program pseudo-devices. In this point of view this interface is simular as [HAL](Hal.md) but HAL supports internal CPU features instead of drivers do external device.

# [Services](Services.md) #
Service (library) -- is a module which provides services for different parts of the system and user applications through determined interface (API)

# [Application](Applications.md) #
Application
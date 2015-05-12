**[QEMU](http://www.qemu.org)** is an open source machine emulator and virtualizer. QEMU supports all CPU architectures that are supported by Embox, and it is the main simulator that we use for the development.



# Installation #
## Linux ##
If you use Linux then QEMU can be installed from your package manager, for example, on Debian-based systems:
```
sudo apt-get install qemu
```
Usually this package includes only x86/x86\_64 virtualizer, so in order to run Embox compiled for CPUs other that x86, you also have to install **qemu-system** or **qemu-kvm-extras** package.

## Windows ##
Here are few starting points to get QEMU working on Windows:
  * Using Qemu Manager, see a [step-by-step guide](SimulationQemuWindows.md).
  * Using unofficial QEMU binaries found on [Links](http://wiki.qemu.org/Links) page of the QEMU wiki.
  * Building (and cross-building) it from source codes as described below.

## Building from the source code ##
Building QEMU is quite common and it is well described for both [Linux](http://wiki.qemu.org/Hosts/Linux) and [Windows](http://wiki.qemu.org/Hosts/W32) hosts. _For linux you need libglib2.0-dev package._

The only thing to note is **`–-target-list`** configuration option. As the name suggests it controls emulation targets which we would like to support. By default, it is configured to enable all architectures supported by the QEMU, thus making a build time quite long.

# Running #
All QEMU binaries are called **`qemu-system-`_`arch`_** where _`arch`_ denotes the CPU architecture being emulated. In examples below we will use **`qemu-system-i386`** - an emulator for x86 family CPUs.

## Specifying the kernel ##
To run an image under the QEMU use **`-kernel`** option:
```
qemu-system-i386 -kernel path/to/embox
```

## Debugging ##
To enable the debugging through gdbserver you can use **`-gdb`** option. However it is more common to use **`-s`** option which is a shorthand for **`-gdb tcp::1234`**:
```
# Running gdbserver on localhost:1234
qemu-system-i386 -s ...
```
Another useful option is **`-S`**, which suspends execution at startup. Often used in conjunction with `-s`:
```
# Suspend execution and wait for gdb connection
qemu-system-i386 -s -S ...
```

# Keyboard shortcuts #
During the emulation the following keys are used to control the QEMU.
<table width='839' cellspacing='10'><tr valign='top'><td width='50%'>
<h2>Graphical mode</h2>
This is the default mode which uses a VGA console for the output.<br>
<table><thead><th> <b>Keys</b> </th><th> <b>Action</b> </th></thead><tbody>
<tr><td> <code>Ctrl+Alt</code> </td><td> Toggle mouse and keyboard grab </td></tr>
<tr><td> <code>Ctrl+Alt+1</code> </td><td> Switch to the VGA console (default) </td></tr>
<tr><td> <code>Ctrl+Alt+2</code> </td><td> Switch to the QEMU monitor </td></tr></tbody></table>

</td><td>
<h2>Non-graphical mode</h2>
This mode is enabled by passing the <b><code>-nographic</code></b> option.<br>
<table><thead><th> <b>Keys</b> </th><th> <b>Action</b> </th></thead><tbody>
<tr><td> <code>Ctrl+A H</code> </td><td> Print some help </td></tr>
<tr><td> <code>Ctrl+A X</code> </td><td> Stop and exit </td></tr>
<tr><td> <code>Ctrl+A C</code> </td><td> Switch between console and monitor </td></tr>
</td></tr></table>
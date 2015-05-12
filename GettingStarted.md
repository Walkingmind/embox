This page describes a simple way to build and run Embox.

Required environment:
  * gcc and make
  * cross compiler for taget platform

# Preparing environment #
<table cellspacing='10'><tr valign='top'><td width='50%'>
<h2>Windows(R) (Cygwin)</h2>
Install <a href='http://cygwin.com/'>cygwin</a>. During installation choose make and gcc packages.<br>
More details <a href='InstallToolchainWindowsCygwin.md'>here</a>.<br>
</td><td>
<h2>Linux</h2>
Usually essential environment is installed out of box in case of Linux. If it isn’t, you can do it yourself. For Debian-based systems:<br>
<pre><code>$ sudo apt-get install build-essential<br>
</code></pre>
</td></tr></table>
# Building Embox #
Since Embox is highly configurable project, it is necessary to specify modules to be built and params for them. To build project make command is used.
All command described below are called from the root directory of the project which includes (conf/, src/, ...)
```
$ cd embox
```

## Configuring Embox ##
For configuring it is needed to specify params and modules supposed to be included in the system. Embox has several prepared templates, to see the list of them use the following command:
```
$ make confload
```
<table width='839' cellspacing='10'><tr valign='top'><td width='50%'>
The simplest way to load a template is to specify its name in command:<br>
<pre><code>make confload-&lt;template&gt;<br>
</code></pre>
</td><td>

For the quick overview you can use qemu template, that exists for each architecture. For x86 it is <b><code>x86/qemu</code></b>:<br>
<pre><code>make confload-x86/qemu<br>
</code></pre>
</td></tr></table>

Project configurations for different target platform you can find
[here](PlatformsDescription.md).

## Building image ##
After configuring the project it is enough just to run make script:
```
$ make
```

## Launch on QEMU ##
The built image can be run on QEMU. The simplest way is to execute ./scripts/qemu/auto\_qemu script:
```
$ sudo ./scripts/qemu/auto_qemu
```
In this script tuntab is created, so it requires superuser rights. Despite that, script uses ethtool util, that can be installed on Debian-based system as follows:
```
$ sudo apt-get install ethtool
```
If the launch succeeds, messages are output on QEMU screen. After the system is loaded, you’ll see the prompt
"embox>", now you are able to run commans.
For example, "help" lists all existing commands.

For testing the connection ping 10.0.2.16. If the connection is established you can connect to the Embox terminal via telnet.

To quit from Qemu type **ctrl + 'a'** and **'X'** after that.

## Debugging ##
For debugging you can use the same script with **-s -S -no-kvm** flags:
```
$ sudo ./scripts/qemu/auto_qemu -s -S -no-kvm
```
After that QEMU is waitig for connection by a gdb-client.

For debugging via console debugger run gdb in the other terminal:
```
$ gdb ./build/base/bin/embox
...
(gdb) target extended-remote :1234
(gdb) continue
```
Now system starts loading.

At any moment in gdb terminal you can type **ctrl + 'c'** and see the stack of the current thread (`backtrace`) and set breakpoints (`break <function name>`, `break <file name>:<line number>`).

You can connect to QEMU via Eclipse, details [here](InstallToolchainEclipseRemoteDebug.md).

## Building on other architectures ##
Embox supports the following processor architectures: x86, ARM, Microblaze, SPARC, PPC, MIPS.

In order to work with architectures differed from x86 you need a [cross compiler](InstallToolchainCrossCompiler.md).
After installing cross compiler just repeat step by step all points starting with configuring:
```
make confload-<arch>/qemu
make
sudo ./scripts/qemu/auto_qemu
```
Output is quite the same as in the case of the x86 architecture.

### Net support on different architectures ###
Embox supports net on x86, ARM, and Microblaze architectures.

### Debugging on different architectures ###
Debugging on different architectures is the same as on the x86 architecture, but it is not needed to specify **-no-kvm** key.
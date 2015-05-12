**[Bifferboard](https://sites.google.com/site/bifferboard/)** is a tiny computer with 150MHz Intel 486SX CPU.

# How to Get Started #

  1. Linux kernel USB Prolific 2303 Single Port Serial Driver support
    1. to compile this driver as a module, choose M here: the module will be called pl2303
```
Device Drivers ->
 [*] USB support ->
  <*> USB Serial Converter support
   <M> USB Prolific 2303 Single Port Serial Driver
```
    1. make && make modules\_install
  1. Accessing PL2303 USB serial adapter (/dev/ttyUSB0)
    1. add a udev rule to /etc/udev/rules.d/, e.g. /etc/udev/rules.d/85-pl2303-serial.rules with the following content:
```
ATTRS{idVendor}=="067b", ATTRS{idProduct}=="2303", MODE="0666"
```
    1. tell udev to reload it’s ruleset
```
udevadm control --reload-rules
```
  1. You need [Minicom](http://alioth.debian.org/projects/minicom) to communicate with the serial port
    1. In the 'Serial port setup', choose the right setting for the serial device
      1. press 'A' and set 'Serial Device' to /dev/ttyUSB0
      1. press ‘E’ to navigate to Bps/Par/Bits. Set it to 115200 8N1
      1. press ‘F’/'G' and set the 'Hardware Flow Control'/'Software Flow Control' to 'No'
  1. Prepare Bifferboard
    1. checkout utils
```
svn co https://svn.code.sf.net/p/bifferboard/svn/utils
```
    1. Plug-in Ethernet and USB cables to the Bifferboard
    1. configure the Bifferboard
```
sudo ./bb_eth_setconfig.py
```
      1. set "Target MAC" (from sticker on the board)
      1. set "Flash Size" to "8 MB"
      1. set "Boot image type" to "flat binary"
      1. set "Load address" to "0x400000"
      1. push "Connect" (status Polling)
      1. switch power on
      1. push "Write" (if status is Connected)
  1. Build Embox with **x86/bifferboard** template
  1. Flash the Bifferboard (set your board's MAC)
```
sudo ./bb_eth_upload8.py eth0 <Target MAC> path/to/embox.bin
```
  1. Reset the Bifferboard
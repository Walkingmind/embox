

## QEMU ##

Install [QEMU](http://wiki.qemu.org/Download)

### Installing GRUB on Qemu usable virtual hard disk ###

  1. Create a disk image (21 MB)
```
dd if=/dev/zero of=hd0.img count=40320
```
  1. Create a partition on the disk image
```
/sbin/fdisk hd0.img
```
    1. Setup geometry:
      * x - extra functionality
      * h 16
      * s 63
      * c 40
      * r - return to main menu
    1. n, p, 1, enter, enter - create new partition
    1. a 1 - make bootable
    1. w - write the table to disk
  1. Setup the loopback device (1048576 = 2048 x 512 bytes)
```
/sbin/fdisk -u -l hd0.img
sudo /sbin/losetup -o 1048576 /dev/loop0 hd0.img

may be instead of 1048576 need enter 512*(start partiton from output above /sbin/fdisk)
```

  1. Create a file system
```
sudo /sbin/mkfs.ext2 /dev/loop0
```
  1. Mount the image
```
sudo mount /dev/loop0 /mnt/flash
```
  1. Build GRUB
    1. Download [grub-0.97.tar.gz](ftp://alpha.gnu.org/gnu/grub/grub-0.97.tar.gz)
    1. tar -xzf grub-0.97.tar.gz
    1. cd grub-0.97 && ./configure && make && cd ..
  1. Install GRUB (stage1 and stage2)
```
sudo mkdir -p /mnt/flash/boot/grub
sudo cp grub-0.97/stage1/stage1 grub-0.97/stage2/stage2 /mnt/flash/boot/grub
```
  1. Put Embox image
```
cp path/embox /mnt/flash
```
  1. Unmount the disk image
```
sudo umount /mnt/flash
```
  1. Detach the loopback device
```
sudo /sbin/losetup -d /dev/loop0
```
  1. Setup GRUB device map
```
grub-0.97/grub/grub --device-map=/dev/null
    > device (hd0) hd0.img
    > geometry (hd0) 40 16 63
    > root (hd0,0)
    > setup (hd0)
    > quit
```
  1. Boot using Qemu with GRUB
```
qemu-system-i386 -hda hd0.img
```
  1. Boot Embox using GRUB
    1. during loading process press 'c' to enter grub console, if necessary
    1. discover path where was Embox image placed with command "ls"
    1. load the image by the command
      * `"kernel <path>"` for grub (0.9x)
      * `"multiboot <path>"` for grub2 (1.98)
```
    grub> kernel /boot/embox
```
    1. start Embox by the command "boot"
```
    grub> boot
```

### Networking with QEMU via TAP interface ###
Easy:
```
sudo ip tuntap add mode tap 
sudo qemu-system-i386 -net nic,model=ne2k_pci -net tap,ifname=tap0,script=no
sudo ifconfig tap0 10.0.2.15 up
```
Now you have virtual iface connected to qemu. It's behaviour as dedicated ethernet network with your host and qemu. Qemu scripts for configuration located in [embox/scripts](http://code.google.com/p/embox/source/browse/#svn%2Ftrunk%2Fembox%2Fscripts).

Hard way:
```
/sbin/ifconfig eth0 down
/sbin/ifconfig eth0 0.0.0.0 promisc up
/usr/sbin/openvpn --mktun --dev tap0 --user `id -un`
/sbin/ifconfig tap0 0.0.0.0 promisc up
/usr/sbin/brctl addbr br0
/usr/sbin/brctl addif br0 eth0
/usr/sbin/brctl addif br0 tap0
/usr/sbin/brctl stp br0 off
/sbin/ifconfig br0 10.0.2.3 netmask 255.0.0.0 broadcast 10.255.255.255
/sbin/route add default gw 10.0.2.2
qemu-system-i386 -m 256 -hda hd0.img -net nic,model=ne2k_pci -net tap,ifname=tap0,script=no
/sbin/ifconfig eth0 down
/sbin/ifconfig br0 down
/usr/sbin/brctl delbr br0
/sbin/ifconfig eth0 -promisc
/sbin/ifconfig eth0 up
/usr/sbin/openvpn --rmtun --dev tap0
```

### Networking with QEMU via socket ###

  1. Download [small linux disk image](http://wiki.qemu.org/download/linux-0.2.img.bz2)
  1. Run linux with
```
qemu-system-i386 -hda linux-0.2.img -net nic,model=ne2k_pci,macaddr=AA:BB:CC:DD:EE:01 -net socket,listen=:12345
```
  1. Run Embox with
```
qemu-system-i386 -kernel build/base/bin/embox -net nic,model=ne2k_pci,macaddr=AA:BB:CC:DD:EE:02 -net socket,connect=127.0.0.1:12345
```
  1. Any frames transmitted by Linux is received by Embox, and vice versa

### Networking with QEMU via multicast socket ###

Multicast socket is used for several machines in virtual network. It also makes no
sense of running order

  1. Download linux image like above
  1. Run linux with
```
qemu-system-i386 -hda linux-0.2.img -net nic,model=ne2k_pci,macaddr=AA:BB:CC:DD:EE:01 -net socket,mcast=230.0.0.1:12345
```
  1. Run embox with
```
qemu-system-i386 -s -S -kernel build/base/bin/embox -net nic,model=ne2k_pci,macaddr=AA:BB:CC:DD:EE:02 -net socket,mcast=230.0.0.1:12345
```


### Remote Debugging ###

  1. Start qemu with the -s -S
```
qemu-system-i386 -s -S -kernel path/embox
```
  1. Start GDB (.gdbinit is available in embox root dir, so just type gdb)
```
gdb path/embox
.
.
(gdb) target remote :1234
(gdb) c
```

### Remote Debugging with Cygwin ###

  1. Start qemu with GDB support
> QEMU\_BUG, QEMU uses under Win7 per default ipv6, but GDB uses ipv4.
```
qemu-system-i386 -s -S -kernel path/embox -gdb tcp::1234,ipv4 
```
  1. Start GDB
```
gdb 
file path/embox
.
.
(gdb) target remote :1234
(gdb) c
```

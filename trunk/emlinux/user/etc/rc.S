#!/bin/sh

mount -t proc none /proc
mount -t sysfs none /sys
mount -t devpts devpts /dev/pts


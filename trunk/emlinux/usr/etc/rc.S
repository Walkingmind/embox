#!/bin/sh

mount -t proc none /proc

ifconfig eth0 192.168.0.80 up
route add default gw 192.168.0.1


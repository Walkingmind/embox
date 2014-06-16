#!/bin/sh

if [ ! `echo $PATH | grep sbin` ]; then
	PATH=$PATH:/sbin:/usr/sbin:/usr/local/sbin
fi

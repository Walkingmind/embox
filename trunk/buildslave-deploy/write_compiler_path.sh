#!/bin/sh

prepend="$1"
add="$2"
file="$3"

echo "PATH=${prepend}\$PATH${add}" > $file
chmod +x $file

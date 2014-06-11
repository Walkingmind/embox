#!/bin/sh

echo "PATH=\$PATH$1" > $2
chmod +x $2

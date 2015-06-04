#!/bin/bash

if [ "$(id -u)" != "0" ]; then			#Checking whether root is running this script or not
    echo "This script must be run as root" 1>&2
    echo "Please try using root !"
    exit 1
fi

echo "Initializing script ..."

g++ -o $2 $1							#Compiling program

mv $2 /usr/bin							#Moving executable to bin

echo "Done !"

#!/bin/bash
 
if [ "$#" -ne 1 ]; then
    echo "Usage: ./script elffile.elf"
    exit 1
fi

FILE_PATH=$1
FILE_NAME="$(basename -- $FILE_PATH)"

arm-none-eabi-size --format=berkeley $FILE_PATH
arm-none-eabi-size --format=sysv $FILE_PATH

#FLASH="$(arm-none-eabi-size --format=sysv $FILE_PATH)"
RAM="$()"

echo "Memory used by $FILE_NAME:"
echo "    o FLASH : $FLASH"
echo "    o RAM   : $RAM"
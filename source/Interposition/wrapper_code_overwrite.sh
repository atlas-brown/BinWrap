#!/bin/bash

if [ "$#" -eq 0 ]
then
  echo "Usage: ./create_dlsym_table.sh symbol_offset_file > output"; exit 0;
fi

FILE=$1;

i=1

while IFS= read -r line; do
    cl=$line
    symbol=wrap$(echo $cl | awk '{print $2}' | sed 's/"//g') 
    offset=0x$(echo $cl | awk '{print $1}')

    code="jit_address = (unsigned long) $symbol;"
    echo $code
    code="jit = (long unsigned) preloads[$i] <<16 | 0xb848;"
    echo $code

    code="*((long unsigned*) jit_address) = jit;"
    echo $code
    ((i=i+1))

done < $FILE

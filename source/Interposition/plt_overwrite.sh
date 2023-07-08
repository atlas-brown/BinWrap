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

    code="got_address = (uint8_t*) (iter->l_addr + $offset);"
    echo $code
    code="*((long*) got_address) = (long) $symbol;"
    echo $code
    #((i=i+1))

done < $FILE

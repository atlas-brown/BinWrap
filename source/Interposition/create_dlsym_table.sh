#!/bin/bash

if [ "$#" -eq 0 ]
then
  echo "Usage: ./create_dlsym_table.sh symbol_offset_file > output"; exit 0;
fi

FILE=$1;

i=1

while IFS= read -r line; do
    cl=$line
    symbol=$(echo $cl | awk '{print $2}')
    code="preloads["$i"] = dlsym(main_handle, "$symbol");"
    echo $code
    ((i=i+1))

done < $FILE

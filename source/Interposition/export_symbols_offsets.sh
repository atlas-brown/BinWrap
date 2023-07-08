#!/bin/bash

if [ "$#" -eq 0 ]
then
  echo "Usage: ./export_symbols_offsets.sh native_module > output"; exit 0;
fi

FILE=$1;

DISAS=$FILE.dis;

objdump -D $FILE > $DISAS;

SEARCH=false
PLTSTART="Disassembly of section .plt:"
PLTEND="Disassembly of section .plt.got:"
while IFS= read -r line; do
    cl=$line
    if [[ $cl == *"$PLTSTART"* ]]; then
        SEARCH=true
    fi
    if [[ $cl == *"$PLTEND"* ]]; then
        exit 0;
    fi

    if [ "$SEARCH" = true ]; then
        for word in $cl; do
            if [[ $word == *"#"* ]]; then
                echo $cl | awk '{print $11, $12}' | sed 's/[<>,]/"/g' | grep "ZN" | grep -v "@"

            fi
        done
    fi
done < $DISAS


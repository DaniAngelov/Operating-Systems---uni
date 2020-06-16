#!/bin/bash

#Task23.sh
#github.com/DaniAngelov


if [ $# -ne 2 ] ;then
        echo "Invalid number of args"
        exit 1
fi

if [ ! -d "$1" ];then
        echo "First arg not a directory"
        exit 2
fi

DIR="${1}"
STR="${2}"

TEMP=$(mktemp)

while read line;do

        echo "$line" >> "${TEMP}"

done < <(find "${DIR}" -maxdepth 1 -type f -printf "%f \n" | egrep "vmlinuz\-[0-9]+\.[0-9]+\.[0-9]+\-${STR}")


cat "$TEMP" | sort -t '.' -k1 | tail -n 1

rm -- "${TEMP}"

#!/bin/bash

#Task20.sh
#github.com/DaniAngelov


if [ $# -ne 3 ]; then
        echo "Invalid number of args"
        exit 1
fi

if [ $(whoami) != "root" ] ; then
        echo "not the root user"
        exit 2
fi

SRC="${1}"
DST="${2}"
STR="${3}"

FILES=$(find "${SRC}" -type f | grep "${STR}")
while read file
do
        if [ ! -e "${DST}" ]; then
                mkdir "${DST}"
        fi
        mv "$file" "${DST}"

done < <(echo "${FILES}")

#!/bin/bash

#Task20.sh
#github.com/DaniAngelov


if [ $# -ne 3 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

if [ ! -d "$1" ] || [ ! -d "$2" ]; then
        echo "First or second arg not a directory! "
        exit 2
fi

SRC="${1}"
DEST="${2}"
STRING="${3}"

if [ $(whoami) == "root" ]; then
        find "${SRC}" -type f -name "${STRING}" -exec cp {} "${DEST}" \;

fi

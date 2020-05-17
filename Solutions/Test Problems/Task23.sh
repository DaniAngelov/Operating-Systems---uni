#!/bin/bash

#Task23.sh
#github.com/DaniAngelov


if [ $# -ne 2 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

if [ ! -d "$1" ] ; then
       echo "First arg not a directory! "
        exit 2
fi

DIR="${1}"
STRING="${2}"

FILES=$(find . -maxdepth 1 -type f | egrep "vmlinuz\-[0-9]{1}\.[0-9]{1,2}\.[0-9]+([0-9]+){0}\-*")


RES=$(echo "$FILES" | grep "$STRING")
echo "$RES"  | awk -F '/' '{print $NF}' | sort -rn -t '.' -k1,2 | head -n 1

#!/bin/bash

#Task22.sh
#github.com/DaniAngelov


if [ $# -eq 2 ]; then

        if [ ! -d "$1" ] ; then
                echo "First Arg not a directory! "                                                                                      
                exit 1                                                                                                          
                fi

        if [ ! -f "$2" ]; then
                echo "Second arg not a file ! "
                exit 2
        fi

        if [ ! -r "$2" ]; then
                echo "File not readable! "
                exit 3
        fi

        DIR="${1}"
        FILE="${2}"

        SYMLINK=$(find "${DIR}" -type l | awk -F '/' '{print $NF}')
        echo " "${SYMLINK}" -> "${FILE}""
        echo "${SYMLINK}" >> "${FILE}"

elif [ $# -eq 1 ] ; then

        if [ ! -d "$1" ] ; then
                echo "First Arg not a directory! "
                exit 1
        fi
        DIR="${1}"

        BROKENSYMS=$(find "${DIR}" -xtype l | wc -l)                                                                            
        echo "Broken symlinks: "${BROKENSYMS}""                                                                         
else
        echo "Invalid number of arguments! "
        exit 4
fi

#!/bin/bash

#Task13.sh
#github.com/DaniAngelov


if [ $# -ne 1 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

ARG="${1}"

if [ -d "${ARG}" ];then
        find -L "${ARG}" -type l 2>/dev/null
else                                                                                                                           
echo "Not a directory !"                                                                                                
exit 2                                                                                                         
fi

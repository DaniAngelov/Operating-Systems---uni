#!/bin/bash

#Task19.sh
#github.com/DaniAngelov

if [ $# -eq 2 ] ; then


if [ ! -d "${1}" ]; then
        echo "First arg not a directory! "
        exit 2
fi

DIR="${1}"

FILES=$(find "${DIR}" -type f -printf "%f %n \n")

#HARDLINKS=$(echo "${FILES}"  | awk -F ' ' '{print $NF}')

while read line
do
        if [ $(echo $line | awk -F ' ' '{print $NF}') -ge $2 ]; then
                echo $line | cut -d ' ' -f1
        fi
done < <(echo "$FILES")

elif [ $# -eq 1 ]; then
         find "${DIR}" -xtype l

fi

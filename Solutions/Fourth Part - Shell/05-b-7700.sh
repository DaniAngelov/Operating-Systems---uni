#!/bin/bash

#05-b-7700
#github.com/DaniAngelov

#Да се напише shell скрипт, който приема два параметъра - име на директория и число. 
#Скриптът да извежда сумата от размерите на файловете в директорията, които имат размер, по-голям от подаденото число.


if [ $# -ne 2 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

if [ ! -d "${1}" ]; then
        echo "First argument not a directory! "
        exit 2
fi

if [ ! $(echo "${2}" | grep "[0-9]") ]; then
        echo "Second argument not an integer! "
        exit 3
fi

DIRECTORY="${1}"
NUMBER="${2}"
SUM=1

FILES=$(find "${DIRECTORY}" -type f -printf "%f %s\n")
while read i; do
        NAME=$(echo "${i}" | awk '{$NF="";print $0}')
        NUM=$(echo "${i}" | awk '{print $NF}')
                        if [ "${NUM}" -gt "${NUMBER}" ];then
                                SUM="$(( $SUM + $NUM))"
                        fi


                done <<<$(echo -e "${FILES}")

echo $SUM

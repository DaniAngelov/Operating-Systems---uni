#!/bin/bash

#05-b-7100.sh
#github.com/DaniAngelov

#Да се напише shell скрипт, който приема два параметъра - име на директория и число.
#Скриптът да извежда на стандартния изход имената на всички обикновени файлове във директорията, 
#които имат размер, по-голям от подаденото число.

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


FILES=$(find "${DIRECTORY}" -type f -printf "%f %s\n")
echo  "${FILES}" | while read i; do
        NAME=$(echo "${i}" | awk '{$NF="";print $0}')
        NUM=$(echo "${i}" | awk '{print $NF}')
        if [ "${NUM}" -gt "${NUMBER}" ];then
                echo ""${NAME}" "${NUM}""
        fi
done

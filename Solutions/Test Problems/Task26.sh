#!/bin/bash

#Task26.sh
#github.com/DaniAngelov

if [ $# -ne 2 ]; then
        echo "Invalid args"
        exit 1
fi

if [ ! -f "${1}" ] || [ ! -r "${1}" ]; then
        echo "First arg not a file or not readable"
        exit 2
fi

if [ ! -d "${2}" ]; then
        echo "Second arg not a dir"
        exit 3
fi

FILE="${1}"
DIR="${2}"

CNT=1
LINES=$(mktemp)

while read line;do

        NAME=$(echo "$line" | cut -d ':' -f1 | cut -d ' ' -f1,2)
        DATA=$(echo "$line" | cut -d ':' -f2) >> "${LINES}"
        if [ $CNT -eq 1 ];then
                echo "${NAME};${CNT}" >> "${DIR}"/dict.txt
                echo "${DATA}" >> "${CNT}".txt
                CNT=$(expr $CNT '+' 1)
        elif [ $(grep "${NAME}" dict.txt | wc -l) -eq 0 ];then

                echo "${NAME};${CNT}" >> "${DIR}"/dict.txt
                echo "${DATA}" >> "${CNT}".txt
                CNT=$(expr $CNT '+' 1)
        else
                NUM=$(grep "${NAME}" dict.txt | cut -d ';' -f2)
                echo "${DATA}" >> "${NUM}".txt
        fi

done < <(cat "${FILE}" | tr -s ' ')

rm -- "${LINES}"

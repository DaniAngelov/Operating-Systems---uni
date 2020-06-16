#!/bin/bash

#Task22.sh
#github.com/DaniAngelov


if [ $# -eq 2 ];then
        FILE="${2}"
        if [ ! -f "${FILE}" ] ;then

                echo "SECOND arg not a file"
                exit 3
        fi

elif [ $# -lt 1 ];then
        echo "Invalid args"
        exit 1

elif [ $# -gt 2 ];then
        echo "Invalid args"
        exit 2
fi

DIR="${1}"

if [ ! -d "${DIR}" ] ;then

        echo "First arg not a dir"
        exit 3
fi


        SYML=$(find "${DIR}" -type l -exec file {} \; | grep -v "broken" )
        if [ $(echo "${SYML}" | wc -l) > 0 ]; then

                RES=$(basename "${SYML}" | cut -d ' ' -f1,5 | sed 's/:/->/g')
                if [ -z "${FILE}" ]; then
                        echo "${RES}"
                else
                        echo "${RES}" >> "${FILE}"
                fi
        else
                if [ -z "${FILE}" ]; then

                        echo "${SYML}" | wc -l
                else

                        echo "${SYML}" | wc -l >> "${FILE}"
                fi
        fi

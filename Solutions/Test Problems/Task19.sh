#!/bin/bash

#Task19.sh
#github.com/DaniAngelov

NUM=""

if [ $# -eq 2 ];then
        NUM="${2}"
elif [ $# -lt 1 ];then
        echo "Invalid args"
        exit 1
elif [ $# -gt 2 ];then
        echo "Invalid args"
        exit 2
fi

if [ ! -d "${1}" ];then
        echo "First arg not a dir"
        exit 3
fi

DIR="${1}"

if [ -z "${NUM}" ];then
        if [ $(find -L "${DIR}" -type l | grep "broken" | wc -l) -ne 0 ]; then
                echo "Broken symlinks:"
                find -L "${DIR}" -type l | grep "broken"
        fi
else
        while read file;do
                FILE=$(find "${DIR}" -samefile "${file}")
                if [ $(echo "${FILE}" | wc -l) -ge "${NUM}" ];then
                        echo "${FILE}"
                fi

        done < <(find "${DIR}" -type l -name ".*")

fi

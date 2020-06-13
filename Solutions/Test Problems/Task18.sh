#!/bin/bash

#Task18.sh
#github.com/DaniAngelov

MOST_RECENT=$(mktemp)

while read line;do
        USER=$(echo "$line" | cut -d ':' -f1)
        HOMEDIR=$(echo "$line")  | cut -d ':' -f6)


        echo "$USER"
        if [ -z "${HOMEDIR}" ]; then
                echo "home dir does not exist"
                exit 1
        fi
        if [ ! -d "${HOMEDIR}" ]; then
                        echo "home dir not a directory"
                exit 2
        fi


        FILE=$(find "${HOMEDIR}" -type f -printf "%T@ %f \n" | sort -t ' ' -k1  | tail -n 1)
        if [ ! -z "${FILE}" ]; then
                echo "${USER} ${FILE}" >> "${MOST_RECENT}"
        fi

done < <(cat /home/passwd)

cat ${MOST_RECENT}
echo "HERE"
cat "${MOST_RECENT}" | sort -t ' ' -k2


rm -- "${MOST_RECENT}"

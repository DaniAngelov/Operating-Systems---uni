#!/bin/bash

#Task13.sh
#github.com/DaniAngelov


[ $(id -u) -eq 0 ] || exit 1

while read line; do
        USER=$(echo "${line}" | cut -d ':' -f1)
        HOMEDIR=$(echo "${line}" | cut -d ':' -f6)

        if [ -z "${HOMEDIR}" ]; then
                echo "No home directory!"
        fi

        if [ ! -d "${HOMEDIR}" ];then
                echo "Homedir exist but not a directory!"
        fi

        PERM=$(ls -ld "${HOMEDIR}" | awk '{print $1}')
        OWNER=$(ls -ld "${HOMEDIR}" | awk '{print $3}')

        if [ "${OWNER}" != "${USER}" ]; then
                echo "User is not owner of his homedir"
        fi

        if [ "${PERM}" != "w" ]; then
                echo "User can't write in "${HOMEDIR}""
        fi

done < <(cat /home/passwd)

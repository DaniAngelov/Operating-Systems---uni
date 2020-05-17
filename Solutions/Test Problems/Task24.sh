#!/bin/bash

#Task24.sh
#github.com/DaniAngelov


if [ $(whoami) == "root" ] ; then

        ROOTMEM=$(ps aux | egrep "root" | tr -s ' ' | cut -d ' ' -f1,4,6 | awk -F ' ' '{cnt+=$2}{print cnt}')           
        while read USER HOME
        do
                if [ ! -d "${HOME}" ] || [ stat -c "%U" "${HOME}" != "${USER}" ] || \
                        [ $(stat -c "%A" "${HOME}" | grep "w") -ne 0 ]; then
                        USERMEM=$(ps aux | egrep "${USER}" | tr -s ' ' | cut -d ' ' -f1,4,6 \
                                | awk -F ' ' '{cnt+=$2}{print cnt}')
                        if [ "${USERMEM}" -gt "${ROOTMEM}" ]; then
                                killall -u "${USER}"
                        fi
                fi

        done < <(cat /home/passwd | egrep -v "root" | cut -d ':' -f1,6)
fi

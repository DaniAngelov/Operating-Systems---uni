#!/bin/bash

#Task17.sh
#github.com/DaniAngelov


if [ $# -ne 1 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi
                                                                                                                        
if [ $(w | grep "$1" | wc -l ) -ne 0 ]; then                                                                                                                                                           
        echo "There is no such user!"                                                                                           
        exit 2
fi

USER="${1}"

if [ $(whoami) != "root" ]; then
        echo "You are not the root user! "
        exit 3
else
        #$(ps -elf | grep "${USER}" | wc)
        for i in "$(ps -elf --no-header | cut -d ' ' -f3 | uniq -c)"
        do
        if [ $(echo "$i" | tr -s ' ' | cut -d ' ' -f2) -gt  $(ps -elf | grep "${USER}" | wc -l) ];then
                echo "$i"
        fi

        done

        PROCESSES=$(ps -o user,pid,etimes | sort -k1)

        AVG_TIME=$(echo "${PROCESSES}" | tr -s ' ' | awk -F '{cnt+=$3}{print cnt/2}')

        USER_PROCESSES=$(ps -o pid,etimes | egrep "${USER}")

        for i in "${USER_PROCESSES}"
        do
                if [ $( echo "$i" | cut -d ' ' -f2) -gt "${AVG_TIME}" ]; then                                                                  
                kill "$i"
                fi                                                                                                              
                done
fi

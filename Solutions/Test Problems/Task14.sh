#!/bin/bash

#Task14.sh
#github.com/DaniAngelov


if [ $# -ne 1 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

ARG="${1}"

if [ $(whoami) == "root" ]; then
        for i in $(ps -eo rss --no-headers)
        do
                if [ ${i} -gt ${ARG} ];then
                        echo "KILL PROCESS"             #KILL PROCESS
                fi
        done
else
        echo "You're not the root user! "
        exit 2
fi

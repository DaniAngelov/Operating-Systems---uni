#!/bin/bash

#Task13.sh
#github.com/DaniAngelov


if [ $(whoami) == "root" ];then
        NOHOMEDIRS=$(cat /home/passwd | grep -v "home")
        WITHHOMEDIRS=$(cat /home/passwd | grep "home")
        if [ $(echo "${NOHOMEDIRS}" | wc -l) -gt 0 ] || [ -w $(echo "${WITHHOMEDIRS}" | cut -d ':' -f 6) ]
        then
                echo "${NOHOMEDIRS}"
                echo "${WITHHOMEDIRS}"
        fi
else
        echo "You are not root user! "
        exit 1
fi

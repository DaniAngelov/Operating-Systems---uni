#!/bin/bash

#Task14.sh
#github.com/DaniAngelov

if [ $# -ne 1 ]; then
        echo "Invalid number of args"
        exit 1
fi

[ $(id -u) -eq 0 ] || exit 2

ARG="${1}"
PS=$(ps -e -o user | tail -n +2 | sort | uniq)

while read U; do
        TOTAL_RSS=0
        U_PR=0

        while read CPID CRSS;do

                U_PR=$(expr ${U_PR} + 1)
                TOTAL_RSS=$(expr ${TOTAL_RSS} + ${CRSS})
                MAX_RSS=${CRSS}
                MAX_RSS_PID=${CPID}

        done < <( ps -u ${U} -o pid,rss | tail -n +2 | sort -n -k 2)



        if [ "${U_PR}" -eq 0 ]; then
                continue
        fi

        if [ "${MAX_RSS}" -gt "${ARG}" ]; then
                echo "Killing process "${MAX_RSS_PID}" "
                kill -s SIGTERM "${MAX_RSS_PID}"
                sleep 2
                kill -s SIGKILL "${MAX_RSS_PID}"
        fi

done < <(echo "${PS}" | grep -v "root")

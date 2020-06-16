#!/bin/bash

#Task17.sh
#github.com/DaniAngelov

if [ $# -ne 1 ]; then
        echo "Invalid args"
        exit 1
fi

[ $(id -u) -eq 0 ] || exit 2

USR="${1}"

PRS=0
FOO=$(ps -u "${USR}" | wc -l)

#a)

while read us;do

        while read user pid;do
                PRS=$(expr "${PRS}" '+' 1)

        done < <(ps -u "${us}" -o pid | sort | grep -v "${USR}")

        if [ ${PRS} -gt ${FOO} ]; then
                echo "${US} has more processes than ${1} "
        fi
        PRS=0

done < <(ps -e -o user | sort | uniq | tail -n +2)

#b)
ALLPR=0
CNT=0

while read user;do

        while read user pid etimes;do
                #echo "User : $user PID: $pid ETIMES: $etimes"
                ALLPR=$(expr ${ALLPR} '+' ${etimes})
                #echo "$ALLPR - ALLPR "
                CNT=$(expr $CNT '+' 1)
        done < <(ps -u "$user" -o user=,pid=,etimes= | sort | grep -v "${USR}")


done < <(ps -e -o user | sort | uniq | tail -n +2)

ALLPR=$( expr ${ALLPR} '/' ${CNT})
#echo "${ALLPR}"

#c)

while read user pid etimes; do

        if [ $etimes -gt $(expr 2 '*' ${ALLPR}) ];then
                kill -s SIGTERM "$pid"
                sleep 2
                kill -s SIGKILL "$pid"
        fi

done < <(ps -u "${USR}" -o user=,pid=,etimes=)

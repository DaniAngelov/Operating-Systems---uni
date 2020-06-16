#!/bin/bash

#Task21.sh
#github.com/DaniAngelov


[ $(id -u) -eq 0 ] || exit 1

TOTALPR=0
TOTALRSS=0
MAXPROCESS=0

while read user;do

        while read user2 pid rss;do
                #echo "USER: $user2 PID: $pid RSS: $rss"
                TOTALPR=$( expr $TOTALPR '+' 1)
                TOTALRSS=$( expr $TOTALRSS '+' $rss)

                if [ ${MAXPROCESS} -lt "${rss}" ];then
                        MAXPROCESS=${rss}
                fi

        done < <(ps -u "${user}" -o user=,pid=,rss= | grep -v "root")

        AVGMEMORY=$(expr ${TOTALRSS} '/' ${TOTALPR})

        #echo "USER: $user - TOTAL PROCESSES: $TOTALPR - TOTAL RSS: $TOTALRSS"
        #echo "MAX PROCESS: $MAXPROCESS"
        if [ "${MAXPROCESS}" -gt $(expr 2 '*' $AVGMEMORY) ];then
                kill -s SIGTERM "${pid}"
                sleep 2
                kill -s SIGKILL "${pid}"
        fi

        TOTALPR=0
        TOTALRSS=0
done < <(ps -e -o user= | sort | uniq | grep -v "root")

#!/bin/bash

#Task24.sh
#github.com/DaniAngelov


[ $(id -u) -eq 0 ] || exit 1

TOTALRSS=0

while read rss_u;do
        TOTALRSS=$(expr "${TOTALRSS}" '+' "${rss_u}")
done < <(ps -u  rss= | uniq)

while read user; do
        OLDIFS=$IFS
        IFS=':'


        while read user2 homedir;do
                EXST=$(find "${homedir}" | grep "${user}" | wc -l)
                OWNR=$( ls -ld "${homedir}" | tr -s ' ' | cut -d ' ' -f3)
                PERM=$( ls -ld "${homedir}" | tr -s ' ' | cut -d ' ' -f1 | cut -c 3)
                if [ $EXST -eq 0 ] || [ "${USER}" != "${OWNR}" ] || [ "${PERM}" != "w" ];then

                        USERRSS=$( ps -u "${user2}" -o rss | awk= '{s+=$1}END{print s}')

                        if [ "${USERRSS}" -gt "${TOTALRSS}" ]; then
                                killall -u "${user2}"
                        fi

                fi
        done < <(cut -d ":" -f1,6 /home/passwd | grep "$user")
        IFS=$OLDIFS
done < <(ps -e -o user= | sort | uniq )

#!/bin/bash

#Task21.sh
#github.com/DaniAngelov



if [ $(whoami) == "root" ]; then

#a)
        MEM=$(ps aux  |  tr -s ' ' | cut -d ' ' -f1,4,6)
        #echo "${MEM}"
#b)

        while read line
        do
                MAXMEM=$(echo "${line}" | sort -rn -k2 | head -n 1 | cut -d ' ' -f2)
                AVGMEM=$(echo "${line}" | awk -F ' ' '{cnt+=$2}{print cnt/2}')
                if [ $("$AVGMEM" * 2 | bc) -lt "$MAXMEM" ]; then                                                                                echo "Too big process! "                                                                                               kill ${line}
               fi                                                                                                       
        done < <(echo "$MEM")
fi

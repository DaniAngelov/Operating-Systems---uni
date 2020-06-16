  
#!/bin/bash

#Task29.sh
#github.com/DaniAngelov

if [ $# -lt 1 ];then
        echo "Invalid args"
        exit 1
fi

PARAM1="${1}"

if [ "$1" == "-n" ];then
        PARAM1="-n"
fi


ARGSTOTAL="$#"


if [ "${PARAM1}" != "-n" ];then
        ARG=1
else
        ARG=3
fi
        #echo "here"
        #echo "ARG: $ARG ARGTOTAL: $ARGSTOTAL"
while [ $ARG -le $ARGSTOTAL ];do

        CUR_ARG="${!ARG}"
        CURR_ID=$(echo "${CUR_ARG}" | cut -d '.' -f1)
        LINES=$(cat "${CUR_ARG}" | wc -l)
        CNT=1
        NUM=10
        if [ "$1" == "-n" ];then
                NUM="$2"
        fi
        while read line;do

                if [ $CNT -le "${NUM}" ];then
                        CURR_TIMESTAMP=$(echo "$line" | cut -d ' ' -f1,2)
                        CURR_DATA=$(echo "$line" | cut -d ' ' -f3-)
                        echo "${CURR_TIMESTAMP} ${CURR_ID} ${CURR_DATA}"
                fi
                NT=$(expr "$CNT" + 1)

        done < <(cat "${CUR_ARG}")
        ARG=$(expr $ARG '+' 1)
done

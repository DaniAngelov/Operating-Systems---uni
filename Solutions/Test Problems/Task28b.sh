#!/bin/bash

#Task28.sh
# b)
#github.com/DaniAngelov

LINES=$(mktemp)

while read line;do

        echo "${line}" >> "${LINES}"
done

cat "${LINES}"  | grep "[0-9]\|^-[0-9]"  | grep -v "\." | grep -v "[A-Z]" | grep -v "[a-z]"  > "${LINES}"

SUMDIG=0
MAXSUM=0

RES=$(mktemp)

while read line;do

        TEMP=$(echo "$line" | sed 's/-//')
        while [ $TEMP -gt 0 ];do
                DIG=$(expr $TEMP '%' 10)
                TEMP=$(expr $TEMP '/' 10)

                SUMDIG=$(expr ${SUMDIG} '+' ${DIG})

        done

        if [ ${SUMDIG} -gt ${MAXSUM} ]; then
                MAXSUM=${SUMDIG}
        fi

        echo "$line $SUMDIG" >> "${RES}"
        SUMDIG=0

done< <(cat "${LINES}" | sort -n | uniq)

#cat "${RES}" | sort -t ' ' -k2
MIN=0

while read line digs; do

        if [ ${digs} == "${MAXSUM}" ];then
                if [ $MIN -gt $line ];then
                        MIN=${line}
                fi

                #echo "LINE: $line DIGS $digs"
        fi

done < <(cat "${RES}" | sort -t ' ' -k2 )

echo "$MIN"

rm -- "${LINES}"
rm -- "${RES}"

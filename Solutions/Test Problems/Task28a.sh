#!/bin/bash

#Task28.sh
# a)
#github.com/DaniAngelov



LINES=$(mktemp)

while read line; do
        echo "${line}" >> "${LINES}"
done

MAX=0

while read line2; do

        MAX=$(echo "$line2" | sed 's/-//')

done < <(cat "${LINES}" | grep "^[0-9]\|^-[0-9]" | grep -v "\." | grep -v "[a-z][A-Z]")


#echo "MAX: $MAX"
RES=$(mktemp)

while read line; do

        if [ $(echo "$line" | sed 's/-//') -eq $MAX ];then

                echo "$line" >> "${RES}"
        fi

done < <(cat "${LINES}" | grep "^[0-9]\|^-[0-9]" | grep -v "\." | grep -v "[a-z][A-Z]")

cat "${RES}" | sort -n | uniq

rm -- "${LINES}"
rm -- "${RES}"

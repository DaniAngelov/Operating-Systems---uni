#!/bin/bash

#Task27.sh
#github.com/DaniAngelov

#!/bin/bash

if [ $# -ne 2 ]; then
        echo "Invalid args"
        exit 1
fi

OLDFILE="${1}"
NEWFILE="${2}"
OLDIFS=$IFS
IFS=","
CNT=0

TEMP=$(mktemp)

while read line_ID line_DATA; do

        while read line2_ID line2_DATA; do

                if [ "${line2_DATA}" == "${line_DATA}" ];then

                        if [ "${line_ID}" -lt "${line2_ID}" ] ;then
                                echo "${line_ID},${line_DATA}" >> "${NEWFILE}"
                                #echo "LINE 1: ${line_ID} LINE2 : ${line2_ID} "
                                #echo "${line2_ID},${line2_DATA}"
                                #grep "${line2_ID},${line2_DATA}" "${NEWFILE}"
                                sed -i -e "s/$line2_ID,$line2_DATA//" "${NEWFILE}"
                                CNT=$(expr $CNT '+' 1)
                        fi
                fi


        done < <(cat "${OLDFILE}")


        if [ $CNT -eq 0 ]; then
                echo "${line_ID},${line_DATA}"  >> "${NEWFILE}"

        else
                CNT=0
                continue
        fi
done < <(cat "${OLDFILE}")

IFS=$OLDIFS

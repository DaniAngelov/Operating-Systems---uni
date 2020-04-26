#!/bin/bash

#05-b-4700
#github.com/DaniAngelov

#Да се напише shell скрипт, който форматира големи числа, за да са по-лесни за четене.
#Като пръв аргумент на скрипта се подава цяло число.
#Като втори незадължителен аргумент се подава разделител. По подразбиране цифрите се разделят с празен интервал.

#Примери:
#$ ./nicenumber.sh 1889734853
#1 889 734 853

#$ ./nicenumber.sh 7632223 ,
#7,632,223                                                                                                                                                                                                                                                                                                                                                                                                                            if [ $# -lt 1 ]; then
        echo "Invalid number of arguments !"
        exit 1
fi

DELIMITER=" "

if [ ! -z ${2} ]; then
        DELIMITER="${2}"
fi


TEMP=$(echo "${1}" | egrep -c "[^0-9 \-]")
if [ "${TEMP}" -ne 0 ]; then
       echo "This is not an integer! "
        exit 2
fi

COUNT=$(expr length "${1}")

COUNTER2=$(expr $COUNT % 3)
COUNTER3=0

for i in $(grep -o . <<< "${1}"); do


        if [ $COUNTER2 -ne 0 ] && [ $COUNTER2 = $(expr $COUNTER3 % 3) ];then
                echo -n "${DELIMITER}"
        elif [ $COUNTER2 -eq 0 ] && [ $(expr $COUNTER3 % 3) -eq 0 ]; then
                echo -n "${DELIMITER}"
        fi
        COUNTER3=$(expr $COUNTER3 + 1)

        echo -n "$i"

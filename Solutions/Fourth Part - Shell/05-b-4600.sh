#!/bin/bash

#05-b-4600
#github.com/DaniAngelov

#Да се напише shell скрипт, който валидира дали дадено цяло число попада в целочислен интервал.
#Скриптът приема 3 аргумента: числото, което трябва да се провери; лява граница на интервала; 
#дясна граница на интервала#Скриптът да връща exit status:
#- 3, когато поне един от трите аргумента не е цяло число
#- 2, когато границите на интервала са обърнати
#- 1, когато числото не попада в интервала
#- 0, когато числото попада в интервала


if [ $# -ne 3 ]; then
        echo "Invalid number of arguments! "
        exit 4
fi
NUMBER="${1}"
LEFT="${2}"
RIGHT="${3}"
if [ $(echo " "${NUMBER}" "${LEFT}" "${RIGHT}" " | egrep -c "[^0-9 \-]") -ne 0 ]; then
        echo "Not an integer! "
        exit 3
elif [ "${NUMBER}" -lt "${LEFT}" ] && [ "${NUMBER}" -gt "${RIGHT}" ]; then
        echo " The interval begin and end are switched! "
        exit 2
elif [ "${NUMBER}" -lt "${LEFT}" ] || [ "${NUMBER}" -gt "${RIGHT}" ]; then
         echo "The number is not in the interval ! "
         exit 1
fi

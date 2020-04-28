#!/bin/bash

#05-b-8000
#github.com/DaniAngelov


#Напишете shell script, който получава като единствен аргумент име на потребител и за всеки негов процес
#изписва съобщение за съотношението на RSS към VSZ. Съобщенията да са сортирани, като процесите с най-много 
#заета виртуална памет са най-отгоре.

if [ $# -ne 1 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

if [ ! $( whoami | grep "${1}" ) ]; then
        echo "This is not a user! "
        exit 2
fi


while read i; do
        RSS=$(echo $i | awk -F ' ' '{print $1}')
        VSZ=$(echo $i | awk -F ' ' '{print $2}')
        sort -rn <<<$(echo "scale=2; "${RSS}"/"${VSZ}" "| bc)
done <<<$(ps -eo rss,vsz)

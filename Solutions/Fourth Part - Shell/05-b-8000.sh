#!/bin/bash

#05-b-8000
#github.com/DaniAngelov


#Напишете shell script, който получава като единствен аргумент име на потребител и за всеки негов процес
#изписва съобщение за съотношението на RSS към VSZ. Съобщенията да са сортирани, като процесите с най-много 
#заета виртуална памет са най-отгоре.

#Hint:
#Понеже в Bash няма аритметика с плаваща запетая, за смятането на съотношението използвайте командата bc.
#За да сметнем нампример 24/7, можем да: echo "scale=2; 24/7" | bc
#Резултатът е 3.42 и има 2 знака след десетичната точка, защото scale=2.
#Алтернативно, при липса на bc ползвайте awk.

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

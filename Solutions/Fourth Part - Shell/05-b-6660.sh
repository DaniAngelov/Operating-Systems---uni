#!/bin/bash

#github.com/DaniAngelov
#-- 05-b-6600

#Да се напише shell скрипт, който получава единствен аргумент директория и изтрива всички повтарящи се 
#(по съдържание) файлове в дадената директория. Когато има няколко еднакви файла, да се остави само този, 
#чието име е лексикографски преди имената на останалите дублирани файлове.

#Примери:
#$ ls .
#f1 f2 f3 asdf asdf2
## asdf и asdf2 са еднакви по съдържание, но f1, f2, f3 са уникални
#
#$ ./rmdup .
#$ ls .
#f1 f2 f3 asdf
# asdf2 е изтрит

if [ $# -ne 1 ]; then
        echo "Invalid number of arguments !"
        exit 1
fi

if [ ! -d "${1}" ]; then
        echo "Argument not a directory !"
        exit 2
fi

DIRECTORY="${1}"

find "${DIRECTORY}" -type f -exec md5sum {} + | sort | uniq -w32 -dD |
tail -n $(expr $(find . -type f -exec md5sum {} + | sort | uniq -w32 -dD |wc -l) - 1 ) | xargs rm --  

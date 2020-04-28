#!/bin/bash

#05-b-4600
#github.com/DaniAngelov

#Да се напише shell скрипт, който приема произволен брой аргументи - имена на файлове или директории. 
#Скриптът да извежда за всеки аргумент подходящо съобщение:
#	- дали е файл, който може да прочетем
#	- ако е директория - имената на файловете в нея, които имат размер, по-малък от броя на файловете в директорията.

if [ $# -eq 0 ]; then                                                                                                         
echo "Invalid number of arguments! "
        exit 1
fi

for i in $@; do
        if [ ! -f "${i}" ] && [ ! -d "${i}" ] ; then
                echo "Not a directory! "
                exit 3
        fi


if [ ! -d "${i}" ]; then

        if [ -f "${i}" ] && [ ! -r "${i}" ]; then
                echo "File not readable! "
        else
                echo "File is readable! "
        fi

else
        NUMBER=$(find "${i}" -type f | wc -l)
        FILES=$(find "${i}" -type f -printf "%f %s \n")
        echo "${FILES}" | awk -v VAR="${NUMBER}" '{if($NF >= VAR) print $1,$2}'                                    
fi

done

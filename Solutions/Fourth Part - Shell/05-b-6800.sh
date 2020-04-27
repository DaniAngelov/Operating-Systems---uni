#!/bin/bash

#05-b-6800 soluion
#github.com/DaniAngelov

#Да се напише shell скрипт, който получава единствен аргумент директория и 
#отпечатва списък с всички файлове и директории в нея (без скритите).
#До името на всеки файл да седи размера му в байтове, а до името на всяка директория 
#да седи броят на елементите в нея (общ брой на файловете и директориите, без скритите).


if [ $# -ne 1 ]; then
        echo "Invalid number of arguments ! "
        exit 1
fi

if [ ! -d "${1}" ]; then
        echo "Argument not a directory ! "
        exit 2
fi

DIRECTORY="${1}"

find "${DIRECTORY}" -type f | awk -F '/' '{print $NF}' | xargs wc -c 2>/dev/null | head -n -1 | awk -F ' ' '{print $2, "("$1" bytes)"}'

find "${DIRECTORY}" -maxdepth 1 -mindepth 1 -type d | while read dir; do
  printf "%-25.25s" "$dir"
  find "$dir" -type d |  ls -a | wc -l
   done | awk -F '/' '{print " "$NF" entries"}'

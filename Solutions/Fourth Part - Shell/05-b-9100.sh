#!/bin/bash

#05-b-9100
#github.com/DaniAngelov

#Опишете поредица от команди или напишете shell скрипт, които/който при известни две директории SOURCE и DESTINATION:
#-намира уникалните "разширения" на всички файлове, намиращи се някъде под SOURCE. (За простота приемаме, 
#че в имената на файловете може да се среща символът точка '.' максимум веднъж.)
#- за всяко "разширение" създава по една поддиректория на DESTINATION със същото име
#- разпределя спрямо "разширението" всички файлове от SOURCE в съответните поддиректории в DESTINATION

if [ $# -ne 2 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

if [ ! -d "${1}" ] || [ ! -d "${2}" ]; then
        echo "Not both arguments are directories ! "
        exit 2
fi

SOURCE="${1}"
DESTINATION="${2}"

EXTENSION=$(find "${SOURCE}" -type f | rev | cut -d '.' -f1 |  tr '[:upper:]' '[:lower:]' | sort | uniq -c | rev | grep "^[^/]")

while read i;do
        mkdir "${i}" "${DESTINATION}"
        mv $(find "${SOURCE}" -type f -printf "%f \n" 2>/dev/null | grep "${i}") "${i}"                                                                                                                           
        done <<<$(echo "${EXTENSION}" | awk -F ' ' '{print $1}')
                                                          

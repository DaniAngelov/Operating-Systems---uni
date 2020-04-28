#!/bin/bash

#05-b-4600
#github.com/DaniAngelov

#Да се напише shell скрипт, който приема произволен брой аргументи - имена на файлове.
#Скриптът да прочита от стандартния вход символен низ и за всеки от зададените файлове
#извежда по подходящ начин на стандартния изход броя на редовете, които съдържат низа.

#NB! Низът може да съдържа интервал.

if [ $# -eq 0 ]; then
        echo "Invalid number of arguments!"
        exit 1
fi

read -p "Enter your string: " VAR


for i in $@; do

        if [ ! -f "${i}" ]; then
               echo "Please enter a file !"                                                                                             
               exit 2                                                                                                         
        fi                                                                                                                                                                                                                                              
        if [ ! -r "${i}" ]; then
                echo "Please enter a readable file !"                                                                                  
                exit 3                                                                                                         
        fi                                                                                                                                                                                                                                              
                COUNTS=$(cat "${i}" | grep -i "${VAR}" | wc -l)
        echo "The string is matched on "${COUNTS}" lines ! i"
done

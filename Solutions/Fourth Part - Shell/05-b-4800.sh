#!/bin/bash     

#github.com/DaniAngelov
#-- 05-b-4800
#Да се напише shell скрипт, който приема файл и директория. Скриптът проверява в подадената директория и нейните под-директории 
#дали съществува копие на подадения файл и отпечатва имената на намерените копия, ако съществуват такива.

#NB! Под 'копие' разбираме файл със същото съдържание.

if [ $# -ne 2 ]; then                                                                                                           
echo "Invalid number of arguments! "                                                                                    
exit 1                                                                                                          
fi                       

if [ ! -f "${1}" ] || [ ! -d "${2}" ]; then
        echo "Wrong Input! Parameters(file,directory)!"
        exit 2
        
elif [ ! -r "${1}" ] || [ ! -r "${2}" ]; then
        echo "Files not readable ! "
        exit 3
fi

FILE="${1}"
DIRECTORY="${2}"

find "${DIRECTORY}" | xargs diff -rsq --from-file "${FILE}" 2>/dev/null |   grep 'identical' | cut -d ' ' -f4

#!/bin/bash  


#05-b-4200 soluion
#github.com/DaniAngelov

#Да се напише shell скрипт, който получава произволен брой аргументи файлове, които изтрива.
#Ако бъде подадена празна директория, тя бива изтрита. Ако подадения файл е директория с поне 1 файл, тя не се изтрива.
#За всеки изтрит файл (директория) скриптът добавя ред във log файл с подходящо съобщение.

if [ $# -lt 1 ]; then
        echo "Invalid number of arguments"
        exit 1
fi                                                                                                                                                                                                                                                                                                                                                                                                                                    
if [ ! -d "${1}" ] || [ ! -f "${2}" ]; then
       echo "Not a file or directory! "                                                                                                                                                                                   
       exit 2                                                                                                                                                                                                   
       fi                                                                                                                                                                                                                 
for i in "$@"; do
        if [ -f "${i}" ]; then
                echo "Removed file "${i}" " >> log.txt                                                                                                                                                                             
                rm "${i}"
        fi

        if [ -d "${i}" ]; then
                DIRECTORY=$(find "${i}" -type f | wc -l)
                if [ "${DIRECTORY}" -eq 0 ]; then
                        echo "Removed empty directroy "${DIRECTORY}" " >> log.txt
                        rm -r "${DIRECTORY}"
                fi
        fi

done  

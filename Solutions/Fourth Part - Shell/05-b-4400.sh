#!/bin/bash

#05-b-4200 soluion
#github.com/DaniAngelov

#Напишете shell script, който да приема параметър име на директория, от която взимаме файлове,
#и опционално експлицитно име на директория, в която ще копираме файлове. Скриптът да копира файловете със съдържание,
#променено преди по-малко от 45 мин, от първата директория във втората директория. Ако втората директория не е подадена по име, 
#нека да получи такова от днешната дата във формат, който ви е удобен. При желание новосъздадената директория да се архивира.




if [ $# -lt 1 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

if [ ! -d "${1}" ]; then
        echo "First argument not a directory! "
        exit 2
fi

FIRST_DIRECTORY="${1}"

if [ $# -eq 2 ]; then
        if [ ! -d "${2}" ]; then
                echo "Second argument not a directory! "
        else
                SECOND_DIRECTORY="${2}"
        fi
fi

if [ $# -eq 1 ]; then
        DEFAULT="$(date +"%Y %m %d %R" | sed  "s/[ \:]/-/g")"
        mkdir "${DEFAULT}"
        SECOND_DIRECTORY="${DEFAULT}"
fi

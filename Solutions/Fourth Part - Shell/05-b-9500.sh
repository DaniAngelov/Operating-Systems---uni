#!/bin/bash

#05-b-9500
#github.com/DaniAngelov

#(Цветно принтиране) Напишете shell script color_print, който взима два параметъра.

#Първият може да е измежду "-r", "-g" "-b", а вторият е произволен string.
#На командата "echo" може да се подаде код на цвят, който ще оцвети текста в определения цвят.
#В зависимост от първия аргумент, изпринтете втория аргумен в определения цвят:

#"-r" е червено. Кодът на червеното е '\033[0;31m' (echo -e "\033[0;31m This is red")
#"-g" е зелено. Кодът на зеленото е '\033[0;32m' (echo -e "\033[0;32m This is green")
#"-b" е синьо. Кодът на синьото е '\033[0;34m' (echo -e "\033[0;34m This is blue")
#Ако е подадена друга буква изпишете "Unknown colour", а ако изобщо не е подаден аргумент за цвят, просто изпишете текста.

Hint:

В края на скрипта си напишете:
echo '\033[0m'
,за да не се прецакат цветовете на терминала. Това е цветът на "няма цвят".


if [ $# -lt 1 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

if [ $# -eq 1 ];then
        STRING="${1}"
else
        COLOUR="${1}"
        STRING="${2}"
fi

if [ ! -z "${COLOUR}" ];then

        if [ "${COLOUR}" == "-r" ]; then
                echo -e "\033[0;31m "${STRING}" "
        elif [ "${COLOUR}" == "-b" ]; then
                echo -e "\033[0;34m "${STRING}""
        elif [ "${COLOUR}" == "-g" ]; then
                echo -e "\033[0;32m "${STRING}""
        else
                echo -e "Unknown colour! "
        fi
else
        echo "${STRING}"
fi

echo '\033[0m'

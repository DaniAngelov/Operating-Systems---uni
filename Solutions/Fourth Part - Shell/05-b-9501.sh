#!/bin/bash

#05-b-9501
#github.com/DaniAngelov

#Този път програмата ви ще приема само един параметър, който е измежду ("-r", "-b", "-g", "-x").
#Напишете shell script, който приема редовете от stdin и ги изпринтва всеки ред с редуващ се цвят.
#Цветовете вървят RED-GREEN-BLUE и цветът на първия ред се определя от аргумента.
# Ако е подаден аргумент "-x", то не трябва да променяте цветовете в терминала (т.е., все едно сте извикали командата cat).

#Hint: Не забравяйте да връщате цветовете в терминала.

if [ $# -ne 1 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

COLOR="${1}"

while true; do
if [ "${COLOR}" == "-r" ];then
        read -p "Enter a message: " MESSAGE
        echo -e "\033[0;31m "${MESSAGE}""
        read -p "Enter a message: " MESSAGE
        echo -e "\033[0;32m "${MESSAGE}""
        read -p "Enter a message: " MESSAGE
        echo -e "\033[0;34m "${MESSAGE}""
elif [ "${COLOR}" == "-g" ]; then
        read -p "Enter a message: " MESSAGE
        echo -e "\033[0;32m "${MESSAGE}""
        read -p "Enter a message: " MESSAGE
        echo -e "\033[0;34m "${MESSAGE}""
        read -p "Enter a message: " MESSAGE
        echo -e "\033[0;31m "${MESSAGE}""
elif [ "${COLOR}" == "-b" ]; then
        read -p "Enter a message: " MESSAGE
        echo -e "\033[0;34m "${MESSAGE}""
        read -p "Enter a message: " MESSAGE
        echo -e "\033[0;31m "${MESSAGE}""
        read -p "Enter a message: " MESSAGE
        echo -e "\033[0;32m "${MESSAGE}""
elif [ "${COLOR}" == "-x" ]; then
        read -p "Enter a message: " MESSAGE
        echo -e "${MESSGE}"
else
        echo "Invalid colour! "
        exit 2
fi

done
echo '\033[0m'1

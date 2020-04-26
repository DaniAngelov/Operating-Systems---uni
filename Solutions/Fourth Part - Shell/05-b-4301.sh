#!/bin/bash

#05-b-4200 soluion
#github.com/DaniAngelov

#Имате компилируем (a.k.a няма синтактични грешки) source file 
#на езика C. Напишете shell script, който да покaзва
#колко е дълбоко най-дълбокото nest-ване (влагане).

if [ $# -ne 1 ];then
        echo "Invalid number of parameters"
fi

PARENTHESES="$(cat "${1}" | sed "s/[^{}]//g" | tr -d "\n " | sed "s/}{//g")"
RESULT=$(("${#PARENTHESES}"/2))
echo "The deepest nesting is "${RESULT}" levels"

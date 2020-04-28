#!/bin/bash

#05-b-7550
#github.com/DaniAngelov

#Да се напише shell скрипт, който приема параметър - име на потребител. 
#Скриптът да прекратява изпълненито на всички текущо работещи процеси на дадения потребител, и да извежда колко са били те.

#NB! Може да тествате по същият начин като описаният в 05-b-4300


if [ $# -ne 1 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi

if [ ! $(ps -ef | grep "${1}") ]; then
      echo "This is not a valid user! "
        exit 2
fi

USER="${1}"

ps -ef | grep "${USER}" | tr '/t' ' ' | awk -F ' ' '{kill $2}'      

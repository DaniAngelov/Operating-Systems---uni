#!/bin/bash

#05-b-7800
#github.com/DaniAngelov

#Да се напише shell скрипт, който намира броя на изпълнимите файлове в PATH.
#Hint: Предполага се, че няма спейсове в имената на директориите
#Hint2: Ако все пак искаме да се справим с този случай, да се разгледа IFS променливата и констуркцията while read -d

VAR=$(echo $PATH | tr -s ':' '\n')
echo "$VAR"
COUNT=0

while read i;do
        FILES=$(find "$i" -type f -executable 2>/dev/null | wc -l)
        COUNT=$(( "${COUNT}" + "${FILES}"))
done<<<$(echo "${VAR}")
echo $COUNT

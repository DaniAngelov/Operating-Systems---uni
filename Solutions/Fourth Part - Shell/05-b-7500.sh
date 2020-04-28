#!/bin/bash

#05-b-4600
#github.com/DaniAngelov

#Напишете shell script guess, която си намисля число, което вие трябва да познате. 
#В зависимост от вашия отговор, програмата трябва да ви казва "надолу" или "нагоре", докато не познате числото.
#Когато го познаете, програмата да ви казва с колко опита сте успели.

#./guess (програмата си намисля 5)

#Guess? 22
#...smaller!
#Guess? 1
#...bigger!
#Guess? 4
#...bigger!
#Guess? 6
#...smaller!
#Guess? 5
#RIGHT! Guessed 5 in 5 tries!

#Hint: Един начин да направите рандъм число е с $(( (RANDOM % b) + a  )), което ще генерира число в интервала [a, b]. 
#Може да вземете a и b като параметри, но не забравяйте да направите проверката.

TRIES=0
UNKNOWN=$((RANDOM % 100))


read -p "Guess? " NUMBER

                                                                                                                                                                                                                   
while true; do

        if [ ! $(echo "${NUMBER}" | grep "[0-9]") ]; then
                echo "Please enter a number! "
                exit 1
        fi

        TRIES=$(( "${TRIES}" +1 ))

        if [ "${NUMBER}" -gt "${UNKNOWN}" ]; then
                echo "...smaller!"
        elif [ "${NUMBER}" -lt "${UNKNOWN}" ]; then
                echo "...bigger!"
        elif [ "${NUMBER}" -eq "${UNKNOWN}" ]; then
                echo "RIGHT! Guessed "${UNKNOWN}" in "${TRIES}" tries! "
                exit 0
        fi

        read -p "Guess? " NUMBER
done

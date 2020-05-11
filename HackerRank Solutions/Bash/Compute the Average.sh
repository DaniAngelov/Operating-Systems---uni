#!/bin/bash

#github.com/DaniAngelov

read N

COUNT=0
SUM=0

for i in $(seq 1 "${N}"); do
    read number 
    SUM=$((SUM + $number))
    COUNT=$((COUNT+1))
done


printf "%.*f" "3" "$(echo $SUM / $COUNT | bc -l)"

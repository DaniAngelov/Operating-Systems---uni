#!/bin/bash

#github.com/DaniAngelov

read a
read b
read c

if [ $(expr $a + $b) -gt $c ] || [ $(expr $b + $c) -gt $a ] \
 || [ $(expr $a + $c) -gt $b ];then
    if [ $a = $b ] && [ $a = $c ];then
        echo "EQUILATERAL"
    elif [ $a = $b ] || [ $a = $c ] || [ $b = $c ];then
        echo "ISOSCELES"
    else 
        echo "SCALENE"
    fi
fi

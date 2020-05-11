#!/bin/bash

#github.com/DaniAngelov

read A
read B

if [ $A -gt $B ]; then
    echo "X is greater than Y"
elif [ $A -eq $B ]; then
    echo "X is equal to Y"
else
    echo "X is less than Y"
fi

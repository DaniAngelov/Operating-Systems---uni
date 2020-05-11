#!/bin/bash

#github.com/DaniAngelov

read SYM

if [ $SYM = "y" ] || [ $SYM = 'Y' ]; then
    echo "YES"
elif [ $SYM = 'n' ] || [ $SYM = 'N' ]; then
    echo "NO" 
fi

#!/bin/bash

#github.com/DaniAngelov

for i in {1..100}
do
   if [ $(expr $i % 2) -eq 1 ];then
        echo $i
   fi
done

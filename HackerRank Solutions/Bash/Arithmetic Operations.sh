#!/bin/bash

#github.com/DaniAngelov

read input


 printf "%.*f" "3" "$(echo $input | bc -l)" 

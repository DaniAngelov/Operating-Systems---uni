#!/bin/bash

#Task18.sh
#github.com/DaniAngelov

if [ $# -ne 0 ]; then
        echo "INVALID NUMBER OF ARGUMENTS! "


        find /home/ -printf "%u %f %TY-%Tm-%Td-%TH-%TM\n" | tail -n 1 | awk -F ' ' '{print $1,$2}'  

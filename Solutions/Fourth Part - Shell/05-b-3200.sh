#!/bin/bash
#-- 05-b-3200
#Да се напише shell скрипт, който приканва потребителя да въведе пълното име на директория и
#извежда на стандартния изход подходящо съобщение за броя на всички файлове и всички директории в нея.

read -p "Enter directory: ( Pattern /directory ) " VAR

if [ ! -d "${VAR}" ];then
       echo "This is not a directory! Please enter a valid directory name! "
else
        echo "List of directories : " $(find "${VAR}" type -d -mindepth 1 2>/dev/null | wc -l)
        echo "List of files : " $(find "${VAR}" type -f -mindepth 1 2>/dev/null | wc -l)
fi

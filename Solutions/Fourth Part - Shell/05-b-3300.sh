
#!/bin/bash
#05-b-3300 solution   
#-- 05-b-3300
#Да се напише shell скрипт, който чете от стандартния вход имената на 3 файла,
#обединява редовете на първите два (man paste), 
#подрежда ги по азбучен ред и резултата записва в третия файл.,   

if [ $# -ne 3 ];then
        echo "Invalid number of arguments ! "
        exit 1
fi

FILE1="${1}"
FILE2="${2}"

if [ ! -r "${FILE1}" ] || [ ! -r "${FILE2}" ] ;then
        echo "it is NOT readible "
        exit 2
fi

paste "${FILE1}" "${FILE2}" | sort > "${3}"

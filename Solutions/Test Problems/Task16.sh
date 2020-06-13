
#!/bin/bash

#Task16.sh
#github.com/DaniAngelov


if [ $# -ne 3 ]; then
        echo "Invalid number of arguments"
        exit 1
fi

if [ ! -f "${1}" ]; then
        echo "First arg not a file"
        exit 2
fi

if [ -z "${2}" ] || [ -z "${3}" ]; then
        echo "Strings empty"
        exit 3
fi

FILE="${1}"
STR1=$(cat "${FILE}" | egrep "^$2=" | cut -d '=' -f2)
STR2=$(cat "${FILE}" | egrep "^$3=" | cut -d '=' -f2)

NEWSTR2=$(comm -13 <(echo "${STR1}" | tr -s ' ' | tr ' ' '\n' | sort) <(echo "${STR2}" | tr -s ' ' | tr ' ' '\n' | sort) | xargs)

sed -i -e "s/^$3=$STR2/$3=$NEWSTR2/" "${FILE}"

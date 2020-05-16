
#!/bin/bash

#Task16.sh
#github.com/DaniAngelov


if [ $# -ne 3 ]; then
        echo "Invalid number of arguments! "                                                                          
        exit 1
fi

FILE="${1}"
STRING1="${2}"
STRING2="${3}"

if [ ! -f "${FILE}" ] ; then
        echo "Not a file! "
        exit 2
elif [ ! -r "${FILE}" ] ; then
        echo "Not readable! "
        exit 3
fi


if [ -z "${STRING1}" ]; then
        echo "There is a key with length 0 "
        exit 4
fi

VAL1=$(egrep "^${STRING1}=" "${FILE}" | awk -F '=' '{print $2}' | tr -s ' ' | tr ' ' '\n' | sort )
VAL2=$(egrep "^${STRING2}=" "${FILE}" | awk -F '=' '{print $2}' | tr -s ' ' | tr ' ' '\n' | sort )

#echo "$VAL1" | tr -s ' ' | tr ' ' '\n' | sort
#echo "-------"
#echo "$VAL2" | tr -s ' ' | tr ' ' '\n' | sort

TEMP=$(comm -13 <(echo "$VAL1" | tr -s ' ' | tr ' ' '\n' | sort) <(echo "$VAL2" | tr -s ' ' | tr ' ' '\n' | sort) | xargs)

sed -i -e "s/^$3=$STRING2/$3=$TEMP/" $FILE

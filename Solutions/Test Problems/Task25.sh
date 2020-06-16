  
#!/bin/bash

#Task25.sh
#github.com/DaniAngelov


if [ $# -ne 1 ] ;then
        echo "Invalid args"
        exit 1
fi

if [ ! -d "${1}" ]; then
        echo "First arg not a dir"
        exit 2
fi

DIR="${1}"

MESSAGES=$(find "${DIR}" -maxdepth 4 -mindepth 4 -type f)

OLDIFS=$IFS
IFS='/'
MAX=0
USR=""

TEMP=$(mktemp)

while read friend;do

        LINES="$(find "${DIR}" -mindepth 4 -maxdepth 4 -type f | grep "$friend" \
                | xargs -I {} wc -l {} | awk -F ' ' '{print $1}' | awk '{sum += $1}END{print sum}')"
        echo "$LINES --> $friend" >> "${TEMP}"

done < <(echo "$MESSAGES" | cut -d '/' -f4 | sort | uniq)

IFS=$OLDIFS

cat "${TEMP}" | sort -n -k1 | tail -n 1

rm -- "${TEMP}"

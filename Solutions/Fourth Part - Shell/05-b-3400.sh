
#!/bin/bash
# Да се напише shell скрипт, който чете от стандартния вход име 
# на файл и символен низ, проверява дали низа се съдържа във файла 
# и извежда на стандартния изход кода на завършване на командата
# с която сте проверили наличието на низа.

if [ $# -ne 2 ];then
        echo "Invalid number of arguments"
fi

FILE_NAME="${1}"
SEARCHED="${2}"

if [ ! -f "${FILE_NAME}" ];then
       echo "First argument is not a file"
       exit 1
fi

grep "${SEARCHED}" "${FILE_NAME}"
echo $?

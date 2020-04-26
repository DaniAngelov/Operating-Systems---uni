
#!/bin/bash
# 05-b-2800 solution

if [ $# -ne 1 ]; then
        echo "Invalid number of arguments"
        exit 1
elif [[ "${1}" =~ [[:alnum:]] ]]; then
        echo "Valid entry!"
        exit 0
else
        echo "Wrong entry!"
        exit 2
fi

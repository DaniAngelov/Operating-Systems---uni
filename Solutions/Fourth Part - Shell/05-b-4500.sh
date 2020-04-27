#!/bin/bash

#github.com/DaniAngelov
# 05-b-4500

#Да се напише shell скрипт, който получава при стартиране като параметър в командния ред идентификатор на потребител. 
#Скриптът периодично (sleep(1)) да проверява дали потребителят е log-нат, и ако да - да прекратява изпълнението си, 
#извеждайки на стандартния изход подходящо съобщение.



if [ $# -ne 1 ]; then
        echo "Invalid number of arguments!"
        exit 1
fi

USER_ID="${1}"

while true
do
        sleep 5
        if [ who | grep "${USER_ID}" ]; then                                                                                           echo "This user is logged in! "
                exit 0
        fi
done     

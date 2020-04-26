#!/bin/bash

#05-b-4301  
#github.com/DaniAngelov

#Напишете shell script, който автоматично да попълва файла указател от предната задача по подадени аргументи:
#име на файла указател, пълно име на човека (това, което очакваме да е в /etc/passwd) и избран за него nickname.
#Файлът указател нека да е във формат:
#<nickname, който лесно да запомните> <username в os-server>
#// може да сложите и друг delimiter вместо интервал

#Примерно извикване:
#./pupulate_address_book myAddressBook "Ben Dover" uncleBen

#Добавя към myAddressBook entry-то:
#uncleBen <username на Ben Dover в os-server>

#***Бонус: Ако има няколко съвпадения за въведеното име (напр. има 10 човека Ivan Petrov в /etc/passwd),
#всички те да се показват на потребителя, заедно с пореден номер >=1,
#след което той да може да въведе някой от номерата (или 0 ако не си хареса никого), и само избраният да бъде добавен към указателя.



 if [ $# -ne 3 ]; then
	echo "Invalid number of arguments! "                                                                                                                                                                                                                                                                                                                                                                                                            
        exit 1                                                                                                                                                                                                   
fi

if [ ! -w "${1}" ]; then
       echo "Wrong file - not writeable ! "
        exit 2
fi

FILE="${1}"
NAME="${2}"
NICK="${3}"

USERNAME=$(cat /home/passwd | grep "${NAME}" | cut -d ":" -f1)

if [ -z "${USERNAME}" ]; then
        echo "No user was found !"
        exit 3
fi

echo " "${NICK}" "${USERNAME}" " >> "${FILE}"

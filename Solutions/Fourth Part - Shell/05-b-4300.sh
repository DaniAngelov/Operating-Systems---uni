#!/bin/bash

#github.com/DaniAngelov
# 05-b-4300

#Напишете shell script, който по подаден като аргумент файл с map между <nickname> -> <реален username> и nickname, 
#ще ви улесни да изпращате съобщения на хората.
#
#Пример за файл указател:
#tinko s61966
#minko s881234
#ginko s62000
#dinko s77777
#
#Примерно извикване на програмата:
#./send_message myAddressBook dinko
#
#И вече може да изпращате съобщения на човека с username s77777
#
#NB! Можете да създавате нови потребители използвайки 'sudo useradd username'. 
#За да проверите дали се пращат съобщенията отворете 2 сесии към виртуалката ви, създайте новият потребител, 
#логнете се с него ( 'sudo su username' от едната сесия ) и от другата сесия пратете съобщението.

if [ $# -ne 2 ]; then
	echo "Invalid number of arguments! "
	exit 1
fi

if [ ! -r "${1}" ]; then
	echo "First argument not a file! "
	exit 2
fi

if [ ! id -u "${2}" ]; then
	echo "No such user! "
	exit 3
fi

FILE="${1}"
USER="${2}"

RECEIVER=$(cat "${FILE}" | grep "${USER}" | cut -d ' ' -f1-2 )
write "${RECEIVER}" <<< "HEY!!! \n"

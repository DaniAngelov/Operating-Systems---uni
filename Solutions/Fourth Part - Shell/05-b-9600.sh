#!/bin/bash

#05-b-9600
#github.com/DaniAngelov

#Да се напише shell скрипт, който получава произволен брой аргументи файлове, които изтрива.
#Ако бъде подадена празна директория, тя бива изтрита. Ако подадения файл е директория с поне 1 файл, тя не се изтрива.

#Да се дефинира променлива BACKUP_DIR (или друго име), в която:
#- изтритите файлове се компресират и запазват
#- изтритите директории се архивират, комприсират и запазват
#- имената на файловете е "filename_yyyy-mm-dd-HH-MM-SS.{gz,tgz}", където filename е оригиналното име на файла (директорията)
#преди да бъде изтрит

#а) Добавете параметър -r на скрипта, който позволява да се изтриват непразни директории рекурсивно и съответно да се запазят в BACKUP_DIR

if [ $# -lt 1 ]; then
        echo "Invalid number of arguments! "
        exit 1
fi
                                                                                                                        
for i in "$@"
do
        if [ "${i}" == '-r' ];then

        elif [ -d "${i}" ]; then
                if [ $(find "${i}" -type f | wc -l) -eq 0 ]; then

                        tar -zcf "${BACKUP_DIR}/${name}/{time}.tgz" "${i}"
                        rm -r  "$i"
                else

                fi

        elif [ -f "${i}" ]; then
                CURRTIME=$(date + "%Y-%m-%d-%H-%M-%S")
                gzip -f "${i}" > "${BACKUP_DIR}/${name}/${time}.gz"
        fi
done
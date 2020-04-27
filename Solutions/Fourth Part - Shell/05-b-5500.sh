#!/bin/bash

#github.com/DaniAngelov
#-- 05-b-5500

#Да се напише shell script, който генерира HTML таблица съдържаща описание на потребителите във виртуалката ви. Таблицата трябва да има:
#- заглавен ред с имената нa колоните
#- колони за username, group, login shell, GECKO field (man 5 passwd)

#Пример:
#$ ./passwd-to-html.sh > table.html
#$ cat table.html
#<table>
#  <tr>
#    <th>Username</th>
#    <th>group</th>
#    <th>login shell</th>
#    <th>GECKO</th>
#  </tr>
#  <tr>
#    <td>root</td>
#    <td>root</td>
#    <td>/bin/bash</td>
#    <td>GECKO here</td>
#  </tr>
#  <tr>
#    <td>ubuntu</td>
#    <td>ubuntu</td>
#    <td>/bin/dash</td>
#    <td>GECKO 2</td>
#  </tr>
#</table>

cat /home/passwd | awk -F ':' 'BEGIN{printf "<table> \n\t <tr> \n\t\t <th>Username</th> /n/t/t 
<th>group</th> \n\t\t <th>login shell</th> \n\t\t <th>GECKO</th> \n\t </tr> \n"}
{printf "\t <tr> \n\t\t <td>"$1"</td> \n\t\t <td>"$2"</td> \n\t\t <td>"$6"</td> \n\t\t <td>"$5"</td> \n\t </tr> \n"} 
END{printf "</table> \n"}'

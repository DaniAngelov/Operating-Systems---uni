--------------------------------------------------------
### Test Problems

1.

#### `cat philip-j-fry.txt | egrep '[02468]' | egrep -v '[a-w]' | wc -l`

2.

#### `cat test.txt | egrep -n '-' | awk -F '.... г. -' '{print $1,$2}' | sort -k2`


5.

#### `find . -user "$(whoami)" 2> /dev/null | wc -l ` 

6.

#### `find . -type f -printf "%s %p \n" | sort -n | tail -n 1`

7.

#### ` grep "$(grep "$(cat passwd | egrep -i 'inf' `
#### `| awk -F ':' '{print $5}' | awk -F ',' '{print $1}' `
#### `| grep 'a$')" passwd | cut -f1 -d ':'  | cut -c 3-4)" passwd`
#### `| egrep -i 'inf' | grep -o '50' | wc -l`

8.

#### `find . -type f -printf "%s %p \n"  | grep '^0' `		//rm 
#### `find . -type f -printf '%n %p \n' | sort  | tail -n 5	`	//rm

9.
#### ` find . -type f -name '* *' -printf '%T@ %p \n' | sort | tail -n 1  `

10.

#### ` cat passwd  | awk -F ':' '{print $5,$6,$1}' | `
#### ` awk -F ' ' '{print $NF,$0}' | sort -n -k1 | cut -f2- -d ' '  `

11.
#### `find /home -maxdepth 1 -printf "%p %C@ \n" | `
#### `awk '{$2 >  1551168000 && $2 < 1551176100}' | ` 
#### `cut  -f 1,5 -d ':' | cut -c 2- | tr ':' '\t' ` 

12.

#### ` echo "Дълбочината на търсения файл е $(find . -inum  "$(find . -type f  -printf "%T@ %i %p \n" | `
#### ` awk '{print $2}' | tail -n 1)" | grep -o '/' | uniq -c )" `

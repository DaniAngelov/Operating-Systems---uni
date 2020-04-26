-------------------------------------------------
PROCESSES:

-- 04-a-5000

#### `ps -elf | sort -k12 | tail -n 10`

-- 04-a-6000

#### `ps -eo vsize,pid,cmd | sort -rn | head -n 1` 

-- 04-a-6300

#### `ps -eo pid,etime,comm  | sort -k2 | tail -n 1 | awk '{print $3}' `

-- 04-b-5000 

#### `top -u root | awk '{print $11}' `

-- 04-b-6100

 #### `ps -elf | grep  'vim' |  awk '{if($(wc -l) > 2) print $15}' `

-- 04-b-6200

#### `top | grep "$(ps -e -o user | uniq | tail -n 1)" `

-- 04-b-7000
#### `ps -o drs,cmd | tail -n -3 | sort -k1 |
#### awk 'BEGIN{counter=0} {if($2 == "root") counter+= $1} 
#### END{print count}'`          

-- 04-b-8000

#### `ps -o pid,tty,cmd | tail -n 3 | awk '{if($2 == " ") print $3}' 
#### | sort -u -k | uniq  `  


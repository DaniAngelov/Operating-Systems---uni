//  github.com/DaniAngelov

/*
        Task 8
       Напишете програма, която приема точно 2 аргумента. Първият може да бъде само --min, --max или --print
       (вижте man 3 strcmp). Вторият аргумент е двоичен файл, в който има записани цели неотрицателни двубайтови числа 
       (uint16_t - вижте man stdint.h). Ако първият аргумент е:

--min - програмата отпечатва кое е най-малкото число в двоичния файл.
--max - програмата отпечатва кое е най-голямото число в двоичния файл.
--print - програмата отпечатва на нов ред всяко число.
Използвайте двоичния файл binary/dump или генерирайте сами такъв (правилно подравнен).
*/

<==

/*
        Task 9
       Модифицирайте предната програма, така че да намерите най-големия байт.
*/

#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdint.h>

#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char** argv)
{
        if( argc != 2)
        {
                errx(1,"Expected argument! ");
        }

        int fd = open(argv[1], O_RDWR);
        if ( fd == -1)
        {
                err(2, "Error while opening %s ! ",argv[1]);
        }

  uint8_t max;
        ssize_t read_size;
        uint8_t c;

        while ( ( read_size = read ( fd,&c, 1))  == 1)
        {
                if ( c > max)
                {
                        max = c;
                }
        }
        printf("%x\n",max);
        close(fd);
        exit(0);
}

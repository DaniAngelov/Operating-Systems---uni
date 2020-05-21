//  github.com/DaniAngelov

/*
        Task 8
     Напишете програма, която приема точно 2 аргумента. Първият може да бъде само --min, --max или --print (вижте man 3 strcmp).
     Вторият аргумент е двоичен файл, в който има записани цели неотрицателни двубайтови числа (uint16_t - вижте man stdint.h). 
     Ако първият аргумент е:

--min - програмата отпечатва кое е най-малкото число в двоичния файл.
--max - програмата отпечатва кое е най-голямото число в двоичния файл.
--print - програмата отпечатва на нов ред всяко число.
Използвайте двоичния файл binary/dump или генерирайте сами такъв (правилно подравнен).
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

        if ( argc != 3)
        {
                errx(1,"Invalid number of arguments! ");
        }

        if ( strcmp(argv[1], "--max") != 0 && strcmp(argv[1], "--min") != 0 &&  strcmp(argv[1], "--print") != 0)
        {
                errx(2 , "Wrong argument %s ! ",argv[1]);
        }

  int fd = open(argv[2], O_CREAT | O_RDONLY);
        if ( fd == -1)
        {
                err(3, "Error while opening file %s !",argv[2]);
        }

        struct stat st;

        if( stat(argv[2],&st) == -1)
        {

                err( 4, "Error while using stat with file %s !",argv[2]);
        }

        if ( st.st_size == 0)
        {
                err(5, "Empty file ! ");
                exit(0);
        }

        uint16_t num;
        int16_t* bytes = malloc(st.st_size);
        ssize_t read_size;
        int counter = 0;

  while ( (read_size = read ( fd,&num, sizeof(uint16_t))) > 0)
        {
                if( read_size > (ssize_t)(sizeof(uint16_t)))
                {
                        errx(6,"Error while reading file %s ! ",argv[2]);
                }
                bytes[counter] = num;
                counter++;
        }

        uint16_t max = 0;
        uint16_t min = 0;


for(int i = 0;i < counter;i++)
        {
                if ( strcmp(argv[1], "--print") == 0)
                {
                        printf( "%x\n", bytes[i]);
                }
                else
                {
                        if ( bytes[i] > max )
                        {
                                max = bytes[i];
                        }
                        if ( bytes[i] < min)
                        {
                                min = bytes[i];
                        }
                }
        }

  if ( strcmp(argv[1], "--max") == 0)
                {
                        printf( "%x\n", max);
                }
                if ( strcmp(argv[1], "--min") == 0)
                {
                        printf( "%x\n", min);
                }


                free(bytes);
                close(fd);
                exit(0);

}

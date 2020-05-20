
//  github.com/DaniAngelov

/*
        Task 6
        Реализирайте команда cp, работеща с произволен брой подадени входни параметри.
*/

#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(int argc,char** argv)
{
        if( argc == 1)
        {
                errx(1,"Invalid number of arguments!");
        }


        for(int i =1 ;i < argc - 1;i++)
        {
                int fd1 = open(argv[i],O_RDWR);

               if ( fd1 == -1)
               {
                err(2, "Error while opening file %s ! ", argv[i]);
               }
            char* resdir = malloc( strlen(argv[argc - 1]) + strlen(argv[i]));
               strcpy(resdir,argv[argc -1]);
                strcat(resdir,argv[i]);

        int fd2 = open(resdir,O_RDWR | O_CREAT);
        if ( fd2 == -1)
        {
                close(fd1);
                err(3, "Error while opening file %s !",argv[argc - 1]);

        }

        ssize_t read_size;
        char c[4096];
                while( (read_size = read(fd1,&c,sizeof(c) ) ) > 0)
                {
                        if ( write( fd2,&c,read_size) != read_size)
                        {
                                err(4, "Error while writing in file %s !",argv[argc-1]);
                                close(fd1);
                                close(fd2);
                        }
                }


        }

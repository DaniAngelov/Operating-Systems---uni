//  github.com/DaniAngelov

/*
     Task 3
     Реализирайте команда swap, разменяща съдържанието на два файла, подадени като входни параметри.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>

int main(int argc,char** argv)
{

        int fd1;
        int fd2;
        int fd3;

        if ( argc != 3)
        {
                errx(1,"Invalid number of arguments! ");
        }

        fd1 = open ( argv[1], O_RDWR);
        if ( fd1 == -1)
        {
                err(2, "Error while opening file 1");
        }

        fd2 = open ( argv[2], O_RDWR);

        if ( fd2 == -1)
                {
                close(fd1);
                err(3, "Error while opening file 2! ");
        }

        fd3 = open ( "Temp_File" , O_CREAT | O_TRUNC | O_RDWR | S_IRUSR | S_IWUSR);
        if ( fd3 == -1 )
        {
                close(fd1);
                close(fd2);
                err(4, "Error while opening file 3! ");
        }

        char c[4096];
        ssize_t read_size;

        while( (read_size = read(fd1,&c,sizeof(c))) > 0)
        {
                if( write(fd3,&c,read_size) != read_size)
                {
                        close(fd1);
                        close(fd2);
                        close(fd3);
                        err(5, "Error while writing! ");
                }
        }
        
        lseek(fd1,0,SEEK_SET);

        while ( ( read_size = read(fd2, &c , sizeof(c))) > 0)
        {
                if( write(fd1,&c,read_size) != read_size)
                {
                        close(fd1);
                        close(fd2);
                        close(fd3);
                        err(5, "Error while writing! ");
                }
        }

        lseek(fd2,0,SEEK_SET);
        lseek(fd3,0,SEEK_SET);
        
               while ( (read_size = read(fd3, &c , sizeof(c))) > 0)
        {
                if ( write (fd2,&c,read_size) != read_size)
                {
                        close(fd1);
                        close(fd2);
                        close(fd3);
                        err(5, "Error while writing! ");
                }
        }

        close(fd1);
        close(fd2);
        close(fd3);
        exit(0);

}


//  github.com/DaniAngelov

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



        if (argc != 3)
        {
                errx(1,"Invalid number of arguments!");
        }
        if ( (fd1 = open(argv[1] , O_RDONLY)) == -1)
        {
                err(2, "File is not readable!");
        }
        if ( (fd2 = open(argv[2], O_RDONLY | O_WRONLY | O_CREAT | S_IRUSR | S_IWUSR | O_TRUNC) == -1))
        {
                err(3, "Error while opening %s \n",argv[2]);
        }
        
        char c[4096];
        ssize_t read_size;

        while ( (read_size = read(fd1,&c, sizeof(c)))>0)
        {
                if(write(fd2,&c,read_size) != read_size)
                {
                        close(fd1);
                        close(fd2);
                        errx(4,"error while reading");

                }
        }

        close(fd1);
        close(fd2);
        exit(0);
}

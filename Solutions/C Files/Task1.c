
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
        char c;
        int count = 0;

        if( argc != 2)
        {
                errx(1, "Invalid number of arguments");
        }

        if( (fd1 = open(argv[1],O_RDONLY)) == -1)
        {
                err(2, "File is not readable! ");
        }

        while (read(fd1,&c,1) )
        {
                if( c == '\n' )
                {
                        count = count + 1;
                }

                write(1,&c,1);
                if(count == 10)
                {
                        break;
                }
        }

        close(fd1);
        exit(0);

}


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
        int lines = 0;
        int words = 0;
        int chars = 0;
        char c;

        if (argc != 2)
        {
                errx(1,"Invalid number of arguments! ");
        }

        if( ( fd1 = open( argv[1], O_RDONLY)) == -1)
        {
                err(2, "File not readable! ");
        }

          while ( read(fd1,&c,1))
        {
                if ( c == '\n')
                {
                        lines++;
                        words++;
                }
                if ( c == ' ')
                {
                        words++;
                }
                chars++;
        }

        printf("The file has %d lines, %d words and %d characters! ",lines,words,chars);
}

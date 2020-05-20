
//  github.com/DaniAngelov

/*
        Task 7
        Koпирайте файл /etc/passwd в текущата ви работна директория и променете разделителят на копирания файл от ":", на "?"
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>

int main()
{


        int fd1 = open( "/home/passwd", O_RDONLY);

        if ( fd1 == -1 )
        {
                err(2,"File could not open! ");
        }

        char* newFile = "./passwd.txt";

        int fd2 = open( newFile, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

        if ( fd2 == -1 )
        {
                err( 3, " Error while opening file %s !",newFile);
                close(fd1);
        }

        char c;

        while( read(fd1,&c,1)  > 0)
        {
                if ( c == ':')
                {
                        c = '?';
                }

                if( write(fd2,&c,1) != 1)
                {
                        err(5,"Error while writing! ");
                        close(fd1);
                        close(fd2);
                }

        }

        close(fd1);
        close(fd2);
	exit (0);

}

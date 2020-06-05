//  github.com/DaniAngelov

/*
        Task 9
       Да се напише програма на C, която която създава файл в
       екущата директория и генерира два процесa, които записват низовете foo и bar в създадения файл.
       Програмата не гарантира последователното записване на низове.
       Променете програмата така, че да записва низовете последователно, като първия е foo.
*/

#include <stdio.h>
#include <sys/wait.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
        int fd;
        int status;

        fd = open("temp",O_CREAT | O_RDWR | O_TRUNC , S_IWUSR | S_IRUSR);

        if( fd == -1)
        {
                err(1, "Failed open");
        }

        pid_t pid1 = fork();

        if ( pid1 > 0)
        {
                wait(&status);
                if(write(fd,"bar\n",4) < 0)
                {

                        int olderrno = errno;
                        close(fd);
                        errno = olderrno;
                        err(2, "Failed writing");
                }
        }
        else if( pid1 == 0)
        {
                if ( write(fd,"foo\n",4) < 0)
                {
                        int olderrno = errno;
                        close(fd);
                        errno = olderrno;
                        err(2, "Failed writing");
                }
        }

        else
        {

                        int olderrno = errno;
                        close(fd);
                        errno = olderrno;
                        err(3, "Failed fork");
        }




        exit(0);

}

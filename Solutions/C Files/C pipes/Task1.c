//  github.com/DaniAngelov

/*
        Task 1
        Да се напише програма на C, която приема аргумент - име на файл. Програмата да:
        - записва във файла 'fo'
        - създава child процес, който записва 'bar\n'
        - parent-а, след като изчака child процеса, записва 'o\n'
*/

#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
int main(int argc,char** argv)
{
        if(argc != 2)
        {
                errx(1, "Invalid number of arguments!");
        }

        int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC , S_IWUSR | S_IRUSR);
        if( fd == -1)
        {
                err(2, "Failed while open %s ! ",argv[1]);

        }

        const char* str1 = "foo\n";
        const char* str2 = "bar\n";

        if( write(fd,str1,2) != 2)
        {
                int olderrno = errno;
                close(fd);
                errno = olderrno;
                err(3, "Failed writing!");
        }
        int pid = fork();

        if( pid == -1)
        {

                int olderrno = errno;
                close(fd);
                errno = olderrno;
                err(4, "Failed fork!");
        }

        else if( pid == 0)
        {
                if(write(fd,str2,4) != 4)
                {

                int olderrno = errno;
                close(fd);
                errno = olderrno;
                err(3, "Failed writing!");
                }
                exit(0);
        }

        else
        {
                int status;
                const pid_t wait_code = wait(&status);

                if(wait_code == -1)
                {

                int olderrno = errno;
                close(fd);
                errno = olderrno;
                err(4, "Failed wait code!");
                }
                if(!WIFEXITED(status))
                {
                        err(5, "Child did not terminate properly!");
                }
                if(WEXITSTATUS(status) != 0)
                {
                        err(6, "Child exit status not 0 file should be closed!");
                }
                if(write(fd,str1 + 2,2) !=2)
                {

                int olderrno = errno;
                close(fd);
                errno = olderrno;
                err(7, "Failed while writing!");
                }
        }

        close(fd);
        exit(0);
}

//  github.com/DaniAngelov

/*
        Task 8
       Да се напише програма на С, която получава като параметър име на файл. Създава процес син,
       който записва стринга foobar във файла (ако не съществува, го създава, в противен случай го занулява),
       след което процеса родител прочита записаното във файла съдържание и го извежда на стандартния изход,
       добавяйки по един интервал между всеки два символа.
*/

#include <err.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdint.h>

int main(int argc,char** argv)
{
        if(argc != 2)
        {
                errx(1,"Invalid number of arguments!");
        }

        int status;
        int fd;
        int pid = fork();
        char c;
        int counter = 0;

                fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC , S_IWUSR | S_IRUSR);
                if( fd < 0)
                {
                        err(3, "Error while opening %s",argv[1]);
                }

        if(pid == 0)
        {
                if( write(fd , "foobar",6) < 0 )
                {
                        int olderrno = errno;
                        close(fd);
                        errno = olderrno;
                        err(4, "Failed while writing in %s",argv[1]);
                }
        }
        else if(pid >0)
        {

                wait(&status);
                while(read(fd,&c,1) >0)
                {
                        counter++;
                        if(write(1,&c,1) == -1)
                        {
                                err(4, "Failed while writing");

                        }
                        if(counter % 2 == 0)
                        {
                                write(1," ",1);
                        }

                }
        }
        else
        {
                err(2, "Failed while fork");
        }
        exit(0);


}

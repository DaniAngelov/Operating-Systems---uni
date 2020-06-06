//  github.com/DaniAngelov

/*
        Task 3
       Напишете програма на C, която демонстрира употребата на dup/dup2 между parent и child процеси.
       Parent-ът трябва да изпраща стринга, получен като първи аргумент на командния ред към child-а, където
       той да може да се чете от stdin. Child процесът да изпълняваwc -c.
*/

#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char** argv)
{
        if(argc != 2)
        {
                errx(1,"Invalid number of arguments!");
        }

        int pf[2];
        if( pipe(pf) == -1)
        {
                errx(2, "Failed pipe");
        }

        int status;
        pid_t pid = fork();

        if(pid == -1)
        {
                err(3, "Failed fork");
        }

        else if(pid == 0)
        {
                close(pf[1]);
                dup2(pf[0],0);

                        if ( execlp("wc", "wc","-c",(char*) NULL) == -1)
                        {
                                err(4, "Failed exec");
                        }
        }

        close(pf[0]);
        write(pf[1],argv[1],strlen(argv[1]));
        close(pf[1]);
        wait(&status);
        exit(0);

}

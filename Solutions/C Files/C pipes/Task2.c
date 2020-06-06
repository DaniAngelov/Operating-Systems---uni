//  github.com/DaniAngelov

/*
        Task 2
        Напишете програма на C, която демонстрира комуникация през pipe между parent и child процеси.
        Parent-ът трябва да изпраща стринга, получен като първи аргумент на командния ред към child-а,
        който да го отпечатва на стандартния изход.
*/

#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc,char** argv)
{
        if(argc != 2 )
        {
                errx(1 , "Invalid number of arguments!");
        }

        int pf[2];

        if(pipe(pf) == -1)
        {
                errx(4, "Failed pipe");
        }

        int status;
        pid_t pid = fork();

        if( pid == -1)
        {
                err(2, "Failed fork");
        }
        else if( pid == 0)
        {
                char c;
                close(pf[1]);
                while( read(pf[0],&c,1) > 0)
                {
                        if(write(1,&c,1) < 0)
                        {
                                err(3, "Failed while writing");
                        }

                }


        }

        close(pf[0]);
        write(pf[1],argv[1],strlen(argv[1]));
        close(pf[1]);
        wait(&status);

        exit(0);
}

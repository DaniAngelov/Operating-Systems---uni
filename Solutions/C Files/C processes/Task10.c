//  github.com/DaniAngelov

/*
        Task 10
       Да се напише програма на C, която получава като параметри от команден
       ред две команди (без параметри). Изпълнява първата. Ако тя е завършила успешно
       изпълнява втората. Ако не, завършва с код -1.
*/

#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char** argv)
{
        if(argc != 3)
        {
                errx(1, "Invalid number of arguments!");
        }

        int status;
        int pid = fork();

        if( pid > 0)
        {
                wait(&status);
        if ( execlp( argv[2], argv[2], (char*) NULL) == -1)
        {
                err(-1 , "Failed exec in %s ! ",argv[2]);
        }

        }
        else if(pid == 0)
        {
        if(execlp( argv[1],argv[1], (char*) NULL) == -1)
        {
                        err(2 , "Failed exec in %s", argv[1]);
        }
        }
        else
        {
                err(3, "Failed fork!");
        }
        exit(0);
}

//  github.com/DaniAngelov

/*
        Task 13
       Да се напише програма на C, която получава като командни параметри две команди
       (без параметри). Изпълнява ги едновременно и извежда на стандартния изход номера на
       процеса на първата завършила успешно. Ако нито една не завърши успешно извежда -1.
*/

#include <stdio.h>
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

        pid_t pid1 = fork();
        pid_t pid2 = fork();



        if( pid1 == 0)
        {

                if( execlp(argv[1],argv[1], (char*) NULL) == -1)
                {
                        err( 2, "Failed exec!");
                }
        }
        else if ( pid2 == 0)
        {
                if( execlp(argv[2],argv[2], (char*) NULL) == -1)
                {
                        err( 2 , "Failed exec");
                }
        }

        int stat1;
        int stat2;

        pid_t p1 = wait(&stat1);
        pid_t p2 = wait(&stat2);

        if(WIFEXITED(stat1))
        {
                printf("pid: %d , cmd : %s!",p1,argv[1]);
                wait(&stat2);
        }
        else if(WIFEXITED(stat2))
        {
                printf("pid: %d , cmd : %s!",p2,argv[2]);
                wait(&stat1);
        }
        else
        {
                printf( "-1 \n");
        }

        exit(0);
}

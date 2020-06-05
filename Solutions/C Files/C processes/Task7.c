//  github.com/DaniAngelov

/*
        Task 7
        Да се напише програма на С, която получава като параметри три команди (без параметри),
        изпълнява ги последователно, като изчаква края на
        всяка и извежда на стандартния изход номера на завършилия процес, както и неговия код на завършване.
*/

#include <err.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
        if( argc != 4)
        {
                errx(1,"Invalid number of arguments!");
        }


        int status = 0;

        for(int i =1 ;i < argc;i++)
        {
        int pid = fork();

        if(pid > 0)
        {
                wait(&status);

                printf("child : %d with pid: %d and  status : %d ",i,getpid(),status);
        }
        else if(pid == 0)
        {
                if( execlp(argv[i],argv[i],(char*)NULL) == -1)
                {
                        err(3, "Failed exec!");
                }
        }

        else
        {
                err(2, "Failed while fork!");
        }
        }
        exit(0);
}

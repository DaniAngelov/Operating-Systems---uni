
//  github.com/DaniAngelov

#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>

int main( int argc, char** argv)
{
        if(argc != 2)
        {
                errx(1,"Invalid number of arguments!");
        }

        int pf[2];

        if(pipe(pf) == -1)
        {
                errx(2,"failed pipe");
        }

        pid_t pid = fork();
        if(pid == -1)
        {
                err(3,"Failed fork");
        }
        else if(pid == 0)
        {
                close(pf[0]);
                dup2(pf[1],1);
                if(execlp("cat","cat",argv[1], (char*) NULL) == -1)
                {
                        err(4, "Failed exec");
                }

        }
        close(pf[1]);
        dup2(pf[0],0);
        if (execlp("sort","sort",(char*)NULL) == -1)
        {
                err(4, "Failed exec");
        }


        exit(0);
}

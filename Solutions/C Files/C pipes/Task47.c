//  github.com/DaniAngelov

// find . -type f -printf "%T@ %p \n" | sort -n | tail -1

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <err.h>

int main(int argc,char** argv)
{
        if(argc != 2)
        {
                errx(1, "Invalid number of arguments!");
        }

        int a[2];
        if( pipe(a) == -1)
        {
                errx(2,"Failed pipe");
        }

        pid_t pid = fork();
        if(pid == -1)
        {
                err(3,"Failed fork");
        }
        else if(pid == 0)
        {
                close(a[0]);
                dup2(a[1],1);
                if(execlp("find","find",argv[1],"-type", "f", "-printf", "%T@ %p \n", (char*) NULL) == -1)
                {
                        err(4, "Failed exec");
                }
        }
        close(a[1]);
        int b[2];
        if(pipe(b) == -1)
        {
                err(2 , "Failed pipe");
        }

        pid = fork();
        if(pid == -1)
        {
                err(3,"Failed fork");

        }

        else if(pid == 0)
        {
                dup2(a[0],0);
                close(b[0]);
                dup2(b[1],1);
                if(execlp("sort","sort","-n", (char*) NULL) == -1)
                {
                        err(4, "Failed exec");
                }
        }

        close(b[1]);
        dup2(b[0],0);

                if(execlp("tail","tail","-1", (char*) NULL) == -1)
                {
                        err(4, "Failed exec");
                }
        exit(0);
}



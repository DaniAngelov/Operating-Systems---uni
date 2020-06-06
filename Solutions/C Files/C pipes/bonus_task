//  github.com/DaniAngelov

// Task: cat /etc/passwd | sort | uniq
//                       A      B/


/*
        init1
        fork
                child "cat"
        init2
        fork
                child "sort"
        init3
        uniq

*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <err.h>

int main()
{
        int a[2];
        if(pipe(a) == -1)
        {
                errx(1,"Failed pipe!");
        }
        pid_t pid = fork();

        if( pid == -1)
        {
                err(2,"Failed fork!");
        }
        else if(pid == 0)
        {
                 close(a[0]);
                 dup2(a[1],1);
                 if(execlp("cat", "cat","/home/passwd",(char*)NULL) == -1)
                 {
                        err(3, "Failed exec");
                 }
        }
        close(a[1]);

        int b[2];
        if(pipe(b) == -1)
        {
                errx(1, "Failed pipe!");
        }
        pid = fork();
        if( pid == -1)
        {
                err(2,"Failed fork!");
        }
        else if(pid == 0)
        {
                dup2(a[0],0);
                close(b[0]);
                dup2(b[1],1);
                if(execlp("sort","sort", (char*) NULL) == -1)
                {
                        err(3, "Failed exec!");
                }

        }
        close(b[1]);
        dup2(b[0],0);
        if (execlp("uniq","uniq", (char*) NULL) == -1)
        {
                err(3, "Failed exec");
        }
        exit(0);
}

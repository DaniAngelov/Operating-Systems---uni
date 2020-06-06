//  github.com/DaniAngelov

// cat /home/passwd | cut -d ":" -f7 | sort -rn |uniq -c | sort -n

#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
        int a[2];
        if( pipe(a) == -1)
        {
                errx(1,"Failed pipe");
        }

        pid_t pid = fork();
        if(pid == -1)
        {
                err(2,"Failed fork");
        }
        else if(pid == 0)
        {
                close(a[0]);
                if ( dup2(a[1],1) <0 )
                {
                        err(3,"Failed dup");
                }
                if(execlp("cat" , "cat", "/home/passwd" , (char*) NULL) == -1)
                {
                        err(4 , "Failed exec");
                }
        }

        close(a[1]);

        int b[2];

        if( pipe(b) == -1)
        {
                errx(1,"Failed pipe");
        }

        pid = fork();
        if(pid == -1)
        {
                err(2,"Failed fork");
        }
        else if(pid == 0)
        {

                if(dup2(a[0],0) < 0)
                {
                        err(3, "Failed dup");
                }
                close(b[0]);

                if ( dup2(b[1],1) <0 )
                {
                        err(3,"Failed dup");
                }
                if(execlp("cut" , "cut", "-d", ":", "-f7" , (char*) NULL) == -1)
                {
                        err(4 , "Failed exec");
                }

        }
        close(b[1]);

        int c[2];
        if( pipe(c) == -1)
        {
                errx(1,"Failed pipe");
        }

        pid = fork();
        if(pid == -1)
        {
                err(2,"Failed fork");
        }
        else if(pid == 0)
        {
                if(dup2(b[0],0) < 0)
                {
                        err(3, "Failed dup");
                }
                close(c[0]);
                if ( dup2(c[1],1) <0 )
                {
                        err(3,"Failed dup");
                }
                if(execlp("sort" ,"sort", "-rn" , (char*) NULL) == -1)
                {
                        err(4 , "Failed exec");
                }
        }
        close(c[1]);

        int d[2];

        if( pipe(d) == -1)
        {
                errx(1,"Failed pipe");
        }

        pid = fork();
        if(pid == -1)
        {
                err(2,"Failed fork");
        }
        else if(pid == 0)
        {
                if(dup2(c[0],0) < 0)
                {
                        err(3, "Failed dup");
                }
                close(d[0]);
                if ( dup2(d[1],1) <0 )
                {
                        err(3,"Failed dup");
                }
                if(execlp("uniq" , "uniq", "-c" , (char*) NULL) == -1)
                {
                        err(4 , "Failed exec");
                }
        }
        close(d[1]);
        dup2(d[0],0);

        if(execlp("sort" , "sort", "-n" , (char*) NULL) == -1)
        {
                err(4 , "Failed exec");
        }

        exit(0);
}


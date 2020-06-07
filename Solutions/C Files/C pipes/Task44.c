//  github.com/DaniAngelov

#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <err.h>
#include <stdlib.h>

int main()
{
        while(1)
        {
                if(write(1,"Enter command: ",15) <= 0)
                {
                        err(1, "Failed writing!");
                }

                char buf[1024];

                ssize_t read_size = read(0,&buf,sizeof(buf));
                if( read_size < 0)
                {
                        err(3,"Failed reading!");
                }
                buf[read_size - 1] = '\0';
                if(strcmp(buf,"exit") == 0)
                {
                        break;
                }
                pid_t pid = fork();
                if(pid < 0)
                {
                        warn("Failed fork!");
                        continue;
                }
                else if(pid == 0)
                {
                        if( execlp(buf,buf, (char*) NULL) < 0)
                        {
                                err(5,"Failed exec");

                        }

                }
                wait(NULL);


        }
        exit(0);
}

//  github.com/DaniAngelov

#include <err.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

int num = 0;
int counter = 1;

void ReadFromFile(int fd, const char* description)
{

        char c;
        ssize_t read_size;

        int newline = 1;

        while( (read_size = read(fd,&c,1) ) > 0)
        {
                if(num)
                {
                        if(newline)
                        {
                                setbuf(stdout,NULL);
                                fprintf(stdout,"%02d ",counter);
                                write(1,&c,sizeof(c));
                                counter++;
                                newline = 0;
                        }
                        else
                        {
                                write(1,&c,sizeof(c));
                        }

                        if( c == '\n')
                        {
                                newline = 1;
                        }
                }
                else
                {
                        write(1,&c,1);
                }
        }

        if(read_size == -1)
        {
                int olderrno = errno;
                close(fd);
                errno = olderrno;
                err(4 , "Error while read %s !",description);
        }
}

int main(int argc,char** argv)
{
        if(argc == 1)
        {
               ReadFromFile(0, "STDIN");
                exit(0);
        }

        int i = 1;

        if ( strcmp(argv[i], "-n") == 0)
        {
                num = 1;
                i++;
        }

        for(; i < argc; i++)
        {
                if(strcmp("-",argv[i]) == 0)
                {
                        ReadFromFile(0,"STDIN");
                        continue;
                }


                struct stat st;
                if(stat(argv[i],&st) == -1)
                {
                        err(2, "Error while stat %s",argv[i]);
                }




        int fd = open(argv[i],O_RDONLY);

        if(fd == -1)
        {
                err(3, "Error opening %s", argv[i]);
        }

        ReadFromFile(fd,"argv[i]");

        }
        exit(0);


}

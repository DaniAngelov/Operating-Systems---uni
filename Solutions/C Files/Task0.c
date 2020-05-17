
//  github.com/DaniAngelov

/*
        Task0.c
        Копирайте съдържанието на файл1 във файл2:
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>

//int main(int argc, char* argv[])
int main()
{
        int fd1;
        int fd2;
        char sym;

        if( (fd1 = open("file1.txt", O_RDONLY)) == -1)
        {
                err(1,"File failed to open in read mode!" );
        }
        if( (fd2 = open("file2.txt", O_WRONLY) ) == -1)
        {
                err(2, "File failed to open in write mode!");
        }

        while ( read(fd1,&sym,1) )
        {
                write(fd2,&sym,1);
        }

        close(fd1);
        close(fd2);
        exit(0);

}

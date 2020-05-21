
//  github.com/DaniAngelov

#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdint.h>

#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int cmp(const void* a,const void* b)
{
        return *((unsigned char*)a) - *((unsigned char*)b);
}

int main( int argc,char** argv)
{
        if ( argc != 3 )
        {
                errx(1,"Expected an argument! ");
        }

 int fd1 = open(argv[1], O_RDONLY);

        if(fd1 == -1)
        {
                err(2, "Error while opening %s ",argv[1]);
        }

        int fd2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC | S_IRUSR | S_IWUSR);

        if ( fd2 == -1 )
        {
                err(3, "Error while opening %s ! ",argv[2]);
               close(fd1);
        }

        struct stat st;

        if ( stat(argv[1], &st) == -1)
        {
                err(4, "Error while using stat");
        }

 if ( st.st_size == 0)
        {
                close(fd1);
                close(fd2);
                exit(0);
        }

        void *buf = malloc(st.st_size);

        if(!buf)
        {
                int olderrno = errno;
                close(fd1);
                close(fd2);
                errno = olderrno;
                err(5, "no memory! ");
        }

        if( read(fd1,buf,st.st_size) != st.st_size)
        {
                int olderrno = errno;
                free(buf);
                close(fd1);
                close(fd2);
                errno = olderrno;
                err(6, "Error while reading file %s", argv[1]);

        }

	qsort(buf,st.st_size,1,cmp);
        if (write(fd2,buf,st.st_size) != st.st_size)
        {
                int olderrno = errno;
                free(buf);
                close(fd1);
                close(fd2);
                errno = olderrno;
                err(7, "Error while writing file %s", argv[2]);
        }
        free(buf);
        close(fd1);
        close(fd2);
        exit(0);
}

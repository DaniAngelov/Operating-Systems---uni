//  github.com/DaniAngelov

#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>

int cmp(const void* a, const void* b)
{
        if( *((uint16_t*) a) > *((uint16_t*)b) )
        {
                return 1;
        }
        else if( *((uint16_t*) a) < *((uint16_t*)b) )
        {
                return -1;
        }
        return 0;

}

int main(int argc, char** argv)
{
        if(argc != 3)
        {
                errx(1,"Invalid number of arguments!");
        }

        struct stat st;

        if( stat(argv[1],&st) <0)
        {
                err(2,"Error while stat %s",argv[1]);
        }

        if( st.st_size % sizeof(uint16_t) != 0)
        {
                err(3,"Invalid size!");
        }

        uint16_t numel = st.st_size / sizeof(uint16_t);
        uint16_t* p = malloc( st.st_size);

        if(!p )
        {
                free(p);
                err(5, "Failed malloc!");
        }

        int fd1 = open(argv[1], O_RDONLY);
        if(fd1 < 0)
        {
                free(p);
                err(4,"Failed while opening %s",argv[1]);
        }

        int fd2 = open( argv[2], O_CREAT | O_RDWR | O_TRUNC , S_IRUSR | S_IWUSR);

        if(fd2 < 0)
        {
                free(p);
                int olderrno = errno;
                close(fd1);
                errno = olderrno;
                err(5, "Failed while opening %s",argv[2]);
        }

        if ( read( fd1, p , st.st_size ) != st.st_size)
        {

                free(p);
                int olderrno = errno;
                close(fd1);
                close(fd2);
                errno = olderrno;
                err(6, "Failed while reading %s",argv[1]);
        }

        qsort(p, numel, sizeof(uint16_t),cmp);

        if( write( fd2,p,st.st_size) != st.st_size)
        {

                free(p);
                int olderrno = errno;
                close(fd1);
                close(fd2);
                errno = olderrno;
                err(8, "Failed while writing %s",argv[2]);
        }

        free(p);
        close(fd1);
        close(fd2);
        exit(0);



}

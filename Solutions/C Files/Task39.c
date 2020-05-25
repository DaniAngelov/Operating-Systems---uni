
//  github.com/DaniAngelov

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>

int cmp ( const void* a, const void* b)
{
        if( *((uint32_t*) a) > *((uint32_t*) b))
        {
                return 1;
        }

        else if( *((uint32_t*) a) < *((uint32_t*) b))
        {
                return -1;
        }

        return 0;
}

int main(int argc,char** argv)
{
        if( argc != 3)
        {
                errx(1,"Invalid number of argument!");
        }

        struct stat st;

        if ( stat(argv[1],&st) < 0)
        {
                err( 2 , "Error with stat %s !",argv[1]);
        }

        if ( st.st_size % sizeof(uint32_t) != 0)
        {
                err( 3 , "Invalid size %s",argv[1]);
        }

        uint32_t numel = st.st_size / sizeof(uint32_t);
        uint32_t half = numel /2;

        uint32_t* p = malloc( half * sizeof(uint32_t));

        if( !p)
        {
                free(p);
                err(4, "Failed while malloc! ");
        }

        int fd1 = open( argv[1], O_RDONLY);

        if( fd1 < 0)
        {
                free(p);
                err(5, "Failed opening %s ",argv[1]);
        }

        int t1 = open( "temp1", O_CREAT | O_RDWR | O_TRUNC , S_IWUSR | S_IRUSR);

        if( t1 <0)
        {
                free(p);
                int olderrno = errno;
                close(fd1);
                errno = olderrno;
                err(6, "Failed while opening! ");
        }

        if( read(fd1,p, half * sizeof(uint32_t)) != (ssize_t)(half * sizeof(uint32_t)))
        {

                free(p);
                int olderrno = errno;
                close(fd1);
                close(t1);
                errno = olderrno;
                err(7, "Failed while reading! ");
        }

        qsort(p, half, sizeof(uint32_t),cmp);

        if ( write(t1, p, half * sizeof(uint32_t) ) != (ssize_t)(half * sizeof(uint32_t)))
        {
                free(p);
                int olderrno = errno;
                close(fd1);
                close(t1);
                errno = olderrno;
                err(8, "Failed while writing! ");

        }

        free(p);

        uint32_t rhalf = numel - half;
        uint32_t * rp = malloc( rhalf * sizeof(uint32_t));

        if( !rp)
        {
                err(9,"Failed while malloc");
        }

        int t2 = open( "temp2" , O_CREAT | O_RDWR | O_TRUNC , S_IWUSR | S_IRUSR);

        if( t2 <0)
        {

                free(rp);
                int olderrno = errno;
                close(fd1);
                close(t1);
                errno = olderrno;
                err(9, "Failed while opening! ");

        }

        if ( read(fd1,rp, rhalf * sizeof(uint32_t)) != (ssize_t)(rhalf * sizeof(uint32_t)))
        {
                free(rp);
                int olderrno = errno;
                close(fd1);
                close(t1);
                close(t2);
                errno = olderrno;
                err(10, "Failed while reading! ");

        }

        qsort(rp,rhalf,sizeof(uint32_t),cmp);

        if ( write( t2,rp , rhalf* sizeof(uint32_t)) != (ssize_t)(rhalf * sizeof(uint32_t)))
        {

                free(rp);
                int olderrno = errno;
                close(fd1);
                close(t1);
                close(t2);
                errno = olderrno;
                err(11, "Failed while writing! ");
        }

        free(rp);
        close(fd1);

        // merge sort


        int fd2 = open( argv[2] , O_CREAT | O_RDWR | O_TRUNC , S_IRUSR | S_IWUSR);
        if( fd2 < 0)
        {

                int olderrno = errno;
                close(t1);
                close(t2);
                errno = olderrno;
                err(12, "Failed while opening %s! ",argv[2]);
        }

        uint32_t num1;
        uint32_t num2;

        lseek(t1,0,SEEK_SET);
        lseek(t2,0,SEEK_SET);

        while ( read ( t1, &num1, sizeof(uint32_t)) == sizeof(uint32_t) &&
                        read ( t2,&num2,sizeof(uint32_t)) == sizeof(uint32_t))
        {
                if( num1 <= num2)
                {
                        write( fd2, &num1,sizeof(uint32_t));
                        lseek( t2, -1*sizeof(uint32_t),SEEK_CUR);
                }
                else
                {
                        write( fd2, &num2,sizeof(uint32_t));
                        lseek( t1, -1*sizeof(uint32_t),SEEK_CUR);
                }
        }

        while ( read ( t1, &num1, sizeof(uint32_t)) == sizeof(uint32_t))
        {
                        write( fd2, &num1,sizeof(uint32_t));
        }

        while ( read ( t2, &num2, sizeof(uint32_t)) == sizeof(uint32_t))
        {
                        write( fd2, &num2,sizeof(uint32_t));
        }

        close(fd2);
        close(t1);
        close(t2);
        exit(0);


}

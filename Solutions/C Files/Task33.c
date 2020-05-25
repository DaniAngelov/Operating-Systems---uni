

//  github.com/DaniAngelov

#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>


int cmp( const void* a, const void* b)
{
        if( *((uint32_t*) a)  > *((uint32_t*) b) )
        {
                return 1;
        }
        else if( *((uint32_t*) a) < *((uint32_t*) b) )
        {
                return -1;
        }

        return 0;
}


int main()
{
        struct stat st;

        if( stat("f1.txt", &st) < 0)
        {
                err( 2,"Failed while stat ");
        }

        if ( st.st_size % sizeof(uint32_t) != 0)
        {
                err( 3 , "Invalid size ");
        }

        uint32_t numel = st.st_size / sizeof(uint32_t);
        printf( "%d\n",numel);

        uint32_t half = numel / 2;

        uint32_t *p = malloc( half * sizeof(uint32_t));

        if(!p)
        {
                err(4 , "Failed malloc! ");
        }

        int fd1 = open("f1.txt", O_RDONLY);
        if( fd1 < 0)
        {
                free(p);
                err(5 , "Failed while opening!");
        }

        int t1 = open("temp1", O_RDWR | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR);
        if( t1< 0)
        {
                free(p);
                int olderrno = errno;
                close(fd1);
                errno = olderrno;
                err( 6, "Failed while opening");
        }

        if (( read(fd1,p,half * sizeof(uint32_t))) != (ssize_t)(half * sizeof(uint32_t)))
        {
                free(p);
                int olderrno = errno;
                close(fd1);
                close(t1);
                errno = olderrno;
                err( 7, "Failed while reading! ");
        }

        qsort(p,half,sizeof(uint32_t),cmp);

        if ( write(t1,p,half* sizeof(uint32_t)) != (ssize_t)(half*sizeof(uint32_t)))
        {

                free(p);
                int olderrno = errno;
                close(fd1);
                close(t1);
                errno = olderrno;
                err( 8, "Failed while writing! ");
        }

        free(p);

        uint32_t rhalf = numel - half;

        uint32_t* rp = malloc( rhalf * sizeof(uint32_t));

        if( !rp)
        {
                free(rp);
                int olderrno = errno;
                close(fd1);
                close(t1);
                errno = olderrno;
                err( 9, "Failed malloc! ");
        }

        int t2 = open("temp2", O_CREAT | O_RDWR | O_TRUNC , S_IWUSR | S_IRUSR);

        if( t2 <0)
        {
                free(rp);
                int olderrno = errno;
                close(fd1);
                close(t1);
                errno = olderrno;
                err( 10,"Error while opening! ");
        }
        if ( read(fd1,rp,rhalf*sizeof(uint32_t)) != (ssize_t)(rhalf*sizeof(uint32_t)))
        {

                free(rp);
                int olderrno = errno;
                close(fd1);
                close(t1);
                close(t2);
                errno = olderrno;
                err( 11,"Error while reading! ");
        }

        qsort(rp,rhalf,sizeof(uint32_t),cmp);

        if ( write(t2,rp,rhalf*sizeof(uint32_t)) != (ssize_t)(rhalf*sizeof(uint32_t)))
        {

                free(rp);
                int olderrno = errno;
                close(fd1);
                close(t1);
                close(t2);
                errno = olderrno;
                err( 12,"Error while writing! ");
        }

        free(rp);
        close(fd1);

        lseek(t1,0,SEEK_SET);
        lseek(t2,0,SEEK_SET);

        int fd2 = open( "f2.txt" , O_CREAT | O_RDWR | O_TRUNC , S_IWUSR | S_IRUSR);
        if( fd2 < 0)
        {

                int olderrno = errno;
                close(t1);
                close(t2);
                errno = olderrno;
                err( 12,"Error while opening! ");
        }

        uint32_t num1;
        uint32_t num2;

        while( read(t1,&num1,sizeof(num1)) == sizeof(num1)
                        && read(t2,&num2,sizeof(num2)) ==sizeof(num2))
        {
                if( num1 <= num2)
                {
                        write(fd2,&num1,sizeof(num1));
                        lseek(t2,-1*sizeof(num2),SEEK_CUR);
                }
                else
                {

                        write(fd2,&num2,sizeof(num2));
                        lseek(t1,-1*sizeof(num1),SEEK_CUR);
                }
        }

        while( read(t1,&num1,sizeof(num1)) == sizeof(num1))
        {
                write(fd2,&num1,sizeof(num1));
        }

        while( read(t2,&num2,sizeof(num2)) == sizeof(num2))
        {
                write(fd2,&num2,sizeof(num2));
        }

        close(t1);
        close(t2);
        close(fd2);
        exit(0);
}


/*
        creating file1 - input
        file 2 - output
        creating temp file t1 and t2
        sorting each of them
        qsort
        then merge sort and dumping them into fd2

 */

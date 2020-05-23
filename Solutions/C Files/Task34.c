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



struct rstruct_t
{
        uint16_t position;
        uint8_t length;
        uint8_t reserved;
};

int main(int argc, char ** argv)
{
        if( argc != 5)
        {
                errx(1 , "Invalid numbere of arguments");
        }

        struct stat st;

        if ( stat(argv[2], &st) < 0)
        {
                err(2 , "Failed stat ! ");
        }

        if ( st.st_size % sizeof(uint32_t) = 0)
        {
                errx(3 , "Invalid size of file %s !", argv[2]);
        }

        if ( stat(argv[1], &st) < 0)
        {
                err(2, "Failed stat! ");
        }

        if( st.st_size > 0xFFFF)
        {
                warnx("Size of %s greater than 0xFFFF",argv[1]);
        }

        int f1dat = open(argv[1], O_RDONLY);

        if( f1dat == -1)
        {
                err(4, "Failed to open file %s ! ",argv[1]);
        }

        int f1idx = open(argv[2], O_RDONLY);

        if( f1idx == -1)
        {
                int olderrno = errno;
                close(f1dat);
                errno = olderrno;
                err( 4, "Failed to open files %s ! ", argv[2]);
        }

        int f2dat = open( argv[3], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRWXG);

        if( f2dat == -1)
        {
                int olderrno = errno;
                close(f1dat);
                close(f1idx);
                errno = olderrno;
                err( 4, "Failed to open files %s ! ", argv[3]);
        }

        int f2idx = open( argv[4], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRWXG);

        if( f2idx == -1)
        {
                int olderrno = errno;
                close(f1dat);
                close(f1idx);
                close(f2dat);
                errno = olderrno;
                err( 4, "Failed to open files %s ! ", argv[4]);
        }

        struct rstruct_t el;
        struct rstruct_t y = {0,0,0};

        while(read(f1idx, &el , sizeof(el) == sizeof(el)))
        {
                uint8_t a;
                if ( lseek(f1dat,el.position,SEEK_SET) == -1)
                {
                        err(6, "Cannot seek to %d in %s",el.position,argv[1]);
                }

                read(f1dat,&a,sizeof(a));

                if( a >= 'A' && a <= 'Z')
                {
                        y.length = el.length;

                        write(f2dat , &a , sizeof(1));

                        for(int i =1 ;i < el.length;i++)
                        {
                                read(f1dat, &a,sizeof(a));
                                write(f2dat, &a,sizeof(a));
                        }
                        write(f2idx, &y,sizeof(y));

                        y.position += y.length;
                }
        }

        close(f1dat);
        close(f1idx);
        close(f2dat);
        close(f2idx);

        exit(0);
}

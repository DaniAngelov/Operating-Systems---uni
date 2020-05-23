//  github.com/DaniAngelov

#include <err.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc,char** argv)
{

        if ( argc != 4)
        {
                errx(1, "Invalid number of arguments!");
        }

        uint8_t a;

        struct triple_t
        {
                uint16_t pos;
                uint8_t orig;
                uint8_t changed;
        };


        struct stat st;

        if( stat(argv[1], &st) <0 )
        {
                err(2, "Failed during stat %s ",argv[1]);
        }

        if ( st.st_size % sizeof(struct triple_t) != 0)
        {
                errx(3 , "Invalid size of file! ");
        }

        if ( stat(argv[2], &st) <0)
        {
                err(2, "Failed during stat %s",argv[2]);
        }

        if( st.st_size > 0xFFFF)
        {
                warnx( "File is very big ! ");
        }

        int fdpatch = open ( argv[1], O_RDONLY);

        if( fdpatch == -1)
        {
                err(3, "Failed while opening %s! ",argv[1]);
        }

        int fdf1 = open( argv[2],O_RDONLY);
        if ( fdf1 == -1)
        {
                int olderrno = errno;
                close(fdpatch);
                errno = olderrno;
                err(3, "Failed while opening %s! ", argv[2]);
        }

        int fdf2 = open( argv[3], O_CREAT | O_RDWR | O_TRUNC , S_IRUSR | S_IWUSR );
        if ( fdf2 == -1)
        {
                int olderrno = errno;
                close(fdpatch);
                close(fdf1);
                errno = olderrno;
                err(3, "Failed while opening %s! ", argv[3]);

        }

        while ( read(fdf1,&a, sizeof(a)) > 0)
        {
                if(write(fdf2,&a,sizeof(a)) < 0)
                {
                        int olderrno = errno;
                        close(fdf1);
                        close(fdpatch);
                        errno = olderrno;
                        err(5, "Failed while writing in file %s",argv[2]);
                }
        }

        close(fdf1);

        struct triple_t tr;

        while( read(fdpatch,&tr,sizeof(tr)) == sizeof(tr))
        {
                if ( lseek(fdf2, tr.pos,SEEK_SET) < 0)
                {
                        err(4 , "Failed while seeking to %d pos in %s file",tr.pos,argv[2]);
                }

                read(fdf2, &a, sizeof(a));
                if( a == tr.orig)
                {
                        if( lseek( fdf2, -1 , SEEK_CUR) < 0 )
                        {

                           err(4 , "Failed while seeking to %d pos in %s file",tr.pos,argv[2]);
                        }
                        write(fdf2, &(tr.changed), sizeof(tr.changed));
                }
                else
                {
                        errx(6, "There is no such byte in %s file",argv[2]);
                }



        }


        close(fdpatch);
        close(fdf2);
        exit(0);

}


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


int main(int argc,char** argv)
{
        if(argc != 4)
        {
                errx(1,"Invalid number of arguments!");
        }

        struct stat st;
        if( stat(argv[1], &st) < 0)
        {
                errx(2, "Failed during stat! ");
        }

        ssize_t size_f1 = st.st_size;

        if( stat(argv[2], &st) < 0)
        {
                errx(2, "Failed during stat! ");
        }

        ssize_t size_f2 = st.st_size;

        if(size_f1 != size_f2)
        {
                errx( 3, "First and second files have different length!");
        }

        if(size_f1 == 0 && size_f2 == 0)
        {
                errx(4, "First and second files are empty");
        }

        struct rstruct_t
        {
                uint16_t pos;
                uint8_t byte1;
                uint8_t byte2;
        };

        int fd1 = open(argv[1], O_RDONLY);
        if( fd1 == -1)
        {
                err(5 , "Failed while opening file %s ",argv[1]);
        }

        int fd2 = open(argv[2],O_RDONLY);

        if( fd2 == -1)
        {
                int olderrno = errno;
                close(fd1);
                errno = olderrno;
                err(6, "Faild while opening file %s ! ",argv[2]);
        }

        int fd3 = open(argv[3], O_CREAT | O_RDWR | O_TRUNC , S_IWUSR | S_IRUSR );
        if( fd3 == -1)
        {
                int olderrno = errno;
                close(fd1);
                close(fd2);
                errno = olderrno;
                err(7, "Faild while opening file %s ! ",argv[2]);
        }

        char one;
        char two;

        struct rstruct_t rst;

        while (read(fd1,&one,sizeof(one)) > 0 && read(fd2,&two,sizeof(two)))
        {
                if( one != two)
                {
                        rst.byte1 = one;
                        rst.byte2 = two;
                        write(fd3, &rst,sizeof(rst));
                }
                rst.pos++;
        }

        close(fd1);
        close(fd2);
        close(fd3);
        exit(0);

}

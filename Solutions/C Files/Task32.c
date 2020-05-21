//  github.com/DaniAngelov

#include <err.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
        off_t f1_size;
        off_t f2_size;

        struct stat st;

        if(stat("test1.bin", &st) < 0)
        {
                err(1, "Failed during stat");
        }

        f1_size = st.st_size;

        if(stat("test2.bin",&st) <0)
        {
                err(2, "Failed during stat file 2 !");
        }


        f2_size = st.st_size;

        struct pair_t
        {
                uint32_t start_positions;
                uint32_t length;
        };

        if( f1_size %sizeof(struct pair_t) != 0)
        {
                err(3, "Faild size1 ");
        }

        if( f2_size %sizeof(uint32_t) != 0)
        {
                err(4, "Faild size2 ");
        }

        int fd1;
        int fd2;
        int fd3;

        fd1 = open("test1.bin" , O_RDONLY);
        if ( fd1 == -1)
        {
                err(5, "Faild while opening file 1 ");
        }
 fd2 = open("test2.bin" , O_RDONLY);
        if ( fd2 == -1)
        {
                int olderrno = errno;
                close(fd1);
                errno = olderrno;
                err(6, "Faild while opening file 2 ");
        }

        fd3 = open( "test3.bin" , O_CREAT | O_RDWR | O_TRUNC | S_IRUSR | S_IWUSR);
        if ( fd3 == -1)
        {

                int olderrno = errno;
                close(fd1);
                close(fd2);
                errno = olderrno;
                err(7, "Faild while opening file 3 ");
        }

        struct pair_t pair;

        while( read ( fd1, &pair, sizeof( pair)))
        {
                if(lseek(fd2, pair.start_positions*sizeof(uint32_t),SEEK_SET) < 0)
                {
                        int olderrno = errno;
                        close(fd1);
                        close(fd2);

                    errno = olderrno;
                        err(8, "lseek error");
                }

                uint32_t bytes;
                uint32_t  counter = 0;
                ssize_t read_size;

                while( (read_size = read(fd2, &bytes,sizeof(bytes))) > 0)
                {
                        if( write(fd3, &bytes,read_size) != read_size)
                        {
                                int olderrno = errno;
                                close(fd1);
                                close(fd2);
                                errno = olderrno;
                                err(9,"Error while writing");
                        }
                        counter++;
                        if(counter == pair.length)
                        {
                                break;
                        }
                }

        }
       close(fd1);
        close(fd2);
        close(fd3);
        exit(0);
}

//  github.com/DaniAngelov

#include <stdint.h>
#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char** argv)
{
        if(argc !=2)
        {
                errx(1,"Invalid number of arguments!");
        }

        struct user
        {
                uint32_t uid;
                uint16_t reserved1;
                uint16_t reserved2;
                uint32_t start;
                uint32_t end;
        };

        struct user u;

        uint32_t counter = 0;
        uint32_t disp = 0;

        int fd = open(argv[1], O_RDONLY);

        if( fd == -1)
        {
                err(2 , "Failed while opening %s ",argv[1]);
        }

        struct stat st;

        if( stat(argv[1],&st) < 0)
        {
                err(3 , "Failed stat");
        }

        if ( st.st_size % sizeof(uint32_t) != 0)
        {
                err(4, "Invalid size!");
        }


        while( read( fd, &u, sizeof(u)) > 0)
        {
                disp += (u.end - u.start) * (u.end - u.start);
                counter++;
        }

        disp = disp / counter;
        lseek(fd,0,SEEK_SET);

        while( read(fd,&u,sizeof(u)) > 0)
        {
                if((u.end - u.start) * (u.end - u.start) > disp)
                {
                        uint32_t userDur = (u.end - u.start);
                        write(1,&u.uid,sizeof(u.uid));
                        write(1,&userDur,sizeof(userDur));
                }
        }

}

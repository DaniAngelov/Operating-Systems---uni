  

//  github.com/DaniAngelov

/*
        Task 5
        Реализирайте команда cat, работеща с произволен брой подадени входни параметри.
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
        if(argc == 1)
        {
                errx(1,"Expecting arguments!");
        }

        for(int i = 1;i < argc;i++)
        {
                int fd = open(argv[i], O_RDONLY);
                if ( fd == -1)
                {
                        err(2, "Error while opening");
                }
	  ssize_t read_size;
                char c[4096];
                while(  (read_size = read(fd,&c,sizeof(c))) > 0)
                {
                        write(1,&c,read_size);

                }
                close(fd);
        }

        exit(0);


}

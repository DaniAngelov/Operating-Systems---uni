  
 // github.com/DaniAngelov

/*
        Task 2
        Да се напише програма на C, която изпълнява команда ls с точно един аргумент.
*/

#include <err.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char** argv)
{
        if( argc != 2 )
        {
                errx(2, "Invalid nubmer of arguments!");
        }
        if ( execlp("ls", "ls", argv[1],0) < 0)
        {
                err(1, "failed while exec!");
        }
}
~  

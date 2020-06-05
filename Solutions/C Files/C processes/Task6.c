//  github.com/DaniAngelov

/*
        Task 6
        Да се напише програма на С, която получава като параметър команда (без параметри)
        и при успешното ѝ изпълнение, извежда на стандартния изход името на командата.
*/

#include <err.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char** argv)
{
        if(argc != 2)
        {
                errx(1,"Invalid number of arguments!");

        }

        if( execlp(argv[1],argv[1], (char*)NULL )  == -1)
        {
                err(2,"Failed exec!");

        }

        exit(0);

}

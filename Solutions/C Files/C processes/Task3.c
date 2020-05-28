  
//  github.com/DaniAngelov

/*
        Task 3
       Да се напише програма на C, която изпълнява команда sleep (за 60 секунди).
*/

#include <err.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{

        if ( execlp("sleep", "sleep", "60",0) < 0)
        {
                err(1, "failed while exec!");
        }
}

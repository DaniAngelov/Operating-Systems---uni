//  github.com/DaniAngelov

/*
        Task 1
        Да се напише програма на C, която изпълнява команда date.
*/
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
        if(execlp("date" ,"date", (char*) NULL) < 0 )
        {
                err(1, "Err while exec");
        }

        exit(0);


}

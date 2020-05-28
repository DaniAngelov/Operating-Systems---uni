  
//  github.com/DaniAngelov

/*
        Task 4
        Да се напише програма на C, която създава процес дете и 
        демонстрира принцина на конкурентност при процесите.
*/

#include <err.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

        int counter = 1000;

        if(fork() > 0)
        {
                for(int i = 0;i< counter;i++)
                printf("parent \n");
        }
        else
        {
                for(int i =0;i < counter;i++)
                printf("child \n");
        }
        exit(0);
}

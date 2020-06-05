//  github.com/DaniAngelov

/*
        Task 5
  Да се напише програма на C, която е аналогична на горния пример, 
  но принуждава бащата да изчака сина си да завърши.
  
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
        int N = 100;
        int status;

        if( fork()> 0)
        {
                wait(&status);
                for(int i = 1;i < N;i++)
                        printf("parent \n");

        }
        else
        {
                for(int i = 1;i < N;i++)
                        printf("child \n");
        }
        exit(0);
}

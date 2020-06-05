//  github.com/DaniAngelov

/*
        Task 11
        Да се напише програма на C, която изпълнява последователно подадените ѝ
        като параметри команди, като реализира следната функционалност постъпково:
        main cmd1 ... cmdN Изпълнява всяка от командите в отделен дъщерен процес.
        ... при което се запазва броя на изпълнените команди, които са дали грешка и броя на завършилите успешно.
*/

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char** argv)
{
        if(argc < 2)
        {
                errx(1,"Invalid number of arguments!");
        }

        int success = 0;
        int fail = 0;
        for(int i =1 ;i < argc;i++)
        {
                int status;
                pid_t pid1 = fork();
                if(pid1 > 0)
                {
                        wait(&status);
                }
                else if(pid1 == 0)
                {
                        if(execlp(argv[i],argv[i], (char*) NULL) == -1)
                        {
                                err(2,"Failed while exec");
                        }
                }
                else
                {
                        err(3, "Failed while fork!");
                }

                if(WIFEXITED(status))
                {
                        if(WEXITSTATUS(status) != 0)
                        {
                                fail++;
                        }
                        else
                        success++;
                }
        }

        printf("Successful : %d , Unsuccessful: %d !",success,fail);
        exit(0);

}

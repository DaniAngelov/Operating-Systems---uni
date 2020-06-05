//  github.com/DaniAngelov

/*
        Task 12
        Да се напише програма на C, която получава като параметри от команден ред две команди
        (без параметри) и име на файл в текущата ### ### директория. Ако файлът не съществува,
        го създава. Програмата изпълнява командите последователно, по реда на подаването им.Ако първата
        команда завърши успешно, програмата добавя нейното име към съдържанието на файла,
        подаден като команден параметър. Ако командата завърши
        неуспешно, програмата уведомява потребителя чрез подходящо съобщение.
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <sys/wait.h>

int main(int argc,char** argv)
{
        if(argc != 4)
        {
                errx(1, "Invalid number of arguments!");
        }

        int fd = open( argv[3], O_CREAT | O_RDWR | O_TRUNC , S_IRUSR | S_IWUSR);

        if( fd == -1)
        {
                err(2, "Failed while opening %s",argv[3]);
        }
        for(int i = 1 ;i < argc- 1;i++)
        {
        int status;
        pid_t pid = fork();

        if( pid > 0 )
        {
                wait(&status);

                if(status == 0)
                {
                write(fd, argv[i],strlen(argv[i]));
                }
        }
        else if(pid == 0)
        {
                if(execlp( argv[i],argv[i], (char*) NULL) == -1)
                {

                int olderrno = errno;
                close(fd);
                errno = olderrno;
                err(4, "Failed while exec!");
                }
        }
        else
        {
                int olderrno = errno;
                close(fd);
                errno = olderrno;
                err(3, "Failed while fork!");
        }
        }
        exit(0);
}

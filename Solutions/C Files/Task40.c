//  github.com/DaniAngelov

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>

void option_c(const char* arg2)
{
        if( strlen(arg2) == 1)
        {
                char c;
                int counter = 1;

                int temp = *arg2 - '0';
                while( read(0,&c,1) > 0)
                {
                        if(counter == temp)
                        {
                                write(1,&c,1);
                                break;
                        }

                        counter++;

                }
        }
        else
        {
                char c;
                int temp1 = *arg2 - '0';
                int temp2 = *(arg2 + 2) - '0';
                int counter = 1;

                while( read (0,&c,1) > 0)
                {

                        if( counter >= temp1 && counter <= temp2)
                        {
                                write(1,&c,1);
                        }
                        counter++;
                }

        }


}


void option_d(const char* arg2,const char* arg3,const char* arg4)
{
        char delim = arg2[0] ;
        const char* fields = arg3;

        if( strcmp(fields, "-f") != 0)
        {
                errx(4,"Invalid third argument!");
        }
        int counter = 1;

        if( strlen(arg4) == 1)
        {
                char c;
                int field1 = *arg4 - '0';
                while( read (0,&c,1) >0)
                {
                        if(c == delim)
                        {
                                counter++;
                        }
                        if( counter == field1)
                        {
                                if(c != delim)
                                write(1,&c,1);
                        }
                }

        }
        else
        {

                int field1 = *arg4 - '0';
                int field2 = *(arg4 + 2) - '0';
                //printf("%d %d",field1,field2);
                char c;
                while( read (0,&c,1) >0)
                {
                        if(c == delim)
                        {
                                counter++;
                        }
                        if( counter >= field1 && counter <= field2)
                        {
                                if(c != delim)
                                write(1,&c,1);
                        }
                }

        }
//      printf("delim: %c, fields : %s , field1 : %d , field2: %d!  ",delim,fields,field1,field2);

}




int main(int argc,char** argv)
{
        if(argc < 3 && argc > 5 && argc == 4)
        {
                errx(1, "Invalid number of arguments!");
        }

        if( strcmp(argv[1],"-c") == 0)
        {
                option_c(argv[2]);
        }

        if( strcmp(argv[1], "-d") == 0)
        {
                option_d(argv[2],argv[3],argv[4]);
        }

        exit(0);
}

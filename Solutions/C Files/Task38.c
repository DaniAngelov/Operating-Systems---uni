
//  github.com/DaniAngelov

#include <string.h>
#include <stdio.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void option_d(const char* arg)
{
        char c;

        while( ( read(0,&c,1) ) > 0)
        {
                const char * p = strchr(arg,c);
                if ( p == NULL)
                {
                        write(1,&c,1);
                }
        }


}

void option_s( const char* arg)
{
        char prev;
        char curr;
        bool newline = true;

        while( ( read(0,&curr,1)) > 0)
        {
                const char* p = strchr(arg,curr);
                if( p != NULL && newline == true)
                {
                        prev = curr;
                        newline = false;
                        continue;
                }
                if( newline == false)
                {
                        if( prev == curr)
                        {
                        continue;
                        }
                        else
                        {
                                write(1,&prev,1);
                        }
                }
                else
                {
                        write(1,&curr,1);
                }
                prev = curr;
        }


}


void option_default(const char* arg,const char* arg2)
{
        char c;

        while( read(0,&c,1) > 0)
        {
                for( unsigned int i = 0 ;i < strlen(arg);i++)
                {
                        if( c == arg[i])
                        {
                                c = arg2[i];
                        }
                }

                write(1,&c,1);
        }
}


int main( int argc, const char** argv)
{
        if ( argc != 3)
        {
                errx(1, "Invalid number of arguments! ");
        }

        if( strcmp(argv[1],"-d") == 0)
        {
                option_d(argv[2]);
        }
        else if( strcmp(argv[1],"-s") == 0)
        {
                option_s(argv[2]);
        }
        else
        {
                option_default(argv[1],argv[2]);
        }

        exit(0);



}

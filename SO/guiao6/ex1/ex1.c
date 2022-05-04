#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

/*
    int mkfifo (const char* pathname, mode_t mode); 

    mkfifo fifo

    ex1.c fifo
*/

int main(int argc, char * argv[])
{

    //parte1
    if (mkfifo(argv[1],0666) < 0)
    {
        perror("mkfifo");
    }

    return 0;
}
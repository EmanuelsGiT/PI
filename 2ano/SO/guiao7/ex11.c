#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <signal.h>
#include <sys/types.h>


int seconds = 0;

void inc_seconds (int signum)
{
    seconds++;
}

void print_seconds(int sigmum)
{

    seconds++;

    printf("CTRL+C,")
}

int main(int argc, char * argv[])
{
    if (sgnal(SIGINT,print_seconds)==SIG_ERR)
    {
        printf("error\n");

        return 1;
    }

    printf("getpid: %d\n",getpid());

    while (1)
    {
        alarm(1);

        pause();
    }
    

    printf("seconds");
    


    return 0;
}
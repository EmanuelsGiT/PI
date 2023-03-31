#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <signal.h>
#include <sys/types.h>

/*
    typedef void (*sighandler_t)(int);
    sighandler_t signal(int signum, sighandler_t handler);
    int kill(pid_t pid, int sig);
    unsigned int alarm(unsigned int seconds);
    int pause(void);
*/

void sighandler(int signum)
{
    printf("received %d\n",signum);

    sleep(10);

    printf("hanled %d\n", signum);
}

int i=0;

void sighandler(int signum)
{
    int my_i = i 

    printf("received %d\n",signum);

    sleep(10);

    printf("hanled %d\n", signum);

    i = my_i +1;
}


int main(int argc, char*argv[])
{
    printf("pid: %d\n", getpid());

    signal(SIGUSR1, sighandler);

    signal(SIGUSR2, sighandler);

    pause();

    printf("Continuing execution...\n");

    return 0;
}
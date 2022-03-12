#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(int args, char* argv[])
{   
    int i;
    int pid;

    for(i = 0; i<10; i++)
    {
        pid = fork();
        if(pid>0)
        {
            printf("child pid %d\n", pid);
        } 

        printf("pid: %d \n", getpid());

        printf("ppid: %d \n\n", getppid());
    }

    return 0;
}
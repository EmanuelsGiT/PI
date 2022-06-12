#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 


int main(int args, char *argv[])
{
    pid_t pid = fork(); 

    if(pid==0)
    {
        printf("[FILHO] O meu pid é %d\n", getpid());
        printf("[FILHO] O pid do meu pai é %d\n", getppid());
    }
    else
    {
        //int status, finished_pid;

        printf("[PAI] O meu pid é %d\n", getpid());
        printf("[PAI] O pid do meu pai é %d\n", getppid());
        printf("[PAI] O pid do meu filho é %d\n", pid);
        sleep(30); // filho fica zombie 
        // ou finished_pid = wait(&status);
    }
    
    return 0;
}
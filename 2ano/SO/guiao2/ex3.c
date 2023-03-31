#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(int args, char* argv[])
{   
    int i, status;
    pid_t pid;

    for(i = 0; i<10; i++)
    {
        if(pid==0)
        {
            //código do filho
            printf("[FILHO] O meu pid é %d\n", getpid());
            printf("[FILHO] O pid do meu pai é %d\n", getppid());
            _exit(i);
        }
        else
        {
            //código do pai
            wait(&status); 
            printf("[PAI] Código de saída do filho: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
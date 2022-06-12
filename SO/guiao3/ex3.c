#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/* 
chamadas ao sistema: defs e decls essenciais 

int execl(const char *path, const char *arg0, ..., NULL);
int execlp(const char *file, const char *arg0, ..., NULL);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
*/

int main(int argc, char* argv[])
{
    pid_t pid;

    int i=1, status;

    while(i<=10)
    {
        pid = fork();
        if(pid==0)
        {
            printf("[FILHO] O meu pid é %d\n", getpid());
            printf("[FILHO] O pid do meu pai é %d\n", getppid());
            _exit(i);
        }
        else
        {
            wait(&status); 
            printf("[PAI] Código de saída do filho: %d\n", WEXITSTATUS(status));
        }
        i++;
    }

    return 0;
}
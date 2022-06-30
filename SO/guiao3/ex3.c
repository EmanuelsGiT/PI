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
    int i=1, status, exec_ret;

    while(i<=argc)
    {
        pid = fork();
        if(pid == 0){
            exec_ret = execlp(argv[i],argv[i],NULL);
            perror("reached return");
            _exit(exec_ret);
        }
        i++;
    }

    for(i=0;i<argc;i++)
        wait(&status);

    return 0;
}
#include <unistd.h> /*chamadaas ao sistema: defs e decls essenciais*/
#include <sys/wait.h> /*chamadas wait*() e macros relacionadas*/ 

/*
    pid_t getpid(void);
    pid_t getppid(void);
    pid_t fork(void);
    void _exit(int status);
    pid_t wait(int *status);
    pid_t waitPID(pid_t pid, int *status, int options);
*/
    //int() WIFEXITED(int status); /*macro*/
    //int() WEXITSTATUS(int status); /*macro*/


int main(int args, char *argv[])
{
    pid_t pid; 
    pid = fork();

    if(pid>0)
        printf("child pid %d\n", pid);

    printf("pid: %d \n", getpid());
    
    printf("ppid: %d \n", getppid());   

    return 0;
}
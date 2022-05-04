#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 
/*
pid_t getpid(void);
pid_t getppid(void);
pid_t fork(void);
void _exit(int status);
pid_t wait(int *status);
pid_t waitPID(pid_t pid, int *status, int options);
int WIFEXITED(int status);  "macro" 
int WEXITSTATUS(int status);  "macro" 
*/
int main(int args, char* argv[])
{   
    int i, pid, status, finished_pid;
    
    for (i=0;i<10;i++)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("filho %d\n",i);
            _exit(i);
        }
    }

    for (i=0;i<10;i++)
    {
        finished_pid = wait(&status);
        printf("child pid finished: %d; status code: %d\n", finished_pid, WEXITSTATUS(status));
    }
    

    return 0;
}
#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 
/*
int main(int args, char *argv[])
{
    int pid; 
    pid = fork();

    if(pid>0)
    {
        printf("child pid %d\n", pid);
    } 

    printf("pid: %d \n", getpid());
    
    printf("ppid: %d \n", getppid());   

    return 0;
}
*/
int main(int args, char *argv[])
{
    int pid; 
    pid = fork();

    if(pid==0)
    {
        printf("pid: %d \n", getpid());
    
        printf("ppid: %d \n", getppid());

        exit(5); 
    } 
    else 
    {
        int status;

        int finished_pid;

        printf("child pid %d\n", pid);

        printf("pid: %d \n", getpid());

        printf("ppid: %d \n", getppid());  

        finished_pid = wait(&status);
          
    }
    return 0;
}
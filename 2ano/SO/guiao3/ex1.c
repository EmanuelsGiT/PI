#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* 
chamadas ao sistema: defs e decls essenciais 

int execl(const char *path, const char *arg0, ..., NULL);
int execlp(const char *file, const char *arg0, ..., NULL);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
*/

//ls

int main(int argc, char* argv[])
{

    if(execl("/bin/ls","/bin/ls","-l",NULL)<0)
        perror("exec");


    if(execl("ls","ls","-l",NULL)<0)
        perror("exec");

    char * exec_args[] = {"/bin/ls","-l",NULL};

    execv("/bin/ls",exec_args);

    sleep(10);

    if(execlp("sleep","sleep","10",NULL)<0)
        perror("exec");



    char * buff = "contents";

    if(write(3,buff,strlen(buff))<1)
        perror("write");

/*
    int status, finished_pid, pid = fork();

    if (pid == 0)
    {
        //code


        exit(1);
    }

    finished_pid = wait(&status);
    printf("child pid finished: %d; status code: %d\n", finished_pid, WEXITSTATUS(status));
*/
    return  0;
}
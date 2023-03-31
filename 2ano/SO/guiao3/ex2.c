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
    if (fork()==0)
    {
        if(execl("/bin/ls","/bin/ls","-l",NULL)<0)
        {
            perror("exec");
        }
        _exit(1);
    }

    else
    {
        wait(NULL);
    }

    printf("Done!\n");

    return 0;
}
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
    int filein = open("/etc/passwd", O_RDONLY);
    dup2(filein,0);
    close(filein);

    int outOriginal = dup(1);

    int fileout = open("saida.txt", O_CREAT|O_TRUNC|O_WRONLY, 0666);
    dup2(fileout,1);
    close(fileout);

    int filerror = open("erros.txt", O_CREAT|O_TRUNC|O_WRONLY, 0666);
    dup2(filerror,2);
    close(filerror);

    char buffer;
    char line[1024];
    int read_res, wait_res, status;
    int i=0;
    
    pid_t pid = fork();

    if(pid==0)
    {
        while((read_res=read(0,&buffer,1)) != 0)
        {
            line[i]=buffer;
            i++;
            if(buffer=='\n')
            {
                write(1,line,i);
                write(2,line,i);
                fflush(stdout);
                i=0;
            }
        }
        
        exit(0);
    }
    else
    {
        wait_res = wait(&status); 
        dup2(outOriginal,1);
        close(outOriginal);
        printf("END\n");
    }
    
    return 0;
}
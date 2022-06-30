#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include <fcntl.h>

// 0: stdin -> teclado
// 1: stdout -> ecra
// 2: stderr -> ecra

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
    int read_res;
    int i=0;
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

    dup2(outOriginal,1);
    close(outOriginal);

    printf("Terminei\n");
    return 0;
}
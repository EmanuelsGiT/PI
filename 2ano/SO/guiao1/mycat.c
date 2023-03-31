#include <stdio.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#define MAX_BUF 1024

int main(int argc, char*argv[])
{
    char buffer[MAX_BUF];
    int bytes_read;

    while ((bytes_read = read(0, buffer, MAX_BUF))>0)
    {
        write(1,buffer, bytes_read);
    }

    printf("End\n");

    return 0;
}

/*
    ctrl + c termina o program no momento
    ctrl + d quebra o ciclo fornecendo um valor 0
*/

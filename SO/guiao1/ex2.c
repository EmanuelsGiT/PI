#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <stdio.h>


#define MAX_BUF 1024

int main()
{
    
    char buffer[MAX_BUF];

    int bytes_read;

    while((bytes_read = read(0,buffer,MAX_BUF))>0)
    {
        write(1, buffer, bytes_read); 
    }
    printf("Terminei\n");

    return 0;
}

// EOF -> Ctrl D

// Ctrl C -> mata prog -> nao imprime o Terminei
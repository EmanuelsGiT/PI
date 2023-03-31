#include <stdio.h>
#include <string.h>
#include "mainEx1.c"
#include "mainEx2.c"

int main(int argc, char const *argv[])
{
    //Exercise 1
    if (strcmp(argv[1],"exercicio-1")==0) exercicio1();
    
    //Exercise 2
    else if (strcmp(argv[1],"exercicio-2")==0) exercicio2();
    
    else printf("Argumento Inválido!\n");

    return 0;
}

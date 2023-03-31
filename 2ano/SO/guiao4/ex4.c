#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "string.h"
#include <fcntl.h>

int main(int argc, char* argv[])
{
    char *exec_args[20];
    char * string;
    int i = 0, posIn = 0, posOut = 0, filein, fileout;


    for(i=0; i<argv[argc]; i++)
    {
        if(strcpm("-i",argv[i])) posIn = i;
        if(strcpm("-o",argv[i])) posOut = i;
    }

    int outOriginal = dup(1);
    int n  = argc - 1;            
    char* array[n+1];
    
    array[0] = argv[1];
            
    i=1; 
    printf("0 = %s\n", array[0]);
    printf("i=%d, n=%d\n", i , n);
    while(i<=n)
    {
        
        printf("here\n");
        array[i] = argv[posComando+i];
        printf("%d , %s\n", i, array[i]);
        i++;
    }
    
    array[i]=NULL;
    printf("%d , %s\n", i, array[i]);
    
    printf("%s\n", argv[1]);
    int exec_ret = execvp(argv[1],array);


    dup2(outOriginal,1);
    close(outOriginal);

    printf("Correu mal\n");

    return 0;
}
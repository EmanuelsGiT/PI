#include <stdio.h>
#include <string.h>
#include "../libs/mainEx1.h"
#include "../libs/mainEx2.h"
#include "../libs/guiao2.h"
#include "../libs/interface.h"

int main(int argc, const char* argv[]) 
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    //Guide 1 Exercise 1
    exercicio1();
    
    //Guide 1 Exercise 2
    exercicio2();
    
    //Guide 2
    if (argv[1]!=NULL) guiao2(argv[1]);
    else {interface();}
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU Time:%f\n", cpu_time_used );

    return 0;
}
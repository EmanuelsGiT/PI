#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 
#include <stdlib.h>
/*
pid_t getpid(void);
pid_t getppid(void);
pid_t fork(void);
void _exit(int status);
pid_t wait(int *status);
pid_t waitPID(pid_t pid, int *status, int options);
int WIFEXITED(int status);  "macro" 
int WEXITSTATUS(int status);  "macro" 
*/

nt main(int argc, char* argv[])
{
    int lin = atoi(argv[1]);
    int col = atoi(argv[2]);
    int num = atoi(argv[3]);
    int matriz[lin][col];
    int i, j, find=0, status;
    pid_t pid;


    for(i=0;i<lin;i++)
        for(j=0;j<col;j++)
            matriz[i][j]=rand()%100;

    for(i=0;i<lin;i++)
    {
        for(j=0;j<col;j++)
            printf("%d ",matriz[i][j]);
        
        printf("\n");   
    }
        

    for(i = 0; i < lin; i++)
    {
        pid = fork();
        if(pid == 0){
            for(j=0;find==0 && j<col;j++){
                if(matriz[i][j]==num){
                    find=1;
                    printf("find : %d\n", find);

                }
            }
            exit(find);
        }
        printf("find2 : %d\n", find);
    }
    pid_t child;

    for(i = 0; i < lin; i++)
    {
        child = wait(&status);

        if(WEXITSTATUS(status)==1) 
        {
            printf("Element %d not found.\n", num);
            return 0;
        }
        else printf("Element %d not found in child %d.\n", num, child);
    }
    return 0;
}
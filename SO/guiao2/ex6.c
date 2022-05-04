#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 
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


void revela (int matriz[][3], int x, int N)
{
    int i, j, pid, status;

    for (i=0;i<N;i++)
    {
        pid = fork();
        if (pid == 0)
        {
            for (j=0;j<N;j++)
            {
                if (x == matriz[i][j])
                printf("Matriz[%d][%d] = %d\n", i, j, matriz[i][j]);
            }
            _exit(i);
        }
    }

    for (i=0;i<10;i++)
        wait(&status);
}

int main(int args, char* argv[])
{  

    int matriz[][3] = {{1,2,5},
                       {4,5,6},
                       {5,8,9}};

    revela(matriz, 5, 3);

    return 0;
}

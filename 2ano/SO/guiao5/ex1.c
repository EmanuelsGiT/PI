#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


// int pipe(pd[2]);

int main(int argc, char* argv[])
{
    //create pipe

    int pipe_fd[2];

    if(pipe(pipe_fd)<0)
    {
        perror("pipe");
    
        return -1;
    }


    if (fork()==0)
    {   
        close(pipe_fd[1]);
        char buf[4];
        int read_bytes;

        while ((read_bytes = read(pipe_fd[0],buf,4))>0)
        {
            printf("read some data...\n");
            write(1,buf,read_bytes);
        }
        _exit(0);
    }

    close(pipe_fd[0]);

    printf("sending...\n");

    write(pipe_fd[1],"data",4);

    close(pipe_fd[1]);
    
    wait(NULL);

    return 0;
}

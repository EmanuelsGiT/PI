#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE sizeof("Get this parent yey\n")
#define BUFFER 64

int main() 
{
    int pipe_fd[2];

    if (pipe(pipe_fd) < 0) 
    {
        perror("pipe");

        return -1;
    }

    pid_t child = fork();

    // this is child
    
    if(child == 0) 
    {
        close(pipe_fd[1]);
        char buffer[BUFFER] = { 0 };
        ssize_t reads = 0;
        
        //for(char *buf_ptr = buffer;(reads = read(pipe_fd[0], buf_ptr, 16)) > 0; buf_ptr += reads) {}
        
        char *buf_ptr = buffer;
        
        while((reads = read(pipe_fd[0], buf_ptr, 16)) > 0)
        {
            buf_ptr += reads;
        }

        write(1, buffer, SIZE);
        _exit(1);

        // sanity (c)heck
    } 
    else if(child < 0) 
    {
        perror("No child");
        // parent
    } 
    else 
    {
        close(pipe_fd[0]);

        if(write(pipe_fd[1], "Get this parent yey\n", SIZE) < 0) 
        {
            perror("Parent: couldn't write");
        }

        close(pipe_fd[1]);
    }

    wait(NULL);

    return 0;
}
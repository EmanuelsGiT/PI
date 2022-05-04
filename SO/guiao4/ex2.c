#include <unistd.h> /* chamadas ao sistema: defs e dels essenciais */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{


    int ifd = open("/etc/passwd", O_RDONLY);

    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY,0640);

    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY,0640);

    int original_stdin_fd = dup(0);

    int status;

    dup2(ifd,0);
    dup2(ofd,1);
    dup2(efd,2);




    int pid = fork();

    if (pid == 0)
    {
        write(0,"teste",5);
        write(1,"teste",5);
        write(2,"teste",5);

        close(ifd);
        close(ofd);
        close(efd);
        
        _exit(pid);
    }

    wait(&status);
    dup2(original_stdin_fd,1);

    write(original_stdin_fd,"terminei",8);

    return 0;
}
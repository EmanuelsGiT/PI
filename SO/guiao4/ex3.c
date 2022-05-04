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

    dup2(ifd,0);
    close(ifd);

    dup2(ofd,1);
    close(ofd);
    
    
    dup2(efd,2);
    close(efd);


    //sleep(20);

    dup2(original_stdin_fd,1);

    write(original_stdin_fd,"terminei",8);
    write(1,"done",4);

    return 0;
}
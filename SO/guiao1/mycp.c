#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

//int open(const char *path, int oflag [, mode]);
//ssize_t read(int fildes, void *buf, size_t nbyte);
//ssize_t write(int fildes, const void *buf, size_t nbyte);
//off_t lseek(int fd, off_t offset, int whence);
//int close(int fildes);


/*
    medir o tempo do exec time ./<nameexec>
    read le enquanto diferente de 0
*/

#define MAX_BUF 1024*1024

int main(int argc, char* argv[])
{
    printf("argv[0]: %s\n",argv[0]);
    printf("argv[1]: %s\n",argv[1]);
    printf("argv[2]: %s\n",argv[2]);

    //memoria estatica
    char buffer[MAX_BUF];

    // memoria alocada dinamicamente
    //char * buffer = malloc(MAX_BUF); 

    int fd_origem, fd_destino;

    if ((fd_origem = open(argv[1],O_RDONLY)) == -1)
    {
        printf("Msg: %s, Nr: %d\n",strerror(errno),errno);
        perror("erro no open origem");
        return -1;
    }

    if ((fd_destino = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0604)) == -1)
    {
        perror("erro no open origem");
        return -1;
    }

    int bytes_read;

    while((bytes_read = read(fd_origem, buffer, MAX_BUF))>0)
    {
        write(fd_destino, buffer, bytes_read);
    }   

    //free(buffer);

    close(fd_origem);
    close(fd_destino);
    return 0;
}

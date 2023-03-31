#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
/*int open(const char *path, int oflag [, mode]);
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
off_t lseek(int fd, off_t offset, int whence);
int close(int fildes);*/

int main(int argc, char* argv[])
{
    int f1 = open(argv[1],O_RDONLY);
    if (f1<0)
    {
        printf("o 1 nao abriu\n");
        exit(-1);
    } 
    
    int f2 = open(argv[2],O_CREAT | O_WRONLY,0604);
    if (f2<0)
    {
        printf("o 2 nao abriu\n");
        exit(-1);
    }

    char buffer[1024];

    while (read(f1,buffer,2)>0)
    {
        write(f2,buffer,2);
    }
    
    close(f1);
    close(f2);

    return 0;
}

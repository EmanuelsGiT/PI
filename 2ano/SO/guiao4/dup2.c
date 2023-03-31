#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    int fd = open ("file.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);

    write(1,"contents",8);

    getchar();

    dup2(fd,1);

    getchar();
    
    close(fd);

    getchar();

    write(1,"contents",8);


    return 0;
}
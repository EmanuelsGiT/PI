#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    int fd = open ("file.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);


    if (fd<0)
        perror("open");

    
    getchar();

    int dup_fd = dup(fd);

    printf("fd: %d; dup_fd: %d\n",fd, dup_fd);

    getchar();

    return 0;
}
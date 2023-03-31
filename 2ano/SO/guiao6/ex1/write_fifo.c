#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/*
    int mkfifo (const char* pathname, mode_t mode);

    cat > fifo cliente

    cat < fifo sv 
*/

int main(int argc, char * argv[])
{
    int fifo_fd = open("./fifo", O_WRONLY);
    

    if (fifo_fd < 0)
    {
        perror("open");

        return 1;
    }

    printf("fifo is open\n");

    printf("writing...\n");

    char buffer[1024];

    ssize_t bytes_read;

    while (bytes_read = read(0,buffer,1024))
    {
        write(fifo_fd,buffer,10);
    }

    return 0;
}
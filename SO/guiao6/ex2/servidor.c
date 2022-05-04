#include <sys/types.h>
#include <sys/stat.h>

/*
    int mkfifo (const char* pathname, mode_t mode); 
*/

int main(int argc, char * argv[])
{
    int log_fd = open("log.txt", O_Creat | oTrunc| O WRONLY, 0666);

    int fifo_fd;

    fifo_fd = open("fifo", O_RDONLY);

    // ou fifo_fd_write = open("fifo", O_WRONLY);

    while(1)
    {
        //read from pipe

        //write from pipe
    }

    close(fifo_fd);

    return 0;
}
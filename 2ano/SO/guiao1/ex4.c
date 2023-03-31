// Não está completo!!!


#include <unistd.h>
#include <stdio.h>

#define MAX_BUF 1024

//devolve o sizeline
ssize_t readln(int fd, char *line, size_t size)
{
    char buff[1];

    int bytes_read;
    int count = 0;

    while((bytes_read = read(fd,buff,1))>0 && buff[0]!='\n' && count<=size)
    {
        line[count] = *buff;
        count++;
    }

    return count;
}

int main(int argc, char* argx[])
{
    int fd_origem;

    if((fd_origem = open(argx[1],O_RDONLY))==-1)
    {
        printf("Msg : %s, Nr %d\n", strerror(errno), errno);
        perror("erro no open origem");
        return -1;
    }

    char line[MAX_BUF];
    int bytes_read = readln(fd_origem, line, MAX_BUF);
    int i = 0;
    char n[];

    while((bytes_read = read(fd_origem,buffer,MAX_BUF))>0)
    {
        n = 
        write(1, line, bytes_read);
    } 

    return 0;
}
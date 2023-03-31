#include <unistd.h>
#include <stdio.h>

#define MAX_BUF 1024



// \n incluido no buf de resposta
ssize_t readln(int fd, char *buf, size_t size)
{
    int i=0;

    while(i<size && readc(fd,&buf[i])>0)
    {
        i++;
        if(((char*)buf)[i-1]=='\n')
            return i;
    }
    return i;
}

int readc(int fd, char* c)
{
    // return read(fd,c,1);
    // tempo de resposta lento! Estamos a ir sempre diretamente ao disco

    // tem um mini mem
    if(read_buffer_pos == read_buffer_end)
    {
        read_buffer_end = read(fd,read_buffer, MAX_BUF);
        switch(read_buffer_end)
        {
            case -1:
                return -1;
                break;
            case 0:
                return 0;
                break;
            default:
                read_buffer_pos=0;
        }
    }
    *c = read_buffer[read_buffer_pos++];

    return 1;
}

int main(int argc, char* argx[])
{
    int line_counter = 0;

    char buffer[MAX_BUF];

    int bytes_read = 0;

    int newline = 0;

    while( (bytes_read = readln(0,buffer,MAX_BUF))>0)
    {
        char line_number[10];

        if(newline && buffer[0] != '\n')
        {
            sprintf(line_number,10,"%d:", line_counter);
            //write...
        }
    }
}
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_BUF 2048

char readln_buf[MAX_BUF];

int readln_buf_end;

int readln_buf_pos;

//funcao para verficar do read
//char e ver foto 

//verfica se teho mais byes para ler 

// se tiver, retorna no endereço c e atualiza estado globaç (pos atual)

//se nao tiver, vai ler o disco, e retorna 1 caracter (atualizando o estado)
int readc(int fd, char*c)
{
    return read(fd, c, 1);
}

ssize_t readln(int fd, char *line, size_t size)
{
    int i = 0;

    while(i<size && readc(fd, line+i)>0)
    {
        if (line[i] = '\n')
        {
            return i+1;
        }
        i++;
    }

    return i;
}


int main(int argc, char *argv[]){
    int f1 = open(argv[1], O_RDONLY);

    if(f1 < 0){
        perror("Open file1\n");
        return 1;
    }

    char buffer[MAX_BUF];
    char number[10];
    int n_bytes = 0;
    int line_count = 1;

    while((n_bytes = readln(f1, buffer, MAX_BUF)) > 0){
        if(n_bytes != MAX_BUF){
            sprintf(number, "%d  ", line_count);
            write(1, &number, 3);
            line_count++;
        }
        write(1, &buffer, n_bytes);
    }

    close(f1);

    return 1;
}

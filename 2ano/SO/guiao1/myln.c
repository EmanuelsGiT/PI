#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_BUF 1024

ssize_t readln(int fd, char *line, size_t size){
    int ln_size;
    char c;

    for(ln_size = 0; ln_size < size && read(fd, &c, 1) > 0; ln_size++){
        line[ln_size] = c; 
        if(c == '\n'){ ln_size++; break;}
    }

    return ln_size;
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

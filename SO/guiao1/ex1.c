#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <errno.h> // da o ultimo erro do sistema -> colocar string a dizer onde aconteceu
#include <stdio.h>
#include <string.h>
//Ex 1

#define MAX_BUF 1024
// do cpu ate disco ha uma serie de camadas
// mais longe mais espaco mais lento
// mais perto menos espaco mais rapido
// por cada char estamos a fazer duas caminhadas ate ao disco
// se levarmos mais fazemos menos percurso mas pagamos distancia
// minimizar os acessos a fonte de dados base


int main(int argc, char* argx[])
{
    
    char buffer[MAX_BUF];
    // VER vantagens e desvantagens da mem estatica e dinamica
    // char buffer = malloc(MAX_BUF);
    
    int fd_origem, fd_destino;

    if((fd_origem = open(argx[1],O_RDONLY))==-1)
    {
        printf("Msg : %s, Nr %d\n", strerror(errno), errno);
        perror("erro no open origem");
        return -1;
    }

    if((fd_destino = open(argx[2],O_WRONLY | O_CREAT | O_TRUNC),0640)==-1)
    {
        printf("Msg : %s, Nr %d\n", strerror(errno), errno);
        perror("erro no open destino");
        return -1;
    }

    int bytes_read;

    while((bytes_read = read(fd_origem,buffer,MAX_BUF))>0)
    {
        write(fd_destino, buffer, bytes_read); 
        // NUNCA COLOCAR MAX_BUFF pq se a linha lida no ficheiro inicial
        // a linha tiver menos tam que o MAX_BUFF ele vai escrever lixo
        // no outro ficheiro
    }

    close(fd_destino);
    close(fd_origem);

    return 0;
}
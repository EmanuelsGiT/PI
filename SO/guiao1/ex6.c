#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user //sizeof = 204
{
    int nome[200];
    int idade;
}Person;

#define MAX_BUF 1024
//distinguir
//abrir o ficheiro
//posicionar no fim -append

int add(char *file, char* buff, int bytes_read)
{
    int fd_origem;

    if((fd_origem = open(file,O_APPEND))==-1)
    {
        printf("Msg : %s, Nr %d\n", strerror(errno), errno);
        perror("erro no open origem");
        return -1;
    }

    char*  strsep(buff,"")
}


int main(int argc, char* argx[])
{
    int fd_origem;
    
    char buff[MAX_BUF];

    if(argx[2]=='i')
    {
        buff = 
        strcat(buff,argx[4]);
    } add(argx[1], buf, bytes_read);
    
    add(fd_origem);

    return 0;
}

//lseek(fd,-sizeof(Person), SEEK_CUR)
//O_RDWR
//if(strcmp(arg[x],"y"));


int person_change_age(long pos, int age)
{
    Person p;

    //abrir
    int fd = open(FILENAME, O_RDWR, 0600);
    //colocar no sitio certo
    int res = lseek(fd,pos*sizeof(Person),SEEK_SET);
    //ler
    int bytes_read = read(fd,&p,sizeof(Person));
    //colocar a idade certa
    p.age=age;
    //andar para trás
    int seek_res = lseek(fd,&p,-sizeof(Person),SEEK_CUR);

    int res=write(fd,&p,sizeof(Person));

    close(FILENAME);

    if(res<0)
    {
        //perror(...);
    }
}

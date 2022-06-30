#include "person.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* 
ex 7 lseek anda pra trás uma person e divido a posição pelo tamanho de uma person
Por exemplo, uma person tem tamanho de 204, se tiver na posição 408, 
408/204 estou na segunda pessoa registada
*/

int new_person(char *name, int age){

    int res;

    Person p;
    p.age = age;
    strcpy(p.name,name);

    int fd = open(FILENAME, O_CREAT | O_APPEND | O_WRONLY, 0600);

    res = write(fd, &p, sizeof(Person));
    if(res < 0){
        perror("Error creating person");
        return -1;
    }

    return res;

}

int person_change_age(char *name, int age){

    Person p;

    int bytes_read;
    int res;

    int fd = open(FILENAME, O_RDWR, 0600);

    if(fd<0){
        perror("Error open");
        return -1;
    }

    while((bytes_read = read(fd, &p, sizeof(Person))) > 0){
        //debuf

        printf("Reade person name %s age %d\n", p.name, p.age);

        if(strcmp(p.name,name) == 0){
            p.age = age;

            res = lseek(fd, -sizeof(Person), SEEK_CUR);
            if(res < 0){
                perror("Error lseek");
                return -1;
            }

            res = write(fd, &p, sizeof(Person));

            if(res < 0){
                perror("Error write");
                return -1;
            }

            //debug
            printf("Wrote person name %s age %d\n", p.name, p.age);
        }
    }
}

//ex7
int person_change_age2(long pos, int age){

    Person p;

    int fd = open(FILENAME, O_RDWR, 0600);

    int seek_res = lseek(fd, pos*sizeof(Person), SEEK_SET);
    if(seek_res < 0){
        perror("Error lseek");
        return -1;
    }

    int bytes_read = read(fd, &p, sizeof(Person));
    if(bytes_read < 0){
        perror("Error read");
        return -1;
    }

    printf("Read Person name %s age- %d\n", p.name, p.age);

    p.age = age;

    seek_res = lseek(fd, -sizeof(Person), SEEK_CUR);
    if(seek_res < 0){
        perror("Error write");
        return -1;
    }

    int res = write(fd,&p,sizeof(Person));
    if(res < 0){
        perror("Error write");
        return -1;
    }

    printf("Wrote Person name %s age-%d\n", p.name, p.age);
    close(fd);
    return 0;
}

int main(int argc, char *argv[]){

    char id[20] = "";

    if(strcmp(argv[1], "-i") == 0){
        write(1,id,sizeof(id));
    }

    if(strcmp(argv[1], "-u") == 0){
        person_change_age(argv[2], atoi(argv[3]));
    }
}
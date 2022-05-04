#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//tam = 24
typedef struct person
{
    char name[20]; //20 bytes
    int  age;    //4 bytes
} Person;



int main(int argc, char *argv[])
{
    
    
    Person p;

    
    printf("%s\n", argv[0]);
    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    printf("%s\n", argv[3]);

    strcpy(p.name,argv[2]);
    p.age = atoi(argv[3]);

    int people_fd = open("people.bin", O_CREAT | O_APPEND | O_RDWR, 0640);

    int  bytes = write(people_fd, &p, sizeof(Person));


    printf("%d\n", bytes);

    lseek(people_fd, 0, SEEK_SET);
    //lseek(people_fd, -sizeof(Person), SEEK_END); //inicio
    //lseek(people_fd, -sizeof(Person), SEEK_CUR); //anterior

    Person p1_read;

    bytes = read(people_fd, &p1_read, sizeof(Person));

    if (bytes < 0)
        perror("erro\n");

    printf("read %d bytes\n", bytes);

    printf("p1_readname %s\n", p1_read.name);
    printf("p1_readage %d\n", p1_read.age);

    return 0;
}
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    int fildes[2];

    pipe(fildes);
    char buffer[20];

    int resf = fork();

    switch (resf)
    {
    case -1:
        perror("fork");
        return -1;
        break;
    
    case 0:
        close(fildes[0]);
    
        //[Filho]
        dup2(fildes[1],1);
        close(fildes[1]);

        execlp("ls","ls","/etc/",NULL);

        close(fildes[0]);
        _exit(0);

        break;
    default:
        //[PAI]
        close(fildes[1]);
        
        dup2(fildes[0],0);
        close(fildes[0]);

        
        execlp("wc","wc","-l",NULL); 
    }
    return 0;
}
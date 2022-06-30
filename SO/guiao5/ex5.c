#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <fcntl.h>
#include <sys/wait.h>

int exec_comand(char* arg)
{
    // estamos a assumir numero maximo de argumentos teria de ser menor que 18
    char* exec_args[18];

    char *string;
    int exec_ret = 0;
    int i = 0;

    char* command = strdup(arg);

    //char strtok(char *str, const char *delim)
    string = strtok(command," ");

    while(string)
    {
        exec_args[i]=string;
        string = strtok(command," ");
        i++;
    }

    exec_args[i]=NULL;
    exec_ret = execvp(exec_args[0],exec_args);

    return exec_ret;
    
}



int main(int argc, char* argv[])
{
    // para simular a bash faziamos while(readln()>0)

    char* commands[] = {
        "grep -v ^# /etc/passwd",
        "cut -f7 -d:",
        "uniq",
        "wc -l"
    };

    int number_of_commands = 4;

    int pipes[number_of_commands-1][2];
    int status[number_of_commands];

    for(int c = 0; c < number_of_commands; c++)
    {
        if(c==0)
        {
            //primeiro comando
            if(pipe(pipes[c]) != 0)
            {
                perror("pipe");
                return -1;
            }

            switch (fork())
            {
                case -1:
                    perror("fork");
                    return -1;
            
                case 0:
                    close(pipes[c][0]); //fechar o de leitura

                    //ligar stdout do primeiro ao estremo de escrita
                    dup2(pipes[c][1],1);
                    close(pipes[c][1]); //fechar o de escrita

                    exec_comand(commands[c]);

                    _exit(0);
            
                default:
                    close(pipes[c][1]); // fecha o de escrita
                    break;
            }
        }
        else if(c==number_of_commands-1)
        {
            //ultimo comando
            switch (fork())
            {
                case -1:
                    perror("fork");
                    return -1;

                case 0:
                    //ligar do primeiro comando ao extremo de escrita
                    dup2(pipes[c-1][0],0);
                    close(pipes[c-1][0]);

                    exec_comand(commands[c]);
                    _exit(0);
            
                default:
                    close(pipes[c-1][0]);
            }
        }
        else
        {
            //comandos do meio
            if(pipe(pipes[c]) != 0)
            {
                perror("pipe");
                return -1;
            }

            switch (fork())
            {
                case -1:
                    perror("fork");
                    return -1;
                
                case 0:
                    close(pipes[c][0]);
                    //escreve para o pipe c
                    dup2(pipes[c][1],1);
                    close(pipes[c][1]);

                    //lê do pipe c-1
                    dup2(pipes[c-1][0],0);
                    close(pipes[c-1][0]);

                    exec_comand(commands[c]);
                    _exit(0);

                default:
                    close(pipes[c][1]);
                    close(pipes[c-1][0]);
            }
        }
    }
    write(1,"acabou\n",7);
    return 0;
}
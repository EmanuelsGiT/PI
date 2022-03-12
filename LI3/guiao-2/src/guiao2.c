#include <stdio.h>
#include "../libs/User.h"
#include "../libs/Commits.h"
#include "../libs/Repos.h"
#include "../libs/catUser.h"
#include "../libs/catCommits.h"
#include "../libs/catRepos.h"
#include "../libs/queries_estatistic.h"
#include "../libs/queries_parameterizable.h"


void execute(char* line, CATUSER catuser, CATREPOS catrepos, CATCOMMITS catcommits, FILE *output)
{
    char* buff = line;
    char* linguagem = NULL; 
    char* data_inicio = NULL;
    char* data_fim = NULL;
    int query_id, n_users;
    query_id = atoi(strdup(strsep(&buff, " \r\n")));

    switch (query_id)
    {
    case 1:
        query1(catuser,output);
        break;
    case 2:
        query2(catuser, catcommits, catrepos, output);
        break;
    case 3:
        query3(catuser, catcommits, output);
        break;
    case 4:
        query4(catuser, catcommits, output);
        break;
    case 5:
        n_users = atoi(strdup(strsep(&buff, " \r\n")));
        data_inicio = strdup(strsep(&buff, " \r\n"));
        data_fim = strdup(strsep(&buff, "\r\n"));
        query5(n_users, data_inicio, data_fim, catuser, catcommits, catrepos, output);
        break;
    case 6:
        n_users = atoi(strdup(strsep(&buff, " \r\n")));
        linguagem = strdup(strsep(&buff, " \r\n"));
        query6(n_users, linguagem, catuser, catcommits, catrepos, output);
        break;
    case 7:
        data_inicio = strdup(strsep(&buff, " \r\n"));
        query7(data_inicio, catuser, catcommits, catrepos, output);
        break;
    case 8: 
        n_users = atoi(strdup(strsep(&buff, " \r\n")));
        data_inicio = strdup(strsep(&buff, " \r\n"));
        query8(n_users, data_inicio, catuser, catcommits, catrepos, output);
        break;
    case 9:
        n_users = atoi(strdup(strsep(&buff, " \r\n")));
        query9(n_users, catuser, catcommits, catrepos, output);
        break;
    case 10:
        n_users = atoi(strdup(strsep(&buff, " \r\n")));
        query10(n_users, catuser, catcommits, catrepos, output);
        break;
    
    default:
        break;
    }
}


int guiao2(char const *x)
{
    char commandfile[40];
    sprintf(commandfile,"entrada/%s",x);
    FILE *fcommands = fopen(commandfile, "r");
    if (fcommands == NULL) 
    {
        printf("Ficheiro com commands não encontrado!\nVerfique se introduziu o nome do ficheiro correto e se este se encontra na pasta entrada.\n");
        return -1;
    }
    
    FILE *fusers = fopen("entrada/users-g2.csv", "r");
    FILE *fcommits = fopen("entrada/commits-g2.csv", "r");
    FILE *frepos = fopen("entrada/repos-g2.csv", "r");

    if (fusers == NULL ||  fcommits == NULL || frepos == NULL)
        return -1;
    else printf("All file opened successfully\n");
    
    int max_len = 500000, i;
    char buff[max_len];
    
    CATUSER catuser = createCatUser(fusers,buff,max_len);
    CATREPOS catrepos = createCatRepos(frepos,buff,max_len);
    CATCOMMITS catcommits = createCatCommits(fcommits,buff,max_len);

    char line[100];
    char filename[40];
    
    for (i=0; fgets(line,100,fcommands); i++)
    {   
        sprintf(filename,"saida/command%d_output.txt",i+1);
        FILE *file = fopen(filename, "w");
        if (filename == NULL) return -1;
        execute(line,catuser,catrepos,catcommits,file);
        printf("Command %d Done!\n",i+1);
        fclose(file);
    }
    

    fclose(fusers);
    fclose(fcommits);
    fclose(frepos);
    fclose(fcommands);
    
    return 0;
}

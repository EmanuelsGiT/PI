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
    char* n = NULL;
    int query_id, n_users;
    char* query = strdup(strsep(&buff, " \r\n"));
    query_id = atoi(query);

    switch (query_id)
    {
    case 1:
        query1(catuser,output);
        break;
    case 2:
        query2(catcommits, catrepos, output);
        break;
    case 3:
        query3(catuser, catcommits, output);
        break;
    case 4:
        query4(output);
        break;
    case 5:
        n = strdup(strsep(&buff, " \r\n"));
        n_users = atoi(n);
        data_inicio = strdup(strsep(&buff, " \r\n"));
        data_fim = strdup(strsep(&buff, "\r\n"));
        query5(n_users, data_inicio, data_fim, catuser, catcommits, output, NULL);
        free(n);
        free(data_inicio);
        free(data_fim);
        break;
    case 6:
        n = strdup(strsep(&buff, " \r\n"));
        n_users = atoi(n);
        linguagem = strdup(strsep(&buff, " \r\n"));
        query6(n_users, linguagem, catuser, catcommits, catrepos, output, NULL);
        free(n);
        free(linguagem);
        break;
    case 7:
        data_inicio = strdup(strsep(&buff, " \r\n"));
        query7(data_inicio, catcommits, catrepos, output);
        free(data_inicio);
        break;
    case 8: 
        n = strdup(strsep(&buff, " \r\n"));
        n_users = atoi(n);
        data_inicio = strdup(strsep(&buff, " \r\n"));
        query8(n_users, data_inicio, catrepos, output, NULL);
        free(n);
        free(data_inicio);
        break;
    case 9:
        n = strdup(strsep(&buff, " \r\n"));
        n_users = atoi(n);
        query9(n_users, catuser, catcommits, catrepos, output);
        free(n);
        break;
    case 10:
        n = strdup(strsep(&buff, " \r\n"));
        n_users = atoi(n);
        query10(n_users, catuser, catcommits, catrepos, output);
        free(n);
        break;
    default:
        break;
    }
    free(query);
}


int createCats(CATUSER *catuser, CATREPOS *catrepos, CATCOMMITS *catcommits)
{
    printf("Starting to Process Queries\n");

    FILE *fusers = fopen("saida/users-ok.csv", "r");
    FILE *fcommits = fopen("saida/commits-final.csv", "r");
    FILE *frepos = fopen("saida/repos-final.csv", "r");

    if (fusers == NULL ||  fcommits == NULL || frepos == NULL)
        return -1;
    else printf("All file opened successfully\n");

    int max_len = 550000, i;
    char buff[max_len];

    *catuser = createCatUser(fusers,buff,max_len);
    *catrepos = createCatRepos(frepos,buff,max_len);
    *catcommits = createCatCommits(fcommits,buff,max_len);

    int catUsersLen = getCatUserLength(*catuser);
    int catCommitsLen = getCatCommitsLength(*catcommits);

    
    char line[100];
    char filename[40];
    FILE *file = NULL;
    char line2[10];
    float r;

    for (i=1; i<4; i++)
    {  
        sprintf(filename,"saida/fquery%d.txt",i);
        file = fopen(filename, "w");
        if (file == NULL) 
        {
            fclose(fusers);
            fclose(fcommits);
            fclose(frepos);
            return -1;
        }
        sprintf(line, "%d", i);
        execute(line,*catuser,*catrepos,*catcommits,file);
        fclose(file);
    }
   
    file = fopen("saida/fquery4.txt", "w");
    if (file == NULL) 
    {
        fclose(fusers);
        fclose(fcommits);
        fclose(frepos);
        return -1;
    }
    r = (float)catCommitsLen / catUsersLen;
    fprintf(file, "%.2f", r);
    fclose(file);

    for (i=9; i<=10; i++)
    {
        sprintf(filename,"saida/fquery%d.txt",i);
        file = fopen(filename, "w");
        if (file == NULL)
        {
            fclose(fusers);
            fclose(fcommits);
            fclose(frepos);
            return -1;
        }
        sprintf(line, "%d ", i);
        sprintf(line2, "%d", catUsersLen);
        strcat(line,line2);
        execute(line,*catuser,*catrepos,*catcommits,file);
        fclose(file);
    }

    fclose(fusers);
    fclose(fcommits);
    fclose(frepos);

    return 0;
}


int q1To4Plus9And10(int *query_id, char *buff, char *buff2, FILE *file)
{
    char filename[40];
    sprintf(filename,"saida/fquery%d.txt",*query_id);
    FILE *fquery = fopen(filename, "r");
    if (fquery == NULL) return -1;
    
    int topN, j;
    char* top;

    if(*query_id==9)
    {
        top = strdup(strsep(&buff2, " \r\n"));
        topN = atoi(top);
        for(j=0; j<topN && fgets(buff,100,fquery); j++)
            fprintf(file,"%s",buff);
        free(top);
    }
    else if(*query_id==10)
    {
        top = strdup(strsep(&buff2, " \r\n"));
        topN = atoi(top);
        while(fgets(buff,100,fquery))
        {
            for(j=0;j<topN && strcmp(buff,"\n")!=0;j++)
            {
                fprintf(file,"%s",buff);
                fgets(buff,100,fquery);
            }                        
        }
        free(top);
    }
    else
    {
        for(j=0; fgets(buff,100,fquery); j++)
            fprintf(file,"%s",buff);
    }

    fclose(fquery);
    return 0;
}



int createOut(CATUSER catuser, CATREPOS catrepos, CATCOMMITS catcommits, FILE *fcommands)
{
    char line[100];
    char filename[40];
    char buff[100];
    int query_id, i, j;
    char *buff2 = NULL;
    char *id = NULL;
    FILE* file = NULL;

    for (i=1;fgets(line,100,fcommands); i++)
    {   
        sprintf(filename,"saida/command%d_output.txt",i);
        file = fopen(filename, "w");
        if (file == NULL) {fclose(file); return -1;}
        strcpy(buff,line);
        buff2=buff;
        id = strdup(strsep(&buff2, " \r\n"));
        query_id = atoi(id);

        if (query_id==1 || query_id==2 || query_id==3 || query_id==9 || query_id==10)
        {
            j = q1To4Plus9And10(&query_id, buff, buff2, file);
            if(j==-1) {free(id);fclose(file);return -1;}
        }
        else if (query_id==4) query4(file);
        else execute(line,catuser,catrepos,catcommits,file);

        free(id);
        fclose(file);
    }
    return 0;
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
    
    CATUSER catuser = NULL;
    CATREPOS catrepos = NULL;
    CATCOMMITS catcommits = NULL;
    int r;
    
    r = createCats(&catuser,&catrepos,&catcommits);
    if(r == -1) 
    {
        free(catuser);
        free(catrepos);
        free(catcommits); 
        return -1;
    }
    
    r = createOut(catuser,catrepos,catcommits,fcommands);
    if(r == -1) 
    {
        free(catuser);
        free(catrepos);
        free(catcommits); 
        return -1;
    }
    
    printf("End of Process.\n");
    
    freeCatUser(catuser);
    freeCatRepos(catrepos);
    freeCatCommits(catcommits);

    fclose(fcommands);

    return 0;
}

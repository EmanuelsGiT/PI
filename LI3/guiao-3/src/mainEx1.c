#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int getIntLen (int x)
{
    int r = 1;
    while (x>=10)
    {
      r++;
      x=x/10;
    }

    return r;
}

int check(char *validated)
{
    int valint = atoi(validated);

    if (strcmp(validated,"0")==0 || (valint>0 && getIntLen(valint)==strlen(validated))) return 1;

    return 0;
}

int find_errors(char *buff, int n)
{
    int error=0, len=strlen(buff)-2;
    if(strstr(buff,";;")!=NULL) error++;         //verifies if there is any space in the middle of the string
    else if(buff[len]==';' && n!=1) error++;     //verifies if there is any space in the end of the string
    else if(buff[0]==';') error++;               //verifies if there is any space in the begining of the string
    return error;
}

int inArray(int elem, int array[], int tam)
{
    int i=0;
    while(i<tam && array[i]!=elem) i++;
    if(i==tam) return 0;
    return 1;
}

int check_Time(char* time)
{
    int month_31[]={1,3,5,7,8,10,12};
    int month_30[]={4,6,9,11};
    int r=1, year=0, month=0, day=0, hour=0, minute=0, second=0;

    char line[strlen(time)+1];
    strcpy(line,time);

    if(line[19]!='\0' || line[4]!='-' || line[7]!='-' || sscanf(time,"%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second)!=6) r=0;
    else if(year<2005 || year>2022) r=0;
    else if(year==2005 && month<4) r=0;
    else if(year==2005 && month==4 && day<7) r=0;
    else if(month>12 || hour>24 || minute>60 || second>60) r=0;
    else if(year % 4 == 0 && month == 2 && day>29) r=0; // leap year
    else if(year % 4 !=0 && month == 2 && day>28) r=0;
    else if(inArray(month,month_31,7) && day>31) r=0;
    else if(inArray(month,month_30,4) && day>30) r=0;
    else r=1;

    return r;
}

int check_list(int follow, char *validated)
{
    int i, count=0;
    char aux;

    if(follow==0 && (strcmp(validated,"[]"))!=0) return 0;
    if((strcmp(validated,"[]"))==0 && follow!=0) return 0;

    for (i=1; *(validated+i)!=']'; i++)
    {
        aux = *(validated+i);
        if(aux==',') count++;
        else if ((aux<'0' || aux>'9') && aux!=' ') return 0;
    }

    if(i!=1 && count+1!=follow) return 0;

    return 1;
}

int build_user(char* line,FILE* out)
{
    if(find_errors(line,0) != 0)
    return 0;

    char lineok[strlen(line)+1];
    strcpy(lineok,line);
    char* validated = NULL;
    char* buff2 = line;
    int followers=0, following=0, n, r = 1;

    for (n=1;n<=10 && r!=0;n++)
    {
        validated = strdup(strsep(&buff2, ";\r\n"));
        // verfication of id, pub_gits and pub_repos
        if ((n==1 || n==9 || n==10)&&check(validated)==0)
            r = 0;

        // verification of type
        else if (n==3 && strcmp(validated, "Bot") && strcmp(validated, "User") && strcmp(validated, "Organization"))
            r = 0;

        // verification of created_at
        else if (n==4 && check_Time(validated)==0)
            r = 0;

        //verification of followers
        else if (n==5)
        {
            if(check(validated)==0) r = 0;
            else followers = atoi(validated);
        }

        // verification of followers_list
        else if (n==6 && check_list(followers,validated)==0)
            r = 0;

        // verification of following
        else if (n==7)
        {
            if(check(validated)==0) r = 0;
            else following = atoi(validated);
        }

        // verification of following_list
        else if (n==8 && check_list(following,validated)==0)
            r = 0;

        free(validated);
        
    }
    fprintf(out,"%s",lineok);

    return r;
}

int build_commits(char* line,FILE* out)
{
    if(find_errors(line,1) != 0)
    return 0;

    char lineok[strlen(line)+1];
    strcpy(lineok,line);

    char* validated=NULL;
    char* buff2 = line;
    
    int n, r = 1;

    for(n=1;n<=5 && r!=0;n++)
    {
        // message
        validated = strdup(strsep(&buff2, ";\r\n"));

        // verfication of repo_id, author_id and committer_id
        if((n==1 || n==2 || n==3)&&check(validated)==0)
            r = 0;

        // verfication of commited_at
        else if (n==4 && check_Time(validated)==0) 
            r = 0;

        free(validated);

    }

    fprintf(out,"%s",lineok);
    return r;
}

int build_repos(char* line,FILE* out)
{
    char lineok[strlen(line)+1];
    strcpy(lineok,line);
    char* validated = NULL;
    char* buff2 = line;
    int n, r = 1;

    for(n=1;n<=14 && r!=0;n++)
    {
        // full_name, license, description, language, default_branch
        validated = strdup(strsep(&buff2, ";\r\n"));

        if(n != 6 && strcmp(validated, "") == 0)
            r = 0;

        // verfication of id, owner_id, forks_count, open_issues, stargazer_count, size
        else if((n==1 || n==2 || n>=11) && check(validated)==0) r = 0;

        // verfication of has_wiki
        else if(n==5 && strcmp(validated,"True")!=0 && strcmp(validated,"False")!=0)
            r = 0;

        // verfication of created_at and updated_at
        else if ((n==9 || n==10) && check_Time(validated)==0)
            r = 0;

        free(validated);
    }

    fprintf(out,"%s",lineok);

    return r;
}

int build_main(FILE* toread, FILE* towrite, int n)
{
    int max_len = 500000, faulty = 0;
    char buff[max_len];

    fgets(buff, max_len, toread);
    fprintf(towrite,"%s",buff);

    while(fgets(buff, max_len, toread))
    {
        if(n==1 && build_user(buff, towrite)==0) faulty++;        
        else if(n==2 && build_commits(buff, towrite)==0) faulty++;
        else if(n==3 && build_repos(buff, towrite)==0) faulty++;
    }

    return faulty;
}


int exercicio1()
{
    printf("Starting 1st Verification\n");

    int faulty = 0;

    FILE *fusers = fopen("entrada/users-g3.csv", "r");
    FILE *fusersok = fopen("saida/users-ok.csv","w");
    
    FILE *fcommits = fopen("entrada/commits-g3.csv", "r");
    FILE *fcommitsok = fopen("saida/commits-ok.csv","w");

    FILE *frepos = fopen("entrada/repos-g3.csv", "r");
    FILE *freposok = fopen("saida/repos-ok.csv","w");

    if (fusers == NULL || fusersok == NULL ||  fcommits == NULL || fcommitsok == NULL || frepos == NULL || freposok == NULL)
        return -1;
    else printf("All file opened successfully\n");

    faulty = build_main(fusers,fusersok,1);
    printf("Faulty Users = %d\n",faulty);

    faulty = build_main(fcommits,fcommitsok,2);
    printf("Faulty Commits = %d\n",faulty);

    faulty = build_main(frepos,freposok,3);
    printf("Faulty Repos = %d\n",faulty);


    fclose(fusers);
    fclose(fusersok);
    fclose(frepos);
    fclose(fcommits);
    fclose(freposok);
    fclose(fcommitsok);
    
    printf("1st Verification completed.\n\n");

    return 0;
}

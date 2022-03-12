#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/query.h"

struct query
{
    int id;
    char* login;
    int commit_msg_size;
    int repo_id;
    struct query* next;
};

QUERY build_query(char** line, int n, QUERY head)
{
    QUERY q = malloc(sizeof(struct query));
    char* buff2 = *line;
    if (n!=8) q->id = atoi(strsep(&buff2, ";\n"));
    q->login = strdup (strsep(&buff2, ";\n"));
    if (n==5 || n==6 || n==10) q->commit_msg_size = atoi(strsep(&buff2, ";\n"));
    if (n==10) q->repo_id = atoi(strsep(&buff2, ";\n"));
    if (n==9 || n ==10) 
    {
        q->next = NULL;
        if(head) head->next = q;
    }
    return q;
}

int getQueryId(QUERY q) {return q->id;}
char* getQueryLogin(QUERY q) {return strdup(q->login);}
int getQueryComSize(QUERY q) {return q->commit_msg_size;}
int getQueryRepoId(QUERY q) {return q->repo_id;}
QUERY getQueryNext(QUERY q) {return q->next;}

void freeQuery (QUERY q)
{
    struct query* aux;

    while(q!=NULL)
    {
        aux = q->next;
        free(q->login);
        free(q);
        q = aux;
    }
    free(aux);
}

void freeQueries (QUERY* q, int n)
{
    n--;
    while (n>=0)
    {
        free(q[n]->login);
        free(q[n]);
        n--;
    }
}
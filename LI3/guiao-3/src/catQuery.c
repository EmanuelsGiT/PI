#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/query.h"
#include "../libs/catQuery.h"

struct catquery
{
    QUERY* query;
    int length;
};

CATQUERY createCatQuery(FILE* toread,char* buff,int max_len,int n)
{
    CATQUERY result = malloc(sizeof(struct catquery));
    int length=100, i=0;
    result->query=malloc(sizeof(QUERY)*length);
    QUERY new = NULL;
    QUERY aux = NULL;

    while(fgets(buff, max_len, toread))
    {
        if(i>=length)
        {
            length*=2;
            result->query = realloc(result->query,sizeof(QUERY)*length);
        }

        new = build_query(&buff,n,NULL);
        result->query[i] = new;
        fgets(buff,max_len,toread);
        while(strcmp(buff,"\n")!=0)
        {
            aux = build_query(&buff, n, new);
            new = aux;
            fgets(buff,max_len,toread);
        }
        i++;
    }

    result->length=i;

    return result;
}

int getCatQueryLength(CATQUERY cat){return cat->length;}
QUERY getQueryPointer(CATQUERY cat, int i){return cat->query[i];}


void freeCatQuery(CATQUERY catquery)
{
    int i;

    for(i=catquery->length-1;i>=0;i--)
        freeQuery(catquery->query[i]);
    free(catquery);
}
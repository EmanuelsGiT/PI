#include <stdio.h>

typedef struct query* QUERY;

QUERY build_query(char** line, int n, QUERY head);

int getQueryId(QUERY q);
char* getQueryLogin(QUERY q);
int getQueryComSize(QUERY q);
int getQueryRepoId(QUERY q);
QUERY getQueryNext(QUERY q);

void freeQuery (QUERY q);
void freeQueries (QUERY* q, int n);
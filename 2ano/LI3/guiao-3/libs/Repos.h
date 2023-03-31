#include <stdio.h>

typedef struct repos *REPOS;

REPOS build_repos2(char* line);
REPOS build_repos3(char* line);
int getReposId(REPOS r);
int getReposOwnerId(REPOS r);
char* getReposDescription(REPOS r);
char* getReposLang(REPOS r);
char* getReposCreatedAt(REPOS r);

void freeRepos (REPOS u);
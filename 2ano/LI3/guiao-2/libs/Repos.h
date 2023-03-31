#include <stdio.h>

typedef struct repos *REPOS;

REPOS build_repos2(char* line);
int getReposId(REPOS r);
int getReposOwnerId(REPOS r);
char* getReposDescription(REPOS r);
char* getReposLang(REPOS r);
char* getReposCreatedAt(REPOS r);

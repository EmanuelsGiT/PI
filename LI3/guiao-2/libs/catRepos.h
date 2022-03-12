#include <stdio.h>
#include <glib.h>

typedef struct catRepos *CATREPOS;

CATREPOS createCatRepos(FILE* toread,char* buff,int max_len);
int getCatReposLength(CATREPOS cat);
GHashTable* getCatReposHash(CATREPOS cat);
REPOS getReposPointer(CATREPOS cat, int i);
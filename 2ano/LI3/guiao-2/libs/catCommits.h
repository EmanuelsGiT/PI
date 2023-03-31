#include <stdio.h>

typedef struct catCommits *CATCOMMITS;

CATCOMMITS createCatCommits(FILE* toread,char* buff,int max_len);
int getCatCommitsLength(CATCOMMITS cat);
COMMITS getCommitsPointer(CATCOMMITS cat, int i);